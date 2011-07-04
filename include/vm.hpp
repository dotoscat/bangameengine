//vm.hpp
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

#ifndef _bange_vm_
#define _bange_vm_

#include <cstring>
#include <chipmunk/chipmunk.h>
#include <lua5.1/lua.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace bange{

	namespace vm{

		void PrepareVM(lua_State *);

		void SetInt(lua_State *, const char *, int);
		bool GetInt(lua_State *, const char *, lua_Number &);

		void SetBoolean(lua_State *, const char *, int);
		bool GetBoolean(lua_State *, const char *, int &);

		bool GetString(lua_State *, const char*, char *, int);
	
	}

}

#endif
