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
#include <drawable.hpp>
#include <aux.hpp>

bool bange::drawable::NewIndex(lua_State *vm, const char *key){
    if ( strcmp("color", key) == 0 ){
        if (!lua_istable(vm, 3)){
            std::cout << lua_touserdata(vm, 1) << ".color: Value isn't a table" << std::endl;
            return false;
        }
        thedrawable->SetColor(bange::TableTosfColor(3, vm));
        return true;
    }
    else if ( strcmp("position", key) == 0){
        if (!lua_istable(vm, 3)){
            std::cout << lua_touserdata(vm, 1) << ".color: Value isn't a table" << std::endl;
            return false;
        }
        thedrawable->SetPosition(bange::TableTosfVector2f(3, vm));
        return true;
    }
    else if ( strcmp("origin", key) == 0 ){
        if (!lua_istable(vm, 3)){
            std::cout << lua_touserdata(vm, 1) << ".origin: Value isn't a table" << std::endl;
            return false;
        }
        thedrawable->SetOrigin(bange::TableTosfVector2f(3, vm));
        return true;
    }
    return false;
}

bool bange::drawable::Index(lua_State *vm, const char *key){
    if ( strcmp("color", key) == 0){
        bange::sfColorToTable(thedrawable->GetColor(), vm);
        return true;
    }
    else if ( strcmp("position", key) == 0){
        bange::sfVector2fToTable(thedrawable->GetPosition(), vm);
        return true;
    }
    else if ( strcmp("origin", key) == 0){
        bange::sfVector2fToTable(thedrawable->GetOrigin(), vm);
        return true;
    }
    return false;
}
