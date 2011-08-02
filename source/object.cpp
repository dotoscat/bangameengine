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
#include <object.hpp>
#include <aux.hpp>

void bange::object::RegisterVM(lua_State *vm){
    luaL_Reg methods[] = {
    {NULL, NULL}};
    lua_createtable(vm, 0, 1);
    luaL_register(vm, NULL, methods);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::object::");
    
    luaL_Reg spritemethods[] = {
    {"Animate", bange::sprite::sprite_Animate},
    {NULL, NULL}};
    lua_createtable(vm, 0, 1);
    luaL_register(vm, NULL, spritemethods);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::sprite::");
    
}

bange::object::object(){
    visible = true;
    del = false;
}

bool bange::object::NewIndex(lua_State *vm, const char *key){
    //this->bange::drawable::NewIndex(vm, key);
    if (this->bange::drawable::NewIndex(vm, key)){
        return true;}
    if (strcmp("visible", key) == 0){
        visible = static_cast<bool>( lua_toboolean(vm, 3) );
        return true;
    }
    else if (strcmp("del", key) == 0){
        del = static_cast<bool>( lua_toboolean(vm, 3) );
        return true;
    }
    else if (strcmp("Destructor", key) == 0 && lua_isfunction(vm, 3)){
        Destructor = luaL_ref(vm, LUA_REGISTRYINDEX);
        return true;
    }
    return false;
}

bool bange::object::Index(lua_State *vm, const char *key){
    if (this->bange::drawable::Index(vm, key)){
        return true;}
    if ( strcmp("visible", key) == 0 ){
        lua_pushboolean(vm, visible);
        return true;
    }
    else if ( strcmp("del", key) == 0 ){
        lua_pushboolean(vm, del);
        return true;
    }
    else if ( strcmp("Destructor", key) == 0){
        lua_rawgeti(vm, LUA_REGISTRYINDEX, this->Destructor);
        return true;
    }
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::object::");
    lua_getfield(vm, -1, key);
    if (lua_isfunction(vm, -1)){
        return true;}
    lua_pop(vm, 1);
    return false;
    
}

void bange::object::Clean(lua_State *vm){
    luaL_unref(vm, LUA_REGISTRYINDEX, this->Destructor);
}
