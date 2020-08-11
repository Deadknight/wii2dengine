#include "Stdafx.h"

SoundObject::SoundObject(uint64 guid)
{
	m_objectType = TYPE_SOUND;
	m_valuesCount = BASIC_END;
	m_uint32Values = _fields;
	memset(m_uint32Values, 0, (BASIC_END) * sizeof(uint32));
	SetGUID(guid);

	m_triggered = false;
	m_canUpdate = true;
	m_loop = false;
}

SoundObject::~SoundObject()
{
}

void SoundObject::Init(const char* name, uint32 entry)
{
	
}

void SoundObject::Update(Real duration)
{
	if(m_triggered && m_canUpdate)
	{
	}
}

void SoundObject::Draw(int32 x, int32 y)
{
	if(!m_triggered)
	{
		m_triggered = true;
	}
}
