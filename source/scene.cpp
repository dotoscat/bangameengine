//scene.cpp
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
#include <scene.hpp>
#include <view.hpp>
#include <aux.hpp>

bange::scene::scene(int nlayers){
    space = cpSpaceNew();
    physics = false;
    layers.reserve(nlayers);
    for(int i = 0; i < nlayers; i += 1){
        layers.push_back(LUA_REFNIL);}
}

bool bange::scene::NewIndex(lua_State *vm, const char *key){
    if (strcmp(key, "data") == 0){
        luaL_unref(vm, LUA_REGISTRYINDEX, data);
        data = luaL_ref(vm, LUA_REGISTRYINDEX);
        return true;
    }
    else if (strcmp(key, "physics") == 0 && lua_isboolean(vm, 3)){
        physics = static_cast<bool>(lua_toboolean(vm, 3));
        return true;
    }
    else if (strcmp(key, "iterations") == 0){
        space->iterations = lua_tonumber(vm, 3);
        return true;
    }
    else if (strcmp(key, "gravity") == 0 ){
        if (!lua_istable(vm, 3)){
            std::cout << lua_touserdata(vm, 1) << ".gravity: Value isn't a table." << std::endl;
            return true;
        }
        
        space->gravity = bange::TableTocpVect(3, vm);
        return true;
    }
    return false;
}

bool bange::scene::Index(lua_State *vm, const char *key){
    if(this->bange::behavior::Index(vm, key)){
        return true;}
    if (strcmp(key, "data") == 0){
        lua_rawgeti(vm, LUA_REGISTRYINDEX, data);
        return true;
    }
    else if (strcmp(key, "physics") == 0){
        lua_pushboolean(vm, static_cast<int>(physics));
        return true;
    }
    else if (strcmp(key, "iterations") == 0){
        lua_pushnumber(vm, space->iterations);
        return true;
    }
    else if (strcmp(key, "gravity") == 0){
        bange::cpVectToTable(space->gravity, vm);
        return true;
    }
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::scene::");
    lua_getfield(vm, -1, key);
    return true;
}

void bange::scene::Clean(lua_State *vm){
    luaL_unref(vm, LUA_REGISTRYINDEX, data);
    this->bange::behavior::Clean(vm);
    for(int i = 0; i < layers.size(); i += 1){
        luaL_unref(vm, LUA_REGISTRYINDEX, layers[i]);
    }
    lua_gc(vm, LUA_GCCOLLECT, 0);
}

void bange::scene::Process(int indexscene, float time, lua_State *vm){
    if (physics){
        cpSpaceStep(space, time);}
    this->bange::behavior::Process(indexscene, time, vm);
    bange::proxy *proxy = NULL;
    bange::layer *layer = NULL;
    std::vector<int>::iterator alayer = layers.begin();
    for(; alayer != layers.end(); alayer++){
        if (*alayer == LUA_REFNIL){
            continue;}
        lua_rawgeti(vm, LUA_REGISTRYINDEX, (*alayer));
        proxy = static_cast<bange::proxy *>( lua_touserdata(vm, -1) );
        layer = static_cast<bange::layer *>(proxy->object);
        layer->Process(lua_gettop(vm), time, vm);
        lua_pop(vm, 1);
    }
}

void bange::scene::Draw(sf::RenderTarget &rendertarget, lua_State *vm){
    bange::proxy *proxy = NULL;
    bange::layer *layer = NULL;
    for (int i = 0; i < layers.size(); i += 1){
        if (layers[i] == LUA_REFNIL){
            continue;}
        lua_rawgeti(vm, LUA_REGISTRYINDEX, layers[i]);
        proxy = static_cast<bange::proxy *>(lua_touserdata(vm, -1));
        lua_pop(vm, 1);
        layer = static_cast<bange::layer *>(proxy->object);
        if (!layer->visible){
            continue;}
        layer->Draw(rendertarget, vm);
    }
}

void bange::scene::SetLayer(int ilayer, int reference, lua_State *vm){
    luaL_unref(vm, LUA_REGISTRYINDEX, layers[ilayer]);
    lua_gc(vm, LUA_GCCOLLECT, 0);
    layers[ilayer] = reference;
}

bange::scene::~scene(){
    cpSpaceFree(space);
}

void bange::scene::RegisterVM(lua_State *vm){
    luaL_Reg functions[] = {
    {"NewScene", bange::NewScene},
    {NULL, NULL}};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
    
    luaL_Reg methods[] = {
    {"SetLayerObject", bange::scene_SetLayerObject},
    {NULL, NULL}};
    lua_createtable(vm, 0, 1);
    luaL_register(vm, NULL, methods);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::scene::");
    
}

static int bange::NewScene(lua_State *vm){
    //nlayers
    if (!lua_isnumber(vm, 1)){
        std::cout << "bange.NewScene: First argument must be a number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    lua_Number layers = lua_tonumber(vm, 1);
    if (layers <= 0){
        std::cout << "bange.NewScene: Layers must be greater than 0." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    bange::scene *scene = new bange::scene(layers);
    bange::BuildProxy(vm, scene);
    return 1;
}

static int bange::scene_SetLayerObject(lua_State *vm){
    //scene, ilayer, maxobjects
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_touserdata(vm, 1) );
    bange::scene *scene = static_cast<bange::scene *>(proxy->object);
    if (!lua_isnumber(vm, 2)){
        std::cout << lua_touserdata(vm, 1) << ":SetLayerObject(): First argument must be a number" << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    int i = lua_tonumber(vm, 2);
    if (i <= 0){
        std::cout << lua_touserdata(vm, 1) << ":SetLayerObject(): First argument must be a greater than 0." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (!lua_isnumber(vm, 3)){
        std::cout << lua_touserdata(vm, 1) << ":SetLayerObject(): 2nd argument must be a number" << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    size_t maxobjects = lua_tonumber(vm, 3);
    if (maxobjects <= 0){
        std::cout << lua_touserdata(vm, 1) << ":SetLayerObject(): 2nd argument must be a greater than 0." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    bange::layer *layer = new bange::layerobject(scene->space, maxobjects);
    bange::BuildProxy(vm, layer);
    lua_pushvalue(vm, -1);
    scene->SetLayer(i-1, luaL_ref(vm, LUA_REGISTRYINDEX), vm);
    return 1;
}
