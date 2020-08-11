#ifndef __LUA_WEAPONFUNCTIONS_H
#define __LUA_WEAPONFUNCTIONS_H

namespace luaWeapon
{
	LUAFUNC int Weapon_GetProjectileEntry(lua_State * L, T * ptr);
	LUAFUNC int Weapon_GetProjectileName(lua_State * L, T * ptr);
	LUAFUNC int Weapon_SetProjectileInfo(lua_State * L, T * ptr);
	LUAFUNC int Weapon_GetCurrentFireCooldown(lua_State * L, T * ptr);
	LUAFUNC int Weapon_GetFireCooldown(lua_State * L, T * ptr);
	LUAFUNC int Weapon_SetFireCooldown(lua_State * L, T * ptr);
	LUAFUNC int Weapon_GetCurrentReloadCooldown(lua_State * L, T * ptr);
	LUAFUNC int Weapon_GetReloadCooldown(lua_State * L, T * ptr);
	LUAFUNC int Weapon_SetReloadCooldown(lua_State * L, T * ptr);
	LUAFUNC int Weapon_GetDamage(lua_State * L, T * ptr);
	LUAFUNC int Weapon_SetDamage(lua_State * L, T * ptr);
	LUAFUNC int Weapon_GetCurrentMagazine(lua_State * L, T * ptr);
	LUAFUNC int Weapon_SetCurrentMagazine(lua_State * L, T * ptr);
	LUAFUNC int Weapon_GetMaxMagazine(lua_State * L, T * ptr);
	LUAFUNC int Weapon_SetMaxMagazine(lua_State * L, T * ptr);
	LUAFUNC int Weapon_CreateProjectile(lua_State * L, T * ptr);
}

#endif
