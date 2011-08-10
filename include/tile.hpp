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
   
#ifndef _bange_tile_
#define _bange_tile_

#include <lua5.1/lua.hpp>
#include <SFML/Graphics.hpp>
#include <base.hpp>
#include <object.hpp>

namespace bange{
    
    class tile: public bange::base{
        sf::Vector2f position;
        public:
            mutable bange::sprite *sprite;
        public:
            tile(float, float);
            ~tile();
            bool NewIndex(lua_State *, const char *);
            bool Index(lua_State *, const char *);
            void Clean(lua_State *);
            void Process(sf::Uint32, lua_State *);
            
            bool BuildSprite();
        
        public:
            static void RegisterVM(lua_State *);

    };
    
    int tile_BuildSprite(lua_State *);
    
}

#endif
   