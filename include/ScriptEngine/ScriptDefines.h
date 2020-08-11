#ifndef SCRIPTDEFINES_H
#define SCRIPTDEFINES_H

/* Events */
enum CreatureEvents
{
	CREATURE_EVENT_INIT						= 1,
	CREATURE_EVENT_UPDATE					= 2,
	CREATURE_EVENT_FIRST_SEEN				= 3,
	CREATURE_EVENT_ON_COMBAT_START			= 4,
	CREATURE_EVENT_ON_COMBAT_STOP			= 5,
	CREATURE_EVENT_ON_DIED					= 6,
	CREATURE_EVENT_ON_DAMAGE_TAKEN			= 7,
	CREATURE_EVENT_ON_TARGET_DIED			= 8,
	CREATURE_EVENT_ON_CRIT_HIT				= 9,
	CREATURE_EVENT_ON_HIT					= 10,
	CREATURE_EVENT_ON_DESPAWN				= 11,
	CREATURE_EVENT_ON_FEAR					= 12,
	CREATURE_EVENT_ON_UNFEAR				= 13,
	CREATURE_EVENT_ON_FLEE					= 14,
	CREATURE_EVENT_ON_CALLFORHELP			= 15,
	CREATURE_EVENT_ON_COLLIDE				= 16,
	CREATURE_EVENT_COUNT
};

enum GameobjectEvents
{
	GAMEOBJECT_EVENT_INIT					= 1,
	GAMEOBJECT_EVENT_UPDATE					= 2,
	GAMEOBJECT_EVENT_FIRST_SEEN				= 3,
	GAMEOBJECT_EVENT_ON_ACTIVATE			= 4,
	GAMEOBJECT_EVENT_ON_LOOT_TAKEN			= 5,
	GAMEOBJECT_EVENT_ON_DESPAWN				= 6,
	GAMEOBJECT_EVENT_ON_COLLIDE				= 7,
	GAMEOBJECT_EVENT_COUNT
};

enum PlayerEvents
{
	PLAYER_EVENT_INIT						= 1,
	PLAYER_EVENT_UPDATE						= 2,
	PLAYER_EVENT_ON_COLLIDE					= 3,
	PLAYER_EVENT_COUNT
};

enum WeaponEvents
{
	WEAPON_EVENT_INIT						= 1,
	WEAPON_EVENT_UPDATE						= 2,
	WEAPON_EVENT_FIRE						= 3,
	WEAPON_EVENT_RELOAD						= 4,
	WEAPON_EVENT_COUNT
};

enum ProjectileEvents
{
	PROJECTILE_EVENT_INIT					= 1,
	PROJECTILE_EVENT_UPDATE					= 2,
	PROJECTILE_EVENT_ON_COLLIDE				= 3,
	PROJECTILE_EVENT_COUNT
};

enum MapObjectEvents
{
	MAPOBJECT_EVENT_INIT							= 1,
	MAPOBJECT_EVENT_UPDATE							= 2,
	MAPOBJECT_EVENT_COUNT
};

enum ScriptObjectEvents
{
	SCRIPTOBJECT_EVENT_INIT							= 1,
	SCRIPTOBJECT_EVENT_UPDATE						= 2,
	SCRIPTOBJECT_EVENT_COUNT
};

enum MYTYPE
{
	MYTYPE_INT,
	MYTYPE_FLOAT,
	MYTYPE_STRING,
	MYTYPE_CREATURE,
	MYTYPE_GAMEOBJECT,
	MYTYPE_PLAYER,
	MYTYPE_UNIT,
	MYTYPE_OBJECT,
	MYTYPE_WEAPON,
	MYTYPE_PROJECTILE,
	MYTYPE_MAPOBJECT,
	MYTYPE_SCRIPTOBJECT
};

struct GType
{
	GType(MYTYPE typeP, void *dataP)
	{
		type = typeP;
		data = dataP;
	}
	enum MYTYPE type;
	void* data;
};

#endif
