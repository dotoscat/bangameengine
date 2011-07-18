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
