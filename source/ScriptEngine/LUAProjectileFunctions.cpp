#include "Stdafx.h"

namespace luaProjectile
{
	LUAFUNC int Projectile_GetLifeTime(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_FLOAT(L, ptr->GetLifeTime());
		return 1;
	}
	LUAADD(Projectile_GetLifeTime, Projectile);

	LUAFUNC int Projectile_GetSpeed(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_FLOAT(L, ptr->GetSpeed());
		return 1;
	}
	LUAADD(Projectile_GetSpeed, Projectile);

	LUAFUNC int Projectile_SetSpeed(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		Real val = CHECK_FLOAT(L, 1);
		ptr->SetSpeed(val);
		return 1;
	}
	LUAADD(Projectile_SetSpeed, Projectile);

	LUAFUNC int Projectile_GetDirectonX(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_FLOAT(L, ptr->GetDirection().x);
		return 1;
	}
	LUAADD(Projectile_GetDirectonX, Projectile);

	LUAFUNC int Projectile_GetDirectonY(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_FLOAT(L, ptr->GetDirection().y);
		return 1;
	}
	LUAADD(Projectile_GetDirectonY, Projectile);

	LUAFUNC int Projectile_SetDirecton(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		Real x = CHECK_FLOAT(L, 1);
		Real y = CHECK_FLOAT(L, 1);
		ptr->SetDirection(x, y, 0);
		return 1;
	}
	LUAADD(Projectile_SetDirecton, Projectile);
}