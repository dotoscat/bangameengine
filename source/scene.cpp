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
#include <scene.hpp>
#include <view.hpp>
#include <aux.hpp>

bange::scene::scene(int nlayers){
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
    return false;
}

bool bange::scene::Index(lua_State *vm, const char *key){
    if(this->bange::behavior::Index(vm, key)){
        return true;}
    if (strcmp(key, "data") == 0){
        lua_rawgeti(vm, LUA_REGISTRYINDEX, data);
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
    bange::layer *layer = new bange::layerobject(maxobjects);
    bange::BuildProxy(vm, layer);
    lua_pushvalue(vm, -1);
    scene->SetLayer(i-1, luaL_ref(vm, LUA_REGISTRYINDEX), vm);
    return 1;
}
