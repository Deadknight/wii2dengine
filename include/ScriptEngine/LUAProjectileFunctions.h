#ifndef __LUA_PROJECTILEFUNCTIONS_H
#define __LUA_PROJECTILEFUNCTIONS_H

namespace luaProjectile
{
	LUAFUNC int Projectile_GetLifeTime(lua_State * L, T * ptr);
	LUAFUNC int Projectile_GetSpeed(lua_State * L, T * ptr);
	LUAFUNC int Projectile_SetSpeed(lua_State * L, T * ptr);
	LUAFUNC int Projectile_GetDirectonX(lua_State * L, T * ptr);
	LUAFUNC int Projectile_GetDirectonY(lua_State * L, T * ptr);
	LUAFUNC int Projectile_SetDirecton(lua_State * L, T * ptr);
}

#endif
