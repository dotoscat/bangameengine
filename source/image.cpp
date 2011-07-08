//image.hpp
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

#include <iostream>
#include <physfs.h>
#include <image.hpp>

void bange::image::RegisterVM(lua_State *vm){
    luaL_Reg functions[] = {
    {"LoadImage", bange::LoadImage},
    NULL};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
}

static int bange::LoadImage(lua_State *vm){
    //string -> bange::image
    if (!lua_isstring(vm, 1) || (lua_isstring(vm, 1) && lua_isnumber(vm, 1)) ){
        std::cout << "bange.LoadImage: First argument must be a string." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if(lua_objlen(vm, 1) == 0){
        std::cout << "bange.LoadImage: The string is void." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    const char *filename = lua_tostring(vm, 1);
    if (PHYSFS_exists(filename) == 0){
        std::cout << "bange.LoadImage: " << filename << " doesn't exists." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    
    PHYSFS_sint64 length = 0, readed = 0;
    PHYSFS_File *file = PHYSFS_openRead(filename);
    length = PHYSFS_fileLength(file);
    char *byteimage = new char[length];
    while(PHYSFS_eof(file) == 0){
        readed += PHYSFS_read(file, byteimage, 1, length);
    }
    if (readed < length){
        std::cout << "bange.LoadImage(physfs): " << PHYSFS_getLastError() << std::endl;
        delete byteimage;
        PHYSFS_close(file);
        lua_pushnil(vm);
        return 1;
    }
    PHYSFS_close(file);
    
	bange::image *image = new bange::image;
	image->LoadFromMemory(byteimage, static_cast<std::size_t>(length));
    delete byteimage;
	bange::BuildProxy(vm, image);
    return 1;
}
