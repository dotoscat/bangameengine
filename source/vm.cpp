//vm.cpp
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

#include <vm.hpp>

void bange::vm::PrepareVM(lua_State *vm){
	using namespace bange::vm;
	using namespace sf::Key;
	using namespace sf::Mouse;
	using namespace sf::Joy;
    SetInt(vm, "KeyA", A);
    SetInt(vm, "KeyB", B);
    SetInt(vm, "KeyC", C);
    SetInt(vm, "KeyD", D);
    SetInt(vm, "KeyE", E);
    SetInt(vm, "KeyF", F);
    SetInt(vm, "KeyG", G);
    SetInt(vm, "KeyH", H);
    SetInt(vm, "KeyI", I);
    SetInt(vm, "KeyJ", J);
    SetInt(vm, "KeyK", K);
    SetInt(vm, "KeyL", L);
    SetInt(vm, "KeyM", M);
    SetInt(vm, "KeyN", N);
    SetInt(vm, "KeyO", O);
    SetInt(vm, "KeyP", P);
    SetInt(vm, "KeyQ", Q);
    SetInt(vm, "KeyR", R);
    SetInt(vm, "KeyS", S);
    SetInt(vm, "KeyT", T);
    SetInt(vm, "KeyU", U);
    SetInt(vm, "KeyV", V);
    SetInt(vm, "KeyW", W);
    SetInt(vm, "KeyX", X);
    SetInt(vm, "KeyY", Y);
    SetInt(vm, "KeyZ", Z);
    SetInt(vm, "KeyNum0", Num0);
    SetInt(vm, "KeyNum1", Num1);
    SetInt(vm, "KeyNum2", Num2);
    SetInt(vm, "KeyNum3", Num3);
    SetInt(vm, "KeyNum4", Num4);
    SetInt(vm, "KeyNum5", Num5);
    SetInt(vm, "KeyNum6", Num6);
    SetInt(vm, "KeyNum7", Num7);
    SetInt(vm, "KeyNum8", Num8);
    SetInt(vm, "KeyNum9", Num9);
    SetInt(vm, "KeyEscape", Escape);
    SetInt(vm, "KeyLControl", LControl);
    SetInt(vm, "KeyLShift", LShift);
    SetInt(vm, "KeyLAlt", LAlt);
    SetInt(vm, "KeyLSystem", LSystem);
    SetInt(vm, "KeyRControl", RControl);
    SetInt(vm, "KeyRShift", RShift);
    SetInt(vm, "KeyRAlt", RAlt);
    SetInt(vm, "KeyRSystem", RSystem);
    SetInt(vm, "KeyMenu", Menu);
    SetInt(vm, "KeyLBracket", LBracket);
    SetInt(vm, "KeyRBracket", RBracket);
    SetInt(vm, "KeySemiColon", SemiColon);
    SetInt(vm, "KeyComma", Comma);
    SetInt(vm, "KeyPeriod", Period);
    SetInt(vm, "KeyQuote", Quote);
    SetInt(vm, "KeySlash", Slash);
    SetInt(vm, "KeyBackSlash", BackSlash);
    SetInt(vm, "KeyTilde", Tilde);
    SetInt(vm, "KeyEqual", Equal);
    SetInt(vm, "KeyDash", Dash);
    SetInt(vm, "KeySpace", Space);
    SetInt(vm, "KeyReturn", Return);
    SetInt(vm, "KeyBack", Back);
    SetInt(vm, "KeyTab", Tab);
    SetInt(vm, "KeyPageUp", PageUp);
    SetInt(vm, "KeyPageDown", PageDown);
    SetInt(vm, "KeyEnd", End);
    SetInt(vm, "KeyHome", Home);
    SetInt(vm, "KeyInsert", Insert);
    SetInt(vm, "KeyDelete", Delete);
    SetInt(vm, "KeyAdd", Add);
    SetInt(vm, "KeySubtract", Subtract);
    SetInt(vm, "KeyMultiply", Multiply);
    SetInt(vm, "KeyDivide", Divide);
    SetInt(vm, "KeyLeft", sf::Key::Left);
    SetInt(vm, "KeyRight", sf::Key::Right);
    SetInt(vm, "KeyUp", Up);
    SetInt(vm, "KeyDown", Down);
    SetInt(vm, "KeyNumpad0", Numpad0);
    SetInt(vm, "KeyNumpad1", Numpad1);
    SetInt(vm, "KeyNumpad2", Numpad2);
    SetInt(vm, "KeyNumpad3", Numpad3);
    SetInt(vm, "KeyNumpad4", Numpad4);
    SetInt(vm, "KeyNumpad5", Numpad5);
    SetInt(vm, "KeyNumpad6", Numpad6);
    SetInt(vm, "KeyNumpad7", Numpad7);
    SetInt(vm, "KeyNumpad8", Numpad8);
    SetInt(vm, "KeyNumpad9", Numpad9);
    SetInt(vm, "KeyF1", F1);
    SetInt(vm, "KeyF2", F2);
    SetInt(vm, "KeyF3", F3);
    SetInt(vm, "KeyF4", F4);
    SetInt(vm, "KeyF5", F5);
    SetInt(vm, "KeyF6", F6);
    SetInt(vm, "KeyF7", F7);
    SetInt(vm, "KeyF8", F8);
    SetInt(vm, "KeyF9", F9);
    SetInt(vm, "KeyF10", F10);
    SetInt(vm, "KeyF11", F11);
    SetInt(vm, "KeyF12", F12);
    SetInt(vm, "KeyF13", F13);
    SetInt(vm, "KeyF14", F14);
    SetInt(vm, "KeyF15", F15);
    SetInt(vm, "KeyPause", Pause);
    //Mouse buttons
    SetInt(vm, "ButtonLeft", sf::Mouse::Left);
    SetInt(vm, "ButtonRight", sf::Mouse::Right);
    SetInt(vm, "ButtonMiddle", Middle);
    SetInt(vm, "ButtonX1", XButton1);
    SetInt(vm, "ButtonX2", XButton2);
    //Joy axis
    SetInt(vm, "JoyAxisX", AxisX);
    SetInt(vm, "JoyAxisY", AxisY);
    SetInt(vm, "JoyAxisZ", AxisZ);
    SetInt(vm, "JoyAxisR", AxisR);
    SetInt(vm, "JoyAxisU", AxisU);
    SetInt(vm, "JoyAxisV", AxisV);
    SetInt(vm, "JoyAxisPOV", AxisPOV);
    //sound constants
    SetInt(vm, "SoundStopped", sf::Sound::Stopped);
    SetInt(vm, "SoundPaused", sf::Sound::Paused);
    SetInt(vm, "SoundPlaying", sf::Sound::Playing);
    //Blend modes
    SetInt(vm, "BlendAlpha", sf::Blend::Alpha);
    SetInt(vm, "BlendAdd", sf::Blend::Add);
    SetInt(vm, "BlendMultiply", sf::Blend::Multiply);
    SetInt(vm, "BlendNone", sf::Blend::None);
    //String styles
    SetInt(vm, "StringRegular", sf::String::Regular);
    SetInt(vm, "StringBold", sf::String::Bold);
    SetInt(vm, "StringItalic", sf::String::Italic);
    SetInt(vm, "StringUndelined", sf::String::Underlined);
    //register chipmunk's constants
    SetInt(vm, "NO_GROUP", CP_NO_GROUP);
    SetInt(vm, "ALL_LAYERS", CP_ALL_LAYERS);
    //register bange functions and other engine's elements
    lua_newtable(vm);
    /*
    bange::RegisterVM(vm);
    bange::image::RegisterVM(vm);
    bange::base::RegisterVM(vm);
    bange::behavior::RegisterVM(vm);
    bange::layer::RegisterVM(vm);
    bange::layerobject::RegisterVM(vm);
    bange::scene::RegisterVM(vm);
    bange::view::RegisterVM(vm);
    bange::object::RegisterVM(vm);
    bange::simplestring::RegisterVM(vm);
    bange::simplesprite::RegisterVM(vm);
    bange::font::RegisterVM(vm);*/
    lua_setglobal(vm, "bange");
}

void bange::vm::SetInt(lua_State *vm, const char *var, int value){
    lua_pushnumber(vm, value);
    lua_setglobal(vm, var);
}

bool bange::vm::GetInt(lua_State *vm, const char *var, lua_Number &value){
    lua_getglobal(vm, var);
    if (lua_isnil(vm, -1) || !lua_isnumber(vm, -1)){
        lua_pop(vm, 1);
        return false;}
    value = lua_tonumber(vm, -1);
    lua_pop(vm, 1);
    return true;
}

void bange::vm::SetBoolean(lua_State *vm, const char *var, int value){
    lua_pushboolean(vm, value);
    lua_setglobal(vm, var);
}

bool bange::vm::GetBoolean(lua_State *vm, const char *var, int &value){
    lua_getglobal(vm, var);
    if (lua_isnil(vm, -1) || !lua_isboolean(vm, -1)){
        lua_pop(vm, 1);
        return false;}
    value = lua_toboolean(vm, -1);
    lua_pop(vm, 1);
    return true;
}

bool bange::vm::GetString(lua_State *vm, const char *var, char *string, int size){
    lua_getglobal(vm, var);
    if (lua_isnil(vm, -1) || !lua_isstring(vm, -1)){
        lua_pop(vm, 1);
        return false;}
    memset(static_cast<void *>(string), 0, size);
    strncpy(string, lua_tostring(vm, -1), size);
    lua_pop(vm, 1);
    return true;
}
