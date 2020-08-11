#ifndef __LUA_OBJECTFUNCTIONS_H
#define __LUA_OBJECTFUNCTIONS_H

namespace luaObject
{
	LUAFUNC int Object_GetType(lua_State * L, T * ptr);
	LUAFUNC int Object_GetX(lua_State * L, T * ptr);
	LUAFUNC int Object_GetY(lua_State * L, T * ptr);
	LUAFUNC int Object_SetPosition(lua_State * L, T * ptr);
	LUAFUNC int Object_GetField(lua_State * L, T * ptr);
	LUAFUNC int Object_GetRealField(lua_State * L, T * ptr);
	LUAFUNC int Object_SetField(lua_State * L, T * ptr);
	LUAFUNC int Object_SetRealField(lua_State * L, T * ptr);
	LUAFUNC int Object_GetEntry(lua_State * L, T * ptr);
	LUAFUNC int Object_GetScale(lua_State * L, T * ptr);
	LUAFUNC int Object_SetScale(lua_State * L, T * ptr);
}

#endif
