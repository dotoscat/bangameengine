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

#include <cstring>
#include <layerobject.hpp>

bange::layerobject::layerobject(cpSpace *space, size_t maxobjects){
    this->space = space;
    this->maxobjects = maxobjects;
    objects.reserve(maxobjects);
    for(size_t i = 0; i < maxobjects; i += 1){
        objects[i] = LUA_REFNIL;}
}

bool bange::layerobject::NewIndex(lua_State *vm, const char *key){
    if (this->bange::layer::NewIndex(vm, key)){
        return true;}
    return false;
}

bool bange::layerobject::Index(lua_State *vm, const char *key){
    if (this->bange::layer::Index(vm, key)){
        return true;}
    if (strcmp(key, "maxobjects") == 0){
        lua_pushnumber(vm, maxobjects);
        return true;}
    else if (strcmp(key, "nobjects") == 0){
        lua_pushnumber(vm, this->CountObjects());
        return true;}
    return false;
}

void bange::layerobject::Clean(lua_State *vm){
    std::vector<int>::iterator aobject = objects.begin();
    for(; aobject != objects.end(); aobject++){
        luaL_unref(vm, LUA_REGISTRYINDEX, *aobject);}
    lua_gc(vm, LUA_GCCOLLECT, 0);
}

void bange::layerobject::Process(int indexlayer, float time, lua_State *vm){
    this->bange::behavior::Process(indexlayer, time, vm);
    std::vector<int>::iterator aobject = objects.begin();
    for(; aobject != objects.end(); aobject++){
    }
}

void bange::layerobject::Draw(sf::RenderTarget &rendertarget){
    if(!visible){
        return;}
}

lua_Number bange::layerobject::CountObjects(){
    size_t nobjects = 0;
    for(size_t i = 0; i < maxobjects; i += 1){
        if (objects[i] != LUA_REFNIL){
            nobjects += 1;}
    }
    return static_cast<lua_Number>(nobjects);
}
