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
    mouseDelta = 0;
    JoystickConnected = -1;
    JoystickDisconnected = -1;
    mouseEntered = false;
    windowFocus = false;
    vm = luaL_newstate();
    bange::PrepareVM(vm);
    if (luaL_dofile(vm, config)){
        std::cout << "bange(lua): Error reading config file \"" << config << "\": " << lua_tostring(vm, -1) << std::endl;
        error = true;
        return;
    }
    //Get Window dimensions
    sf::VideoMode videomode(640, 480);
    lua_Number wh = 0;
    if (vm::GetNumber(vm, "Width", wh)){
        videomode.Width = wh;}
    if (vm::GetNumber(vm, "Height", wh)){
        videomode.Height = wh;}
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
    std::cout << "Texture maximum size: " << sf::Image::GetMaximumSize() << std::endl;
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
        lua_getfield(vm, 1, "Exit");
        if (!lua_isnil(vm, -1) && lua_isboolean(vm, -1) && lua_toboolean(vm, -1)){
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
            else if (event.Type == sf::Event::MouseWheelMoved){
                mouseDelta = event.MouseWheel.Delta;}
            else if (event.Type == sf::Event::JoystickConnected){
                JoystickConnected = (int)event.JoystickConnect.JoystickId;}
            else if (event.Type == sf::Event::JoystickDisconnected){
                JoystickDisconnected = (int)event.JoystickConnect.JoystickId;}
            else if (event.Type == sf::Event::MouseEntered){
                mouseEntered = true;}
            else if (event.Type == sf::Event::MouseLeft){
                mouseEntered = false;}
            else if (event.Type == sf::Event::GainedFocus){
                windowFocus = true;}
            else if (event.Type == sf::Event::LostFocus){
                windowFocus = false;}
                
        }
        
        window->Clear();
        //Process the scenes
        lua_getfield(vm, 1, "Run");
        
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
                proxy->behavior->Process(lua_gettop(vm), window->GetFrameTime(), vm);
                scene->Process(window->GetFrameTime(), *window, vm);
                lua_pop(vm, 1);//next
            }
            
        }
        lua_pop(vm, 1);
        //---
        window->Display();
        
        lua_pop(vm, 1);
        
        //Reset
        this->mouseDelta = 0;
        this->JoystickConnected = -1;
        this->JoystickDisconnected = -1;
        
    }
}

void bange::box::RegisterVM(lua_State *vm){
    luaL_Reg functions[] = {
    {"IsKeyPressed", bange::IsKeyPressed},
    {"GetMousePosition", bange::GetMousePosition},
    {"IsMouseButtonPressed", bange::IsMouseButtonPressed},
    {"GetMouseDelta", bange::GetMouseDelta},
    {"MouseInWindow", bange::MouseInWindow},
    {"JoystickConnected", bange::JoystickConnected},
    {"JoystickDisconnected", bange::JoystickDisconnected},
    {"IsJoystickConnected", bange::IsJoystickConnected},
    {"JoystickGetButtonCount", bange::JoystickGetButtonCount},
    {"JoystickHasAxis", bange::JoystickHasAxis},
    {"JoystickIsButtonPressed", bange::JoystickIsButtonPressed},
    {"JoystickGetAxisPosition", bange::JoystickGetAxisPosition},
    {"WindowHasFocus", bange::WindowHasFocus},
    {"GetFrameTime", bange::GetFrameTime},
    {"GetWidth", bange::GetWidth},
    {"GetHeight", bange::GetHeight},
    NULL};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
}

int bange::IsKeyPressed(lua_State *vm){
    //keycode -> bool
    if (sf::Keyboard::IsKeyPressed( static_cast<sf::Keyboard::Key>(lua_tonumber(vm, 1)) ) ){
        lua_pushboolean(vm, 1);
    }else{
        lua_pushboolean(vm, 0);}
    return 1;
}

int bange::GetMousePosition(lua_State *vm){
    //-> table {x, y}
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box::window");
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(lua_touserdata(vm, -1));
    lua_pop(vm, 1);
    sf::Vector2i position = sf::Mouse::GetPosition(*window);
    lua_createtable(vm, 0, 2);
    lua_pushnumber(vm, static_cast<lua_Number>(position.x) );
    lua_setfield(vm, -2, "x");
    lua_pushnumber(vm, static_cast<lua_Number>(position.y) );
    lua_setfield(vm, -2, "y");
    return 1;
}

int bange::IsMouseButtonPressed(lua_State *vm){
    //mousebutton -> bool
    if (sf::Mouse::IsButtonPressed( static_cast<sf::Mouse::Button>(lua_tonumber(vm, 1)) ) ){
        lua_pushboolean(vm, 1);
    }else{
        lua_pushboolean(vm, 0);}
    return 1;
}

int bange::GetMouseDelta(lua_State *vm){
    //-> number
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box");
    bange::box *box = static_cast<bange::box *>( lua_touserdata(vm, 1) );
    lua_pop(vm, 1);
    lua_pushnumber(vm, (lua_Number)box->mouseDelta);
    return 1;
}

int bange::MouseInWindow(lua_State *vm){
    //-> bool
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box");
    bange::box *box = static_cast<bange::box *>( lua_touserdata(vm, 1) );
    lua_pop(vm, 1);
    lua_pushboolean(vm, (int)box->mouseEntered);
    return 1;
}

int bange::JoystickConnected(lua_State *vm){
    //-> number
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box");
    bange::box *box = static_cast<bange::box *>( lua_touserdata(vm, 1) );
    lua_pop(vm, 1);
    lua_pushnumber(vm, (lua_Number)box->JoystickConnected);
    return 1;
}

int bange::JoystickDisconnected(lua_State *vm){
    //-> number
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box");
    bange::box *box = static_cast<bange::box *>( lua_touserdata(vm, 1) );
    lua_pop(vm, 1);
    lua_pushnumber(vm, (lua_Number)box->JoystickDisconnected);
    return 1;
}

int bange::IsJoystickConnected(lua_State *vm){
    //number -> bool
    if (!lua_isnumber(vm, 1)){
        std::cout << "bange.IsJoystickConnected() -> First argument isn't a valid number" << std::endl;
    }
    lua_Number joystick = lua_tonumber(vm, 1);
    bool connected = false;
    connected = sf::Joystick::IsConnected((unsigned int)joystick);
    lua_pushboolean(vm, (int)connected);
    return 1;
}

int bange::JoystickGetButtonCount(lua_State *vm){
    //number -> number
    if (!lua_isnumber(vm, 1)){
        std::cout << "bange.JoystickGetButtonCount() -> First argument isn't a valid number" << std::endl;
    }
    lua_Number joystick = lua_tonumber(vm, 1);
    lua_pushnumber(vm, (lua_Number)sf::Joystick::GetButtonCount( (unsigned int)joystick ) );
    return 1;
}

int bange::JoystickHasAxis(lua_State *vm){
    //number, number -> bool
    if (!lua_isnumber(vm, 1)){
        std::cout << "bange.JoystickHasAxis() -> First argument isn't a valid number" << std::endl;
    }
    if (!lua_isnumber(vm, 2)){
        std::cout << "bange.JoystickHasAxis() -> 2nd argument isn't a valid number" << std::endl;
    }
    bool hasaxis = sf::Joystick::HasAxis( (unsigned int)lua_tonumber(vm, 1), (sf::Joystick::Axis)lua_tonumber(vm, 2) );
    lua_pushboolean(vm, (int)hasaxis );
    return 1;
}

int bange::JoystickIsButtonPressed(lua_State *vm){
    //number, number -> bool
    if (!lua_isnumber(vm, 1)){
        std::cout << "bange.JoystickIsButtonPressed() -> First argument isn't a valid number" << std::endl;
    }
    if (!lua_isnumber(vm, 2)){
        std::cout << "bange.JoystickIsButtonPressed() -> 2nd argument isn't a valid number" << std::endl;
    }
    bool buttonpressed = sf::Joystick::IsButtonPressed( (unsigned int)lua_tonumber(vm, 1), (unsigned int)lua_tonumber(vm, 2) );
    lua_pushboolean(vm, (int)buttonpressed);
    return 1;
}

int bange::JoystickGetAxisPosition(lua_State *vm){
    //number, number -> number
    if (!lua_isnumber(vm, 1)){
        std::cout << "bange.JoystickGetAxisPosition() -> First argument isn't a valid number" << std::endl;
    }
    if (!lua_isnumber(vm, 2)){
        std::cout << "bange.JoystickGetAxisPosition() -> 2nd argument isn't a valid number" << std::endl;
    }
    float position = sf::Joystick::GetAxisPosition( (unsigned int)lua_tonumber(vm, 1), (sf::Joystick::Axis)lua_tonumber(vm, 2) );
    lua_pushnumber(vm, position);
    return 1;
}

int bange::WindowHasFocus(lua_State *vm){
    //-> bool
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box");
    bange::box *box = static_cast<bange::box *>( lua_touserdata(vm, 1) );
    lua_pop(vm, 1);
    lua_pushboolean(vm, (int)box->windowFocus);
    return 1;
}

int bange::GetFrameTime(lua_State *vm){
    //->number
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box::window");
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(lua_touserdata(vm, -1));
    lua_pop(vm, 1);
    lua_pushnumber(vm, window->GetFrameTime());
    return 1;
}

int bange::GetWidth(lua_State *vm){
    //->number
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box::window");
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(lua_touserdata(vm, -1));
    lua_pop(vm, 1);
    lua_pushnumber(vm, window->GetWidth());
    return 1;
}

int bange::GetHeight(lua_State *vm){
    //->number
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::box::window");
    sf::RenderWindow *window = static_cast<sf::RenderWindow *>(lua_touserdata(vm, -1));
    lua_pop(vm, 1);
    lua_pushnumber(vm, window->GetHeight());
    return 1;
}
