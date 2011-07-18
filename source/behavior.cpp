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
#include <base.hpp>
#include <behavior.hpp>

bool bange::behavior::Index(lua_State *vm, const char *key){
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::behavior::");
    lua_getfield(vm, -1, key);
    if (lua_isfunction(vm, -1)){
        return true;}
    return false;
}

void bange::behavior::Process(int indexobject, sf::Uint32 time, lua_State *vm){
    if (functions.empty()){
        return;}
    std::map<const void *, bange::behavior::function>::iterator afunction;
    for(afunction = functions.begin(); afunction != functions.end(); afunction++){
        if ( afunction->second.stop ){
            continue;}
        if ( afunction->second.timestored >= afunction->second.time){
            lua_rawgeti(vm, LUA_REGISTRYINDEX, afunction->second.thefunction);
            lua_pushvalue(vm, indexobject);//object with the behavior
            lua_rawgeti(vm, LUA_REGISTRYINDEX, afunction->second.data);
            if (lua_pcall(vm, 2, 0, 0) == LUA_ERRRUN){
                std::cout << this << ": Error executing: " << lua_tostring(vm, -1) << std::endl;
                lua_pop(vm, 1);
            }
            afunction->second.timestored = 0;
        }else{
            afunction->second.timestored += time;
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
    sf::Uint32 time = 0;
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
        time = 0;}
    else if (lua_gettop(vm) > 2 && lua_isnumber(vm, 3)){
        time = static_cast<sf::Uint32>(lua_tonumber(vm, 3));}
    bange::behavior::function newfunction;
    lua_pushvalue(vm, 2);//function
    newfunction.thefunction = luaL_ref(vm, LUA_REGISTRYINDEX);
    lua_pushvalue(vm, 4);//data
    newfunction.data = luaL_ref(vm, LUA_REGISTRYINDEX);
    newfunction.time = time;
    newfunction.timestored = 0;
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
