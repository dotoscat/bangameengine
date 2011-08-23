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
   
#ifndef _bange_layerimagetilemap_
#define _bange_layerimagetilemap_

#include <vector>
#include <lua5.1/lua.hpp>
#include <layer.hpp>
#include <tile.hpp>
#include <drawable.hpp>

namespace bange{
    
    class layerimagetilemap: public bange::layer, public bange::drawable{
        sf::Sprite sprite;
        sf::RenderTexture rendertexture;
        int width, height;
        int widthtilemap, heighttilemap;
        std::vector<int> processtiles;
        float velx, vely;
        float velautoscrollx, velautoscrolly;
        float xautoscrollx, yautoscrolly;
        unsigned int flags;
        
        enum __flags{
            repeatx = 1 << 0,
            repeaty = 1 << 1,
            autoscrollx = 1 << 2,
            autoscrolly = 1 << 3,
        };
        
        public:
            mutable std::vector< std::vector<int> >tiles;
            mutable int widthtile, heighttile;
        public:
            layerimagetilemap(int width, int height, int widthtile, int heighttile);
            bool NewIndex(lua_State *, const char *);
            bool Index(lua_State *, const char *);
            void Clean(lua_State *);
            void Process(sf::Uint32, sf::RenderTarget &, std::map<const void *, int> &, lua_State *);
            
            void SetTile(int x, int y, int, lua_State *);
            
        public:
            static void RegisterVM(lua_State *);
        
    };
    
    int layerimagetilemap_BuildTile(lua_State *);
    
}

#endif
