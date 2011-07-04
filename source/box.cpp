#include <iostream>
#include <box.hpp>
#include <vm.hpp>

bange::box::box(const char *config){
    error = false;
    window = NULL;
    escapekey = sf::Key::Escape;
    vm = luaL_newstate();
    if (luaL_dofile(vm, config)){
        std::cout << "bange(lua): Error reading config file \"" << config << "\": " << lua_tostring(vm, -1) << std::endl;
        error = true;
        return;
    }
    char runfile[128] = "run.lua";
    vm::GetString(vm, "Run", runfile, 128);
    luaL_openlibs(vm);
    if (luaL_dofile(vm, runfile)){
        std::cout << "bange(lua): Error reading run file \"" << runfile << "\": " << lua_tostring(vm, -1) << std::endl;
        error = true;
        return;
    }
    //Get Window dimensions
    sf::VideoMode videomode(640, 480);
    //Get Title
    char title[128] = "BAN Game Engine";
    vm::GetString(vm, "Title", title, 128);
    //Set styles (fullscreen, close, resize, titlebar, none)
    unsigned long windowstyle = sf::Style::Close;
    //Set Window settings
    sf::WindowSettings windowsettings;
    //Create window
    window = new sf::RenderWindow(videomode, title, windowstyle, windowsettings);
    //Set FPS
    lua_Number FPS = 60;
    vm::GetNumber(vm, "FPS", FPS);
    window->SetFramerateLimit( static_cast<unsigned int>(FPS) );
    //Set KeyRepeat
    //Set Key
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
            else if (event.Type == sf::Event::KeyPressed && event.Key.Code == escapekey){
                window->Close();}
        }
        
        window->Clear();
        window->Display();
        
    }
}
