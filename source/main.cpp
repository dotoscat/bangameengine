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
