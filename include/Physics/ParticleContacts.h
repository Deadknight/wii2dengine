#ifndef PARTICLE_CONTACTS_H
#define PARTICLE_CONTACTS_H

class ParticleContactResolver;

/**
 * A Contact represents two objects in contact (in this case
 * ParticleContact representing two Particles). Resolving a
 * contact removes their interpenetration, and applies sufficient
 * impulse to keep them apart. Colliding bodies may also rebound.
 *
 * The contact has no callable functions, it just holds the
 * contact details. To resolve a set of contacts, use the particle
 * contact resolver class.
 */
class ParticleContact
{
	/**
	 * The contact resolver object needs access into the contacts to
	 * set and effect the contact.
	 */
	friend class ParticleContactResolver;


public:
	/**
	 * Holds the particles that are involved in the contact. The
	 * second of these can be NULL, for contacts with the scenery.
	 */
	Particle* particle[2];

	/**
	 * Holds the normal restitution coefficient at the contact.
	 */
	Real restitution;

	/**
	 * Holds the direction of the contact in world coordinates.
	 */
	Vector3 contactNormal;

	/**
	 * Holds the depth of penetration at the contact.
	 */
	Real penetration;

	/** 
	 * Holds the amount each particle is moved by during interpenetration 
	 * resolution. 
	 */
	Vector3 particleMovement[2];

protected:
	/**
	 * Resolves this contact, for both velocity and interpenetration.
	 */
	void Resolve(Real duration);

	/**
	 * Calculates the separating velocity at this contact.
	 */
	Real CalculateSeparatingVelocity() const;

private:
	/**
	 * Handles the impulse calculations for this collision.
	 */
	void ResolveVelocity(Real duration);

	/**
	 * Handles the interpenetration resolution for this contact.
	 */
	void ResolveInterpenetration(Real duration);
};

/**
 * The contact resolution routine for particle contacts. One
 * resolver instance can be shared for the whole simulation.
 */
class ParticleContactResolver
{
protected:
	/**
	 * Holds the number of iterations allowed.
	 */
	unsigned iterations;

	/**
	 * This is a performance tracking value - we keep a record
	 * of the actual number of iterations used.
	 */
	unsigned iterationsUsed;

public:
	/**
	 * Creates a new contact resolver.
	 */
	ParticleContactResolver(unsigned iterations);

	/**
	 * Sets the number of iterations that can be used.
	 */
	void SetIterations(unsigned iterations);

	/**
	 * Resolves a set of particle contacts for both penetration
	 * and velocity.
	 *
	 * Contacts that cannot interact with each other should be
	 * passed to separate calls to resolveContacts, as the
	 * resolution algorithm takes much longer for lots of contacts
	 * than it does for the same number of contacts in small sets.
	 *
	 * @param contactArray Pointer to an array of particle contact
	 * objects.
	 *
	 * @param numContacts The number of contacts in the array to
	 * resolve.
	 *
	 * @param numIterations The number of iterations through the
	 * resolution algorithm. This should be at least the number of
	 * contacts (otherwise some constraints will not be resolved -
	 * although sometimes this is not noticable). If the
	 * iterations are not needed they will not be used, so adding
	 * more iterations may not make any difference. But in some
	 * cases you would need millions of iterations. Think about
	 * the number of iterations as a bound: if you specify a large
	 * number, sometimes the algorithm WILL use it, and you may
	 * drop frames.
	 *
	 * @param duration The duration of the previous integration step.
	 * This is used to compensate for forces applied.
	*/
	void ResolveContacts(ParticleContact *contactArray,	unsigned numContacts, Real duration);
};

/**
 * This is the basic polymorphic interface for contact generators
 * applying to particles.
 */
class ParticleContactGenerator
{
public:
	/**
	 * Fills the given contact structure with the generated
	 * contact. The contact pointer should point to the first
	 * available contact in a contact array, where limit is the
	 * maximum number of contacts in the array that can be written
	 * to. The method returns the number of contacts that have
	 * been written.
	 */
	virtual unsigned AddContact(ParticleContact *contact, unsigned limit) const = 0;
};
#endif
