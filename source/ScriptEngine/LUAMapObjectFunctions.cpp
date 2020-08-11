#include "Stdafx.h"

namespace luaMapObject
{
	LUAFUNC int MapObject_SetCanUpdate(lua_State * L, T * ptr)
	{
		int32 val = CHECK_INT32(L, 1);
		ptr->SetCanUpdate(val);
		return 1;
	}
	LUAADD(MapObject_SetCanUpdate, MapObject);
}
