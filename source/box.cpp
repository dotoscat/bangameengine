#include <box.hpp>

bange::box::box(){
    this->Initialize();
}

bange::box::box(const char *package){
    this->Initialize();
}

bange::box::~box(){
    lua_close(vm);
}

void bange::box::Initialize(){
    vm = luaL_newstate();
}
