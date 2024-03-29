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

#ifndef _bange_auxiliar_
#define _bange_auxiliar_

#include <SFML/Graphics.hpp>
#include <lua5.1/lua.hpp>

namespace bange{
    
    inline sf::Vector3f TableTosfVector3f(int indextable, lua_State *vm){
        sf::Vector3f vector;
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
        lua_getfield(vm, indextable, "z");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 3);
        }
        vector.z = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        return vector;
    }
    
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

    inline void sfVector2fToTable(sf::Vector2f vector, lua_State *vm){
        lua_createtable(vm, 0, 2);
        lua_pushnumber(vm, vector.x);
        lua_setfield(vm, -2, "x");
        lua_pushnumber(vm, vector.y);
        lua_setfield(vm, -2, "y");
        //+1
    }

    inline void sfVector3fToTable(sf::Vector3f vector, lua_State *vm){
        lua_createtable(vm, 0, 3);
        lua_pushnumber(vm, vector.x);
        lua_setfield(vm, -2, "x");
        lua_pushnumber(vm, vector.y);
        lua_setfield(vm, -2, "y");
        lua_pushnumber(vm, vector.z);
        lua_setfield(vm, -2, "z");
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
        lua_setfield(vm, -2, "r");
        lua_pushnumber(vm, color.g);
        lua_setfield(vm, -2, "g");
        lua_pushnumber(vm, color.b);
        lua_setfield(vm, -2, "b");
        lua_pushnumber(vm, color.a);
        lua_setfield(vm, -2, "a");
        //+1
    }

    inline sf::FloatRect TableTosfFloatRect(int indextable, lua_State *vm){
        sf::FloatRect rect;
        
        lua_getfield(vm, indextable, "Left");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 1);
        }
        rect.Left = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        
        lua_getfield(vm, indextable, "Top");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 2);
        }
        rect.Top = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        
        lua_getfield(vm, indextable, "Width");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 3);
        }
        rect.Width = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        
        lua_getfield(vm, indextable, "Height");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 4);
        }
        rect.Height = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        
        return rect;
    }

    inline sf::IntRect TableTosfIntRect(int indextable, lua_State *vm){
        sf::IntRect rect;
        
        lua_getfield(vm, indextable, "Left");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 1);
        }
        rect.Left = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        
        lua_getfield(vm, indextable, "Top");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 2);
        }
        rect.Top = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        
        lua_getfield(vm, indextable, "Width");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 3);
        }
        rect.Width = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        
        lua_getfield(vm, indextable, "Height");
        if (lua_isnil(vm, -1)){
            lua_pop(vm, 1);
            lua_rawgeti(vm, indextable, 4);
        }
        rect.Height = lua_tonumber(vm, -1);
        lua_pop(vm, 1);
        
        return rect;
    }

    inline void sfFloatRectToTable(sf::FloatRect rect, lua_State *vm){
        lua_createtable(vm, 0, 4);
        lua_pushnumber(vm, rect.Left);
        lua_setfield(vm, -2, "Left");
        lua_pushnumber(vm, rect.Top);
        lua_setfield(vm, -2, "Top");
        lua_pushnumber(vm, rect.Width);
        lua_setfield(vm, -2, "Width");
        lua_pushnumber(vm, rect.Height);
        lua_setfield(vm, -2, "Height");
    }

    inline void sfIntRectToTable(sf::IntRect rect, lua_State *vm){
        lua_createtable(vm, 0, 4);
        lua_pushnumber(vm, rect.Left);
        lua_setfield(vm, -2, "Left");
        lua_pushnumber(vm, rect.Top);
        lua_setfield(vm, -2, "Top");
        lua_pushnumber(vm, rect.Width);
        lua_setfield(vm, -2, "Width");
        lua_pushnumber(vm, rect.Height);
        lua_setfield(vm, -2, "Height");
    }

}

#endif
