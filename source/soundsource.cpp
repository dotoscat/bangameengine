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

#include <cstring>   
#include <soundsource.hpp>
#include <auxiliar.hpp>

void bange::soundsource::SetSoundSource(sf::SoundSource *thesource){
    this->thesource = thesource;
}

bool bange::soundsource::NewIndex(lua_State *vm, const char *key){

    if ( strcmp("pitch", key) == 0){
        thesource->SetPitch(lua_tonumber(vm, 3));
        return true;
    }
    else if( strcmp("volume", key) == 0){
        thesource->SetVolume(lua_tonumber(vm, 3));
        return true;
    }
    else if( strcmp("position", key) == 0){
        thesource->SetPosition( bange::TableTosfVector3f(3, vm) );
        return true;
    }
    else if( strcmp("relativetolistener", key) == 0){
        thesource->SetRelativeToListener((bool)lua_toboolean(vm, 3));
        return true;
    }
    else if( strcmp("mindistance", key) == 0){
        thesource->SetMinDistance(lua_tonumber(vm, 3));
        return true;
    }
    else if( strcmp("attenuation", key) == 0){
        thesource->SetAttenuation(lua_tonumber(vm, 3));
        return true;
    }
    
    return false;
    
}

bool bange::soundsource::Index(lua_State *vm, const char *key){
        
    if( strcmp("pitch", key) == 0){
        lua_pushnumber(vm, thesource->GetPitch());
        return true;
    }
    else if( strcmp("volume", key) == 0){
        lua_pushnumber(vm, thesource->GetVolume());
        return true;
    }
    else if( strcmp("position", key) == 0){
        bange::sfVector3fToTable(thesource->GetPosition(), vm);
        return true;
    }
    else if( strcmp("relativetolistener", key) == 0){
        lua_pushboolean(vm, (int)thesource->IsRelativeToListener());
        return true;
    }
    else if( strcmp("mindistance", key) == 0){
        lua_pushnumber(vm, thesource->GetMinDistance());
        return true;
    }
    else if( strcmp("attenuation", key) == 0){
        lua_pushnumber(vm, thesource->GetAttenuation());
        return true;
    }
    
    return false;
}
