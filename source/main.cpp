//main.cpp
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
#include <cstdlib>
#include <cstring>
#include <physfs.h>
#include <chipmunk/chipmunk.h>
#include <box.hpp>

main(int argc, char *argv[]){
    if (PHYSFS_init(argv[0]) == 0){
        std::cout << "bange(physfs): " << PHYSFS_getLastError() << std::endl;
        return EXIT_FAILURE;
    }
    cpInitChipmunk();
    bange::box *box = NULL;
    if (argc > 1){
        box = new bange::box(argv[1]);
    }
    else{
        box = new bange::box("config.lua");
    }
    if (!box->GetError()){
        box->Run();}
    delete box;
    if (PHYSFS_deinit() == 0){
        std::cout << "bange(physfs): " << PHYSFS_getLastError() << std::endl;
        return EXIT_FAILURE;
    }
    if (box->GetError()){
        return EXIT_FAILURE;}
    return EXIT_SUCCESS;
}
