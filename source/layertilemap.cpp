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
#include <layertilemap.hpp>
#include <tile.hpp>
#include <view.hpp>

void bange::layertilemap::RegisterVM(lua_State *vm){
    luaL_Reg methods[] = {
    {"BuildTile", bange::layertilemap_BuildTile},
    {NULL, NULL}};
    lua_createtable(vm, 0, 1);
    luaL_register(vm, NULL, methods);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::layertilemap::");
}

bange::layertilemap::layertilemap(int width, int height, int widthtile, int heighttile){
    this->width = width;
    this->height = height;
    this->widthtile = widthtile;
    this->heighttile = heighttile;
    widthtilemap = width * widthtile;
    heighttilemap = height * heighttile;
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

bool bange::layertilemap::NewIndex(lua_State *vm, const char *key){
    if (this->bange::layer::NewIndex(vm, key)){
        return true;}
}
            
bool bange::layertilemap::Index(lua_State *vm, const char *key){
    if (this->bange::layer::Index(vm, key)){
        return true;}
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::layertilemap::");
    lua_getfield(vm, -1, key);
    return true;
}

void bange::layertilemap::Clean(lua_State *vm){
    std::vector< std::vector<int> >::iterator arow;
    std::vector<int>::iterator acol;
    for (arow = tiles.begin(); arow != tiles.end(); arow++){
        for (acol = (*arow).begin(); acol != (*arow).end(); acol++){
            luaL_unref(vm, LUA_REGISTRYINDEX, *acol);
        }
    }
    lua_gc(vm, LUA_GCCOLLECT, 0);
}

void bange::layertilemap::Process(sf::Uint32 time, sf::RenderTarget &rendertarget, std::map<const void *, int> &views, lua_State *vm){
    if (rendertexture.GetWidth() != rendertarget.GetWidth() || rendertexture.GetHeight() != rendertarget.GetHeight()){
        rendertexture.Create(rendertarget.GetWidth(), rendertarget.GetHeight());
    }
    std::map<const void *, int>::iterator aview;
    bange::proxy *proxy = NULL;
    bange::tile *tile = NULL;
    for (int i = 0; i < processtiles.size(); i += 1){
        lua_rawgeti(vm, LUA_REGISTRYINDEX, processtiles[i]);
        proxy = static_cast<bange::proxy *>( lua_touserdata(vm, -1) );
        lua_pop(vm, 1);
        proxy->behavior->Process(lua_gettop(vm), time, vm);
        tile = static_cast<bange::tile *>(proxy->object);
        //tile->Process(time, vm);
    }
    rendertarget.SetView( rendertarget.GetDefaultView() );
    for (aview = views.begin(); aview != views.end(); aview++){
        const bange::view *view = static_cast<const bange::view *>(aview->first);
        sf::Vector2f center = view->GetCenter();
        sf::Vector2f size = view->GetSize();
        int starttilex = ((int)center.x-(int)size.x/2) / widthtile;
        if (starttilex < 0){
            starttilex = 0;}
        int starttiley = ((int)center.y-(int)size.y/2) / heighttile;
        if (starttiley < 0){
            starttiley = 0;}
        int endtilex = ((int)center.x+(int)size.x/2) / widthtile;
        if (endtilex >= width){
            endtilex = width-1;}
        int endtiley = ((int)center.y+(int)size.y/2) / heighttile;
        if (endtiley >= height){
            endtiley = height-1;}
        //draw things on the texture
        rendertexture.SetView(*view);
        rendertexture.Clear();
        for (int y = starttiley; y <= endtiley; y += 1){
            for (int x = starttilex; x <= endtilex; x += 1){
                if (tiles[y][x] == LUA_REFNIL){
                    continue;}
                lua_rawgeti(vm, LUA_REGISTRYINDEX, tiles[y][x]);
                proxy = static_cast<bange::proxy *>( lua_touserdata(vm, -1) );
                bange::tile *tile = static_cast<bange::tile *>(proxy->object);
                lua_pop(vm, 1);//Pop proxy
                if (tile->sprite != NULL){
                    rendertexture.Draw(*tile->sprite);
                }
            }
        }
        rendertexture.Display();
        //Set view to render target. Then draw the sprite with the tilemap rendered.
        sprite.SetTexture(rendertexture.GetTexture());
        rendertarget.Draw(sprite);
    }
}

void bange::layertilemap::SetTile(int x, int y, int ref, lua_State *vm){
    tiles[y][x] = ref;
    lua_rawgeti(vm, LUA_REGISTRYINDEX, ref);
    processtiles.push_back(luaL_ref(vm, LUA_REGISTRYINDEX));
}

int bange::layertilemap_BuildTile(lua_State *vm){
    //x, y -> tile
    bange::proxy *proxy = static_cast<bange::proxy *>( lua_touserdata(vm, 1) );
    bange::layertilemap *layertilemap = static_cast<bange::layertilemap *>(proxy->object);
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
    if (layertilemap->tiles[y][x] != LUA_REFNIL){
        std::cout << proxy << ":BuildTile() -> Tile " << x << ":" << y << ", already builded." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    bange::tile *tile = new bange::tile(x*layertilemap->widthtile, y*layertilemap->heighttile);
    bange::BuildProxy(vm, tile);
    lua_pushvalue(vm, -1);
    layertilemap->SetTile(x, y, luaL_ref(vm, LUA_REGISTRYINDEX), vm);
    return 1;
}
