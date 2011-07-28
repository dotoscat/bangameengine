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
#include <base.hpp>

void bange::proxy::RegisterVM(lua_State *vm){
    luaL_Reg meta[] = {
    {"__newindex", bange::proxy_newindex},
    {"__index", bange::proxy_index},
    {"__gc", bange::proxy_gc},
    {NULL, NULL}};
    lua_createtable(vm, 0, 3);
    luaL_register(vm, NULL, meta);
    lua_setfield(vm, LUA_REGISTRYINDEX, "metatable_proxy");
}

bange::proxy *bange::BuildProxy(lua_State *vm, bange::base *object, bool hasbehavior){
    
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_newuserdata(vm, sizeof(bange::proxy)) );
    proxy->object = object;
    proxy->behavior = NULL;
    if (hasbehavior){
        proxy->behavior = new bange::behavior(); }
    lua_getfield(vm, LUA_REGISTRYINDEX, "metatable_proxy");
    lua_setmetatable(vm, -2);
    
    return proxy;
}

int bange::proxy_newindex(lua_State *vm){
    //userdata, key, value
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_touserdata(vm, 1) );
    const char *key = lua_tostring(vm, 2);
    if (proxy->behavior != NULL && proxy->behavior->NewIndex(vm, key)){
        return 0;}
    proxy->object->NewIndex(vm, key);
    return 0;
}

int bange::proxy_index(lua_State *vm){
    //userdata, key
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_touserdata(vm, 1) );
    const char *key = lua_tostring(vm, 2);
    if (proxy->behavior != NULL && proxy->behavior->Index(vm, key)){
        return 1;}
    if (!proxy->object->Index(vm, lua_tostring(vm, 2)) ){
        lua_pushnil(vm);}
    return 1;
}

int bange::proxy_gc(lua_State *vm){
    //userdata
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_touserdata(vm, 1) );
    if (proxy->behavior != NULL){
        proxy->behavior->Clean(vm);
        delete proxy->behavior;
    }
    proxy->object->Clean(vm);
    delete proxy->object;
    return 0;
}
