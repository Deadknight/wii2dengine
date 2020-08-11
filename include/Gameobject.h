#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

enum GAMEOBJECT_STATE
{
	GO_STATE_CLOSED			= 0x1,
	GO_STATE_OPENED			= 0x2,
	GO_STATE_DESTROYED		= 0x8,
	GO_STATE_MASK			= 0xFF
};

enum GAMEOBJECT_FLAG
{
	GO_FLAG_CAN_BE_OPENED	= 0x100,
	GO_FLAG_LOCKED			= 0x200
};

class Gameobject : public Object
{
public:
	Gameobject(uint64 guid);
	~Gameobject();

	virtual void Init(const char* name, uint32 entry);
	virtual void Draw(int32 x, int32 y);
	virtual void Update(Real duration);

	virtual void OnCollide(CollisionPrimitive *cpTarget);

	void SetName(std::string val) { m_name = val; }

private:
	uint32 m_flag;
	uint32 m_lastFlag;
	std::string m_name;
	uint32 _fields[GAMEOBJECT_END];
	ML_Sprite *m_spr;
	std::string m_sprName;
	std::map<uint32, SpriteInfo*> m_spriteMap;
};

#endif
