#include "Stdafx.h"

ScriptObject::ScriptObject(uint64 guid)
{
	m_objectType = TYPE_SCRIPT;
	m_valuesCount = BASIC_END;
	m_uint32Values = _fields;
	memset(m_uint32Values, 0, (BASIC_END) * sizeof(uint32));
	SetGUID(guid);

	m_triggered = false;
	m_canUpdate = true;
}

ScriptObject::~ScriptObject()
{
}

void ScriptObject::Init(const char* name, uint32 entry)
{
	SetEntry(entry);
}

void ScriptObject::Update(Real duration)
{
	if(m_triggered && m_canUpdate)
	{
		GType dur(MYTYPE_FLOAT, &duration);
		ScriptSystem->OnScriptObjectEvent(this, SCRIPTOBJECT_EVENT_UPDATE, 1, &dur);
		sLuaMgr.OnScriptObjectEvent(this, SCRIPTOBJECT_EVENT_UPDATE, 1, &dur);
	}
}

void ScriptObject::Draw(int32 x, int32 y)
{
	if(!m_triggered)
	{
		m_triggered = true;
		ScriptSystem->OnScriptObjectEvent(this, SCRIPTOBJECT_EVENT_INIT, 0);
		sLuaMgr.OnScriptObjectEvent(this, SCRIPTOBJECT_EVENT_INIT, 0);
	}
}
