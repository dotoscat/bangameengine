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
   
#include <object.hpp>
#include <image.hpp>

bange::sprite::sprite(){
    thedrawable = this;
    image = LUA_REFNIL;
}

bool bange::sprite::NewIndex(lua_State *vm, const char *key){
    if (this->bange::object::NewIndex(vm, key)){
        return true;}
    
    if (strcmp("image", key) == 0){
        
        bange::proxyimage *proxyimage = NULL;
        proxyimage = static_cast<bange::proxyimage *>( lua_touserdata(vm, 3) );
        if (proxyimage == NULL){
            std::cout << this << ".image -> Value isn't a valid image." << std::endl;
            return true;
        }
        bange::image *image = dynamic_cast<bange::image *>( proxyimage->object );
        if (image == NULL){
            std::cout << this << ".image -> Value isn't a valid image." << std::endl;
            return true;
        }
        this->SetImage(*image);
        luaL_unref(vm, LUA_REGISTRYINDEX, this->image);
        this->image = luaL_ref(vm, LUA_REGISTRYINDEX);
        
    }
    
    return true;
}

bool bange::sprite::Index(lua_State *vm, const char *key){
    if (this->bange::object::Index(vm, key)){
        return true;}
    
    if ( strcmp("image", key) == 0 ){
        lua_rawgeti(vm, LUA_REGISTRYINDEX, this->image);
        return true;
    }
    
    return false;
}
