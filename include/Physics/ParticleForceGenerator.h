#ifndef PARTICLEFORCEGENERATOR_H
#define PARTICLEFORCEGENERATOR_H

/**     
 * A force generator can be asked to add a force to one or more
 * particles.
 */
class ParticleForceGenerator
{
public:

    /**
     * Overload this in implementations of the interface to calculate
     * and update the force applied to the given particle.
     */
    virtual void UpdateForce(Particle *particle, Real duration) = 0;
};

/**
 * A force generator that applies a gravitational force. One instance
 * can be used for multiple particles.
 */
class ParticleGravity : public ParticleForceGenerator
{
    /** Holds the acceleration due to gravity. */
    Vector3 gravity;

public:

    /** Creates the generator with the given acceleration. */
    ParticleGravity(const Vector3 &gravity);

    /** Applies the gravitational force to the given particle. */
    virtual void UpdateForce(Particle *particle, Real duration);
};

/**
 * A force generator that applies a drag force. One instance
 * can be used for multiple particles.
 */
class ParticleDrag : public ParticleForceGenerator
{
    /** Holds the velocity drag coeffificent. */
    Real k1;

    /** Holds the velocity squared drag coeffificent. */
    Real k2;

public:

    /** Creates the generator with the given coefficients. */
    ParticleDrag(Real k1, Real k2);

    /** Applies the drag force to the given particle. */
    virtual void UpdateForce(Particle *particle, Real duration);
};

/**
 * A force generator that applies a Spring force, where
 * one end is attached to a fixed point in space.
 */
class ParticleAnchoredSpring : public ParticleForceGenerator
{
protected:
    /** The location of the anchored end of the spring. */
    Vector3 *anchor;

    /** Holds the sprint constant. */
    Real springConstant;

    /** Holds the rest length of the spring. */
    Real restLength;

public:
	ParticleAnchoredSpring();

    /** Creates a new spring with the given parameters. */
    ParticleAnchoredSpring(Vector3 *anchor,
						   Real springConstant, 
						   Real restLength);

	/** Retrieve the anchor point. */
	const Vector3* GetAnchor() const { return anchor; }

	/** Set the spring's properties. */
	void Init(Vector3 *anchor,
			  Real springConstant, 
			  Real restLength);

    /** Applies the spring force to the given particle. */
    virtual void UpdateForce(Particle *particle, Real duration);
};

/**
* A force generator that applies a bungee force, where
* one end is attached to a fixed point in space.
*/
class ParticleAnchoredBungee : public ParticleAnchoredSpring
{
public:
	ParticleAnchoredBungee();

    /** Creates a new spring with the given parameters. */
    ParticleAnchoredBungee(Vector3 *anchor,
						   Real springConstant, 
						   Real restLength);
						   
	/** Applies the spring force to the given particle. */
	virtual void UpdateForce(Particle *particle, Real duration);
};

/**
 * A force generator that fakes a stiff spring force, and where
 * one end is attached to a fixed point in space.
 */
class ParticleFakeSpring : public ParticleForceGenerator
{
    /** The location of the anchored end of the spring. */
    Vector3 *anchor;

    /** Holds the sprint constant. */
    Real springConstant;

    /** Holds the damping on the oscillation of the spring. */
    Real damping;

public:

    /** Creates a new spring with the given parameters. */
    ParticleFakeSpring(Vector3 *anchor, Real springConstant,
        Real damping);

    /** Applies the spring force to the given particle. */
    virtual void UpdateForce(Particle *particle, Real duration);
};

/**
 * A force generator that applies a Spring force.
 */
class ParticleSpring : public ParticleForceGenerator
{
    /** The particle at the other end of the spring. */
    Particle *other;

    /** Holds the sprint constant. */
    Real springConstant;

    /** Holds the rest length of the spring. */
    Real restLength;

public:

    /** Creates a new spring with the given parameters. */
    ParticleSpring(Particle *other,
        Real springConstant, Real restLength);

    /** Applies the spring force to the given particle. */
    virtual void UpdateForce(Particle *particle, Real duration);
};

/**
 * A force generator that applies a spring force only
 * when extended.
 */
class ParticleBungee : public ParticleForceGenerator
{
    /** The particle at the other end of the spring. */
    Particle *other;

    /** Holds the sprint constant. */
    Real springConstant;

    /**
     * Holds the length of the bungee at the point it begins to
     * generator a force.
     */
    Real restLength;

public:

    /** Creates a new bungee with the given parameters. */
    ParticleBungee(Particle *other,
        Real springConstant, Real restLength);

    /** Applies the spring force to the given particle. */
    virtual void UpdateForce(Particle *particle, Real duration);
};

/**
 * A force generator that applies a buoyancy force for a plane of
 * liquid parrallel to XZ plane.
 */
class ParticleBuoyancy : public ParticleForceGenerator
{
    /**
     * The maximum submersion depth of the object before
     * it generates its maximum boyancy force.
     */
    Real maxDepth;

    /**
     * The volume of the object.
     */
    Real volume;

    /**
     * The height of the water plane above y=0. The plane will be
     * parrallel to the XZ plane.
     */
    Real waterHeight;

    /**
     * The density of the liquid. Pure water has a density of
     * 1000kg per cubic meter.
     */
    Real liquidDensity;

public:

    /** Creates a new buoyancy force with the given parameters. */
    ParticleBuoyancy(Real maxDepth, Real volume, Real waterHeight,
        Real liquidDensity = 1000.0f);

    /** Applies the buoyancy force to the given particle. */
    virtual void UpdateForce(Particle *particle, Real duration);
};

#endif
