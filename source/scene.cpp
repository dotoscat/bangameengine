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
#include <auxiliar.hpp>
#include <layerobject.hpp>
#include <layertilemap.hpp>
#include <layerimagetilemap.hpp>

bange::scene::scene(int nlayers){
    layers.reserve(nlayers);
    for(int i = 0; i < nlayers; i += 1){
        layers.push_back(LUA_REFNIL);}
}

bool bange::scene::NewIndex(lua_State *vm, const char *key){
    return false;
}

bool bange::scene::Index(lua_State *vm, const char *key){
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::scene::");
    lua_getfield(vm, -1, key);
    return true;
}

void bange::scene::Clean(lua_State *vm){
    for(int i = 0; i < layers.size(); i += 1){
        luaL_unref(vm, LUA_REGISTRYINDEX, layers[i]);
    }
    std::map<const void *, int>::iterator aview = views.begin();
    for(; aview != views.end(); aview++){
        luaL_unref(vm, LUA_REGISTRYINDEX, aview->second);
    }
    lua_gc(vm, LUA_GCCOLLECT, 0);
}

void bange::scene::Process(sf::Uint32 time, sf::RenderTarget &rendertarget, lua_State *vm){
    bange::proxy *proxy = NULL;
    bange::layer *layer = NULL;
    std::vector<int>::iterator alayer = layers.begin();
    for(; alayer != layers.end(); alayer++){
        if (*alayer == LUA_REFNIL){
            continue;}
        lua_rawgeti(vm, LUA_REGISTRYINDEX, (*alayer));
        proxy = static_cast<bange::proxy *>( lua_touserdata(vm, -1) );
        proxy->behavior->Process(lua_gettop(vm), time, vm);
        layer = static_cast<bange::layer *>(proxy->object);
        layer->Process(time, rendertarget, views, vm);
        lua_pop(vm, 1);
    }
}

void bange::scene::SetLayer(int ilayer, int reference, lua_State *vm){
    luaL_unref(vm, LUA_REGISTRYINDEX, layers[ilayer]);
    lua_gc(vm, LUA_GCCOLLECT, 0);
    layers[ilayer] = reference;
}

void bange::scene::RegisterVM(lua_State *vm){    
    luaL_Reg methods[] = {
    {"SetLayerObject", bange::scene_SetLayerObject},
    {"SetLayerTilemap", bange::scene_SetLayerTilemap},
    {"SetLayerImageTilemap", bange::scene_SetLayerImageTilemap},
    {"AddView", bange::scene_AddView},
    {NULL, NULL}};
    lua_createtable(vm, 0, 4);
    luaL_register(vm, NULL, methods);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::scene::");    
}

int bange::NewScene(lua_State *vm){
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

int bange::scene_SetLayerObject(lua_State *vm){
    //scene, ilayer, maxobjects -> layer
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

int bange::scene_SetLayerTilemap(lua_State *vm){
    //layer, width, height, widthtile, heighttile -> layer
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_touserdata(vm, 1) );
    bange::scene *scene = static_cast<bange::scene *>(proxy->object);
    int i = 0;
    lua_Number width = 0, height = 0, widthtile = 0, heighttile = 0;
    i = lua_tonumber(vm, 2);
    width = lua_tonumber(vm, 3);
    height = lua_tonumber(vm, 4);
    widthtile = lua_tonumber(vm, 5);
    heighttile = lua_tonumber(vm, 6);
    if (i <= 0){
        std::cout << proxy << ":SetLayerTilemap() -> Layer must be greater than 0." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (width == 0){
        std::cout << proxy << ":SetLayerTilemap() -> First value isn't a valid number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (height == 0){
        std::cout << proxy << ":SetLayerTilemap() -> Second value isn't a valid number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (widthtile == 0){
        std::cout << proxy << ":SetLayerTilemap() -> Third value isn't a valid number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (heighttile == 0){
        std::cout << proxy << ":SetLayerTilemap() -> Fourth value isn't a valid number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    bange::layer *layer = new bange::layertilemap(width, height, widthtile, heighttile);
    bange::BuildProxy(vm, layer);
    lua_pushvalue(vm, -1);
    scene->SetLayer(i-1, luaL_ref(vm, LUA_REGISTRYINDEX), vm);
    return 1;
}

int bange::scene_SetLayerImageTilemap(lua_State *vm){
    //layer, width, height, widthtile, heighttile -> layer
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_touserdata(vm, 1) );
    bange::scene *scene = static_cast<bange::scene *>(proxy->object);
    int i = 0;
    lua_Number width = 0, height = 0, widthtile = 0, heighttile = 0;
    i = lua_tonumber(vm, 2);
    width = lua_tonumber(vm, 3);
    height = lua_tonumber(vm, 4);
    widthtile = lua_tonumber(vm, 5);
    heighttile = lua_tonumber(vm, 6);
    if (i <= 0){
        std::cout << proxy << ":SetLayerImageTilemap() -> Layer must be greater than 0." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (width == 0){
        std::cout << proxy << ":SetLayerImageTilemap() -> First value isn't a valid number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (height == 0){
        std::cout << proxy << ":SetLayerImageTilemap() -> Second value isn't a valid number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (widthtile == 0){
        std::cout << proxy << ":SetLayerImageTilemap() -> Third value isn't a valid number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (heighttile == 0){
        std::cout << proxy << ":SetLayerImageTilemap() -> Fourth value isn't a valid number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    bange::layer *layer = new bange::layerimagetilemap(width, height, widthtile, heighttile);
    bange::BuildProxy(vm, layer);
    lua_pushvalue(vm, -1);
    scene->SetLayer(i-1, luaL_ref(vm, LUA_REGISTRYINDEX), vm);
    return 1;
}

int bange::scene_AddView(lua_State *vm){
    //scene, view
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_touserdata(vm, 1) );
    bange::scene *scene = static_cast<bange::scene *>(proxy->object);
    if (!lua_isuserdata(vm, 2)){
        std::cout << proxy << ":AddView() : Object a valid userdata" << std::endl;
        return 0;
    }
    bange::view *view = dynamic_cast<bange::view *>( static_cast<bange::proxy *>(lua_touserdata(vm, 2))->object );
    if (view == NULL){
        std::cout << proxy << ":AddView() : First argument ins't a view" << std::endl;
        return 0;
    }
    scene->views[view] = luaL_ref(vm, LUA_REGISTRYINDEX);
    return 0;
}
