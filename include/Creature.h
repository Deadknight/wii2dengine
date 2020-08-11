#ifndef CREATURE_H
#define CREATURE_H

class Creature : public Unit
{
public:
	Creature(uint64 guid);
	virtual ~Creature();

	virtual void Init(const char* name, uint32 entry);
	virtual void Update(Real duration);
	virtual void OnCollide(CollisionPrimitive *cpTarget);

	void SetName(std::string val) { m_name = val; }

private:
	std::string m_name;

	uint32 _fields[UNIT_END];
	
};

#endif