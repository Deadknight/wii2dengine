#include "Stdafx.h"

namespace luaObject
{
	LUAFUNC int Object_GetType(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_UINT32(L, ptr->GetType());
		return 1;
	}
	LUAADD(Object_GetType, Player);
	LUAADD(Object_GetType, Creature);
	LUAADD(Object_GetType, Gameobject);
	LUAADD(Object_GetType, Unit);
	LUAADD(Object_GetType, Object);
	LUAADD(Object_GetType, Projectile);

	LUAFUNC int Object_GetX(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_UINT32(L, ptr->GetPosition().x);
		return 1;
	}
	LUAADD(Object_GetX, Player);
	LUAADD(Object_GetX, Creature);
	LUAADD(Object_GetX, Gameobject);
	LUAADD(Object_GetX, Unit);
	LUAADD(Object_GetX, Object);
	LUAADD(Object_GetX, Projectile);

	LUAFUNC int Object_GetY(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_UINT32(L, ptr->GetPosition().y);
		return 1;
	}
	LUAADD(Object_GetY, Player);
	LUAADD(Object_GetY, Creature);
	LUAADD(Object_GetY, Gameobject);
	LUAADD(Object_GetY, Unit);
	LUAADD(Object_GetY, Object);
	LUAADD(Object_GetY, Projectile);

	LUAFUNC int Object_SetPosition(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		int32 x = CHECK_INT32(L, 1);
		int32 y = CHECK_INT32(L, 2);
		
		ptr->SetPosition(x, y, 0);

		return 1;
	}
	LUAADD(Object_SetPosition, Player);
	LUAADD(Object_SetPosition, Creature);
	LUAADD(Object_SetPosition, Gameobject);
	LUAADD(Object_SetPosition, Unit);
	LUAADD(Object_SetPosition, Object);
	LUAADD(Object_SetPosition, Projectile);

	LUAFUNC int Object_GetField(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		uint32 index = CHECK_UINT32(L, 1);

		PUSH_UINT32(L, ptr->GetUInt32Value(index));
		return 1;
	}
	LUAADD(Object_GetField, Player);
	LUAADD(Object_GetField, Creature);
	LUAADD(Object_GetField, Gameobject);
	LUAADD(Object_GetField, Unit);
	LUAADD(Object_GetField, Object);
	LUAADD(Object_GetField, Projectile);

	LUAFUNC int Object_GetRealField(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		uint32 index = CHECK_UINT32(L, 1);

		PUSH_FLOAT(L, ptr->GetRealValue(index));
		return 1;
	}
	LUAADD(Object_GetRealField, Player);
	LUAADD(Object_GetRealField, Creature);
	LUAADD(Object_GetRealField, Gameobject);
	LUAADD(Object_GetRealField, Unit);
	LUAADD(Object_GetRealField, Object);
	LUAADD(Object_GetRealField, Projectile);

	LUAFUNC int Object_SetField(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		uint32 index = CHECK_UINT32(L, 1);
		uint32 val = CHECK_UINT32(L, 2);

		ptr->SetUInt32Value(index, val);

		return 1;
	}
	LUAADD(Object_SetField, Player);
	LUAADD(Object_SetField, Creature);
	LUAADD(Object_SetField, Gameobject);
	LUAADD(Object_SetField, Unit);
	LUAADD(Object_SetField, Object);
	LUAADD(Object_SetField, Projectile);

	LUAFUNC int Object_SetRealField(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		uint32 index = CHECK_UINT32(L, 1);
		Real val = CHECK_FLOAT(L, 2);

		ptr->SetRealValue(index, val);

		return 1;
	}
	LUAADD(Object_SetRealField, Player);
	LUAADD(Object_SetRealField, Creature);
	LUAADD(Object_SetRealField, Gameobject);
	LUAADD(Object_SetRealField, Unit);
	LUAADD(Object_SetRealField, Object);
	LUAADD(Object_SetRealField, Projectile);

	LUAFUNC int Object_GetEntry(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_UINT32(L, ptr->GetEntry());
		return 1;
	}
	LUAADD(Object_GetEntry, Player);
	LUAADD(Object_GetEntry, Creature);
	LUAADD(Object_GetEntry, Gameobject);
	LUAADD(Object_GetEntry, Unit);
	LUAADD(Object_GetEntry, Object);
	LUAADD(Object_GetEntry, Projectile);

	LUAFUNC int Object_GetScale(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		PUSH_FLOAT(L, ptr->GetScale());
		return 1;
	}
	LUAADD(Object_GetScale, Player);
	LUAADD(Object_GetScale, Creature);
	LUAADD(Object_GetScale, Gameobject);
	LUAADD(Object_GetScale, Unit);
	LUAADD(Object_GetScale, Object);
	LUAADD(Object_GetScale, Projectile);

	LUAFUNC int Object_SetScale(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		Real val = CHECK_FLOAT(L, 1);

		ptr->SetScale(val);

		return 1;
	}
	LUAADD(Object_SetScale, Player);
	LUAADD(Object_SetScale, Creature);
	LUAADD(Object_SetScale, Gameobject);
	LUAADD(Object_SetScale, Unit);
	LUAADD(Object_SetScale, Object);
	LUAADD(Object_SetScale, Projectile);
}
