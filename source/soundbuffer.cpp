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
#include <soundbuffer.hpp>
#include <sfmlphysfs.hpp>

void bange::soundbuffer::RegisterVM(lua_State *vm){
    luaL_reg functions[] = {
    {"LoadSoundBuffer", bange::soundbuffer_LoadSoundBuffer},
    {"LoadSoundBufferFromPackage", bange::soundbuffer_LoadSoundBufferFromPackage},
    {NULL, NULL}};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
}

int bange::soundbuffer_LoadSoundBuffer(lua_State *vm){
    //string -> soundbuffer
    if (!lua_isstring(vm, 1) || (lua_isstring(vm, 1) && lua_isnumber(vm, 1)) ){
        std::cout << "bange.LoadSoundBuffer(): First argument must be a string." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if(lua_objlen(vm, 1) == 0){
        std::cout << "bange.LoadSoundBuffer(): The string is void." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    const char *filename = lua_tostring(vm, 1);
    bange::soundbuffer *soundbuffer = new bange::soundbuffer;
    soundbuffer->LoadFromFile(std::string(filename));
	bange::BuildProxy(vm, soundbuffer, false);
    return 1;
}

int bange::soundbuffer_LoadSoundBufferFromPackage(lua_State *vm){
    //string -> soundbuffer
    if (!lua_isstring(vm, 1) || (lua_isstring(vm, 1) && lua_isnumber(vm, 1)) ){
        std::cout << "bange.LoadSoundBufferFromPackage() -> First argument must be a string." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if(lua_objlen(vm, 1) == 0){
        std::cout << "bange.LoadSoundBufferFromPackage() -> The string is void." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    const char *filename = lua_tostring(vm, 1);
    sf::physfs streamsoundbuffer(filename);
	bange::soundbuffer *soundbuffer = new bange::soundbuffer;
	soundbuffer->LoadFromStream(streamsoundbuffer);
	bange::BuildProxy(vm, soundbuffer);
    return 1;
}
