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

#include <register.hpp>
#include <box.hpp>
#include <base.hpp>
#include <scene.hpp>
#include <image.hpp>
#include <layerobject.hpp>
#include <object.hpp>
#include <view.hpp>

void bange::PrepareVM(lua_State *vm){
	using namespace bange::vm;
	using namespace sf::Key;
	using namespace sf::Mouse;
	using namespace sf::Joy;
    SetNumber(vm, "KeyA", A);
    SetNumber(vm, "KeyB", B);
    SetNumber(vm, "KeyC", C);
    SetNumber(vm, "KeyD", D);
    SetNumber(vm, "KeyE", E);
    SetNumber(vm, "KeyF", F);
    SetNumber(vm, "KeyG", G);
    SetNumber(vm, "KeyH", H);
    SetNumber(vm, "KeyI", I);
    SetNumber(vm, "KeyJ", J);
    SetNumber(vm, "KeyK", K);
    SetNumber(vm, "KeyL", L);
    SetNumber(vm, "KeyM", M);
    SetNumber(vm, "KeyN", N);
    SetNumber(vm, "KeyO", O);
    SetNumber(vm, "KeyP", P);
    SetNumber(vm, "KeyQ", Q);
    SetNumber(vm, "KeyR", R);
    SetNumber(vm, "KeyS", S);
    SetNumber(vm, "KeyT", T);
    SetNumber(vm, "KeyU", U);
    SetNumber(vm, "KeyV", V);
    SetNumber(vm, "KeyW", W);
    SetNumber(vm, "KeyX", X);
    SetNumber(vm, "KeyY", Y);
    SetNumber(vm, "KeyZ", Z);
    SetNumber(vm, "KeyNum0", Num0);
    SetNumber(vm, "KeyNum1", Num1);
    SetNumber(vm, "KeyNum2", Num2);
    SetNumber(vm, "KeyNum3", Num3);
    SetNumber(vm, "KeyNum4", Num4);
    SetNumber(vm, "KeyNum5", Num5);
    SetNumber(vm, "KeyNum6", Num6);
    SetNumber(vm, "KeyNum7", Num7);
    SetNumber(vm, "KeyNum8", Num8);
    SetNumber(vm, "KeyNum9", Num9);
    SetNumber(vm, "KeyEscape", Escape);
    SetNumber(vm, "KeyLControl", LControl);
    SetNumber(vm, "KeyLShift", LShift);
    SetNumber(vm, "KeyLAlt", LAlt);
    SetNumber(vm, "KeyLSystem", LSystem);
    SetNumber(vm, "KeyRControl", RControl);
    SetNumber(vm, "KeyRShift", RShift);
    SetNumber(vm, "KeyRAlt", RAlt);
    SetNumber(vm, "KeyRSystem", RSystem);
    SetNumber(vm, "KeyMenu", Menu);
    SetNumber(vm, "KeyLBracket", LBracket);
    SetNumber(vm, "KeyRBracket", RBracket);
    SetNumber(vm, "KeySemiColon", SemiColon);
    SetNumber(vm, "KeyComma", Comma);
    SetNumber(vm, "KeyPeriod", Period);
    SetNumber(vm, "KeyQuote", Quote);
    SetNumber(vm, "KeySlash", Slash);
    SetNumber(vm, "KeyBackSlash", BackSlash);
    SetNumber(vm, "KeyTilde", Tilde);
    SetNumber(vm, "KeyEqual", Equal);
    SetNumber(vm, "KeyDash", Dash);
    SetNumber(vm, "KeySpace", Space);
    SetNumber(vm, "KeyReturn", Return);
    SetNumber(vm, "KeyBack", Back);
    SetNumber(vm, "KeyTab", Tab);
    SetNumber(vm, "KeyPageUp", PageUp);
    SetNumber(vm, "KeyPageDown", PageDown);
    SetNumber(vm, "KeyEnd", End);
    SetNumber(vm, "KeyHome", Home);
    SetNumber(vm, "KeyInsert", Insert);
    SetNumber(vm, "KeyDelete", Delete);
    SetNumber(vm, "KeyAdd", Add);
    SetNumber(vm, "KeySubtract", Subtract);
    SetNumber(vm, "KeyMultiply", Multiply);
    SetNumber(vm, "KeyDivide", Divide);
    SetNumber(vm, "KeyLeft", sf::Key::Left);
    SetNumber(vm, "KeyRight", sf::Key::Right);
    SetNumber(vm, "KeyUp", Up);
    SetNumber(vm, "KeyDown", Down);
    SetNumber(vm, "KeyNumpad0", Numpad0);
    SetNumber(vm, "KeyNumpad1", Numpad1);
    SetNumber(vm, "KeyNumpad2", Numpad2);
    SetNumber(vm, "KeyNumpad3", Numpad3);
    SetNumber(vm, "KeyNumpad4", Numpad4);
    SetNumber(vm, "KeyNumpad5", Numpad5);
    SetNumber(vm, "KeyNumpad6", Numpad6);
    SetNumber(vm, "KeyNumpad7", Numpad7);
    SetNumber(vm, "KeyNumpad8", Numpad8);
    SetNumber(vm, "KeyNumpad9", Numpad9);
    SetNumber(vm, "KeyF1", F1);
    SetNumber(vm, "KeyF2", F2);
    SetNumber(vm, "KeyF3", F3);
    SetNumber(vm, "KeyF4", F4);
    SetNumber(vm, "KeyF5", F5);
    SetNumber(vm, "KeyF6", F6);
    SetNumber(vm, "KeyF7", F7);
    SetNumber(vm, "KeyF8", F8);
    SetNumber(vm, "KeyF9", F9);
    SetNumber(vm, "KeyF10", F10);
    SetNumber(vm, "KeyF11", F11);
    SetNumber(vm, "KeyF12", F12);
    SetNumber(vm, "KeyF13", F13);
    SetNumber(vm, "KeyF14", F14);
    SetNumber(vm, "KeyF15", F15);
    SetNumber(vm, "KeyPause", Pause);
    //Mouse buttons
    SetNumber(vm, "ButtonLeft", sf::Mouse::Left);
    SetNumber(vm, "ButtonRight", sf::Mouse::Right);
    SetNumber(vm, "ButtonMiddle", Middle);
    SetNumber(vm, "ButtonX1", XButton1);
    SetNumber(vm, "ButtonX2", XButton2);
    //Joy axis
    SetNumber(vm, "JoyAxisX", AxisX);
    SetNumber(vm, "JoyAxisY", AxisY);
    SetNumber(vm, "JoyAxisZ", AxisZ);
    SetNumber(vm, "JoyAxisR", AxisR);
    SetNumber(vm, "JoyAxisU", AxisU);
    SetNumber(vm, "JoyAxisV", AxisV);
    SetNumber(vm, "JoyAxisPOV", AxisPOV);
    //sound constants
    SetNumber(vm, "SoundStopped", sf::Sound::Stopped);
    SetNumber(vm, "SoundPaused", sf::Sound::Paused);
    SetNumber(vm, "SoundPlaying", sf::Sound::Playing);
    //Blend modes
    SetNumber(vm, "BlendAlpha", sf::Blend::Alpha);
    SetNumber(vm, "BlendAdd", sf::Blend::Add);
    SetNumber(vm, "BlendMultiply", sf::Blend::Multiply);
    SetNumber(vm, "BlendNone", sf::Blend::None);
    //String styles
    SetNumber(vm, "StringRegular", sf::String::Regular);
    SetNumber(vm, "StringBold", sf::String::Bold);
    SetNumber(vm, "StringItalic", sf::String::Italic);
    SetNumber(vm, "StringUndelined", sf::String::Underlined);
    //register chipmunk's constants
    SetNumber(vm, "NO_GROUP", CP_NO_GROUP);
    SetNumber(vm, "ALL_LAYERS", CP_ALL_LAYERS);
    SetNumber(vm, "INFINITY", INFINITY);
    //register bange functions and other engine's elements
    bange::box::RegisterVM(vm);
    bange::behavior::RegisterVM(vm);
    bange::proxy::RegisterVM(vm);
    bange::scene::RegisterVM(vm);
    bange::view::RegisterVM(vm);
    bange::layerobject::RegisterVM(vm);
    bange::object::RegisterVM(vm);
    bange::image::RegisterVM(vm);
}
