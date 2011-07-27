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

#include <iostream>
#include <cstring>
#include <layer.hpp>

bool bange::layer::NewIndex(lua_State *vm, const char *key){
    if (strcmp(key, "visible") == 0 && lua_isboolean(vm, 3)){
        visible = static_cast<bool>(lua_toboolean(vm, 3));
        return true;
    }
    return false;
}

bool bange::layer::Index(lua_State *vm, const char *key){
    if (strcmp(key, "visible") == 0){
        lua_pushboolean(vm, static_cast<int>(visible));
        return true;
    }
    return false;
}
