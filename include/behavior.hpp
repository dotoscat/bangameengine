//behavior.hpp
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

#ifndef _bange_behavior_
#define _bange_behavior_

#include <map>
#include <lua5.1/lua.hpp>

namespace bange{
    
    class behavior{
        
        public:
        
            struct function{
                int thefunction;
                int data;
                float timeleft;
                float time;
                bool stop;
                
                function(): thefunction(LUA_REFNIL), data(LUA_REFNIL), timeleft(0.f), time(0.f), stop(false){};
                
            };
        
        public:
            mutable std::map<const void *, bange::behavior::function> functions;
        
        public:
            bool NewIndex(lua_State *, const char *){};
            bool Index(lua_State *, const char *);
            void Clean(lua_State *);
            void Process(int, float, lua_State *);

            static void RegisterVM(lua_State *);
        
    };
    
    static int behavior_AddFunction(lua_State *);
    static int behavior_StopFunction(lua_State *);
    
}

#endif
