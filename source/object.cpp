//object.cpp
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
#include <object.hpp>

void bange::object::RegisterVM(lua_State *vm){
    luaL_Reg methods[] = {
    {"GiveBody", bange::object_GiveBody},
    {NULL, NULL}};
    lua_createtable(vm, 0, 1);
    luaL_register(vm, NULL, methods);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::object::");
}

bange::object::object(){
    data = LUA_REFNIL;
    visible = true;
    del = false;
    body = NULL;
}

bool bange::object::NewIndex(lua_State *vm, const char *key){
    //this->bange::drawable::NewIndex(vm, key);
    if (this->bange::drawable::NewIndex(vm, key)){
        return true;}
    if (strcmp("data", key) == 0){
        luaL_unref(vm, LUA_REGISTRYINDEX, data);
        data = luaL_ref(vm, LUA_REGISTRYINDEX);
        return true;
    }
    else if (strcmp("visible", key) == 0){
        visible = static_cast<bool>( lua_toboolean(vm, 3) );
        return true;
    }
    else if (strcmp("del", key) == 0){
        del = static_cast<bool>( lua_toboolean(vm, 3) );
        return true;
    }
    if (body != NULL){
        if (strcmp("inspace", key) == 0){
            if(lua_toboolean(vm, 3)){
                body->AddToSpace();
            }else{
                body->RemoveFromSpace();}
            return true;
        }
    }
    return false;
}

bool bange::object::Index(lua_State *vm, const char *key){
    if (this->bange::behavior::Index(vm, key)){
        return true;}
    if (this->bange::drawable::Index(vm, key)){
        return true;}
    if ( strcmp("data", key) == 0 ){
        lua_rawgeti(vm, LUA_REGISTRYINDEX, data);
        return true;
    }
    else if ( strcmp("visible", key) == 0 ){
        lua_pushboolean(vm, visible);
        return true;
    }
    else if ( strcmp("del", key) == 0 ){
        lua_pushboolean(vm, del);
        return true;
    }
    if (body != NULL){
        if (strcmp("inspace", key) == 0){
            lua_pushboolean(vm, static_cast<int>(body->inspace));
            return true;
        }
    }
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::object::");
    lua_getfield(vm, -1, key);
    if (lua_isfunction(vm, -1)){
        return true;}
    lua_pop(vm, 1);
    return false;
    
}

bange::object::~object(){
    if (body != NULL){
        delete body;}
}

void bange::object::Clean(lua_State *vm){
    luaL_unref(vm, LUA_REGISTRYINDEX, data);
}

void bange::object::Process(int indexobject, float time, lua_State *vm){
    this->bange::behavior::Process(indexobject, time, vm);
    if (body != NULL){
        cpVect pos = body->GetPos();
        thedrawable->SetPosition(pos.x, pos.y);
    }
}

void bange::object::GiveBody(cpFloat mass, cpFloat moi){
    if (body != NULL){
        return;}
    body = new bange::body(space, this, mass, moi);
}

const bange::body &bange::object::GetBody(){
    return *body;
}

static int bange::object_GiveBody(lua_State *vm){
    //object, (mass), (moi)
    bange::proxy *proxy  = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    bange::object *object = static_cast<bange::object *>(proxy->object);
    cpFloat mass = INFINITY, moi = INFINITY;
    if (lua_gettop(vm) > 1 && !lua_isnumber(vm, 2)){
        std::cout << proxy << ":GiveBody(): First argument isn't a valid number." << std::endl;
        return 0;
    }
    else if (lua_isnumber(vm, 2)){
        mass = lua_tonumber(vm, 2);}
    if (lua_gettop(vm) > 2 && !lua_isnumber(vm, 3)){
        std::cout << proxy << ":GiveBody(): 2nd argument isn't a valid number." << std::endl;
        return 0;
    }
    else if (lua_isnumber(vm, 3)){
        moi = lua_tonumber(vm, 3);}
    std::cout << "Mass: " << mass << ", moi: " << moi << std::endl;
    object->GiveBody(mass, moi);
    return 0;
}
