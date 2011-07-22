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
            sf::Keyboard::Key escapekey;
        public:
            box(const char *);
            ~box();
            bool GetError();
            void Run();
            
            static void RegisterVM(lua_State *);
            
    };
    
    static int IsKeyPressed(lua_State *);
    static int GetMousePosition(lua_State *);
    static int IsMouseButtonPressed(lua_State *);
    static int GetFrameTime(lua_State *);
    static int GetWidth(lua_State *);
    static int GetHeight(lua_State *);
    
}

#endif
