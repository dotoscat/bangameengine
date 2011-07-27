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

#ifndef _bange_layerobject_
#define _bange_layerobject_

#include <vector>
#include <chipmunk/chipmunk.h>
#include <layer.hpp>

namespace bange{
    
    class layerobject: public bange::layer{
        private:
            size_t maxobjects;
            size_t nobjects;
            size_t iterations;
            size_t position;
            std::vector<int> objects;
        public:
            layerobject(size_t);
            bool NewIndex(lua_State *, const char *);
            bool Index(lua_State *, const char *);
            void Clean(lua_State *);
            void Process(sf::Uint32, sf::RenderTarget &, std::map<const void *, int> &, lua_State *);
            bool AddObject(int);
            bool Filled(){
                if (nobjects == maxobjects){
                    return true;}
                return false;
            };
            
    };
    
    static int layerobject_AddText(lua_State *);
    static int layerobject_AddShapeRectangle(lua_State *);
    static int layerobject_AddShapeCircle(lua_State *);
    static int layerobject_AddShapeLine(lua_State *);
    
}

#endif
