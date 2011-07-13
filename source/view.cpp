//view.cpp
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
#include <view.hpp>
#include <scene.hpp>

bange::view::view(){
    scene = LUA_REFNIL;
}

bool bange::view::NewIndex(lua_State *vm, const char *key){
    if (strcmp("scene", key) == 0){
        if (!lua_isuserdata(vm, 3)){
            std::cout << lua_touserdata(vm, 1) << ".scene : Value isn't a userdata" << std::endl;
            return true;
        }
        if ( dynamic_cast<bange::scene *>( static_cast<bange::proxy *>(lua_touserdata(vm, 3))->object ) == NULL ){
            std::cout << lua_touserdata(vm, 1) << ".scene : Value isn't a scene" << std::endl;
            return true;
        }
        luaL_unref(vm, LUA_REGISTRYINDEX, scene);
        scene = luaL_ref(vm, LUA_REGISTRYINDEX);
    }
    return true;
}

bool bange::view::Index(lua_State *vm, const char *key){
    if (strcmp("scene", key) == 0){
        lua_rawgeti(vm, LUA_REGISTRYINDEX, scene);
        return true;
    }
    return false;
}

bange::view::Clean(lua_State *vm){
    luaL_unref(vm, LUA_REGISTRYINDEX, scene);
}
