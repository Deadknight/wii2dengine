#include "Stdafx.h"

FireworkRule::FireworkRule()
{
	random = new Random();
}

FireworkRule::~FireworkRule()
{
	delete random;
}

void FireworkRule::Create(Firework *firework, const Firework *parent)
{
    firework->type = type;
    firework->age = random->RandomReal(minAge, maxAge);
	
	Vector3 vel;
	if (parent)
	{
		// The position and velocity are based on the parent.
		firework->SetPosition(parent->GetPosition());
		vel += parent->GetVelocity();
	}
	else
	{
		/*Vector3 start;
		int x = (int)random->RandomInt(3) - 1;
		start.x = 5.0f * Real(x);
		firework->SetPosition(start);*/
	}

    vel += random->RandomVector(minVelocity, maxVelocity);
    firework->SetVelocity(vel);

    // We use a mass of one in all cases (no point having fireworks 
    // with different masses, since they are only under the influence 
    // of gravity).
    firework->SetMass(1);

    firework->SetDamping(damping);

    firework->SetAcceleration(Vector3(0,0.98f,0));

    firework->ClearAccumulator();
}
