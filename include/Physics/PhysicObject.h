#ifndef PHYSIC_OBJECT_H
#define PHYSIC_OBJECT_H

enum PHYSICS_OBJECT_TYPE
{
	POT_PARTICLE,
	POT_RIGID_BODY
};

class PhysicObject
{
public:
	virtual bool Simulate(Real duration) { return true; }
	virtual Vector3 GetPosition() const { return Vector3(0, 0, 0); }
	virtual Vector3 GetRotation() const { return Vector3(0, 0, 0); }
	virtual Quaternion GetOrientation() const { return Quaternion(0, 0, 0, 0); }
	virtual void SetRotation(const Real x, const Real y, const Real z) { };
	virtual Real GetMass() const { return 0; }
	virtual void SetMass(const Real mass) { }
	virtual Real GetInverseMass() const { return 0; }
	virtual void SetInverseMass(const Real inverseMass) { }
	virtual Real GetDamping() const { return 0; }
	virtual void SetDamping(const Real damping) { }
	virtual void SetDamping(const Real ldamping, const Real adamping) { }
	virtual void SetPosition(const Vector3 &position) { }
	virtual void SetPosition(const Real x, const Real y, const Real z) { }
	virtual Vector3 GetVelocity() { return Vector3(0, 0, 0); }
	virtual void SetVelocity(const Real x, const Real y, const Real z) { }
	virtual void AddForce(const Vector3 &force) { }
	virtual void SetCanSleep(const bool canSleep=true) { }

	virtual void ClearAccumulator() { }
	virtual void CalculateDerivedData() { }

	int GetType() { return objectType; }
protected:
	int objectType;
};

#endif
