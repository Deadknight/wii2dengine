#include "Stdafx.h"

MapObject::MapObject(uint64 guid)
{
	m_objectType = TYPE_MAP;
	m_valuesCount = BASIC_END;
	m_uint32Values = _fields;
	memset(m_uint32Values, 0, (BASIC_END) * sizeof(uint32));
	SetGUID(guid);

	m_triggered = false;
	m_canUpdate = false;
}

MapObject::~MapObject()
{
}

void MapObject::Init(const char* name, uint32 entry)
{
	std::string nameS = name;
	SpriteProp prop;
	m_spr = sResourceMgr.GetSpriteByName(nameS, &prop, MEMORY_MAP);
}

void MapObject::Update(Real duration)
{
	if(m_triggered && m_canUpdate)
	{
		GType dur(MYTYPE_FLOAT, &duration);
		ScriptSystem->OnMapObjectEvent(this, MAPOBJECT_EVENT_UPDATE, 1, &dur);
		sLuaMgr.OnMapObjectEvent(this, MAPOBJECT_EVENT_UPDATE, 1, &dur);
	}
}

void MapObject::Draw(int32 x, int32 y)
{
	if(!m_triggered)
	{
		m_triggered = true;
		ScriptSystem->OnMapObjectEvent(this, MAPOBJECT_EVENT_INIT, 0);
		sLuaMgr.OnMapObjectEvent(this, MAPOBJECT_EVENT_INIT, 0);
	}
	if(m_spr)
		ML_DrawSpriteXY(m_spr, x, y);
}
