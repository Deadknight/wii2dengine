#ifndef __LUA_PHYSICSFUNCTIONS_H
#define __LUA_PHYSICSFUNCTIONS_H

namespace luaPhysics
{
	LUAFUNC int Physics_SetVelocity(lua_State * L, T * ptr);
	LUAFUNC int Physics_SetDamping(lua_State * L, T * ptr);
	LUAFUNC int Physics_SetMass(lua_State * L, T * ptr);
	LUAFUNC int Physics_SetInverseMass(lua_State * L, T * ptr);
	LUAFUNC int Physics_AddForce(lua_State * L, T * ptr);
	LUAFUNC int Physics_AddForceGenerator(lua_State * L, T * ptr);
	LUAFUNC int Physics_RemoveForceGenerator(lua_State * L, T * ptr);
	LUAFUNC int Physics_GetCollisionFlag(lua_State * L, T * ptr);
	LUAFUNC int Physics_SetCollisionFlag(lua_State * L, T * ptr);
}

#endif