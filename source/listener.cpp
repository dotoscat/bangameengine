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
#include <SFML/Audio.hpp>
#include <auxiliar.hpp>
#include <listener.hpp>

void bange::listener::RegisterVM(lua_State *vm){
    luaL_Reg functions[] = {
    {"SetGlobalVolume", bange::listener::SetGlobalVolume},
    {"GetGlobalVolume", bange::listener::GetGlobalVolume},
    {"SetPosition", bange::listener::SetPosition},
    {"GetPosition", bange::listener::GetPosition},
    {"SetDirection", bange::listener::SetDirection},
    {"GetDirection", bange::listener::GetDirection},
    {NULL, NULL}};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
}

int bange::listener::SetGlobalVolume(lua_State *vm){
    //volume
    sf::Listener::SetGlobalVolume(lua_tonumber(vm, 1));
    return 0;
}

int bange::listener::GetGlobalVolume(lua_State *vm){
    //-> volume
    lua_pushnumber(vm, sf::Listener::GetGlobalVolume() );
    return 1;
}

int bange::listener::SetPosition(lua_State *vm){
    //{x, y, x}
    if (!lua_istable(vm, 1)){
        std::cout << "SetPosition() -> First parameter isn't a valid table" << std::endl;
        return 0;
    }
    sf::Listener::SetPosition(bange::TableTosfVector3f(1, vm));
    return 0;
}

int bange::listener::GetPosition(lua_State *vm){
    //-> {x, y, z}
    bange::sfVector3fToTable(sf::Listener::GetPosition(), vm);
    return 1;
}

int bange::listener::SetDirection(lua_State *vm){
    //{x, y, x}
    if (!lua_istable(vm, 1)){
        std::cout << "SetDirection() -> First parameter isn't a valid table" << std::endl;
        return 0;
    }
    sf::Listener::SetDirection(bange::TableTosfVector3f(1, vm));
    return 0;
}

int bange::listener::GetDirection(lua_State *vm){
    //-> {x, y, z}
    bange::sfVector3fToTable(sf::Listener::GetDirection(), vm);
    return 1;
}
