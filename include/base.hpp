//base.hpp
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

#ifndef _bange_base_
#define _bange_base_

#include <lua5.1/lua.hpp>

namespace bange{

    class base{
        public:
            virtual bool NewIndex(lua_State *, const char *) = 0;//Set attributes
            virtual bool Index(lua_State *, const char *) = 0;//Get attributes, request methods
            virtual void Clean(lua_State *){};//Some classes doesn't need clean
            virtual ~base(){};
    };

    struct proxy{
        bange::base *object;
        
        static void RegisterVM(lua_State *);//Just for arrange the code
    };
    
    
    bange::proxy *BuildProxy(lua_State *, bange::base *);//+1

    static int proxy_newindex(lua_State *);
    static int proxy_index(lua_State *);
    static int proxy_gc(lua_State *);

}

#endif
