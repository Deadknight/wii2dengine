#ifndef __LUAENGINE_H
#define __LUAENGINE_H

//#define CPPSCRIPTING

#include <sys/stat.h>
#include <sys/types.h>

#define LUAFUNC template <typename T>
#define THIS static_cast<T*>(ptr)
#define LUAADD(fname, obj) template int fname<obj>(lua_State *, obj*)
#define LUAFUNCTHISCHECKNULL if(ptr == NULL) return 0;

/** Forward Declarations
 */
class Creature;
class Gameobject;
class Player;
class Unit;
class Object;
class Weapon;
class Projectile;
class MapObject;
class ScriptObject;

class LuaEngine;
#ifdef CPPSCRIPTING
class LuaCreature;
class LuaGameObject;
#endif
template <typename T> class Lunar;
class GUID_MGR;

#ifdef WIN32
	HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

extern LuaEngine g_luaMgr;
#define sLuaMgr g_luaMgr

#define GET_LOCK sLuaMgr.getLock().Acquire();
#define RELEASE_LOCK sLuaMgr.getLock().Release();
#define CHECK_BINDING_ACQUIRELOCK GET_LOCK if(m_binding == NULL) { RELEASE_LOCK return; }

//reg type defines
#define REGTYPE_PLAYER (1 << 0)
#define REGTYPE_CREATURE (1 << 1)
#define REGTYPE_GO (1 << 2)
#define REGTYPE_WEAPON (1 << 3)
#define REGTYPE_PROJECTILE (1 << 4)
#define REGTYPE_MAPOBJECT (1 << 5)
#define REGTYPE_SCRIPTOBJECT (1 << 6)


struct LUALoadScripts
{
	std::set<std::string> luaFiles;
};

struct LuaPlayerBinding { const char * Functions[PLAYER_EVENT_COUNT]; };
struct LuaCreatureBinding { const char * Functions[CREATURE_EVENT_COUNT]; };
struct LuaGameObjectBinding { const char * Functions[GAMEOBJECT_EVENT_COUNT]; };
struct LuaWeaponBinding { const char * Functions[WEAPON_EVENT_COUNT]; };
struct LuaProjectileBinding { const char * Functions[PROJECTILE_EVENT_COUNT]; };
struct LuaMapObjectBinding { const char * Functions[MAPOBJECT_EVENT_COUNT]; };
struct LuaScriptObjectBinding { const char * Functions[SCRIPTOBJECT_EVENT_COUNT]; };

#define CHECK_TYPEID(expected_type) if(!ptr || ptr->GetType() != expected_type) { return 0; }
#define CHECK_TYPEID_RET(expected_type) if(!ptr || ptr->GetType() != expected_type) { lua_pushboolean(L,0); return 1; }
#define CHECK_TYPEID_RET_INT(expected_type) if(!ptr || ptr->GetType() != expected_type) { lua_pushinteger(L,0); return 1; }

#define CHECK_PLAYER(L,narg) static_cast<Player*>(CHECK_CREATURE(L,narg))
#define CHECK_CREATURE(L,narg) sLuaMgr.CheckUnit(L,narg)
#define CHECK_GO(L,narg) sLuaMgr.CheckGO(L,narg)
#define CHECK_GUID(L, narg) sLuaMgr.CheckGUID(L,narg)
#define CHECK_OBJECT(L, narg) sLuaMgr.CheckObject(L,narg)

#define CHECK_FLOAT(L,narg) (lua_isnoneornil(L,(narg)) ) ? 0.00f : (float)luaL_checknumber(L,(narg)); 
#define CHECK_ULONG(L,narg) (uint32)luaL_checknumber((L),(narg))
#define CHECK_UINT32(L,narg) (uint32)luaL_checknumber((L),(narg))
#define CHECK_USHORT(L, narg) (uint16)luaL_checkinteger((L),(narg))
#define CHECK_UINT16(L, narg) (uint16)luaL_checkinteger((L),(narg))
#define CHECK_LONG(L, narg) (int32)luaL_checkinteger((L),(narg))
#define CHECK_INT32(L, narg) (int32)luaL_checkinteger((L),(narg))
#define CHECK_BOOL(L,narg) (lua_toboolean((L),(narg)) > 0) ? true : false
#define CHECK_STRING(L, narg) (lua_tostring((L),(narg)))

#define PUSH_UINT32(L, val) lua_pushinteger(L, (uint32)val)
#define PUSH_INT32(L, val) lua_pushinteger(L, val)
#define PUSH_FLOAT(L, val) lua_pushnumber(L, (float)val)
#define PUSH_STRING(L, val) lua_pushstring(L, val);

#define PUSH_UNIT(L, unit) sLuaMgr.PushUnit(TO_UNIT(unit),L)
#define PUSH_GO(L, go) sLuaMgr.PushGO(static_cast<Gameobject*>(go),L)

template<typename T>
struct RegType
{
	const char * name;
	int(*mfunc)(lua_State*,T*);
};
template<typename T> RegType<T>* GetMethodTable();
template<typename T> const char * GetTClassName();
void report(lua_State*);

class LuaEngine
{
private:
	lua_State * lu; // main state.
	Mutex call_lock;
	Mutex co_lock;

	typedef __gnu_cxx::hash_map<uint32, LuaPlayerBinding> PlayerBindingMap;
	typedef __gnu_cxx::hash_map<uint32, LuaCreatureBinding> CreatureBindingMap;
	typedef __gnu_cxx::hash_map<uint32, LuaGameObjectBinding> GameObjectBindingMap;
	typedef __gnu_cxx::hash_map<uint32, LuaWeaponBinding> WeaponBindingMap;
	typedef __gnu_cxx::hash_map<uint32, LuaProjectileBinding> ProjectileBindingMap;
	typedef __gnu_cxx::hash_map<uint32, LuaMapObjectBinding> MapObjectBindingMap;
	typedef __gnu_cxx::hash_map<uint32, LuaScriptObjectBinding> ScriptObjectBindingMap;
	std::set<lua_State * > m_pendingThreads;

#ifdef CPPSCRIPTING
	//maps to creature, & go script interfaces
	std::multimap<uint32, LuaCreature*> m_cAIScripts;
	std::multimap<uint32, LuaGameObject*> m_gAIScripts;
#endif

	PlayerBindingMap m_playerBinding;
	CreatureBindingMap m_creatureBinding;
	GameObjectBindingMap m_gameobjectBinding;
	WeaponBindingMap m_weaponBinding;
	ProjectileBindingMap m_projectileBinding;
	MapObjectBindingMap m_mapobjectBinding;
	ScriptObjectBindingMap m_scriptobjectBinding;
public:
	~LuaEngine() 
	{
		getLock().Acquire();
		getcoLock().Acquire();
		Unload();
		getLock().Release();
		getcoLock().Release();
	}

	void Startup();
	void LoadScripts(const char *root);
	void Restart();

	void RegisterEvent(uint8 regtype, uint32 id, uint32 evt, const char * func);
	void ResumeLuaThread(lua_State *, int);
	bool BeginCall(const char * func);
	void CallFunction(const char * FuncName, int ref);

	void FillVariable(void *val, MYTYPE type);
	void OnPlayerEvent(Player * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...);
	void OnPlayerEvent(Player * pUnit, uint32 EventType, uint32 ArgCount, ...);
	void OnCreatureEvent(Creature * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...);
	void OnCreatureEvent(Creature * pUnit, uint32 EventType, uint32 ArgCount, ...);
	void OnGameObjectEvent(Gameobject * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...);
	void OnGameObjectEvent(Gameobject * pUnit, uint32 EventType, uint32 ArgCount, ...);
	void OnWeaponEvent(Weapon * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...);
	void OnWeaponEvent(Weapon * pUnit, uint32 EventType, uint32 ArgCount, ...);
	void OnProjectileEvent(Projectile * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...);
	void OnProjectileEvent(Projectile * pUnit, uint32 EventType, uint32 ArgCount, ...);
	void OnMapObjectEvent(MapObject * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...);
	void OnMapObjectEvent(MapObject * pUnit, uint32 EventType, uint32 ArgCount, ...);
	void OnScriptObjectEvent(ScriptObject * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...);
	void OnScriptObjectEvent(ScriptObject * pUnit, uint32 EventType, uint32 ArgCount, ...);

	DEDOSAN_INLINE bool ExecuteCall(uint8 params = 0,uint8 res = 0);
	DEDOSAN_INLINE void EndCall(uint8 res = 0);

	//Wrappers
	DEDOSAN_INLINE Player * CheckPlayer(lua_State * L,int narg) 
	{ 
		if(L == NULL) return Lunar<Player>::check(lu,narg);
		else return Lunar<Player>::check(L,narg);
	}

	DEDOSAN_INLINE Unit * CheckCreature(lua_State * L,int narg) 
	{ 
		if(L == NULL) return Lunar<Creature>::check(lu,narg);
		else return Lunar<Creature>::check(L,narg);
	}

	DEDOSAN_INLINE Gameobject * CheckGO(lua_State * L,int narg) 
	{ 
		if(L == NULL) return Lunar<Gameobject>::check(lu,narg);
		else return Lunar<Gameobject>::check(L,narg);
	}

	DEDOSAN_INLINE uint64 CheckGUID(lua_State * L, int narg) 
	{
		if(L == NULL) return GUID_MGR::check(lu,narg);
		else return GUID_MGR::check(L,narg);
	}

	DEDOSAN_INLINE Object * CheckObject(lua_State * L, int narg) 
	{
		if(L == NULL) return Lunar<Object>::check(lu,narg);
		else return Lunar<Object>::check(L,narg);
	}

	void PushUnit(Object * unit, lua_State * L = NULL);
	void PushGO(Object * go, lua_State * L = NULL);
	void PushGUID(uint64 guid, lua_State * L = NULL);

	DEDOSAN_INLINE void PushBool(bool bewl) 
	{
		if(bewl) 
			lua_pushboolean(lu,1);
		else 
			lua_pushboolean(lu,0);
	}

	DEDOSAN_INLINE void PushNIL(lua_State * L = NULL) 
	{
		if(L == NULL)
			lua_pushnil(lu);
		else
			lua_pushnil(L);
	}

	DEDOSAN_INLINE void PushInt(int32 value) {	lua_pushinteger(lu,value); }
	DEDOSAN_INLINE void PushUInt(uint32 value) { lua_pushnumber(lu,value); }
	DEDOSAN_INLINE void PushFloat(float value) { lua_pushnumber(lu,value);	}
	DEDOSAN_INLINE void PushString(const char * str) { lua_pushstring(lu,str);	}

	void RegisterCoreFunctions();

	DEDOSAN_INLINE Mutex & getLock() { return call_lock; }
	DEDOSAN_INLINE Mutex & getcoLock() { return co_lock; }
	DEDOSAN_INLINE lua_State * getluState() { return lu; }

	LuaPlayerBinding * getPlayerBinding(uint32 Id)
	{
		PlayerBindingMap::iterator itr = m_playerBinding.find(Id);
		return (itr == m_playerBinding.end()) ? NULL : &itr->second;
	}

	LuaCreatureBinding * getCreatureBinding(uint32 Id)
	{
		CreatureBindingMap::iterator itr = m_creatureBinding.find(Id);
		return (itr == m_creatureBinding.end()) ? NULL : &itr->second;
	}

	LuaGameObjectBinding * getGameObjectBinding(uint32 Id)
	{
		GameObjectBindingMap::iterator itr =m_gameobjectBinding.find(Id);
		return (itr == m_gameobjectBinding.end()) ? NULL : &itr->second;
	}

	LuaWeaponBinding * getWeaponBinding(uint32 Id)
	{
		WeaponBindingMap::iterator itr =m_weaponBinding.find(Id);
		return (itr == m_weaponBinding.end()) ? NULL : &itr->second;
	}

	LuaProjectileBinding * getProjectileBinding(uint32 Id)
	{
		ProjectileBindingMap::iterator itr =m_projectileBinding.find(Id);
		return (itr == m_projectileBinding.end()) ? NULL : &itr->second;
	}

	LuaMapObjectBinding * getMapObjectBinding(uint32 Id)
	{
		MapObjectBindingMap::iterator itr =m_mapobjectBinding.find(Id);
		return (itr == m_mapobjectBinding.end()) ? NULL : &itr->second;
	}

	LuaScriptObjectBinding * getScriptObjectBinding(uint32 Id)
	{
		ScriptObjectBindingMap::iterator itr =m_scriptobjectBinding.find(Id);
		return (itr == m_scriptobjectBinding.end()) ? NULL : &itr->second;
	}

	lua_State* getPendingThread(lua_State * threadtosearch)
	{
		std::set<lua_State*>::iterator itr = m_pendingThreads.find(threadtosearch);
		return (itr == m_pendingThreads.end() )? NULL : (*itr);
	}

#ifdef CPPSCRIPTING
	DEDOSAN_INLINE std::multimap<uint32, LuaCreature*> & getLuCreatureMap() { return m_cAIScripts; }
	DEDOSAN_INLINE std::multimap<uint32, LuaGameObject*> & getLuGameObjectMap() { return m_gAIScripts; }
#endif
	DEDOSAN_INLINE std::set<lua_State * > & getPendingThreadSet() { return m_pendingThreads; }

class CLuaThread : public ThreadBase
{
	lua_State * thread;
	int ref;
	public:
		CLuaThread(lua_State * state, int nref) : thread(state), ref(nref) {}
		bool run() {
			//Acquire our coroutine lock here.
			sLuaMgr.getcoLock().Acquire();
			lua_State * expectedThread = NULL;
			lua_State * foundthread = NULL;
			lua_rawgeti(sLuaMgr.getluState(),LUA_REGISTRYINDEX,ref);
			if(lua_isthread(sLuaMgr.getluState(),-1) )
				expectedThread = lua_tothread(sLuaMgr.getluState(),-1);
			foundthread = sLuaMgr.getPendingThread(thread);
			if(expectedThread != NULL && foundthread != NULL) 
			{
				//push ourself on the stack
				lua_pushthread(foundthread);
				//move the thread to the main lu state(and pop it off)
				lua_xmove(foundthread,sLuaMgr.getluState(),1);
				if(lua_rawequal(sLuaMgr.getluState(),-1,-2) )
				{
					int res = lua_resume(expectedThread,lua_gettop(expectedThread));
					if(res != LUA_YIELD && res)
						report(expectedThread);
				}
				luaL_unref(sLuaMgr.getluState(),LUA_REGISTRYINDEX,ref);
			}
			sLuaMgr.getcoLock().Release();
			return true;
		}
};

template <typename T> 
class Lunar
{
public:
	typedef int (*mfp)(lua_State *L, T* ptr);
	typedef struct { const char *name; mfp mfunc; } RegType;

	static void Register(lua_State *L)
	{
		lua_newtable(L);
		int methods = lua_gettop(L);

		luaL_newmetatable(L, GetTClassName<T>());
		int metatable = lua_gettop(L);
		
		luaL_newmetatable(L,"DO NOT TRASH");
		lua_pop(L,1);

		// store method table in globals so that
		// scripts can add functions written in Lua.
		lua_pushvalue(L, methods);
		lua_setfield(L, LUA_GLOBALSINDEX, GetTClassName<T>());

		// hide metatable from Lua getmetatable()
		lua_pushvalue(L, methods);
		lua_setfield(L, metatable, "__metatable");

		lua_pushvalue(L, methods);
		lua_setfield(L, metatable, "__index");

		lua_pushcfunction(L, tostring_T);
		lua_setfield(L, metatable, "__tostring");

		lua_pushcfunction(L, gc_T);
		lua_setfield(L, metatable, "__gc");

		lua_newtable(L);                // mt for method table
		lua_setmetatable(L, methods);

		// fill method table with methods from class T
		for (RegType *l = ((RegType*)GetMethodTable<T>()); l->name; l++) {
			lua_pushstring(L, l->name);
			lua_pushlightuserdata(L, (void*)l);
			lua_pushcclosure(L, thunk, 1);
			lua_settable(L, methods);
		}
		lua_pop(L, 2);  // drop metatable and method table
	}

// push onto the Lua stack a userdata containing a pointer to T object
	static int push(lua_State *L, T *obj, bool gc=false) {
		if (!obj) { lua_pushnil(L); return lua_gettop(L); }
		luaL_getmetatable(L, GetTClassName<T>());  // lookup metatable in Lua registry
		if (lua_isnil(L, -1)) luaL_error(L, "%s missing metatable", GetTClassName<T>());
		int mt = lua_gettop(L);
		T ** ptrHold = (T**)lua_newuserdata(L,sizeof(T**));
		int ud = lua_gettop(L);
		if(ptrHold != NULL)
		{
			*ptrHold = obj;
			lua_pushvalue(L, mt);
			lua_setmetatable(L, -2);
			char name[32];
			tostring(name,obj);
			lua_getfield(L,LUA_REGISTRYINDEX,"DO NOT TRASH");
			if(lua_isnil(L,-1) )
			{
				luaL_newmetatable(L,"DO NOT TRASH");
				lua_pop(L,1);
			}
			lua_getfield(L,LUA_REGISTRYINDEX,"DO NOT TRASH");
			if(gc == false)
			{
				lua_pushboolean(L,1);
				lua_setfield(L,-2,name);
			}
			lua_pop(L,1);
		}
		lua_settop(L,ud);
		lua_replace(L, mt);
		lua_settop(L, mt);
		return mt;  // index of userdata containing pointer to T object
	}

// get userdata from Lua stack and return pointer to T object
	static T *check(lua_State *L, int narg) {
		T ** ptrHold = static_cast<T**>(lua_touserdata(L,narg));
		if(ptrHold == NULL)
			return NULL;
		return *ptrHold;
	}

	private:
	Lunar();  // hide default constructor

	// member function dispatcher
	static int thunk(lua_State *L) {
		// stack has userdata, followed by method args
		T *obj = check(L, 1);  // get 'self', or if you prefer, 'this'
		lua_remove(L, 1);  // remove self so member function args start at index 1
		// get member function from upvalue
		RegType *l = static_cast<RegType*>(lua_touserdata(L, lua_upvalueindex(1)));
		//return (obj->*(l->mfunc))(L);  // call member function
		return l->mfunc(L,obj);
	}

	// garbage collection metamethod
	static int gc_T(lua_State *L) 
	{
		T * obj = check(L,1);
		if(obj == NULL)
			return 0;
		lua_getfield(L,LUA_REGISTRYINDEX,"DO NOT TRASH");
		if(lua_istable(L,-1) )
		{
			char name[32];
			tostring(name,obj);
			lua_getfield(L,-1,std::string(name).c_str());
			if(lua_isnil(L,-1) )
			{
				delete obj;
				obj = NULL;
			}
		}
		lua_pop(L,3);
		return 0;
	}
	static int tostring_T (lua_State *L) {
		char buff[32];
		T ** ptrHold = (T**)lua_touserdata(L,1);
		T *obj = *ptrHold;
		sprintf(buff, "%p", obj);
		lua_pushfstring(L, "%s (%s)", GetTClassName<T>(), buff);
		return 1;
	}
	DEDOSAN_INLINE static void tostring(char * buff,void * obj)
	{
		sprintf(buff,"%p",obj);
	}
};	
	
class GUID_MGR 
{
	static const char * GetName() { return "SNGUID"; }
public:
	static void Register(lua_State * L) {
		luaL_newmetatable(L,GetName());
		int mt = lua_gettop(L);
		//Hide metatable.
		lua_pushnil(L);
		lua_setfield(L,mt,"__metatable");
		//nil gc method
		lua_pushnil(L);
		lua_setfield(L,mt,"__gc");
		//set our tostring method
		lua_pushcfunction(L,_tostring);
		lua_setfield(L,mt,"__tostring");
		//nil __index field
		lua_pushnil(L);
		lua_setfield(L,mt,"__index");
		//set __newindex method
		lua_pushcfunction(L,_newindex);
		lua_setfield(L,mt,"__newindex");
		//no call method
		lua_pushnil(L);
		lua_setfield(L,mt,"__call");
	}
	static uint64 check(lua_State * L, int narg) 
	{
		uint64 GUID = 0;
		uint64 * ptrHold = (uint64*)lua_touserdata(L,narg);
		if(ptrHold != NULL)
			GUID = *ptrHold;
		return GUID;
	}
	static int push(lua_State *L, uint64 guid)
	{
		int index = 0;
		if(guid == 0) 
		{
			lua_pushnil(L);
			index = lua_gettop(L);
		}
		else
		{
			luaL_getmetatable(L,GetName());
			if(lua_isnoneornil(L,-1) )
				luaL_error(L,"%s metatable not found!. \n",GetName());
			else 
			{
				int mt = lua_gettop(L);
				uint64* guidHold = (uint64*)lua_newuserdata(L,sizeof(uint64));
				int ud = lua_gettop(L);
				if(guidHold == NULL)
					luaL_error(L,"Lua tried to allocate size %d of memory and failed! \n",sizeof(uint64*));
				else
				{
					(*guidHold) = guid;
					lua_pushvalue(L,mt);
					lua_setmetatable(L,ud);
					lua_replace(L,mt);
					lua_settop(L,mt);
					index = mt;
				}
			}
		}
		return index;
	}
private:
	GUID_MGR() {}
	//This method prints formats the GUID in hexform and pushes to the stack.
	static int _tostring(lua_State * L) 
	{
		uint64 GUID = GUID_MGR::check(L,1);
		if(GUID == 0)
			lua_pushnil(L);
		else {
			char buff[32];
			sprintf(buff,I64FMT,GUID);
			lua_pushfstring(L,"%s",buff);
		}
		return 1;
	}
	static int _newindex(lua_State *L) 
	{
		//Remove table, key, and value
		lua_remove(L,1);
		lua_remove(L,1);
		lua_remove(L,1);
		luaL_error(L,"OPERATION PROHIBITED!\n");
		return 0;
	}
};

protected:
	//Hidden methods
	void Unload(); 
	void ScriptLoadDir(char* Dirname, LUALoadScripts *pak);
};
#endif



