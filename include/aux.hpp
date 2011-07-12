//aux.hpp
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

#ifndef _bange_aux_
#define _bange_aux_

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>
#include <lua5.1/lua.hpp>

namespace bange{

    inline sf::Vector2f TableTosfVector2f(int indextable, lua_State *vm){
        sf::Vector2f vector;
        lua_getfield(vm, indextable, "x");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 1);
        }
        vector.x = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        lua_getfield(vm, indextable, "y");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 2);
        }
        vector.y = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        return vector;
    }

    inline cpVect TableTocpVect(int indextable, lua_State *vm){
        cpVect vector = cpvzero;
        lua_getfield(vm, indextable, "x");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 1);
        }
        vector.x = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        lua_getfield(vm, indextable, "y");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 2);
        }
        vector.y = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        return vector;
    }

    inline void sfVector2fToTable(sf::Vector2f vector, lua_State *vm){
        lua_createtable(vm, 0, 2);
        lua_pushnumber(vm, vector.x);
        lua_setfield(vm, -1, "x");
        lua_pushnumber(vm, vector.y);
        lua_setfield(vm, -1, "y");
        //+1
    }

    inline void cpVect2fToTable(cpVect vector, lua_State *vm){
        lua_createtable(vm, 0, 2);
        lua_pushnumber(vm, vector.x);
        lua_setfield(vm, -1, "x");
        lua_pushnumber(vm, vector.y);
        lua_setfield(vm, -1, "y");
        //+1
    }

    inline sf::Color TableTosfColor(int indextable, lua_State *vm){
        sf::Color color;
        lua_getfield(vm, indextable, "r");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 1);
        }
        color.r = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        lua_getfield(vm, indextable, "g");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 2);
        }
        color.g = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        lua_getfield(vm, indextable, "b");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 3);
        }
        color.b = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        lua_getfield(vm, indextable, "a");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 4);
        }
        if (!lua_isnil(vm, -1)){
            color.a = lua_tonumber(vm, -1);}
        else{
            color.a = 255;}
        lua_pop(vm, 1);
        return color;
    }

    inline void sfColorToTable(sf::Color color, lua_State *vm){
        lua_createtable(vm, 0, 4);
        lua_pushnumber(vm, color.r);
        lua_setfield(vm, -1, "r");
        lua_pushnumber(vm, color.g);
        lua_setfield(vm, -1, "g");
        lua_pushnumber(vm, color.b);
        lua_setfield(vm, -1, "b");
        lua_pushnumber(vm, color.a);
        lua_setfield(vm, -1, "a");
        //+1
    }

}

#endif
