#include "Stdafx.h"

TimedObject::TimedObject()
{
	m_spr = NULL;
	m_sprInfo = NULL;
	m_objectType = TYPE_TIMEDOBJECT;
	m_valuesCount = BASIC_END;
	m_uint32Values = _fields;	
	memset(m_uint32Values, 0,(BASIC_END)*sizeof(uint32));
}

TimedObject::~TimedObject()
{
	if(m_sprInfo)
		delete m_sprInfo;
	if(cp)
	{
		sPhysicsMgr.RemovePhysicsObject(cp);
		delete cp;
		cp = NULL;
	}		
}

void TimedObject::Init(const char* name, uint32 entry)
{
	SetEntry(entry);
	
	SpriteProp prop;
	m_spr = sResourceMgr.GetSpriteByName(name, &prop, MEMORY_MAP);
	if(m_spr)
	{
		InitPhysics(&prop);
		m_sprInfo = new SpriteInfo();
		//si->body Generate this;
		m_sprInfo->spr = m_spr;
		m_sprInfo->centerX = prop.centerX;
		m_sprInfo->centerY = prop.centerY;		
	}
	else
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Cannot load projectile %s\r\n", name);
		
	if(!cp)
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Cannot load collision primitive %s\r\n", name);
}

void TimedObject::Update(Real duration)
{
	if(m_lifeTime)
	{
		m_lifeTime -= duration;
		if(m_lifeTime <= duration)
			m_lifeTime = 0;
	}
}

void TimedObject::Draw(int32 x, int32 y)
{
	if(!m_spr)
		return;

	ML_DrawSpriteXY(m_spr, x/* - m_sprInfo->centerX*/, y /*- m_sprInfo->centerY*/);
	
	//ML_FillRect(x, y, 5, 5, 0xFFFF0000);
}
