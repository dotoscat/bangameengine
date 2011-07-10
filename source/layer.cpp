//layer.cpp
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
#include <cstring>
#include <layer.hpp>

bool bange::layer::NewIndex(lua_State *vm, const char *key){
    if (strcmp(key, "data") == 0){
        luaL_unref(vm, LUA_REGISTRYINDEX, data);
        data = luaL_ref(vm, LUA_REGISTRYINDEX);
        return true;
    }
    else if (strcmp(key, "visible") == 0 && lua_isboolean(vm, 3)){
        visible = static_cast<bool>(lua_toboolean(vm, 3));
        return true;
    }
    return false;
}

bool bange::layer::Index(lua_State *vm, const char *key){
    if (this->bange::behavior::Index(vm, key)){
        return true;}
    if (strcmp(key, "data") == 0){
        lua_rawgeti(vm, LUA_REGISTRYINDEX, data);
        return true;
    }
    else if (strcmp(key, "visible") == 0){
        lua_pushboolean(vm, static_cast<int>(visible));
        return true;
    }
    return false;
}

void bange::layer::Clean(lua_State *vm){
    luaL_unref(vm, LUA_REGISTRYINDEX, data);
}
