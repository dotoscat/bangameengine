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
   
#include <tile.hpp>

bange::tile::tile(float x, float y){
    position.x = x;
    position.y = y;
    sprite = NULL;
}

bange::tile::~tile{
    if (sprite != NULL){
        delete sprite;}
}

bool bange::tile::NewIndex(lua_State *vm, const char *key){
    if (sprite != NULL && sprite->NewIndex(vm, key)){
        return true;}
    return false;
}

bool bange::tile::Index(lua_State *vm, const char *key){
    if (sprite != NULL && sprite->Index(vm, key)){
        return true;}
    return false;
}

void bang::tile::Clean(lua_State *vm){
    if (sprite != NULL){
        sprite->Clean(vm);}
}
