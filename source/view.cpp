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

void bange::view::Clean(lua_State *vm){
    luaL_unref(vm, LUA_REGISTRYINDEX, scene);
}

void bange::view::RegisterVM(lua_State *vm){
    luaL_Reg functions[] = {
    {"NewView", bange::NewView},
    {NULL, NULL}};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
}

static int bange::NewView(lua_State *vm){
    //width, height
    if (!lua_isnumber(vm, 1)){
        std::cout << "bange.NewView(): First parameter must be a valid number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (!lua_isnumber(vm, 2)){
        std::cout << "bange.NewView(): 2nd parameter must be a valid number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    float width = 0.f, height = 0.f;
    width = lua_tonumber(vm, 1);
    if (width <= 0){
        std::cout << "bange.NewView(): First parameter must be greater than 0" << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    height = lua_tonumber(vm, 2);
    if (height <= 0){
        std::cout << "bange.NewView(): 2nd para must be greater than 0" << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    bange::view *view = new bange::view();
    view->SetCenter(width/2.f, height/2.f);
    view->SetHalfSize(width/2.f, height/2.f);
    BuildProxy(vm, view);
    return 1;
}
