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
#include <animation.hpp>
#include <aux.hpp>

bange::animation::animation(sf::Sprite *sprite){
    this->sprite = sprite;
    storetime = 0;
    iframe = 1;
    refanimation = LUA_REFNIL;
}

bool bange::animation::NewIndex(lua_State *vm, const char *key){
    
    if (strcmp("animation", key) == 0){
        if (!lua_istable(vm, 3)){
            return true;}
        iframe = 1;
        storetime = 0;
        lua_getfield(vm, 3, "frames");
        lua_rawgeti(vm, -1, iframe);
        if (!lua_istable(vm, 3)){
            lua_pop(vm, 2);//iframe and frames
            return true;}
        bange::animation::frame aframe = bange::animation::BuildFrame(lua_gettop(vm), vm);
        lua_pop(vm, 2);//iframe and frames
        this->SetSubRect(aframe);
        refanimation = luaL_ref(vm, LUA_REGISTRYINDEX);
    }
    
    return true;
}

bool bange::animation::Index(lua_State *vm, const char *key){
    
    if ( strcmp("animation", key) == 0){
        lua_rawgeti(vm, LUA_REGISTRYINDEX, this->refanimation);
        return true;
    }
    
    return false;
}

void bange::animation::Clean(lua_State *vm){
    luaL_unref(vm, LUA_REGISTRYINDEX, this->refanimation);
}

void bange::animation::Process(sf::Uint32 time, lua_State *vm){
    lua_rawgeti(vm, LUA_REGISTRYINDEX, this->refanimation);
    if (!lua_istable(vm, -1)){
        lua_pop(vm, 1);
        return;
    }
    
    int automatic = 1;
    lua_getfield(vm, -1, "auto");
    if (lua_isboolean(vm, -1)){
        automatic = lua_toboolean(vm, -1);
    }
    lua_pop(vm, 1);//auto
    if(automatic){
        storetime += time;}
    
    lua_getfield(vm, -1, "frames");
    if (!lua_istable(vm, -1)){
        lua_pop(vm, 2);//"frames" and animation table
        return;
    }
    
    size_t lenframes = lua_objlen(vm, -1);
    if (lenframes > 0){
        lua_rawgeti(vm, -1, iframe);
        bange::animation::frame aframe = bange::animation::BuildFrame(lua_gettop(vm), vm);
        lua_pop(vm, 1);//frame
                
        if (storetime >= aframe.timestep){
            iframe += 1;
            if (iframe > lenframes){
                iframe = 1;}
            this->SetSubRect(aframe);
            storetime = 0;
        }
        
    }
    
    lua_pop(vm, 2);//Frames and animation table
}

void bange::animation::SetSubRect(bange::animation::frame aframe){
    sprite->SetSubRect(aframe.rect);
    sprite->FlipX(aframe.flipx);
    sprite->FlipY(aframe.flipy);
    sprite->SetOrigin(aframe.origin);
}

bange::animation::frame bange::animation::BuildFrame(int indexframe, lua_State *vm){
    bange::animation::frame aframe;
    aframe.flipx = false;
    aframe.flipy = false;
    lua_getfield(vm, indexframe, "timestep");
    aframe.timestep = lua_tonumber(vm, -1);
    lua_pop(vm, 1);//timestep
    lua_getfield(vm, indexframe, "flipx");
    aframe.flipx = (bool)lua_toboolean(vm, -1);
    lua_pop(vm, 1);//flipx
    lua_getfield(vm, indexframe, "flipy");
    aframe.flipy = (bool)lua_toboolean(vm, -1);
    lua_pop(vm, 1);//flipy
    
    lua_getfield(vm, indexframe, "rect");
    if (lua_istable(vm, -1)){
        aframe.rect = bange::TableTosfIntRect(-1, vm);}
    else{
        std::cout << "bange::animation: frame table " << lua_topointer(vm, indexframe) << " doesn't have a rect." << std::endl;
    }
    lua_pop(vm, 1);//rect
    
    lua_getfield(vm, indexframe, "origin");
    aframe.origin.x = 0.f;
    aframe.origin.y = 0.f;
    if (lua_istable(vm, -1)){
        aframe.origin = bange::TableTosfVector2f(-1, vm);}
    else{
        std::cout << "bange::animation: frame table " << lua_topointer(vm, indexframe) << " doesn't have a origin." << std::endl;
    }
    lua_pop(vm, 1);//origin
    
    return aframe;
}
