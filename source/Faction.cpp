#include "Stdafx.h"

bool Faction::IsHostile(Unit *one, Unit *two)
{
	if(one == two)
		return false;
	if(one->IsDead() || two->IsDead())
		return false;
	if(one->GetUInt32Value(UNIT_FIELD_FACTION) & two->GetUInt32Value(UNIT_FIELD_FACTION_HOSTILE_MASK))
		return true;
	return false;
}

bool Faction::IsFriendly(Unit *one, Unit *two)
{
	if(IsHostile(one, two))
		return false;
	return true;
}

bool Faction::IsAttackable(Unit *one, Unit * two)
{
	if(one->HasFlag(OBJECT_FIELD_FLAG, OBJECT_FLAG_NOT_ATTACKABLE))
		return false;

	if(two->HasFlag(OBJECT_FIELD_FLAG, OBJECT_FLAG_NOT_SELECTABLE))
		return false;

	if(!IsHostile(one, two))
		return false;

	return true;
}
