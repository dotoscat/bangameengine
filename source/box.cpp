#include <iostream>
#include <box.hpp>

bange::box::box(const char *config){
    error = false;
    window = NULL;
    vm = luaL_newstate();
    if (luaL_dofile(vm, config)){
        std::cout << "bange(lua): Error reading \"" << config << "\": " << lua_tostring(vm, -1) << std::endl;
        error = true;
        return;
    }
    luaL_openlibs(vm);
    sf::VideoMode videomode(640, 480);
    char title[128] = {0};
    unsigned long windowstyle = sf::Style::Close;
    sf::WindowSettings windowsettings;
    window = new sf::RenderWindow(videomode, title, windowstyle, windowsettings);
}

bange::box::~box(){
    lua_close(vm);
    if (window != NULL){
        delete window;}
}

bool bange::box::GetError(){
    return error;}

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
