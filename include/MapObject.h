#ifndef MAPOBJECT_H
#define MAPOBJECT_H

class MapObject : public Object
{
public:
	MapObject(uint64 guid);
	~MapObject();

	virtual void Init(const char* name, uint32 entry);
	virtual void Draw(int32 x, int32 y);
	virtual void Update(Real duration);

	void SetCanUpdate(bool val) { m_canUpdate = val; }
	void SetCanRepeat(bool val) { m_canRepeat = val; }
	void SetCanBreakable(bool val) { m_canBreakable = val; }

private:
	bool m_triggered;
	bool m_canUpdate;
	bool m_canRepeat;
	bool m_canBreakable;

	ML_Sprite *m_spr;
	std::string m_sprName;
	uint32 _fields[BASIC_END];
};

#endif