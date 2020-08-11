#include "Stdafx.h"

ParticleGravity::ParticleGravity(const Vector3& gravity)
: gravity(gravity)
{
}

void ParticleGravity::UpdateForce(Particle* particle, Real duration)
{
    // Check that we do not have infinite mass
    if (!particle->HasFiniteMass()) return;

    // Apply the mass-scaled force to the particle
    particle->AddForce(gravity * particle->GetMass());
}

ParticleDrag::ParticleDrag(Real k1, Real k2)
: k1(k1), k2(k2)
{
}

void ParticleDrag::UpdateForce(Particle* particle, Real duration)
{
    Vector3 force;
    particle->GetVelocity(&force);

    // Calculate the total drag coefficient
    Real dragCoeff = force.length();
    dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

    // Calculate the final force and apply it
    force.normalise();
    force *= -dragCoeff;
    particle->AddForce(force);
}

ParticleSpring::ParticleSpring(Particle *other, Real sc, Real rl)
: other(other), springConstant(sc), restLength(rl)
{
}

void ParticleSpring::UpdateForce(Particle* particle, Real duration)
{
    // Calculate the vector of the spring
    Vector3 force;
    particle->GetPosition(&force);
    force -= other->GetPosition();

    // Calculate the length of the force
    Real length = force.length();
    length = abs(length - restLength);
    length *= springConstant;

    // Calculate the final force and apply it
    force.normalise();
    force *= -length;
    particle->AddForce(force);
}

ParticleBuoyancy::ParticleBuoyancy(Real maxDepth, 
                                 Real volume, 
                                 Real waterHeight,
                                 Real liquidDensity)
: 
maxDepth(maxDepth), volume(volume), 
waterHeight(waterHeight), liquidDensity(liquidDensity)
{
}

void ParticleBuoyancy::UpdateForce(Particle* particle, Real duration)
{
    // Calculate the submersion depth
    Real depth = particle->GetPosition().y;
   
    // Check if we're out of the water
    if (depth >= waterHeight + maxDepth)
		return;
    Vector3 force(0,0,0);

    // Check if we're at maximum depth
    if (depth <= waterHeight - maxDepth)
    {
        force.y = liquidDensity * volume;
        particle->AddForce(force);
        return;
    }

    // Otherwise we are partly submerged
    force.y = liquidDensity * volume * (depth - maxDepth - waterHeight) / 2 * maxDepth;
    particle->AddForce(force);
}

ParticleBungee::ParticleBungee(Particle *other, Real sc, Real rl)
: other(other), springConstant(sc), restLength(rl)
{
}

void ParticleBungee::UpdateForce(Particle* particle, Real duration)
{
    // Calculate the vector of the spring
    Vector3 force;
    particle->GetPosition(&force);
    force -= other->GetPosition();

    // Check if the bungee is compressed
    Real length = force.length();
    if (length <= restLength) return;

    // Calculate the length of the force
    length = springConstant * (restLength - length);

    // Calculate the final force and apply it
    force.normalise();
    force *= -length;
    particle->AddForce(force);
}

ParticleFakeSpring::ParticleFakeSpring(Vector3 *anchor, Real sc, Real d)
: anchor(anchor), springConstant(sc), damping(d)
{
}

void ParticleFakeSpring::UpdateForce(Particle* particle, Real duration)
{
    // Check that we do not have infinite mass
    if (!particle->HasFiniteMass()) return;

    // Calculate the relative position of the particle to the anchor
    Vector3 position;
    particle->GetPosition(&position);
    position -= *anchor;

    // Calculate the constants and check they are in bounds.
    Real gamma = 0.5f * sqrt(4 * springConstant - damping*damping);
    if (gamma == 0.0f) return;
    Vector3 c = position * (damping / (2.0f * gamma)) + 
        particle->GetVelocity() * (1.0f / gamma);

    // Calculate the target position
    Vector3 target = position * cosf(gamma * duration) + 
        c * sinf(gamma * duration);
    target *= exp(-0.5f * duration * damping);

    // Calculate the resulting acceleration and therefore the force
    Vector3 accel = (target - position) * (1.0f / duration*duration) - 
        particle->GetVelocity() * duration;
    particle->AddForce(accel * particle->GetMass());
}

ParticleAnchoredSpring::ParticleAnchoredSpring()
{
}

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3 *anchor, Real sc, Real rl)
: anchor(anchor), springConstant(sc), restLength(rl)
{
}

void ParticleAnchoredSpring::Init(Vector3 *anchor, Real springConstant, Real restLength)
{
	ParticleAnchoredSpring::anchor = anchor;
	ParticleAnchoredSpring::springConstant = springConstant;
	ParticleAnchoredSpring::restLength = restLength;
}

ParticleAnchoredBungee::ParticleAnchoredBungee()
{
}

ParticleAnchoredBungee::ParticleAnchoredBungee(Vector3 *anchor, Real sc, Real rl)
{
	::ParticleAnchoredSpring(anchor, sc, rl);
}

void ParticleAnchoredBungee::UpdateForce(Particle* particle, Real duration)
{
	// Calculate the vector of the spring
	Vector3 force;
	particle->GetPosition(&force);
	force -= *anchor;

	// Calculate the length of the force
	Real length = force.length();
	if (length < restLength) return;

	length = length - restLength;
	length *= springConstant;

	// Calculate the final force and apply it
	force.normalise();
	force *= -length;
	particle->AddForce(force);
}

void ParticleAnchoredSpring::UpdateForce(Particle* particle, Real duration)
{
    // Calculate the vector of the spring
    Vector3 force;
    particle->GetPosition(&force);
    force -= *anchor;

    // Calculate the length of the force
    Real length = force.length();
    length = abs(length - restLength);
    length *= springConstant;

    // Calculate the final force and apply it
    force.normalise();
    force *= -length;
    particle->AddForce(force);
}
