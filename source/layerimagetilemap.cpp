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
#include <cmath>
#include <layerimagetilemap.hpp>
#include <tile.hpp>
#include <view.hpp>
#include <object.hpp>
#include <auxiliar.hpp>

void bange::layerimagetilemap::RegisterVM(lua_State *vm){
    luaL_Reg methods[] = {
    {"BuildTile", bange::layerimagetilemap_BuildTile},
    {NULL, NULL}};
    lua_createtable(vm, 0, 1);
    luaL_register(vm, NULL, methods);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::layerimagetilemap::");
}

bange::layerimagetilemap::layerimagetilemap(int width, int height, int widthtile, int heighttile){
    this->width = width;
    this->height = height;
    this->widthtile = widthtile;
    this->heighttile = heighttile;
    velx = 0;
    vely = 0;
    xautoscrollx = 0;
    yautoscrolly = 0;
    velautoscrollx = 0;
    velautoscrolly = 0;
    widthtilemap = width * widthtile;
    heighttilemap = height * heighttile;
    rendertexture.Create(widthtilemap, heighttilemap);
    flags = 0;
    tiles.reserve(height);
    for (int i = 0; i < height; i += 1){
        std::vector<int> coltiles;
        coltiles.reserve(width);
        for (int i2 = 0; i2 < width; i2 += 1){
            coltiles.push_back(LUA_REFNIL);
        }
        tiles.push_back(coltiles);
    }
}

bool bange::layerimagetilemap::NewIndex(lua_State *vm, const char *key){
    if (this->bange::layer::NewIndex(vm, key)){
        return true;}
    
    if ( strcmp("repeatx", key) == 0){
        int repeatx = lua_toboolean(vm, 3);
        if (repeatx){
            flags |= bange::layerimagetilemap::repeatx;}
        else if (!repeatx && (flags & bange::layerimagetilemap::repeatx) == bange::layerimagetilemap::repeatx){
            flags ^= bange::layerimagetilemap::repeatx;}
    }
    else if ( strcmp("repeaty", key) == 0){
        int repeaty = lua_toboolean(vm, 3);
        if (repeaty){
            flags |= bange::layerimagetilemap::repeaty;}
        else if (!repeaty && (flags & bange::layerimagetilemap::repeaty) == bange::layerimagetilemap::repeaty){
            flags ^= bange::layerimagetilemap::repeaty;}
    }
    else if ( strcmp("autoscrollx", key) == 0){
        int autoscrollx = lua_toboolean(vm, 3);
        if (autoscrollx){
            flags |= bange::layerimagetilemap::autoscrollx;}
        else if (!autoscrollx && (flags & bange::layerimagetilemap::autoscrollx) == bange::layerimagetilemap::autoscrollx){
            flags ^= bange::layerimagetilemap::autoscrollx;}
    }
    else if ( strcmp("autoscrolly", key) == 0){
        int autoscrolly = lua_toboolean(vm, 3);
        if (autoscrolly){
            flags |= bange::layerimagetilemap::autoscrolly;}
        else if (!autoscrolly && (flags & bange::layerimagetilemap::autoscrolly) == bange::layerimagetilemap::autoscrolly){
            flags ^= bange::layerimagetilemap::autoscrolly;}
    }
    else if (strcmp("velx", key) == 0){
        velx = lua_tonumber(vm, 3);
    }
    else if (strcmp("vely", key) == 0){
        vely = lua_tonumber(vm, 3);
    }
    else if (strcmp("velautoscrollx", key) == 0){
        velautoscrollx = lua_tonumber(vm, 3);
    }
    else if (strcmp("velautoscrolly", key) == 0){
        velautoscrolly = lua_tonumber(vm, 3);
    }
    else if (strcmp("posx", key) == 0){
        this->sprite.SetX(lua_tonumber(vm, 3));
    }
    else if (strcmp("posy", key) == 0){
        this->sprite.SetY(lua_tonumber(vm, 3));
    }
    return true;
}
            
bool bange::layerimagetilemap::Index(lua_State *vm, const char *key){
    if (this->bange::layer::Index(vm, key)){
        return true;}
    
    if ( strcmp("repeatx", key) == 0){
        if ((flags & bange::layerimagetilemap::repeatx) == bange::layerimagetilemap::repeatx){
            lua_pushboolean(vm, 1);}
        else{
            lua_pushboolean(vm, 0);}
        return true;
    }
    else if ( strcmp("repeaty", key) == 0){
        if ((flags & bange::layerimagetilemap::repeatx) == bange::layerimagetilemap::repeaty){
            lua_pushboolean(vm, 1);}
        else{
            lua_pushboolean(vm, 0);}
        return true;
    }
    else if ( strcmp("autoscrollx", key) == 0){
        if ((flags & bange::layerimagetilemap::autoscrollx) == bange::layerimagetilemap::autoscrollx){
            lua_pushboolean(vm, 1);}
        else{
            lua_pushboolean(vm, 0);}
        return true;
    }
    else if ( strcmp("autoscrolly", key) == 0){
        if ((flags & bange::layerimagetilemap::autoscrolly) == bange::layerimagetilemap::autoscrolly){
            lua_pushboolean(vm, 1);}
        else{
            lua_pushboolean(vm, 0);}
        return true;
    }
    else if ( strcmp("velx", key ) == 0){
        lua_pushnumber(vm, velx);
        return true;
    }
    else if ( strcmp("vely", key ) == 0){
        lua_pushnumber(vm, vely);
        return true;
    }
    else if ( strcmp("velautoscrollx", key ) == 0){
        lua_pushnumber(vm, velautoscrollx);
        return true;
    }
    else if ( strcmp("velautoscrolly", key ) == 0){
        lua_pushnumber(vm, velautoscrolly);
        return true;
    }
    else if ( strcmp("posy", key) == 0){
        lua_pushnumber(vm, this->sprite.GetPosition().y);
        return true;
    }
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::layerimagetilemap::");
    lua_getfield(vm, -1, key);
    return true;
}

void bange::layerimagetilemap::Clean(lua_State *vm){
    std::vector< std::vector<int> >::iterator arow;
    std::vector<int>::iterator acol;
    for (arow = tiles.begin(); arow != tiles.end(); arow++){
        for (acol = (*arow).begin(); acol != (*arow).end(); acol++){
            luaL_unref(vm, LUA_REGISTRYINDEX, *acol);
        }
    }
    lua_gc(vm, LUA_GCCOLLECT, 0);
}

void bange::layerimagetilemap::Process(sf::Uint32 time, sf::RenderTarget &rendertarget, std::map<const void *, int> &views, lua_State *vm){
    std::map<const void *, int>::iterator aview;
    bange::proxy *proxy = NULL;
    bange::tile *tile = NULL;
    bange::sprite *sprite = NULL;
    for (int i = 0; i < processtiles.size(); i += 1){
        lua_rawgeti(vm, LUA_REGISTRYINDEX, processtiles[i]);
        proxy = static_cast<bange::proxy *>( lua_touserdata(vm, -1) );
        proxy->behavior->Process(lua_gettop(vm), time, vm);
        lua_pop(vm, 1);
        tile = static_cast<bange::tile *>(proxy->object);
        tile->Process(time, vm);
    }
    //Process the autoscroll
    float ctime = (float)time / 1000.f;
    if ( (flags & bange::layerimagetilemap::autoscrollx) == bange::layerimagetilemap::autoscrollx ){
        xautoscrollx += velautoscrollx * ctime;
        if ( fabs(xautoscrollx) > widthtilemap ){
            xautoscrollx = 0.f;
        }
    }
    if ( (flags & bange::layerimagetilemap::autoscrolly) == bange::layerimagetilemap::autoscrolly ){
        yautoscrolly += velautoscrolly * ctime;
        if ( fabs(yautoscrolly) > heighttilemap ){
            yautoscrolly = 0.f;
        }
    }
    //---
    //Draw all the tiles in rendertexture
    std::vector< std::vector<int> >::iterator arow;
    std::vector<int>::iterator acol;
    rendertexture.Clear();
    for (arow = tiles.begin(); arow != tiles.end(); arow++){
        for(acol = (*arow).begin(); acol != (*arow).end(); acol++){
            if ( (*acol) == LUA_REFNIL){
                continue;}
            lua_rawgeti(vm, LUA_REGISTRYINDEX, (*acol));
            proxy = static_cast<bange::proxy *>( lua_touserdata(vm, -1) );
            tile = static_cast<bange::tile *>(proxy->object);
            lua_pop(vm, 1);//proxy
            if (tile->sprite == LUA_REFNIL){
                continue;}
            lua_rawgeti(vm, LUA_REGISTRYINDEX, tile->sprite);
            proxy = static_cast<bange::proxy *>( lua_touserdata(vm, -1) );//Reuse proxy is safe
            lua_pop(vm, 1);//proxy sprite
            sprite = static_cast<bange::sprite *>(proxy->object);
            rendertexture.Draw(*sprite);
        }
    }
    rendertexture.Display();
    
    //Now draw the tilemap's sprite with each view
    sf::Vector2f opos = this->sprite.GetPosition();
    rendertarget.SetView( rendertarget.GetDefaultView() );
    for (aview = views.begin(); aview != views.end(); aview++){
        const bange::view *view = static_cast<const bange::view *>(aview->first);
        sf::Vector2f center = view->GetCenter();
        sf::Vector2f size = view->GetSize();
        float startxview = center.x-size.x/2.f;
        float startyview = center.y-size.y/2.f;
        rendertarget.SetView(*view);
        //Draw the sprite with the tilemap rendered.
        this->sprite.SetTexture(rendertexture.GetTexture());
        //What...
        if (flags == 0){
            rendertarget.Draw(this->sprite);
        }
        else if ((flags & bange::layerimagetilemap::repeatx) == bange::layerimagetilemap::repeatx \
        && (flags & bange::layerimagetilemap::repeaty) != bange::layerimagetilemap::repeaty){
            float x = -(int(center.x * velx + xautoscrollx) % (int)widthtilemap) + startxview - widthtilemap;
            float posrepeatx = vely * center.y;
            this->sprite.SetY(posrepeatx + opos.y);
            for (; x < startxview+size.x; x += widthtilemap){
                this->sprite.SetX(x);
                rendertarget.Draw(this->sprite);
            }
        }
        else if ((flags & bange::layerimagetilemap::repeaty) == bange::layerimagetilemap::repeaty \
        && (flags & bange::layerimagetilemap::repeatx) != bange::layerimagetilemap::repeatx){
            float y = -(int(center.y * vely + yautoscrolly) % (int)heighttilemap) + startyview - heighttilemap;
            float posrepeaty = velx * center.x;
            this->sprite.SetX(posrepeaty + opos.x);
            for (; y < startyview+size.y; y += heighttilemap){
                this->sprite.SetY(y);
                rendertarget.Draw(this->sprite);
            }
        }
        else if ((flags & bange::layerimagetilemap::repeatx) == bange::layerimagetilemap::repeatx \
        && (flags & bange::layerimagetilemap::repeaty) == bange::layerimagetilemap::repeaty){
            float y = -(int(center.y * vely + yautoscrolly) % (int)heighttilemap) + startyview - heighttilemap;
            for(; y < startyview+size.y; y += heighttilemap){
                this->sprite.SetY(y);                            
                for (float x = -(int(center.x * velx + xautoscrollx) % (int)widthtilemap) + startxview - widthtilemap; x < startxview+size.x; x += widthtilemap){
                    this->sprite.SetX(x);
                    rendertarget.Draw(this->sprite);
                }
            }
        }
        this->sprite.SetPosition(opos);
    }
}

void bange::layerimagetilemap::SetTile(int x, int y, int ref, lua_State *vm){
    tiles[y][x] = ref;
    lua_rawgeti(vm, LUA_REGISTRYINDEX, ref);
    processtiles.push_back(luaL_ref(vm, LUA_REGISTRYINDEX));
}

int bange::layerimagetilemap_BuildTile(lua_State *vm){
    //x, y -> tile
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_touserdata(vm, 1) );
    bange::layerimagetilemap *layerimagetilemap = static_cast<bange::layerimagetilemap *>(proxy->object);
    int x = 0, y = 0;
    //0 is a valid index in arrays so...
    if (!lua_isnumber(vm, 2)){
        std::cout << proxy << ":BuildTile() -> First value isn't a valid number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    x = lua_tonumber(vm, 2);
    if (!lua_isnumber(vm, 3)){
        std::cout << proxy << ":BuildTile() -> Second value isn't a valid number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    y = lua_tonumber(vm, 3);
    if (layerimagetilemap->tiles[y][x] != LUA_REFNIL){
        std::cout << proxy << ":BuildTile() -> Tile " << x << ":" << y << ", already builded." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    bange::tile *tile = new bange::tile(x*layerimagetilemap->widthtile, y*layerimagetilemap->heighttile);
    bange::BuildProxy(vm, tile);
    lua_pushvalue(vm, -1);
    layerimagetilemap->SetTile(x, y, luaL_ref(vm, LUA_REGISTRYINDEX), vm);
    return 1;
}
