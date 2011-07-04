#include <box.hpp>

bange::box::box(){
    this->Initialize();
}

bange::box::box(const char *package){
    this->Initialize();
}

bange::box::~box(){
    lua_close(vm);
    delete window;
}

void bange::box::Initialize(){
    vm = luaL_newstate();
    window = new sf::RenderWindow(sf::VideoMode(640, 480), "bange");
}

void bange::box::Run(){
    sf::Event event;
    while(window->IsOpened()){
        
        while(window->GetEvent(event)){
            if (event.Type == sf::Event::Closed){
                window->Close();}
        }
        
        window->Clear();
        window->Display();
        
    }
}
