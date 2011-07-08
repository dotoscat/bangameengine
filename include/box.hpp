//box.hpp
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

#ifndef _bange_box_
#define _bange_box_

#include <SFML/Graphics.hpp>
#include <lua5.1/lua.hpp>

namespace bange{
    
    class box{
        private:
            lua_State *vm;
            sf::RenderWindow *window;
            bool error;
            sf::Key::Code escapekey;
        public:
            box(const char *);
            ~box();
            bool GetError();
            void Run();
            
            static void RegisterVM(lua_State *);
            
    };
    
}

static int IsKeyDown(lua_State *);
static int GetMouseX(lua_State *);
static int GetMouseY(lua_State *);

#endif
