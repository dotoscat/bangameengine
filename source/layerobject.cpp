//layerobject.cpp
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
#include <SFML/System.hpp>
#include <layerobject.hpp>
#include <object.hpp>
#include <aux.hpp>

void bange::layerobject::RegisterVM(lua_State *vm){
    luaL_Reg methods[] = {
    {"AddShapeRectangle", bange::layerobject_AddShapeRectangle},
    {NULL, NULL}};
    lua_createtable(vm, 0, 1);
    luaL_register(vm, NULL, methods);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::layerobject::");
}

bange::layerobject::layerobject(cpSpace *space, size_t maxobjects){
    this->space = space;
    this->maxobjects = maxobjects;
    nobjects = 0;
    iterations = maxobjects;
    position = 0;
    objects.reserve(maxobjects);
    for(size_t i = 0; i < maxobjects; i += 1){
        objects.push_back(LUA_REFNIL);}
}

bool bange::layerobject::NewIndex(lua_State *vm, const char *key){
    if (this->bange::layer::NewIndex(vm, key)){
        return true;}
    if (strcmp("iterations", key) == 0){
        iterations = lua_tonumber(vm, 3);
        return true;
    }
    return false;
}

bool bange::layerobject::Index(lua_State *vm, const char *key){
    if (this->bange::layer::Index(vm, key)){
        return true;}
    if (strcmp(key, "maxobjects") == 0){
        lua_pushnumber(vm, maxobjects);
        return true;}
    else if (strcmp(key, "nobjects") == 0){
        lua_pushnumber(vm, nobjects);
        return true;}
    else if (strcmp(key, "iterations") == 0){
        lua_pushnumber(vm, iterations);
        return true;}
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::layerobject::");
    lua_getfield(vm, -1, key);
    return true;
}

void bange::layerobject::Clean(lua_State *vm){
    this->bange::layer::Clean(vm);
    std::vector<int>::iterator aobject = objects.begin();
    for(; aobject != objects.end(); aobject++){
        luaL_unref(vm, LUA_REGISTRYINDEX, *aobject);}
    lua_gc(vm, LUA_GCCOLLECT, 0);
}

void bange::layerobject::Process(int indexlayer, float time, lua_State *vm){
    this->bange::behavior::Process(indexlayer, time, vm);
    size_t end = position+iterations, i = position;
    for(; i < end; i += 1){
        if (i == maxobjects){
            i = 0;
            break;}
    }
    position = i;    
}

void bange::layerobject::Draw(sf::RenderTarget &rendertarget, lua_State *vm){
    bange::proxy *proxy = NULL;
    bange::object *object = NULL;
    for(int i = 0; i < objects.size(); i += 1){
        if (objects[i] == LUA_REFNIL){
            continue;}
        lua_rawgeti(vm, LUA_REGISTRYINDEX, objects[i]);
        proxy = static_cast<bange::proxy *>(lua_touserdata(vm, -1));
        lua_pop(vm, 1);
        object = static_cast<bange::object *>(proxy->object);
        rendertarget.Draw(*object->thedrawable);
    }
}

bool bange::layerobject::AddObject(int referenceobject){
    for (size_t i=0; i < maxobjects; i += 1){
        
        if (objects[i] == LUA_REFNIL){
            objects[i] = referenceobject;
            nobjects += 1;
            return true;
        }

    }
    return false;
}

static int bange::layerobject_AddShapeRectangle(lua_State *vm){
    //layerobject, vect1, vect2, color, float outline, outlinecolor
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    bange::layerobject *layerobject = static_cast<bange::layerobject *>(proxy->object);
    if (!lua_istable(vm, 2)){
        std::cout << "bange.NewRectangle: First argument must be a table with the 1st point." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (!lua_istable(vm, 3)){
        std::cout << "bange.NewRectangle: 2nd argument must be a table with the 2st point." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (!lua_istable(vm, 4)){
        std::cout << "bange.NewRectangle: 3hd argument must be a table with the colors." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    sf::Color outlinecolor(0, 0, 0);
    float outline = 0.f;
    if (lua_gettop(vm) > 4){
        
        if (!lua_isnumber(vm, 5)){
            std::cout << "bange.NewRectangle: 4th argument must be a valid number." << std::endl;
            lua_pushnil(vm);
            return 1;
        }
        else if (lua_isnumber(vm, 5)){
            outline = lua_tonumber(vm, 5);}
        if (!lua_istable(vm, 6)){
            std::cout << "bange.NewRectangle: 5th argument must be a table with the colors.." << std::endl;
            lua_pushnil(vm);
            return 1;
        }
        else if (lua_isnumber(vm, 6)){
            outlinecolor = bange::TableTosfColor(6, vm);}
            
    }
    sf::Vector2f P1 = bange::TableTosfVector2f(2, vm);
    sf::Vector2f P2 = bange::TableTosfVector2f(3, vm);
    sf::Color color = bange::TableTosfColor(4, vm);
    bange::shape *shape = new bange::shape(layerobject->space);
    *static_cast<sf::Shape *>(shape) = sf::Shape::Rectangle(P1, P2, color, outline, outlinecolor);
    bange::BuildProxy(vm, shape);
    lua_pushvalue(vm, -1);
    if ( !layerobject->AddObject(luaL_ref(vm, LUA_REGISTRYINDEX)) ){
        lua_pushnil(vm);
        return 1;
    }
    return 1;
}

