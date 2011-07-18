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

#ifndef _bange_scene_
#define _bange_scene_

#include <vector>
#include <chipmunk/chipmunk.h>
#include <base.hpp>
#include <behavior.hpp>
#include <layerobject.hpp>

namespace bange{
    
    class scene: public bange::base, public bange::behavior{
        private:
            int data;
            std::vector<int> layers;
        public:
            mutable cpSpace *space;
            mutable bool physics;
        public:
            scene(int);
            bool NewIndex(lua_State *, const char *);
            bool Index(lua_State *, const char *);
            void Clean(lua_State *);
            void Process(int, float, lua_State *);
            void SetLayer(int, int, lua_State *);
            void Draw(sf::RenderTarget &, lua_State *);
            ~scene();
            
            static void RegisterVM(lua_State *);

    };
    
    static int NewScene(lua_State *);
    
    static int scene_SetLayerObject(lua_State *);
    
}

#endif
