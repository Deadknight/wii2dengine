#include "Stdafx.h"

namespace luaScriptObject
{
	LUAFUNC int ScriptObject_SetCanUpdate(lua_State * L, T * ptr)
	{
		int32 val = CHECK_INT32(L, 1);
		ptr->SetCanUpdate(val);
		return 1;
		return 1;
	}
	LUAADD(ScriptObject_SetCanUpdate, ScriptObject);
}