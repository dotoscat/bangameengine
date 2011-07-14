//behavior.cpp
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
#include <base.hpp>
#include <behavior.hpp>

bool bange::behavior::Index(lua_State *vm, const char *key){
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::behavior::");
    lua_getfield(vm, -1, key);
    if (lua_isfunction(vm, -1)){
        return true;}
    return false;
}

void bange::behavior::Process(int indexobject, float time, lua_State *vm){
    if (functions.empty()){
        return;}
    std::map<const void *, bange::behavior::function>::iterator afunction;
    for(afunction = functions.begin(); afunction != functions.end(); afunction++){
        if ( afunction->second.stop ){
            continue;}
        if ( afunction->second.timeleft <= 0.f ){
            lua_rawgeti(vm, LUA_REGISTRYINDEX, afunction->second.thefunction);
            lua_pushvalue(vm, indexobject);//object with the behavior
            lua_pushnumber(vm, time);
            lua_rawgeti(vm, LUA_REGISTRYINDEX, afunction->second.data);
            if (lua_pcall(vm, 3, 0, 0) == LUA_ERRRUN){
                std::cout << this << ": Error executing: " << lua_tostring(vm, -1) << std::endl;
                lua_pop(vm, 1);
            }
            afunction->second.timeleft = afunction->second.time;
        }else{
            afunction->second.timeleft -= time;
        }
        
    }
}

void bange::behavior::Clean(lua_State *vm){
    std::map<const void *, bange::behavior::function>::iterator afunction;
    for(afunction = functions.begin(); afunction != functions.end(); afunction++){
        luaL_unref(vm, LUA_REGISTRYINDEX, afunction->second.thefunction);
        luaL_unref(vm, LUA_REGISTRYINDEX, afunction->second.data);
    }
}

void bange::behavior::RegisterVM(lua_State *vm){
    luaL_Reg methods[] = {
    {"AddFunction", bange::behavior_AddFunction},
    {"StopFunction", bange::behavior_StopFunction},
    {NULL, NULL}};
    lua_createtable(vm, 0, 2);
    luaL_register(vm, NULL, methods);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::behavior::");
}

static int bange::behavior_AddFunction(lua_State *vm){
    //userdata, function, time, data
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    bange::behavior *behavior = dynamic_cast<bange::behavior *>(proxy->object);
    float time = 0.f;
    if (behavior == NULL){
        std::cout << lua_touserdata(vm, 1) << ":AddFunction(): Object without any behavior." << std::endl;
        return 0;
    }
    if (!lua_isfunction(vm, 2)){
        std::cout << lua_touserdata(vm, 1) << ":AddFunction(): First parameter isn't a function." << std::endl;
        return 0;
    }
    if (lua_gettop(vm) > 2 && !lua_isnumber(vm, 3) && !lua_isnil(vm, 3)){
        std::cout << lua_touserdata(vm, 1) << ":AddFunction(): 2nd parameter isn't a valid number." << std::endl;
        return 0;
    }
    else if (lua_gettop(vm) > 2 && lua_isnil(vm, 3)){
        time = 0.f;}
    else if (lua_gettop(vm) > 2 && lua_isnumber(vm, 3)){
        time = lua_tonumber(vm, 3);}
    bange::behavior::function newfunction;
    lua_pushvalue(vm, 2);//function
    newfunction.thefunction = luaL_ref(vm, LUA_REGISTRYINDEX);
    lua_pushvalue(vm, 4);//data
    newfunction.data = luaL_ref(vm, LUA_REGISTRYINDEX);
    newfunction.time = time;
    newfunction.timeleft = time;
    behavior->functions[lua_topointer(vm, 2)] = newfunction;
    return 0;
}

static int bange::behavior_StopFunction(lua_State *vm){
    //userdata, function, boolean
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    bange::behavior *behavior = dynamic_cast<bange::behavior *>(proxy->object);
    if (behavior == NULL){
        std::cout << lua_touserdata(vm, 1) << ":AddFunction(): Object without any behavior." << std::endl;
        return 0;
    }
    if (!lua_isfunction(vm, 2)){
        std::cout << lua_touserdata(vm, 1) << ":AddFunction(): First parameter isn't a function." << std::endl;
        return 0;
    }
    if (!lua_isnil(vm, 3) && !lua_isboolean(vm, 3)){
        std::cout << lua_touserdata(vm, 1) << ":AddFunction(): First parameter isn't a boolean." << std::endl;
        return 0;
    }
    behavior->functions[lua_topointer(vm, 2)].stop = static_cast<bool>( lua_toboolean(vm, 3) );
    return 0;
}
