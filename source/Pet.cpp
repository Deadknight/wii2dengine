#include "Stdafx.h"

Pet::Pet(uint64 guid) : Creature(guid)
{
}

Pet::~Pet()
{
}

void Pet::Update(Real duration)
{
	Creature::Update(duration);
}
