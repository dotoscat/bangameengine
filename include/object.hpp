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

#ifndef _bange_object_
#define _bange_object_

#include <lua5.1/lua.hpp>
#include <base.hpp>
#include <behavior.hpp>
#include <drawable.hpp>

namespace bange{
    
    class object: public bange::base, public bange::drawable, public bange::behavior{
        protected:
            int data;
        public:
            mutable bool del;
            mutable bool visible;
        public:
            object();
            bool NewIndex(lua_State *, const char *);
            bool Index(lua_State *, const char *);
            void Clean(lua_State *);
            void Process(int, sf::Uint32, lua_State *);
            virtual ~object(){};
            
            static void RegisterVM(lua_State *);

    };

    class shape: public bange::object, public sf::Shape{
        public:
            shape();
    };
    
    class text: public bange::object, public sf::Text{
        public:
            text(){thedrawable=this;};
            bool NewIndex(lua_State *, const char *);
            bool Index(lua_State *, const char *);
    };
    
}

#endif
