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
        box = new bange::box(argv[1]);
    }
    else{
        box = new bange::box();
    }
    delete box;
    if (PHYSFS_deinit() == 0){
        std::cout << "bange(physfs): " << PHYSFS_getLastError() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
