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
#include <object.hpp>
#include <image.hpp>
#include <aux.hpp>

bange::sprite::sprite(){
    thedrawable = this;
    image = LUA_REFNIL;
    animation = NULL;
}

bool bange::sprite::NewIndex(lua_State *vm, const char *key){
    if (this->bange::object::NewIndex(vm, key)){
        return true;}
    
    if (animation != NULL && animation->NewIndex(vm, key)){
        return true;}
    
    if (strcmp("image", key) == 0){
        
        bange::proxy *proxyimage = NULL;
        proxyimage = static_cast<bange::proxy *>( lua_touserdata(vm, 3) );
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
    else if ( strcmp("subrect", key) == 0 ){
        
        if (!lua_istable(vm, 3)){
            std::cout << this << ".subrect -> value isn't a valid table" << std::endl;
            return true;
        }
        
        this->SetSubRect(bange::TableTosfIntRect(3, vm));
    }
    
    return true;
}

bool bange::sprite::Index(lua_State *vm, const char *key){
    if (this->bange::object::Index(vm, key)){
        return true;}
    
    if (animation != NULL && animation->Index(vm, key)){
        return true;}
    
    if ( strcmp("image", key) == 0 ){
        lua_rawgeti(vm, LUA_REGISTRYINDEX, this->image);
        return true;
    }
    else if ( strcmp("subrect", key) == 0 ){
        bange::sfIntRectToTable(this->GetSubRect(), vm);
        return true;
    }
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::sprite::");
    lua_getfield(vm, -1, key);
    return true;
}

void bange::sprite::Clean(lua_State *vm){
    this->bange::object::Clean(vm);
    luaL_unref(vm, LUA_REGISTRYINDEX, this->image);
    if (animation != NULL){
        animation->Clean(vm);}
}

void bange::sprite::Animate(){
    if (animation != NULL){
        return;}
    animation = new bange::animation(static_cast<sf::Sprite *>(this));
}

void bange::sprite::Process(sf::Uint32 time, lua_State *vm){
    if (animation != NULL){
        animation->Process(time, vm);}
}

int bange::sprite::sprite_Animate(lua_State *vm){
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_touserdata(vm, 1) );
    bange::sprite *sprite = static_cast<bange::sprite *>( proxy->object );
    sprite->Animate();
    return 0;
}
