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

#ifndef _bange_base_
#define _bange_base_

#include <lua5.1/lua.hpp>
#include <behavior.hpp>

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
        bange::behavior* behavior;
        
        //Function
        static void RegisterVM(lua_State *);//Just for arrange the code
    };
    
    
    bange::proxy *BuildProxy(lua_State *, bange::base *, bool=true);//+1

    int proxy_newindex(lua_State *);
    int proxy_index(lua_State *);
    int proxy_gc(lua_State *);

}

#endif
