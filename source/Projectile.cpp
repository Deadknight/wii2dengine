#include "Stdafx.h"

void Projectile::Init(const char* name, uint32 entry)
{
	TimedObject::Init(name, entry);
	Real valX = m_direction.x * 1000.0f;
	Real valY = m_direction.y * 1000.0f;
	static_cast<RigidBody*>(GetCollisionPrimitive()->GetPhysicObject())->AddForce(Vector3(valX, valY, 0.0f));
	GetCollisionPrimitive()->GetPhysicObject()->SetDamping(0.995f, 0.995f);
	GetCollisionPrimitive()->GetPhysicObject()->SetMass(1);
	
	double angle = atan2(m_direction.y, m_direction.x);
	if(angle < 0)
		angle += 2 * M_PI;
	//ML_RotateSprite(m_spr, rot.z*180/R_PI, 0);
	ML_RotateSprite(m_spr, angle*180/R_PI, 0);
	
	ScriptSystem->OnProjectileEvent(this, PROJECTILE_EVENT_INIT, 0);
	sLuaMgr.OnProjectileEvent(this, PROJECTILE_EVENT_INIT, 0);
}

void Projectile::Update(Real duration)
{
	TimedObject::Update(duration);
	GType val(MYTYPE_FLOAT, &duration);
	ScriptSystem->OnProjectileEvent(this, PROJECTILE_EVENT_UPDATE, 1, &val);
	sLuaMgr.OnProjectileEvent(this, PROJECTILE_EVENT_UPDATE, 1, &val);
}

void Projectile::OnCollide(CollisionPrimitive *cpTargeT)
{
	m_lifeTime = 0;
	//Explode?

	GType val(MYTYPE_OBJECT, cpTargeT->GetOwner());
	ScriptSystem->OnProjectileEvent(this, PROJECTILE_EVENT_ON_COLLIDE, 1, &val);
	sLuaMgr.OnProjectileEvent(this, PROJECTILE_EVENT_ON_COLLIDE, 1, &val);
}

