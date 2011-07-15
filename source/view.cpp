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