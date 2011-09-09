//Copyright (c) 2011 Oscar (.teri) Triano <teritriano@gmail.com>

//This software is provided 'as-is', without any express or implied
//warranty. In no event will the authors be held liable for any damages
//arising from the use of this software.

//Permission is granted to anyone to use this software for any purpose,
//including commercial applications, and to alter it and redistribute it
//freely, subject to the following restrictions:

   //1. The origin of this software must not be misrepresented; you must not
   //claim that you wrote the original software. If you use this software
   //in a product, an acknowledgment in the product documentation would be
   //appreciated but is not required.

   //2. Altered source versions must be plainly marked as such, and must not be
   //misrepresented as being the original software.

   //3. This notice may not be removed or altered from any source
   //distribution.

#include <iostream>
#include <cstring>
#include <sound.hpp>   
#include <soundbuffer.hpp>

void bange::sound::RegisterVM(lua_State *vm){
    luaL_Reg functions[] = {
    {"NewSound", bange::sound_NewSound},
    {NULL, NULL}};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
    
    luaL_Reg methods[] = {
    {"Play", bange::sound_Play},
    {"Pause", bange::sound_Pause},
    {"Stop", bange::sound_Stop},
    {NULL, NULL}};
    lua_createtable(vm, 0, 3);
    luaL_register(vm, NULL, methods);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::sound::");
    
}

bange::sound::sound(){
    soundbuffer = LUA_REFNIL;
    soundsource.SetSoundSource(this);
}

bool bange::sound::NewIndex(lua_State *vm, const char *key){
    
    if (soundsource.NewIndex(vm, key)){
        return true;}
    
    if ( strcmp("soundbuffer", key) == 0){
        bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 3));
        if (proxy == NULL){
            std::cout << this << ".soundbuffer -> value isn't a valid userdata." << std::endl;
            return true;
        }
        bange::soundbuffer *soundbuffer = dynamic_cast<bange::soundbuffer *>(proxy->object);
        if (soundbuffer == NULL){
            std::cout << this << ".soundbuffer -> userdata isn't a valid sound." << std::endl;
            return true;
        }
        luaL_unref(vm, LUA_REGISTRYINDEX, this->soundbuffer);
        this->soundbuffer = luaL_ref(vm, LUA_REGISTRYINDEX);
        this->SetBuffer(*soundbuffer);
        return true;
    }
    else if (strcmp("loop", key) == 0){
        this->SetLoop((bool)lua_toboolean(vm, 3));
        return true;
    }
    else if (strcmp("playingoffset", key) == 0){
        this->SetPlayingOffset(lua_tonumber(vm, 3));
        return true;
    }
    return false;
}

bool bange::sound::Index(lua_State *vm, const char *key){
    
    if (soundsource.Index(vm, key)){
        return true;}
    
    if (strcmp("soundbuffer", key) == 0){
        lua_rawgeti(vm, LUA_REGISTRYINDEX, soundbuffer);
        return true;
    }
    else if (strcmp("status", key) == 0){
        lua_pushnumber(vm, (lua_Number)this->GetStatus());
        return true;
    }
    else if (strcmp("loop", key) == 0){
        lua_pushboolean(vm, (int)this->GetLoop());
        return true;
    }
    else if (strcmp("playingoffset", key) == 0){
        lua_pushnumber(vm, (lua_Number)this->GetPlayingOffset() );
        return true;
    }
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::sound::");
    lua_getfield(vm, -1, key);
    return true;
}

void bange::sound::Clean(lua_State *vm){
    luaL_unref(vm, LUA_REGISTRYINDEX, soundbuffer);
}

int bange::sound_NewSound(lua_State *vm){
    //-> sound
    bange::sound *sound = new bange::sound();
    bange::BuildProxy(vm, sound, false);
    return 1;
}

int bange::sound_Play(lua_State *vm){
    //sound
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    if (proxy == NULL){
        std::cout << "sound::Play() -> object isn't a userdata" << std::endl;
    }
    bange::sound *sound = static_cast<bange::sound *>(proxy->object);
    sound->Play();
    return 0;
}

int bange::sound_Pause(lua_State *vm){
    //sound
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    if (proxy == NULL){
        std::cout << "sound::Pause() -> object isn't a userdata" << std::endl;
    }
    bange::sound *sound = static_cast<bange::sound *>(proxy->object);
    sound->Pause();
    return 0;
}

int bange::sound_Stop(lua_State *vm){
    //sound
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    if (proxy == NULL){
        std::cout << "sound::Stop() -> object isn't a userdata" << std::endl;
    }
    bange::sound *sound = static_cast<bange::sound *>(proxy->object);
    sound->Stop();
    return 0;
}
