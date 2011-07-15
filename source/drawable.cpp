//drawable.hpp
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
    return false;
}
