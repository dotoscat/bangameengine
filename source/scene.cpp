//scene.cpp
//Copyright (C) 2010-2011 Oscar (.teri) Triano

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <scene.hpp>

bange::scene::scene(int nlayers){
    space = cpSpaceNew();
    layers.reserve(nlayers);
    for(int i = 0; i < nlayers; i += 1){
        layers[i] = LUA_REFNIL;}
}

bool bange::scene::Index(lua_State *vm, const char *key){
    if(this->bange::behavior::Index(vm, key)){
        return true;}
}

void bange::scene::Clean(lua_State *vm){
    this->bange::behavior::Clean(vm);
    for(int i = 0; i < layers.size(); i += 1){
        luaL_unref(vm, LUA_REGISTRYINDEX, layers[i]);
    }
    lua_gc(vm, LUA_GCCOLLECT, 0);
}

bange::scene::~scene(){
    cpSpaceFree(space);
}

void bange::scene::RegisterVM(lua_State *vm){
    luaL_Reg functions[] = {
    {"NewScene", bange::NewScene},
    {NULL, NULL}};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
}

static int bange::NewScene(lua_State *vm){
    //nlayers
    if (!lua_isnumber(vm, 1)){
        std::cout << "bange.NewScene: First argument must be a number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    lua_Number layers = lua_tonumber(vm, 1);
    if (layers <= 0){
        std::cout << "bange.NewScene: Layers must be greater than 0." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    bange::scene *scene = new bange::scene(lua_tonumber(vm, 1));
    bange::BuildProxy(vm, scene);
    return 1;
}
