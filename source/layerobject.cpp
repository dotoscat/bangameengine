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
#include <cstring>
#include <SFML/System.hpp>
#include <layerobject.hpp>
#include <object.hpp>
#include <aux.hpp>
#include <view.hpp>

void bange::layerobject::RegisterVM(lua_State *vm){
    luaL_Reg methods[] = {
    {"AddShapeRectangle", bange::layerobject_AddShapeRectangle},
    {"AddShapeCircle", bange::layerobject_AddShapeCircle},
    {"AddShapeLine", bange::layerobject_AddShapeLine},
    {"AddText", bange::layerobject_AddText},
    {NULL, NULL}};
    lua_createtable(vm, 0, 4);
    luaL_register(vm, NULL, methods);
    lua_setfield(vm, LUA_REGISTRYINDEX, "bange::layerobject::");
}

bange::layerobject::layerobject(size_t maxobjects){
    this->maxobjects = maxobjects;
    nobjects = 0;
    iterations = maxobjects;
    position = 0;
    objects.reserve(maxobjects);
    for(size_t i = 0; i < maxobjects; i += 1){
        objects.push_back(LUA_REFNIL);}
}

bool bange::layerobject::NewIndex(lua_State *vm, const char *key){
    if (this->bange::layer::NewIndex(vm, key)){
        return true;}
    if (strcmp("iterations", key) == 0){
        iterations = lua_tonumber(vm, 3);
        return true;
    }
    return false;
}

bool bange::layerobject::Index(lua_State *vm, const char *key){
    if (this->bange::layer::Index(vm, key)){
        return true;}
    if (strcmp(key, "maxobjects") == 0){
        lua_pushnumber(vm, maxobjects);
        return true;}
    else if (strcmp(key, "nobjects") == 0){
        lua_pushnumber(vm, nobjects);
        return true;}
    else if (strcmp(key, "iterations") == 0){
        lua_pushnumber(vm, iterations);
        return true;}
    //Methods
    lua_getfield(vm, LUA_REGISTRYINDEX, "bange::layerobject::");
    lua_getfield(vm, -1, key);
    return true;
}

void bange::layerobject::Clean(lua_State *vm){
    std::vector<int>::iterator aobject = objects.begin();
    for(; aobject != objects.end(); aobject++){
        luaL_unref(vm, LUA_REGISTRYINDEX, *aobject);}
    lua_gc(vm, LUA_GCCOLLECT, 0);
}

void bange::layerobject::Process(sf::Uint32 time, sf::RenderTarget &rendertarget, \
std::map<const void *, int> &views, lua_State *vm){
    bange::proxy *proxy = NULL;
    bange::object *object = NULL;
    std::map<const void *, int>::iterator aview;
    size_t end = position+iterations, i = position;
    if (end > maxobjects){
        end=maxobjects;}
    
    for(; i < end; i += 1){
        if (objects[i] == LUA_REFNIL){
            continue;}
        lua_rawgeti(vm, LUA_REGISTRYINDEX, objects[i]);
        proxy = static_cast<bange::proxy *>(lua_touserdata(vm, -1));
        if (proxy == NULL){
            std::cout << "bange::layerobject(" << this << ")::Process() -> void object at: " << i << "!!" << std::endl;
            objects[i] = LUA_REFNIL;//Try fix it without unref the corrupted object
            lua_pop(vm, 1);;//pop "proxy"
            continue;//And continue
        }
        object = static_cast<bange::object *>(proxy->object);
        if (object->del){
            luaL_unref(vm, LUA_REGISTRYINDEX, objects[i]);
            objects[i] = LUA_REFNIL;
            nobjects -= 1;
        }
        proxy->behavior->Process(lua_gettop(vm), time, vm);
        object->Process(time, vm);
        if (this->visible && object->visible){
            for (aview = views.begin(); aview != views.end(); aview++){
                rendertarget.SetView( *static_cast<const bange::view *>(aview->first) );
                rendertarget.Draw(*object->thedrawable);
            }
        }
        if (object->del){
            luaL_unref(vm, LUA_REGISTRYINDEX, objects[i]);
            objects[i] = LUA_REFNIL;
            nobjects -= 1;
        }
        lua_pop(vm, 1);//pop proxy
        
    }
    position = i;
    if (position == maxobjects){
        position = 0;}
}

bool bange::layerobject::AddObject(int referenceobject){
    for (size_t i=0; i < maxobjects; i += 1){
        
        if (objects[i] == LUA_REFNIL){
            objects[i] = referenceobject;
            nobjects += 1;
            return true;
        }

    }
    return false;
}

int bange::layerobject_AddShapeRectangle(lua_State *vm){
    //layerobject, {Left, Top, Width, Height}, color, float outline, outlinecolor -> rect shape
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    bange::layerobject *layerobject = static_cast<bange::layerobject *>(proxy->object);
    if (!lua_istable(vm, 2)){
        std::cout << "bange.NewRectangle: First argument must be a table" << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if (!lua_istable(vm, 3)){
        std::cout << "bange.NewRectangle: 3hd argument must be a table with the colors." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    sf::Color outlinecolor(0, 0, 0);
    float outline = 0.f;
    if (lua_gettop(vm) > 3){
        
        if (!lua_isnumber(vm, 4)){
            std::cout << "bange.NewRectangle: 4th argument must be a valid number." << std::endl;
            lua_pushnil(vm);
            return 1;
        }
        else if (lua_isnumber(vm, 4)){
            outline = lua_tonumber(vm, 4);}
        if (!lua_istable(vm, 5)){
            std::cout << "bange.NewRectangle: 5th argument must be a table with the colors.." << std::endl;
            lua_pushnil(vm);
            return 1;
        }
        else if (lua_istable(vm, 5)){
            outlinecolor = bange::TableTosfColor(5, vm);}
            
    }
    if (layerobject->Filled()){
        lua_pushnil(vm);
        return 1;
    }
    sf::FloatRect rect = bange::TableTosfFloatRect(2, vm);
    sf::Color color = bange::TableTosfColor(3, vm);
    bange::shape *shape = new bange::shape();
    *static_cast<sf::Shape *>(shape) = sf::Shape::Rectangle(rect, color, outline, outlinecolor);
    bange::BuildProxy(vm, shape);
    lua_pushvalue(vm, -1);
    layerobject->AddObject(luaL_ref(vm, LUA_REGISTRYINDEX));
    return 1;
}

int bange::layerobject_AddShapeCircle(lua_State *vm){
    //layerobject, center, radius, color, outline, outlinecolor -> circle shape
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    bange::layerobject *layerobject = static_cast<bange::layerobject *>(proxy->object);
    if (!lua_istable(vm, 2)){
        std::cout << proxy << ":AddShapeCircle() : First argument must be a table with the center." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    sf::Vector2f center = bange::TableTosfVector2f(2, vm);
    if (!lua_isnumber(vm, 3)){
        std::cout << proxy << ":AddShapeCircle() : Second argument must be a number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    cpFloat radius = lua_tonumber(vm, 3);
    if (!lua_istable(vm, 4)){
        std::cout << proxy << ":AddShapeCircle() : 3d argument must be a table with the color." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    sf::Color color = bange::TableTosfColor(4, vm);
    cpFloat outline = 0;
    if (lua_gettop(vm) > 4 && lua_isnumber(vm, 5)){
        outline = lua_tonumber(vm, 5);
    }
    sf::Color outlinecolor(0, 0, 0);
    if (lua_gettop(vm) > 5 && lua_istable(vm, 6)){
        outlinecolor = bange::TableTosfColor(6, vm);
    }
    bange::shape *shape = new bange::shape();
    *static_cast<sf::Shape *>(shape) = sf::Shape::Circle(center, radius, color, outline, outlinecolor);
    bange::BuildProxy(vm, shape);
    lua_pushvalue(vm, -1);
    layerobject->AddObject(luaL_ref(vm, LUA_REGISTRYINDEX));
    return 1;
}

int bange::layerobject_AddShapeLine(lua_State *vm){
    //layerobject, point1 {x, y}, point2 {x, y}, thickness, color, outline, outlinecolor -> line shape
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    bange::layerobject *layerobject = static_cast<bange::layerobject *>(proxy->object);
    if (!lua_istable(vm, 2)){
        std::cout << proxy << ":AddShapeLine() : First argument must be a table with the 1st point." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    sf::Vector2f point1 = bange::TableTosfVector2f(2, vm);
    if (!lua_istable(vm, 3)){
        std::cout << proxy << ":AddShapeLine() : 2nd argument must be a table with the 2n point." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    sf::Vector2f point2 = bange::TableTosfVector2f(3, vm);
    if (!lua_isnumber(vm, 4)){
        std::cout << proxy << ":AddShapeLine() : 3rd argument must be a number." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    cpFloat thickness = lua_tonumber(vm, 4);
    if (!lua_istable(vm, 5)){
        std::cout << proxy << ":AddShapeLine() : 4th argument must be a table with the color." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    sf::Color color = bange::TableTosfColor(5, vm);
    cpFloat outline = 0;
    if (lua_gettop(vm) > 5 && lua_isnumber(vm, 6)){
        outline = lua_tonumber(vm, 6);
    }
    sf::Color outlinecolor(0, 0, 0);
    if (lua_gettop(vm) > 6 && lua_istable(vm, 7)){
        outlinecolor = bange::TableTosfColor(7, vm);
    }
    bange::shape *shape = new bange::shape();
    *static_cast<sf::Shape *>(shape) = sf::Shape::Line(point1, point2, thickness, color, outline, outlinecolor);
    bange::BuildProxy(vm, shape);
    lua_pushvalue(vm, -1);
    int ref = luaL_ref(vm, LUA_REGISTRYINDEX);
    layerobject->AddObject(ref);
    return 1;
}

int bange::layerobject_AddText(lua_State *vm){
    //layerobject, text
    bange::proxy *proxy = static_cast<bange::proxy *>(lua_touserdata(vm, 1));
    bange::layerobject *layerobject = static_cast<bange::layerobject *>(proxy->object);
    const char *strtext = NULL;
    if (lua_isstring(vm, 2)){
            strtext = lua_tostring(vm, 2);
    }
    else if (!lua_isstring(vm, 2)){
            std::cout << "bange.NewText: 2nd argument isn't a valid string" << std::endl;
            lua_pushnil(vm);
            return 1;
    }
    bange::text *text = new bange::text();
    if (strtext != NULL){
        text->SetString(sf::String(strtext));}
    bange::BuildProxy(vm, text);
    lua_pushvalue(vm, -1);
    int ref = luaL_ref(vm, LUA_REGISTRYINDEX);
    layerobject->AddObject(ref);
    return 1;
}
