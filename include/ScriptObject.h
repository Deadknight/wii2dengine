#ifndef SCRIPTOBJECT_H
#define SCRIPTOBJECT_H

enum MapEventType
{
    MAP_EVENT_LEVEL_START,
    MAP_EVENT_LEVEL_END,
    MAP_EVENT_SCRIPT
};

class ScriptObject : public Object
{
public:
	ScriptObject(uint64 guid);
	~ScriptObject();

	virtual void Init(const char* name, uint32 entry);
	virtual void Draw(int32 x, int32 y);
	virtual void Update(Real duration);

	void SetType(uint8 val) { m_type = val; }
	void SetCanUpdate(bool val) { m_canUpdate = val; }

private:
	bool m_triggered;
	bool m_canUpdate;
	uint8 m_type;

	ML_Sprite *m_spr;
	std::string m_sprName;
	uint32 _fields[BASIC_END];
};

#endif