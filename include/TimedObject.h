#ifndef TIMEDOBJECT_H
#define TIMEDOBJECT_H

class TimedObject : public Object
{
public:
	TimedObject();
	virtual ~TimedObject();

	virtual void Init(const char* name, uint32 entry);
	virtual void Draw(int32 x, int32 y);
	virtual void Update(Real duration);
	virtual void OnCollide(CollisionPrimitive *cpTarget) { }

	Real GetLifeTime() { return m_lifeTime; }
	void SetLifeTime(Real val) { m_lifeTime = val; }

protected:
	ML_Sprite* m_spr;
	SpriteInfo *m_sprInfo;
	Real m_lifeTime;
	uint32 _fields[BASIC_END];
};

#endif
