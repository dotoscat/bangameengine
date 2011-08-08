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
   
#include <layertilemap.hpp>
#include <tile.hpp>

bange::tilemap::tilemap(int width, int height, float widthtile, float heighttile){
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

bool bange::tilemap::NewIndex(lua_State *vm, const char *key){
}
            
bool bange::tilemap::Index(lua_State *vm, const char *key){
}

void bange::tilemap::Clean(lua_State *vm){
    std::vector< std::vector<int> >::iterator arow;
    std::vector<int>::iterator acol;
    for (arow = tiles.begin(); arow != tiles.end(); arow++){
        for (acol = (*arow).begin(); acol != (*arow).end(); acol++){
            luaL_unref(vm, LUA_REGISTRYINDEX, *acol);
        }
    }
    lua_gc(vm, LUA_GCCOLLECT, 0);
}

void bange::tilemap::Process(sf::Uint32 time, sf::RenderTarget &rendertarget, std::map<const void *, int> &views, lua_State *vm){
    renderimage.Create(rendertarget.GetWidth(), rendertarget.GetHeight());
    std::map<const void *, int>::iterator aview;
    bange::proxy *proxy = NULL;
    bange::tile *tile = NULL;s
    rendertarget.SetView( rendertarget.GetDefaultView() );
    for (aview = views.begin(); aview != views.end(); aview++){
        bange::view *view = *static_cast<const bange::view *>(aview->first)
        sf::Vector2f center = view->GetCenter();
        sf::Vector2d size = view->GetSize();
        int starttilex = (int)center.x / widthtile;
        int statttiley = (int)center.y / heighttile;
        //draw things on the renderimage
        renderimage.Clear();
        for (int y = starttiley; y < tiles.size(); y += 1){
            for (int x = starttilex; x < tiles[y][x].size(); x += 1){
                if (tiles[y][x] == LUA_REFNIL){
                    continue;}
                lua_rawgeti(vm, LUA_REGISTRYINDEX, tiles[y][x]);
                proxy = static_cast<bange::proxy *>( lua_touserdata(vm, -1) );
                bange::tile *tile = static_cast<bange::tile *>(proxy->object);
                lua_pop(vm, 1);//Pop proxy
                if (tile->sprite != NULL){
                    renderimage.Draw(*tile->sprite);
                }
            }
        }
        renderimage.Display();
        //Set view to render target. Then draw the sprite with the tilemap rendered.
        sprite.SetImage(renderimage.GetImage());
        rendertarget.draw(sprite);
    }
}

int bange::tilemap_BuildTile(lua_State *vm){
}
