//layerobject.hpp
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
            mutable cpSpace *space;
        public:
            layerobject(cpSpace *, size_t);
            bool NewIndex(lua_State *, const char *);
            bool Index(lua_State *, const char *);
            void Clean(lua_State *);
            void Process(int, float, lua_State *);
            void Draw(sf::RenderTarget &, lua_State *);
            bool AddObject(int);
            bool Filled(){
                if (nobjects == maxobjects){
                    return true;}
                return false;
            };

        public:
            static void RegisterVM(lua_State *);
            
    };
    
    static int layerobject_AddShapeRectangle(lua_State *);
    
}

#endif
