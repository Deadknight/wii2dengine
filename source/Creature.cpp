#include "Stdafx.h"

Creature::Creature(uint64 guid)
{
	m_objectType = TYPE_UNIT;
	m_valuesCount = UNIT_END;
	m_uint32Values = _fields;
	memset(m_uint32Values, 0,(UNIT_END)*sizeof(uint32));
	SetGUID(guid);
}

Creature::~Creature()
{

}

void Creature::Init(const char* name, uint32 entry)
{
	Unit::Init(name, entry);
	if(cp && cp->GetPhysicObject())
	{
		cp->SetCollisionFlag(COLLISION_FLAG_CREATURE);
	}
	ScriptSystem->OnCreatureEvent(this, CREATURE_EVENT_INIT, 0);
	sLuaMgr.OnCreatureEvent(this, CREATURE_EVENT_INIT, 0);
}

void Creature::Update(Real duration)
{
	GType val(MYTYPE_FLOAT, &duration);
	ScriptSystem->OnCreatureEvent(this, CREATURE_EVENT_UPDATE, 1, &val);
	sLuaMgr.OnCreatureEvent(this, CREATURE_EVENT_UPDATE, 1, &val);

	Unit::Update(duration);
}

void Creature::OnCollide(CollisionPrimitive *cpTarget)
{
	GType val(MYTYPE_OBJECT, cpTarget->GetOwner());
	ScriptSystem->OnCreatureEvent(this, CREATURE_EVENT_ON_COLLIDE, 1, &val);
	sLuaMgr.OnCreatureEvent(this, CREATURE_EVENT_ON_COLLIDE, 1, &val);
}
