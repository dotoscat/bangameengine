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
#include <music.hpp>

bange::music::music(){
    soundsource.SetSoundSource(this);
}

bool bange::music::NewIndex(lua_State *vm, const char *key){
    
    if (soundsource.NewIndex(vm, key)){
        return true;}
    
    if ( strcmp("loop", key) == 0){
        this->SetLoop( (bool)lua_toboolean(vm, 3) );
        return true;
    }
    else if( strcmp("playingoffset", key) == 0 ){
        this->SetPlayingOffset( lua_tonumber(vm, 3) );
        return true;
    }
    
    return false;
    
}

bool bange::music::Index(lua_State *vm, const char *key){
    
    if (soundsource.Index(vm, key)){
        return true;}
    
    if ( strcmp("channelscount", key) == 0){
        lua_pushnumber(vm, this->GetChannelsCount() );
        return true;
    }
    else if (  strcmp("duration", key) == 0){
        lua_pushnumber(vm, this->GetDuration());
        return true;
    }
    else if( strcmp("loop", key) == 0){
        lua_pushboolean(vm, (int)this->GetLoop());
        return true;
    }
    else if( strcmp("playingoffset", key) == 0){
        lua_pushnumber(vm, this->GetPlayingOffset() );
        return true;
    }
    else if( strcmp("samplerate", key) == 0){
        lua_pushnumber(vm, this->GetSampleRate() );
        return true;
    }
    else if( strcmp("status", key) == 0){
        lua_pushnumber(vm, this->GetStatus() );
        return true;
    }
    
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::music::");
    lua_getfield(vm, -1, key);
    
    return true;
}

void bange::music::RegisterVM(lua_State *vm){
    
    luaL_Reg functions[] = {
    {"OpenMusic", bange::music_OpenMusic},
    {NULL, NULL}};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
    
    luaL_Reg methods[] = {
    {"Play", bange::music_Play},
    {"Pause", bange::music_Pause},
    {"Stop", bange::music_Stop},
    {NULL, NULL}};
    lua_createtable(vm, 0, 3);
    luaL_register(vm, NULL, methods);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::music::");
    
}

int bange::music_OpenMusic(lua_State *vm){
    //string -> music
    if (!lua_isstring(vm, 1)){
        std::cout << "bange.LoadMusic() -> First argument isn't a valid string." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    bange::music *music = new bange::music();
    if ( !music->OpenFromFile( std::string( lua_tostring(vm, 1) ) ) ){
        delete music;
        lua_pushnil(vm);
        return 1;
    }
    bange::BuildProxy(vm, music, false);
    return 1;
}

int bange::music_Play(lua_State *vm){
    //music
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    if (proxy == NULL){
        std::cout << "music::Play() -> object isn't a userdata" << std::endl;
    }
    bange::music *music = static_cast<bange::music *>(proxy->object);
    music->Play();
    return 0;
}

int bange::music_Pause(lua_State *vm){
    //music
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    if (proxy == NULL){
        std::cout << "music::Pause() -> object isn't a userdata" << std::endl;
    }
    bange::music *music = static_cast<bange::music *>(proxy->object);
    music->Pause();
    return 0;
}

int bange::music_Stop(lua_State *vm){
    //music
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    if (proxy == NULL){
        std::cout << "music::Stop() -> object isn't a userdata" << std::endl;
    }
    bange::music *music = static_cast<bange::music *>(proxy->object);
    music->Stop();
    return 0;
}