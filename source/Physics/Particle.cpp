#include <assert.h>
#include "Stdafx.h"

Particle::Particle()
{
	objectType = POT_PARTICLE;
	velocity = Vector3(0, 0, 0);
	forceAccum = Vector3(0, 0, 0);
	acceleration = Vector3(0, 0, 0);
}

Particle::~Particle()
{
}

bool Particle::Simulate(Real duration)
{
    // We don't integrate things with zero mass.
    if (inverseMass <= 0.0f) return false;

    assert(duration > 0.0);

	//Update Particle Forces
	PFGSET::iterator itr = pfgList.begin();
	for(; itr != pfgList.end(); ++itr)
	{
		(*itr)->pfg->UpdateForce(this, duration);
	}

    // Update linear position.
    position.addScaledVector(velocity, duration);

    // Work out the acceleration from the force
    Vector3 resultingAcc = acceleration;
    resultingAcc.addScaledVector(forceAccum, inverseMass);

    // Update linear velocity from the acceleration.
    velocity.addScaledVector(resultingAcc, duration);

    // Impose drag.
    velocity *= powf(damping, duration);

    // Clear the forces.
    ClearAccumulator();

	return false;
}

Real Particle::GetMass() const
{
    if (inverseMass == 0) 
        return REAL_MAX;
	else 
        return ((Real)1.0)/inverseMass;
}

void Particle::SetMass(const Real mass)
{
    assert(mass != 0);
    Particle::inverseMass = ((Real)1.0)/mass;
}

Real Particle::GetInverseMass() const
{
    return inverseMass;
}

void Particle::SetInverseMass(const Real inverseMass)
{
    Particle::inverseMass = inverseMass;
}

bool Particle::HasFiniteMass() const
{
    return inverseMass >= 0.0f;
}

Real Particle::GetDamping() const
{
    return damping;
}

void Particle::SetDamping(const Real damping)
{
    Particle::damping = damping;
}

void Particle::GetPosition(Vector3 *position) const
{
    *position = Particle::position;
}

Vector3 Particle::GetPosition() const
{
    return position;
}

void Particle::SetPosition(const Vector3 &position)
{
    Particle::position = position;
}

void Particle::SetPosition(const Real x, const Real y, const Real z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void Particle::GetVelocity(Vector3 *velocity) const
{
    *velocity = Particle::velocity;
}

Vector3 Particle::GetVelocity() const
{
    return velocity;
}

void Particle::SetVelocity(const Vector3 &velocity)
{
    Particle::velocity = velocity;
}

void Particle::SetVelocity(const Real x, const Real y, const Real z)
{
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
}

void Particle::GetAcceleration(Vector3 *acceleration) const
{
    *acceleration = Particle::acceleration;
}

Vector3 Particle::GetAcceleration() const
{
    return acceleration;
}

void Particle::SetAcceleration(const Vector3 &acceleration)
{
    Particle::acceleration = acceleration;
}

void Particle::SetAcceleration(const Real x, const Real y, const Real z)
{
    acceleration.x = x;
    acceleration.y = y;
    acceleration.z = z;
}

void Particle::AddForce(const Vector3 &force)
{
    forceAccum += force;
}

void Particle::AddForceGenerator(std::string name, ParticleForceGenerator* pfg)
{
	ParticleForce *pf = new ParticleForce();
	pf->name = name;
	pf->pfg = pfg;
	pfgList.insert(pf);
}

void Particle::RemoveForceGenerator(std::string name)
{
	ParticleForce *pf = NULL;
	PFGSET::iterator itr = pfgList.begin();
	for(; itr != pfgList.end(); )
	{
		if((*itr)->name == name)
		{
			pf = (*itr);
			break;
		}
	}
	if(pf)
	{
		delete pf->pfg;
		delete pf;
		pfgList.erase(itr);
	}
}

void Particle::RemoveForceGenerator(ParticleForceGenerator *pfg)
{
	ParticleForce *pf = NULL;
	PFGSET::iterator itr = pfgList.begin();
	for(; itr != pfgList.end(); )
	{
		if((*itr)->pfg == pfg)
		{
			pf = (*itr);
			break;
		}
	}
	if(pf)
	{
		delete pf->pfg;
		delete pf;
		pfgList.erase(itr);
	}
}

void Particle::ClearForceGenerators()
{
	PFGSET::iterator itr = pfgList.begin();
	for(; itr != pfgList.end(); )
	{
		ParticleForce *pf = (*itr);
		++itr;
		delete pf->pfg;
		delete pf;
	}
	pfgList.clear(); 
}

void Particle::ClearAccumulator()
{
    forceAccum = Vector3::ZERO;
}


