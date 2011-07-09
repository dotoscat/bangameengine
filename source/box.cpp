//box.cpp
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
#include <box.hpp>
#include <register.hpp>
#include <scene.hpp>

bange::box::box(const char *config){
    error = false;
    window = NULL;
    this->escapekey = sf::Key::Escape;
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
    sf::WindowSettings windowsettings;
    //Create window
    window = new sf::RenderWindow(videomode, title, windowstyle, windowsettings);
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
    window->UseVerticalSync((bool)verticalsync);
    //Set EscapeKey
    lua_Number escapekey = 0;
    if (vm::GetNumber(vm, "EscapeKey", escapekey)){
        this->escapekey = static_cast<sf::Key::Code>(escapekey);}
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
        
        while(window->GetEvent(event)){
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
                scene->Process(lua_gettop(vm), window->GetFrameTime(), vm);
                lua_pop(vm, 1);//Next
            }
            
        }
        lua_pop(vm, 1);
        //---
        
        window->Clear();
        window->Display();
        
        lua_pop(vm, 1);
        
    }
}

void bange::box::RegisterVM(lua_State *vm){
    luaL_Reg functions[] = {
    {"IsKeyDown", bange::IsKeyDown},
    {"GetMouseX", bange::GetMouseX},
    {"GetMouseY", bange::GetMouseY},
    NULL};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
}

static int bange::IsKeyDown(lua_State *vm){
    //keycode -> bool
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box::window");
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(lua_touserdata(vm, -1));
    lua_pop(vm, 1);
    if (window->GetInput().IsKeyDown( static_cast<sf::Key::Code>(lua_tonumber(vm, 1)) ) ){
        lua_pushboolean(vm, 1);
    }else{
        lua_pushboolean(vm, 0);}
    return 1;
}

static int bange::GetMouseX(lua_State *vm){
    //-> number
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box::window");
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(lua_touserdata(vm, -1));
    lua_pop(vm, 1);
    lua_pushnumber(vm, window->GetInput().GetMouseX());
    return 1;
}

static int bange::GetMouseY(lua_State *vm){
    //-> number
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box::window");
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(lua_touserdata(vm, -1));
    lua_pop(vm, 1);
    lua_pushnumber(vm, window->GetInput().GetMouseY());
    return 1;
}
