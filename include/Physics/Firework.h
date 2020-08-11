#ifndef _FIREWORK_H
#define _FIREWORK_H

struct FireworkRule;

class Firework : public Particle
{
public:
	Firework(unsigned maxSplitP);
	~Firework();
	
	void Init(FireworkRule *frP);

	void AddFirework(Firework* fw) {  m_fireworkList.push_back(fw); }

	void AddFirework(FireworkRule *fr);

    bool Simulate(Real duration);

	std::vector<Firework*> GetSubFireworks() { return m_fireworkList; }

	bool allend;
	FireworkRule *fr;
    unsigned type;
    Real age;
	unsigned maxSplit;
	std::vector<Firework*> m_fireworkList;
};

#endif
