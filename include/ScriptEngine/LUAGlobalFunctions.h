#ifndef __LUA_GLOBALFUNCTIONS_H
#define __LUA_GLOBALFUNCTIONS_H

namespace luaGlobalFunctions {

	//static int GetLUAEngine(lua_State * L);
	//static int PerformIngameSpawn(lua_State * L);
	//static int GetPlayer(lua_State * L);
	//static int CharDBQuery(lua_State * L);
	//static int WorldDBQuery(lua_State * L);
	//static int SendWorldMessage(lua_State * L);
	//static int GetLuaEngineVersion(lua_State * L);
	//static int GetGameTime(lua_State * L);
	//static int ReloadTable(lua_State * L);
	//static int ReloadLuaEngine(lua_State * L);
	//static int Rehash(lua_State * L);
	//static int logcol(lua_State * L);
	//static int GetPlayersInWorld(lua_State * L);
	////static int GetInstanceIdsByMap(lua_State * L);
	////static int SendPvPCaptureMessage(lua_State * L);
	//static int GetPlayersInMap(lua_State * L);
	//static int GetPlayersInZone(lua_State * L);
	////static int RemoveTimedEvent(lua_State * L);
	//static int SendMail(lua_State * L);
	////static int CreateChannel(lua_State * L); add these!
	////static int RemoveChannel(lua_State * L); 
	//static int GetTaxiPath(lua_State * L);
	//static int SetDBCSpellVar(lua_State * L);
	//static int GetDBCSpellVar(lua_State * L);

	void Register(lua_State *L);
}
#endif
