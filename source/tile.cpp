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

#include <cstring>
#include <iostream>
#include <tile.hpp>
#include <object.hpp>

bange::tile::tile(float x, float y){
    position.x = x;
    position.y = y;
    sprite = LUA_REFNIL;
}

bool bange::tile::NewIndex(lua_State *vm, const char *key){
    return false;
}

bool bange::tile::Index(lua_State *vm, const char *key){
    if (strcmp("sprite", key) == 0){
        lua_rawgeti(vm, LUA_REGISTRYINDEX, sprite);
        return true;
    }
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::tile::");
    lua_getfield(vm, -1, key);
    return true;
}

void bange::tile::Clean(lua_State *vm){
    luaL_unref(vm, LUA_REGISTRYINDEX, sprite);
}

void bange::tile::Process(sf::Uint32 time, lua_State *vm){
    if (this->sprite == LUA_REFNIL){
        return;}
    lua_rawgeti(vm, LUA_REGISTRYINDEX, this->sprite);
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, -1));
    bange::sprite *sprite = static_cast<bange::sprite *>(proxy->object);
    lua_pop(vm, 1);//pop proxy
    sprite->Process(time, vm);
}

bool bange::tile::BuildSprite(lua_State *vm){
    if (this->sprite != LUA_REFNIL){
        return false;}
    bange::sprite *sprite = new bange::sprite();
    sprite->SetPosition(position);
    bange::BuildProxy(vm, sprite, false);
    this->sprite = luaL_ref(vm, LUA_REGISTRYINDEX);
    return true;
}

void bange::tile::RegisterVM(lua_State *vm){
    luaL_Reg methods[] = {
    {"BuildSprite", bange::tile_BuildSprite},
    {NULL, NULL}};
    lua_createtable(vm, 0, 1);
    luaL_register(vm, NULL, methods);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::tile::");
    
}

int bange::tile_BuildSprite(lua_State *vm){
    //tile -> bool/nil
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    bange::tile *tile = static_cast<bange::tile *>(proxy->object);
    if (tile == NULL){
        std::cout << ":BuildSprite() -> no valid object." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (tile->BuildSprite(vm)){
        lua_pushboolean(vm, 1);
    }else{
        lua_pushboolean(vm, 0);}
    return 1;
}
