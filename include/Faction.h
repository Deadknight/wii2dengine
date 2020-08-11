#ifndef FACTION_H
#define FACTION_H

class Unit;

enum FACTION_TYPES
{
	FACTION_NONE,
	FACTION_PLAYER					= 0x01,
	FACTION_PLAYER_NPC				= 0x02,
	FACTION_PLAYER_HOSTILE_MASK		= 0xF0,
	FACTION_CREATURE				= 0x10,
	FACTION_CREATURE_NPC			= 0x20,
	FACTION_CREATURE_HOSTILE_MASK	= 0x0F
};

class Faction
{
public:
	static bool IsHostile(Unit *one, Unit *two);
	static bool IsFriendly(Unit *one, Unit *two);
	static bool IsAttackable(Unit *one, Unit * two);
};

#endif
