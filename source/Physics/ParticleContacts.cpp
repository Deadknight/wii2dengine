#include "Stdafx.h"

void ParticleContact::Resolve(Real duration)
{
    ResolveVelocity(duration);
    ResolveInterpenetration(duration);
}

Real ParticleContact::CalculateSeparatingVelocity() const
{
    Vector3 relativeVelocity = particle[0]->GetVelocity();
    if (particle[1]) 
		relativeVelocity -= particle[1]->GetVelocity();
    //return relativeVelocity * contactNormal;
	return relativeVelocity.dotProduct(contactNormal);
}

void ParticleContact::ResolveVelocity(Real duration)
{
    // Find the velocity in the direction of the contact
    Real separatingVelocity = CalculateSeparatingVelocity();

    // Check if it needs to be Resolved
    if (separatingVelocity > 0)
    {
        // The contact is either separating, or stationary - there's
        // no impulse required.
        return;
    }

    // Calculate the new separating velocity
    Real newSepVelocity = -separatingVelocity * restitution;

    // Check the velocity build-up due to acceleration only
    Vector3 accCausedVelocity = particle[0]->GetAcceleration();
    if (particle[1]) 
		accCausedVelocity -= particle[1]->GetAcceleration();
    //Real accCausedSepVelocity = accCausedVelocity * contactNormal * duration;
	Real accCausedSepVelocity = accCausedVelocity.dotProduct(contactNormal) * duration;

    // If we've got a closing velocity due to acelleration build-up,
    // remove it from the new separating velocity
    if (accCausedSepVelocity < 0) 
    {
        newSepVelocity += restitution * accCausedSepVelocity;

        // Make sure we haven't removed more than was 
        // there to remove.
        if (newSepVelocity < 0) 
			newSepVelocity = 0;
    }

    Real deltaVelocity = newSepVelocity - separatingVelocity;

    // We apply the change in velocity to each object in proportion to
    // their inverse mass (i.e. those with lower inverse mass [higher
    // actual mass] get less change in velocity)..
    Real totalInverseMass = particle[0]->GetInverseMass();
    if (particle[1]) 
		totalInverseMass += particle[1]->GetInverseMass();

    // If all particles have infinite mass, then impulses have no effect
    if (totalInverseMass <= 0) 
		return;

    // Calculate the impulse to apply
    Real impulse = deltaVelocity / totalInverseMass;

    // Find the amount of impulse per unit of inverse mass
    Vector3 impulsePerIMass = contactNormal * impulse;

    // Apply impulses: they are applied in the direction of the contact,
    // and are proportional to the inverse mass.
    particle[0]->SetVelocity(particle[0]->GetVelocity() + impulsePerIMass * particle[0]->GetInverseMass());
    if (particle[1])
    {
	    // Particle 1 goes in the opposite direction
        particle[1]->SetVelocity(particle[1]->GetVelocity() + impulsePerIMass * -particle[1]->GetInverseMass());
    }
}

void ParticleContact::ResolveInterpenetration(Real duration)
{
    // If we don't have any penetration, skip this step.
    if (penetration <= 0) 
		return;

	// The movement of each object is based on their inverse mass, so 
	// total that.
    Real totalInverseMass = particle[0]->GetInverseMass();
    if (particle[1]) 
		totalInverseMass += particle[1]->GetInverseMass();

    // If all particles have infinite mass, then we do nothing
    if (totalInverseMass <= 0) 
		return;

    // Find the amount of penetration resolution per unit of inverse mass
    Vector3 movePerIMass = contactNormal * (penetration / totalInverseMass);

	// Calculate the the movement amounts
	particleMovement[0] = movePerIMass * particle[0]->GetInverseMass();
	if (particle[1]) 
	{
		particleMovement[1] = movePerIMass * -particle[1]->GetInverseMass();
	} 
	else 
	{
		particleMovement[1] = Vector3::ZERO;
	}

    // Apply the penetration resolution
    particle[0]->SetPosition(particle[0]->GetPosition() + particleMovement[0]);
    if (particle[1]) 
	{
        particle[1]->SetPosition(particle[1]->GetPosition() + particleMovement[1]);
    }
}

ParticleContactResolver::ParticleContactResolver(unsigned iterations)
: iterations(iterations)
{
}

void ParticleContactResolver::SetIterations(unsigned iterations)
{
    ParticleContactResolver::iterations = iterations;
}

void ParticleContactResolver::ResolveContacts(ParticleContact *contactArray, unsigned numContacts, Real duration)
{
    iterationsUsed = 0;
    while(iterationsUsed < iterations)
    {
        // Find the contact with the largest closing velocity;
        Real max = REAL_MAX;
        unsigned maxIndex = numContacts;
        for (unsigned i = 0; i < numContacts; i++)
        {
            Real sepVel = contactArray[i].CalculateSeparatingVelocity();
            if (sepVel < max && (sepVel < 0 || contactArray[i].penetration > 0))
            {
                max = sepVel;
                maxIndex = i;
            }
        }

		// Do we have anything worth resolving?
		if (maxIndex == numContacts) 
			break;

        // Resolve this contact
        contactArray[maxIndex].Resolve(duration);

		// Update the interpenetrations for all particles
		Vector3 *move = contactArray[maxIndex].particleMovement; 
		for (unsigned i = 0; i < numContacts; i++)
		{
			if (contactArray[i].particle[0] == contactArray[maxIndex].particle[0])
			{
				//contactArray[i].penetration -= move[0] * contactArray[i].contactNormal;
				contactArray[i].penetration -= move[0].dotProduct(contactArray[i].contactNormal);
			}
			else if (contactArray[i].particle[0] == contactArray[maxIndex].particle[1])
			{
				//contactArray[i].penetration -= move[1] * contactArray[i].contactNormal;
				contactArray[i].penetration -= move[1].dotProduct(contactArray[i].contactNormal);
			}
			if (contactArray[i].particle[1])
			{
				if (contactArray[i].particle[1] == contactArray[maxIndex].particle[0])
				{
					//contactArray[i].penetration += move[0] * contactArray[i].contactNormal;
					contactArray[i].penetration += move[0].dotProduct(contactArray[i].contactNormal);
				}
				else if (contactArray[i].particle[1] == contactArray[maxIndex].particle[1])
				{
					//contactArray[i].penetration += move[1] * contactArray[i].contactNormal;
					contactArray[i].penetration += move[1].dotProduct(contactArray[i].contactNormal);
				}
			}
		}

        iterationsUsed++;
    }
}
