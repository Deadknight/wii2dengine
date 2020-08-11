#include "Stdafx.h"

namespace luaWeapon
{
	LUAFUNC int Weapon_GetProjectileEntry(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_UINT32(L, ptr->GetProjectileEntry());
		return 1;
	}
	LUAADD(Weapon_GetProjectileEntry, Weapon);

	LUAFUNC int Weapon_GetProjectileName(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_STRING(L, ptr->GetProjectileName().c_str());
		return 1;
	}
	LUAADD(Weapon_GetProjectileName, Weapon);

	LUAFUNC int Weapon_SetProjectileInfo(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		const char *name = CHECK_STRING(L, 1);
		uint32 entry = CHECK_UINT32(L, 2);

		ptr->SetProjectileName(name);
		ptr->SetProjectileEntry(entry);

		return 1;
	}
	LUAADD(Weapon_SetProjectileInfo, Weapon);

	LUAFUNC int Weapon_GetCurrentFireCooldown(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_STRING(L, ptr->GetProjectileName().c_str());
		return 1;
	}
	LUAADD(Weapon_GetCurrentFireCooldown, Weapon);

	LUAFUNC int Weapon_GetFireCooldown(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_STRING(L, ptr->GetProjectileName().c_str());
		return 1;
	}
	LUAADD(Weapon_GetFireCooldown, Weapon);

	LUAFUNC int Weapon_SetFireCooldown(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		Real value = CHECK_FLOAT(L, 1);

		ptr->SetFireCooldown(value);

		return 1;
	}
	LUAADD(Weapon_SetFireCooldown, Weapon);

	LUAFUNC int Weapon_GetCurrentReloadCooldown(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_STRING(L, ptr->GetProjectileName().c_str());
		return 1;
	}
	LUAADD(Weapon_GetCurrentReloadCooldown, Weapon);

	LUAFUNC int Weapon_GetReloadCooldown(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_STRING(L, ptr->GetProjectileName().c_str());
		return 1;
	}
	LUAADD(Weapon_GetReloadCooldown, Weapon);

	LUAFUNC int Weapon_SetReloadCooldown(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		Real value = CHECK_FLOAT(L, 1);

		ptr->SetReloadCooldown(value);

		return 1;
	}
	LUAADD(Weapon_SetReloadCooldown, Weapon);

	LUAFUNC int Weapon_GetDamage(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_STRING(L, ptr->GetProjectileName().c_str());
		return 1;
	}
	LUAADD(Weapon_GetDamage, Weapon);

	LUAFUNC int Weapon_SetDamage(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		uint32 value = CHECK_FLOAT(L, 1);

		ptr->SetDamage(value);

		return 1;
	}
	LUAADD(Weapon_SetDamage, Weapon);

	LUAFUNC int Weapon_GetCurrentMagazine(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_STRING(L, ptr->GetProjectileName().c_str());
		return 1;
	}
	LUAADD(Weapon_GetCurrentMagazine, Weapon);

	LUAFUNC int Weapon_SetCurrentMagazine(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		uint32 value = CHECK_FLOAT(L, 1);

		ptr->SetCurrentMagazine(value);

		return 1;
	}
	LUAADD(Weapon_SetCurrentMagazine, Weapon);

	LUAFUNC int Weapon_GetMaxMagazine(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_STRING(L, ptr->GetProjectileName().c_str());
		return 1;
	}
	LUAADD(Weapon_GetMaxMagazine, Weapon);

	LUAFUNC int Weapon_SetMaxMagazine(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		uint32 value = CHECK_FLOAT(L, 1);

		ptr->SetMaxMagazine(value);

		return 1;
	}
	LUAADD(Weapon_SetMaxMagazine, Weapon);

	LUAFUNC int Weapon_CreateProjectile(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		const char *name = CHECK_STRING(L, 1);
		uint32 entry = CHECK_UINT32(L, 2);
		Real lifeTime = CHECK_FLOAT(L, 3);

		ptr->CreateProjectile(name, entry, lifeTime);

		return 1;
	}
	LUAADD(Weapon_CreateProjectile, Weapon);
}