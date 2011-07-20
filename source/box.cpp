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
#include <physfs.h>
#include <box.hpp>
#include <register.hpp>
#include <scene.hpp>
#include <view.hpp>

bange::box::box(const char *config){
    error = false;
    window = NULL;
    this->escapekey = sf::Keyboard::Escape;
    vm = luaL_newstate();
    bange::PrepareVM(vm);
    if (luaL_dofile(vm, config)){
        std::cout << "bange(lua): Error reading config file \"" << config << "\": " << lua_tostring(vm, -1) << std::endl;
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
    sf::ContextSettings contextsettings;
    //Create window
    window = new sf::RenderWindow(videomode, title, windowstyle, contextsettings);
    //Set FPS
    lua_Number FPS = 60;
    vm::GetNumber(vm, "FPS", FPS);
    window->SetFramerateLimit( static_cast<unsigned int>(FPS) );
    //Set KeyRepeat
    int keyrepeat = 0;
    vm::GetBoolean(vm, "KeyRepeat", keyrepeat);
    window->EnableKeyRepeat((bool)keyrepeat);
    //Set VerticalSync
    int verticalsync = 0;
    vm::GetBoolean(vm, "VerticalSync", verticalsync);
    window->EnableVerticalSync((bool)verticalsync);
    //Set EscapeKey
    lua_Number escapekey = 0;
    if (vm::GetNumber(vm, "EscapeKey", escapekey)){
        this->escapekey = static_cast<sf::Keyboard::Key>(escapekey);}
    //Store in lua environment this box
    lua_pushlightuserdata(vm, this);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::box");
    //Store in lua environment box's window
    lua_pushlightuserdata(vm, this->window);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::box::window");
    //Add packages
    if (bange::vm::GetTable(vm, "Packages")){
        lua_pushnil(vm);
        while(lua_next(vm, -2)){
            if (!lua_isstring(vm, -1)){
                lua_pop(vm, 1);
                continue;
            }
            if (PHYSFS_addToSearchPath(lua_tostring(vm, -1), 0) == 0){
                std::cout << "bange(physfs): " << lua_tostring(vm, -1) << ": " << PHYSFS_getLastError() << std::endl;
            }
            //next
            lua_pop(vm, 1);
        }
        lua_pop(vm, 1);
    }
    //Execute the run file
    char runfile[128] = "run.lua";
    vm::GetString(vm, "Run", runfile, 128);
    luaL_openlibs(vm);
    if (luaL_dofile(vm, runfile)){
        std::cout << "bange(lua): Error reading run file \"" << runfile << "\": " << lua_tostring(vm, -1) << std::endl;
        error = true;
        return;
    }
}

bange::box::~box(){
    std::cout << "bange(lua): vm top: " << lua_gettop(vm) << std::endl;
    lua_close(vm);
    if (window != NULL){
        delete window;}
}

bool bange::box::GetError(){
    return error;}

void bange::box::Run(){
    sf::Event event;
    bange::proxy *proxy = NULL;
    bange::scene *scene = NULL;
    bange::view *view = NULL;
    int indexscene = -1;
    while(window->IsOpened()){
        
        lua_getglobal(vm, "bange");
        lua_getfield(vm, -1, "Exit");
        if (!lua_isnil(vm, -1) && lua_isboolean(vm, -1) && lua_toboolean(vm, 1)){
            lua_pop(vm, 2);
            window->Close();
            continue;
        }
        lua_pop(vm, 1);
        
        while(window->PollEvent(event)){
            if (event.Type == sf::Event::Closed){
                window->Close();}
            else if (event.Type == sf::Event::KeyPressed && event.Key.Code == escapekey){
                window->Close();}
        }
        
        //Process the scenes
        lua_getfield(vm, -1, "Scenes");
        if (lua_istable(vm, -1)){
            lua_pushnil(vm);
            
            while(lua_next(vm, -2)){
                if (!lua_isuserdata(vm, -1)){
                    lua_pop(vm, 1);
                    continue;
                }
                proxy = static_cast<bange::proxy *>(lua_touserdata(vm, -1));
                scene = dynamic_cast<bange::scene *>(proxy->object);
                if (scene == NULL){
                    lua_pop(vm, 1);
                    continue;
                }
                scene->Process(lua_gettop(vm), window->GetFrameTime(), *window, vm);
                lua_pop(vm, 1);//next
            }
            
        }
        lua_pop(vm, 1);
        //---
        
        window->Clear();
        //Process the view
        lua_getfield(vm, -1, "Views");
        if (lua_istable(vm, -1)){
            lua_pushnil(vm);
            
            while(lua_next(vm, -2)){
                if (!lua_isuserdata(vm, -1)){
                    lua_pop(vm, 1);
                    continue;
                }
                proxy = static_cast<bange::proxy *>(lua_touserdata(vm, -1));
                view = dynamic_cast<bange::view *>(proxy->object);
                if (view == NULL || (view != NULL && view->scene == LUA_REFNIL) ){
                    lua_pop(vm, 1);
                    continue;
                }
                window->SetView(*view);
                lua_rawgeti(vm, LUA_REGISTRYINDEX, view->scene);
                scene = static_cast<bange::scene *>(static_cast<bange::proxy *>(lua_touserdata(vm, -1))->object);
                //scene->Draw(*window, vm);
                lua_pop(vm, 2);//Scene and next
            }
            
        }
        lua_pop(vm, 1);
        window->Display();
        
        lua_pop(vm, 1);
        
    }
}

void bange::box::RegisterVM(lua_State *vm){
    luaL_Reg functions[] = {
    {"IsKeyPressed", bange::IsKeyPressed},
    {"GetMousePosition", bange::GetMousePosition},
    {"GetFrameTime", bange::GetFrameTime},
    NULL};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
}

static int bange::IsKeyPressed(lua_State *vm){
    //keycode -> bool
    if (sf::Keyboard::IsKeyPressed( static_cast<sf::Keyboard::Key>(lua_tonumber(vm, 1)) ) ){
        lua_pushboolean(vm, 1);
    }else{
        lua_pushboolean(vm, 0);}
    return 1;
}

static int bange::GetMousePosition(lua_State *vm){
    //-> table {x, y}
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box::window");
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(lua_touserdata(vm, -1));
    lua_pop(vm, 1);
    sf::Vector2i position = sf::Mouse::GetPosition(*window);
    lua_createtable(vm, 0, 2);
    lua_pushnumber(vm, static_cast<lua_Number>(position.x) );
    lua_setfield(vm, -1, "x");
    lua_pushnumber(vm, static_cast<lua_Number>(position.y) );
    lua_setfield(vm, -1, "y");
    return 1;
}

static int bange::GetFrameTime(lua_State *vm){
    //->number
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box::window");
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(lua_touserdata(vm, -1));
    lua_pop(vm, 1);
    lua_pushnumber(vm, window->GetFrameTime());
    return 1;
}
