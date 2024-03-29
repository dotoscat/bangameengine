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
#include <cstdlib>
#include <cstring>
#include <physfs.h>
#include <box.hpp>

main(int argc, char *argv[]){
    if (PHYSFS_init(argv[0]) == 0){
        std::cout << "bange(physfs): " << PHYSFS_getLastError() << std::endl;
        return EXIT_FAILURE;
    }
    bange::box *box = NULL;
    if (argc > 1){
        box = new bange::box(argv[1], argc, argv);
    }
    else{
        box = new bange::box("config.lua", argc, argv);
    }
    if (!box->GetError()){
        box->Run();}
    if (box->GetError()){
        delete box;
        return EXIT_FAILURE;}
    delete box;
    if (PHYSFS_deinit() == 0){
        std::cout << "bange(physfs): " << PHYSFS_getLastError() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
