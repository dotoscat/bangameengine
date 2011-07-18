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

#ifndef _bange_behavior_
#define _bange_behavior_

#include <map>
#include <SFML/Config.hpp>
#include <lua5.1/lua.hpp>

namespace bange{
    
    class behavior{
        
        public:
        
            struct function{
                int thefunction;
                int data;
                sf::Uint32 timeleft;
                sf::Uint32 time;
                bool stop;
                
                function(): thefunction(LUA_REFNIL), data(LUA_REFNIL), timeleft(0.f), time(0.f), stop(false){};
                
            };
        
        public:
            mutable std::map<const void *, bange::behavior::function> functions;
        
        public:
            bool NewIndex(lua_State *, const char *){return false;};
            bool Index(lua_State *, const char *);
            void Clean(lua_State *);
            void Process(int, sf::Uint32, lua_State *);

            static void RegisterVM(lua_State *);
        
    };
    
    static int behavior_AddFunction(lua_State *);
    static int behavior_StopFunction(lua_State *);
    
}

#endif
