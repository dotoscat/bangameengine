#include <iostream>
#include <base.hpp>

bange::proxy *bange::BuildProxy(lua_State *vm, bange::base *object, int parent){
    
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_newuserdata(vm, sizeof(bange::proxy)) );
    proxy->parent = parent;
    proxy->object = object;
    
    lua_createtable(vm, 0, 3);
    lua_pushcfunction(vm, bange::proxy_newindex);
    lua_setfield(vm, -2, "__newindex");
    lua_pushcfunction(vm, bange::proxy_index);
    lua_setfield(vm, -2, "__index");
    lua_pushcfunction(vm, bange::proxy_gc);
    lua_setfield(vm, -2, "__gc");
    lua_setmetatable(vm, -2);
    
    return proxy;
}

static int bange::proxy_newindex(lua_State *vm){
    //userdata, key, value
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_touserdata(vm, 1) );
    proxy->object->NewIndex(vm, lua_tostring(vm, 2) );
    return 0;
}

static int bange::proxy_index(lua_State *vm){
    //userdata, key
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_touserdata(vm, 1) );
    if (!proxy->object->Index(vm, lua_tostring(vm, 2)) ){
        lua_pushnil(vm);}
    return 1;
}

static int bange::proxy_gc(lua_State *vm){
    //userdata
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_touserdata(vm, 1) );
    if (proxy->parent != LUA_REFNIL){
        luaL_unref(vm, LUA_REGISTRYINDEX, proxy->parent);
        return 0;
    }
    std::cout << "GC collects: " << proxy << std::endl;
    proxy->object->Clean(vm);
    delete proxy->object;
    return 0;
}
