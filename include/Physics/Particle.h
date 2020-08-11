#ifndef _PARTICLE_H
#define _PARTICLE_H

class ParticleForceGenerator;

struct ParticleForce
{
	std::string name;
	ParticleForceGenerator *pfg;
};

class Particle : public PhysicObject
{
public:
	Particle();
	virtual ~Particle();

	typedef std::set<ParticleForce*> PFGSET;

    bool Simulate(Real duration);

    void SetMass(const Real mass);
	Real GetMass() const;

    Real GetInverseMass() const;
    void SetInverseMass(const Real inverseMass);
    bool HasFiniteMass() const;

	Real GetDamping() const;
    void SetDamping(const Real damping);

    void GetPosition(Vector3 *position) const;
    Vector3 GetPosition() const;
    void SetPosition(const Vector3 &position);
    void SetPosition(const Real x, const Real y, const Real z);

    Vector3 GetVelocity() const;
    void GetVelocity(Vector3 *velocity) const;
    void SetVelocity(const Vector3 &velocity);
    void SetVelocity(const Real x, const Real y, const Real z);

    void GetAcceleration(Vector3 *acceleration) const;
    Vector3 GetAcceleration() const;
    void SetAcceleration(const Vector3 &acceleration);
    void SetAcceleration(const Real x, const Real y, const Real z);

    void AddForce(const Vector3 &force);
	void AddForceGenerator(std::string name, ParticleForceGenerator* pfg);
	void RemoveForceGenerator(std::string name);
	//This function is not safe
	void RemoveForceGenerator(ParticleForceGenerator *pfg);
	void ClearForceGenerators();

	void ClearAccumulator();

protected:

	PFGSET pfgList;
	Real inverseMass;
    Real damping;
    Vector3 position;
    Vector3 velocity;
    Vector3 forceAccum;
    Vector3 acceleration;
};

#endif
