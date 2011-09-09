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
#include <layerobject.hpp>
#include <texture.hpp>
#include <object.hpp>
#include <view.hpp>
#include <tile.hpp>
#include <layertilemap.hpp>
#include <layerimagetilemap.hpp>
#include <soundbuffer.hpp>
#include <sound.hpp>
#include <music.hpp>
#include <listener.hpp>

void bange::PrepareVM(lua_State *vm){
	using namespace bange::vm;
	using namespace sf;
    SetNumber(vm, "KeyA", Keyboard::A);
    SetNumber(vm, "KeyB", Keyboard::B);
    SetNumber(vm, "KeyC", Keyboard::C);
    SetNumber(vm, "KeyD", Keyboard::D);
    SetNumber(vm, "KeyE", Keyboard::E);
    SetNumber(vm, "KeyF", Keyboard::F);
    SetNumber(vm, "KeyG", Keyboard::G);
    SetNumber(vm, "KeyH", Keyboard::H);
    SetNumber(vm, "KeyI", Keyboard::I);
    SetNumber(vm, "KeyJ", Keyboard::J);
    SetNumber(vm, "KeyK", Keyboard::K);
    SetNumber(vm, "KeyL", Keyboard::L);
    SetNumber(vm, "KeyM", Keyboard::M);
    SetNumber(vm, "KeyN", Keyboard::N);
    SetNumber(vm, "KeyO", Keyboard::O);
    SetNumber(vm, "KeyP", Keyboard::P);
    SetNumber(vm, "KeyQ", Keyboard::Q);
    SetNumber(vm, "KeyR", Keyboard::R);
    SetNumber(vm, "KeyS", Keyboard::S);
    SetNumber(vm, "KeyT", Keyboard::T);
    SetNumber(vm, "KeyU", Keyboard::U);
    SetNumber(vm, "KeyV", Keyboard::V);
    SetNumber(vm, "KeyW", Keyboard::W);
    SetNumber(vm, "KeyX", Keyboard::X);
    SetNumber(vm, "KeyY", Keyboard::Y);
    SetNumber(vm, "KeyZ", Keyboard::Z);
    SetNumber(vm, "KeyNum0", Keyboard::Num0);
    SetNumber(vm, "KeyNum1", Keyboard::Num1);
    SetNumber(vm, "KeyNum2", Keyboard::Num2);
    SetNumber(vm, "KeyNum3", Keyboard::Num3);
    SetNumber(vm, "KeyNum4", Keyboard::Num4);
    SetNumber(vm, "KeyNum5", Keyboard::Num5);
    SetNumber(vm, "KeyNum6", Keyboard::Num6);
    SetNumber(vm, "KeyNum7", Keyboard::Num7);
    SetNumber(vm, "KeyNum8", Keyboard::Num8);
    SetNumber(vm, "KeyNum9", Keyboard::Num9);
    SetNumber(vm, "KeyEscape", Keyboard::Escape);
    SetNumber(vm, "KeyLControl", Keyboard::LControl);
    SetNumber(vm, "KeyLShift", Keyboard::LShift);
    SetNumber(vm, "KeyLAlt", Keyboard::LAlt);
    SetNumber(vm, "KeyLSystem", Keyboard::LSystem);
    SetNumber(vm, "KeyRControl", Keyboard::RControl);
    SetNumber(vm, "KeyRShift", Keyboard::RShift);
    SetNumber(vm, "KeyRAlt", Keyboard::RAlt);
    SetNumber(vm, "KeyRSystem", Keyboard::RSystem);
    SetNumber(vm, "KeyMenu", Keyboard::Menu);
    SetNumber(vm, "KeyLBracket", Keyboard::LBracket);
    SetNumber(vm, "KeyRBracket", Keyboard::RBracket);
    SetNumber(vm, "KeySemiColon", Keyboard::SemiColon);
    SetNumber(vm, "KeyComma", Keyboard::Comma);
    SetNumber(vm, "KeyPeriod", Keyboard::Period);
    SetNumber(vm, "KeyQuote", Keyboard::Quote);
    SetNumber(vm, "KeySlash", Keyboard::Slash);
    SetNumber(vm, "KeyBackSlash", Keyboard::BackSlash);
    SetNumber(vm, "KeyTilde", Keyboard::Tilde);
    SetNumber(vm, "KeyEqual", Keyboard::Equal);
    SetNumber(vm, "KeyDash", Keyboard::Dash);
    SetNumber(vm, "KeySpace", Keyboard::Space);
    SetNumber(vm, "KeyReturn", Keyboard::Return);
    SetNumber(vm, "KeyBack", Keyboard::Back);
    SetNumber(vm, "KeyTab", Keyboard::Tab);
    SetNumber(vm, "KeyPageUp", Keyboard::PageUp);
    SetNumber(vm, "KeyPageDown", Keyboard::PageDown);
    SetNumber(vm, "KeyEnd", Keyboard::End);
    SetNumber(vm, "KeyHome", Keyboard::Home);
    SetNumber(vm, "KeyInsert", Keyboard::Insert);
    SetNumber(vm, "KeyDelete", Keyboard::Delete);
    SetNumber(vm, "KeyAdd", Keyboard::Add);
    SetNumber(vm, "KeySubtract", Keyboard::Subtract);
    SetNumber(vm, "KeyMultiply", Keyboard::Multiply);
    SetNumber(vm, "KeyDivide", Keyboard::Divide);
    SetNumber(vm, "KeyLeft", Keyboard::Left);
    SetNumber(vm, "KeyRight", Keyboard::Right);
    SetNumber(vm, "KeyUp", Keyboard::Up);
    SetNumber(vm, "KeyDown", Keyboard::Down);
    SetNumber(vm, "KeyNumpad0", Keyboard::Numpad0);
    SetNumber(vm, "KeyNumpad1", Keyboard::Numpad1);
    SetNumber(vm, "KeyNumpad2", Keyboard::Numpad2);
    SetNumber(vm, "KeyNumpad3", Keyboard::Numpad3);
    SetNumber(vm, "KeyNumpad4", Keyboard::Numpad4);
    SetNumber(vm, "KeyNumpad5", Keyboard::Numpad5);
    SetNumber(vm, "KeyNumpad6", Keyboard::Numpad6);
    SetNumber(vm, "KeyNumpad7", Keyboard::Numpad7);
    SetNumber(vm, "KeyNumpad8", Keyboard::Numpad8);
    SetNumber(vm, "KeyNumpad9", Keyboard::Numpad9);
    SetNumber(vm, "KeyF1", Keyboard::F1);
    SetNumber(vm, "KeyF2", Keyboard::F2);
    SetNumber(vm, "KeyF3", Keyboard::F3);
    SetNumber(vm, "KeyF4", Keyboard::F4);
    SetNumber(vm, "KeyF5", Keyboard::F5);
    SetNumber(vm, "KeyF6", Keyboard::F6);
    SetNumber(vm, "KeyF7", Keyboard::F7);
    SetNumber(vm, "KeyF8", Keyboard::F8);
    SetNumber(vm, "KeyF9", Keyboard::F9);
    SetNumber(vm, "KeyF10", Keyboard::F10);
    SetNumber(vm, "KeyF11", Keyboard::F11);
    SetNumber(vm, "KeyF12", Keyboard::F12);
    SetNumber(vm, "KeyF13", Keyboard::F13);
    SetNumber(vm, "KeyF14", Keyboard::F14);
    SetNumber(vm, "KeyF15", Keyboard::F15);
    SetNumber(vm, "KeyPause", Keyboard::Pause);
    //Mouse buttons
    SetNumber(vm, "ButtonLeft", Mouse::Left);
    SetNumber(vm, "ButtonRight", Mouse::Right);
    SetNumber(vm, "ButtonMiddle", Mouse::Middle);
    SetNumber(vm, "ButtonX1", Mouse::XButton1);
    SetNumber(vm, "ButtonX2", Mouse::XButton2);
    //Joy axis
    SetNumber(vm, "JoyAxisX", Joystick::X);
    SetNumber(vm, "JoyAxisY", Joystick::Y);
    SetNumber(vm, "JoyAxisZ", Joystick::Z);
    SetNumber(vm, "JoyAxisR", Joystick::R);
    SetNumber(vm, "JoyAxisU", Joystick::U);
    SetNumber(vm, "JoyAxisV", Joystick::V);
    SetNumber(vm, "JoyAxisPovX", Joystick::PovX);
    SetNumber(vm, "JoyAxisPovY", Joystick::PovY);
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
    SetNumber(vm, "TextRegular", sf::Text::Regular);
    SetNumber(vm, "TextBold", sf::Text::Bold);
    SetNumber(vm, "TextItalic", sf::Text::Italic);
    SetNumber(vm, "TextUndelined", sf::Text::Underlined);
    //register bange functions and other engine's elements
    luaL_Reg functions[] = {
    {"NewScene", bange::NewScene},
    {"NewView", bange::NewView},
    {NULL, NULL}};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
    
    bange::box::RegisterVM(vm);
    bange::behavior::RegisterVM(vm);
    bange::proxy::RegisterVM(vm);
    bange::scene::RegisterVM(vm);
    bange::layerobject::RegisterVM(vm);
    bange::view::RegisterVM(vm);
    bange::object::RegisterVM(vm);
    bange::texture::RegisterVM(vm);
    bange::tile::RegisterVM(vm);
    bange::layertilemap::RegisterVM(vm);
    bange::layerimagetilemap::RegisterVM(vm);
    bange::soundbuffer::RegisterVM(vm);
    bange::sound::RegisterVM(vm);
    bange::music::RegisterVM(vm);
    bange::listener::RegisterVM(vm);
}
