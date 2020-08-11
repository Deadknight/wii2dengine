#include "gmMachine.h"
#include "gmUserObject.h"
#include "gmCall.h"

#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

/** Forward Declarations
 */
class Creature;
class Gameobject;
class Player;
class Weapon;
class Projectile;
class MapObject;
class ScriptObject;

/** @class ScriptEngine
 * Provides an interface for creatures to interface with serverside scripts. This class is created
 * once per instance.
 */

class ScriptEngine
{
	/** gmMachine Instance
	 */
	gmMachine * m_machine;

public:
	/** gmType variables (for player, unit, gameobject)
	 */
	gmType m_creatureType;
	gmType m_gameobjectType;
	gmType m_playerType;
	gmType m_unitType;
	gmType m_weaponType;
	gmType m_projectileType;
	gmType m_mapobjectType;
	gmType m_scriptobjectType;
	gmType m_scriptEngineType;
	
	/** Allowed pointer types
	 */
	std::list<gmType> m_allowedTypes;

protected:
	/** ScriptMap - binding of events to gm functions
	 */
	 //Windows
	/*typedef stdext::hash_map<uint32, std::map<uint32, gmFunctionObject*> > ScriptMap;
	typedef stdext::hash_map<uint32, gmFunctionObject*> SingleScriptMap;*/
	typedef __gnu_cxx::hash_map<uint32, std::map<uint32, gmFunctionObject*> > ScriptMap;
	typedef __gnu_cxx::hash_map<uint32, gmFunctionObject*> SingleScriptMap;
	ScriptMap m_creatureMap;
	ScriptMap m_gameobjectMap;
	ScriptMap m_playerMap;
	ScriptMap m_weaponMap;
	ScriptMap m_projectileMap;
	ScriptMap m_mapobjectMap;
	ScriptMap m_scriptobjectMap;

	/** Mutex - ensures a script isn't executed twice at once
	 */
	Mutex m_lock;
	Mutex m_creatureLock;
	Mutex m_gameobjectLock;
	Mutex m_playerLock;
	Mutex m_weaponLock;
	Mutex m_projectileLock;
	Mutex m_mapobjectLock;
	Mutex m_scriptobjectLock;

public:

	/** Lock Grabber
	 */
	inline Mutex & GetLock() { return m_lock; }

	/** User objects, used in passing of arguments and used for 'this' pointer.
	 */
	gmVariable m_variables[10];
	gmUserObject * m_userObjects[10];
	
	/** UserObject counter */
	uint32 m_userObjectCounter;

protected:
	/** Gets the function table of scriptable exports.
	 */
	void SetCreatureFunctionTable();
	void SetGameobjectFunctionTable();
	void SetPlayerFunctionTable();
	void SetWeaponFunctionTable();
	void SetProjectileFunctionTable();
	void SetMapObjectFunctionTable();
	void SetScriptObjectFunctionTable();
	void SetScriptEngineFunctionTable();

public:
	/** Function pointer setting/adding public functions
	 */
	inline void AddCreatureEvent(uint32 Entry, uint32 Type, gmFunctionObject * func) { m_creatureMap[Entry].insert( std::make_pair( Type, func ) ); }
	inline void AddGameobjectEvent(uint32 Entry, uint32 Type, gmFunctionObject * func) { m_gameobjectMap[Entry].insert( std::make_pair( Type, func ) ); }
	inline void AddPlayerEvent(uint32 Entry, uint32 Type, gmFunctionObject * func) { m_playerMap[Entry].insert( std::make_pair( Type, func ) ); }
	inline void AddWeaponEvent(uint32 Entry, uint32 Type, gmFunctionObject * func) { m_weaponMap[Entry].insert( std::make_pair( Type, func ) ); }
	inline void AddProjectileEvent(uint32 Entry, uint32 Type, gmFunctionObject * func) { m_projectileMap[Entry].insert( std::make_pair( Type, func ) ); }
	inline void AddMapObjectEvent(uint32 Entry, uint32 Type, gmFunctionObject * func) { m_mapobjectMap[Entry].insert( std::make_pair( Type, func ) ); }
	inline void AddScriptObjectEvent(uint32 Entry, uint32 Type, gmFunctionObject * func) { m_scriptobjectMap[Entry].insert( std::make_pair( Type, func ) ); }

	/** Constructor - does nothing but nulls out variables
	 */
	ScriptEngine();

	/** Destructor - does nothing but frees pointers
	 */
	~ScriptEngine();

	/** Reloads the script system, recompiling all scripts and registering any functions.
	 */
	void Reload(const char * root);

	/** Executes a script file
	 */
	void ExecuteScriptFile(const char * filename);

	/** Dumps the error log from the script engine
	 */
	std::string DumpErrors();

	/** Sets up a gm call with the specified number of arguments
	 */
	void DoGMCall(gmFunctionObject * obj, uint32 ArgumentCount, int * return_value);

	/** Sets up a userobject and variable to this type and pointer.
	 */
	inline void SetVariable(uint32 Index, void * Pointer, gmType Type)
	{
		m_userObjects[Index]->m_userType = Type;
		m_userObjects[Index]->m_user = Pointer;
		m_variables[Index].SetUser(m_userObjects[Index]);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/** Looks up a script on creature event and executes it.
	 */
	void FillVariable(int index, void *val, MYTYPE type);
	bool OnCreatureEvent(Creature *pCreature, gmFunctionObject *pointer);
	bool OnCreatureEvent(Creature *pCreature, uint32 Event, uint32 ArgCount, ...);
	bool OnGameobjectEvent(Gameobject *pGameobject, gmFunctionObject *pointer);
	bool OnGameobjectEvent(Gameobject *pGameobject, uint32 Event, uint32 ArgCount, ...);
	bool OnPlayerEvent(Player *pPlayer, gmFunctionObject *pointer);
	bool OnPlayerEvent(Player *pPlayer, uint32 Event, uint32 ArgCount, ...);
	bool OnWeaponEvent(Weapon *pWeapon, gmFunctionObject *pointer);
	bool OnWeaponEvent(Weapon *pWeapon, uint32 Event, uint32 ArgCount, ...);
	bool OnProjectileEvent(Projectile *pProjectile, gmFunctionObject *pointer);
	bool OnProjectileEvent(Projectile *pProjectile, uint32 Event, uint32 ArgCount, ...);
	bool OnMapObjectEvent(MapObject *pMap, gmFunctionObject *pointer);
	bool OnMapObjectEvent(MapObject *pMap, uint32 Event, uint32 ArgCount, ...);
	bool OnScriptObjectEvent(ScriptObject *pMap, gmFunctionObject *pointer);
	bool OnScriptObjectEvent(ScriptObject *pMap, uint32 Event, uint32 ArgCount, ...);

	/*bool OnLayerEvent(Object * pObject, gmFunctionObject * pointer);
	bool OnLayerEvent(Layer* pLayer, Object * pObject, uint32 Event);*/
	/*bool OnLayerEventArg(Creature * pCreature, uint32 Argument, uint32 Event);*/

	/** Returns the machine
	 */
	inline gmMachine * GetMachine() { return m_machine; }

	/** Has event of type?
	 */
	bool HasEventType(uint32 Entry, uint32 Event);

	/** Calls a function
	 */
	bool CallGMFunction(const char * name, void* forthis, gmType type);
};

/* gonna make one global scriptengine for testing */
extern ScriptEngine * ScriptSystem;

#endif

