//vm.cpp
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

#include <vm.hpp>

void bange::vm::SetNumber(lua_State *vm, const char *var, int value){
    lua_pushnumber(vm, value);
    lua_setglobal(vm, var);
}

bool bange::vm::GetNumber(lua_State *vm, const char *var, lua_Number &value){
    lua_getglobal(vm, var);
    if (lua_isnil(vm, -1) || !lua_isnumber(vm, -1)){
        lua_pop(vm, 1);
        return false;}
    value = lua_tonumber(vm, -1);
    lua_pop(vm, 1);
    return true;
}

void bange::vm::SetBoolean(lua_State *vm, const char *var, int value){
    lua_pushboolean(vm, value);
    lua_setglobal(vm, var);
}

bool bange::vm::GetBoolean(lua_State *vm, const char *var, int &value){
    lua_getglobal(vm, var);
    if (lua_isnil(vm, -1) || !lua_isboolean(vm, -1)){
        lua_pop(vm, 1);
        return false;}
    value = lua_toboolean(vm, -1);
    lua_pop(vm, 1);
    return true;
}

bool bange::vm::GetString(lua_State *vm, const char *var, char *string, int size){
    lua_getglobal(vm, var);
    if (lua_isnil(vm, -1) || !lua_isstring(vm, -1)){
        lua_pop(vm, 1);
        return false;}
    memset(static_cast<void *>(string), 0, size);
    strncpy(string, lua_tostring(vm, -1), size);
    lua_pop(vm, 1);
    return true;
}

bool bange::vm::GetTable(lua_State *vm, const char *name){
    lua_getglobal(vm, name);
    if (!lua_istable(vm, -1)){
        lua_pop(vm, 1);
        return false;}
    return true;
}
