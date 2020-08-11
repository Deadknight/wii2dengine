#include "Stdafx.h"

Firework::Firework(unsigned maxSplitP)
{
	allend = false;
	maxSplit = maxSplitP;
}

Firework::~Firework()
{
	std::vector<Firework*>::iterator itr = m_fireworkList.begin();
	for(; itr != m_fireworkList.end(); )
	{
		Firework *fw = (*itr);
		itr++;
		delete fw;
	}
}

void Firework::Init(FireworkRule *frP)
{
	fr = frP;
	Random *r = new Random();
	fr->Create(this, NULL);
	int randomVal = r->RandomInt(maxSplit);
	//int randomVal = maxSplit;
	for(int i = 0; i < randomVal; i++)
	{
		AddFirework(fr);
	}
	delete r;
}

void Firework::AddFirework(FireworkRule *fr)
{
	Firework *fw = new Firework(0);
	fr->Create(fw, this);
	m_fireworkList.push_back(fw);
}

bool Firework::Simulate(Real duration)
{
	//FixMe add sleep here
	if(allend)
		return false;

	Particle::Simulate(duration);

    // We work backwards from our age to zero.
    age -= duration;
    allend = (age <= 0);

	std::vector<Firework*>::iterator itr = m_fireworkList.begin();
	for(; itr != m_fireworkList.end(); ++itr)
		allend = (*itr)->Simulate(duration);

	return allend;
}
