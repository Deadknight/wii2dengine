#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile : public TimedObject
{
public:
	virtual void Init(const char* name, uint32 entry);
	virtual void Update(Real duration);
	virtual void OnCollide(CollisionPrimitive *cpTarget);

	Real GetSpeed() { return m_speed; }
	void SetSpeed(Real val) { m_speed = val; }
	Vector3 GetDirection() { return m_direction; }
	void SetDirection(Vector3 val) { m_direction = val; }
	void SetDirection(Real x, Real y, Real z) { m_direction.x = x; m_direction.y = y; m_direction.z = z; }
protected:
	Vector3 m_direction;
	Real m_speed;
};

#endif
