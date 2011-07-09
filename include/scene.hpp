//scene.hpp
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

#ifndef _bange_scene_
#define _bange_scene_

#include <vector>
#include <chipmunk/chipmunk.h>
#include <base.hpp>

namespace bange{
    
    class scene: public bange::base{
        private:
            cpSpace *space;
            std::vector<int> layers;
        public:
            mutable bool physics;
        public:
            scene(int);
            bool NewIndex(lua_State *, const char *){};
            bool Index(lua_State *, const char *){};
            void Clean(lua_State *);
            ~scene();
            
            static void RegisterVM(lua_State *);
            
    };
    
    static int NewScene(lua_State *);
    
}

#endif
