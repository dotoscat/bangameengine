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
#include <sfmlphysfs.hpp>
#include <texture.hpp>

void bange::texture::RegisterVM(lua_State *vm){
    luaL_Reg functions[] = {
    {"LoadTexture", bange::LoadTexture},
    {"LoadTextureFromPackage", bange::LoadTextureFromPackage},
    {NULL, NULL}};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
}

int bange::LoadTexture(lua_State *vm){
    //string -> bange::image
    if (!lua_isstring(vm, 1) || (lua_isstring(vm, 1) && lua_isnumber(vm, 1)) ){
        std::cout << "bange.LoadTexture(): First argument must be a string." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if(lua_objlen(vm, 1) == 0){
        std::cout << "bange.LoadTexture(): The string is void." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    const char *filename = lua_tostring(vm, 1);
    bange::texture *texture = new bange::texture;
    texture->LoadFromFile(std::string(filename));
	bange::BuildProxy(vm, texture);
    return 1;
}

int bange::LoadTextureFromPackage(lua_State *vm){
    //string -> bange::image
    if (!lua_isstring(vm, 1) || (lua_isstring(vm, 1) && lua_isnumber(vm, 1)) ){
        std::cout << "bange.LoadImageFromPackage() -> First argument must be a string." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if(lua_objlen(vm, 1) == 0){
        std::cout << "bange.LoadImageFromPackage() -> The string is void." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    const char *filename = lua_tostring(vm, 1);
    sf::physfs *streamtexture = new sf::physfs(filename);
	bange::texture *texture = new bange::texture;
	texture->LoadFromStream(*streamtexture);
	bange::BuildProxy(vm, texture);
    delete streamtexture;
    return 1;
}
