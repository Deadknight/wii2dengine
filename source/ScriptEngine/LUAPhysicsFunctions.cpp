#include "Stdafx.h"

namespace luaPhysics
{
	LUAFUNC int Physics_SetVelocity(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		Real x = CHECK_FLOAT(L, 1);
		Real y = CHECK_FLOAT(L, 2);
		Real z = CHECK_FLOAT(L, 3);

		if(!ptr->GetCollisionPrimitive())
			return 0;

		ptr->GetCollisionPrimitive()->GetPhysicObject()->SetVelocity(x, y, z);

		return 1;
	}
	LUAADD(Physics_SetVelocity, Player);
	LUAADD(Physics_SetVelocity, Creature);
	LUAADD(Physics_SetVelocity, Gameobject);
	LUAADD(Physics_SetVelocity, Unit);
	LUAADD(Physics_SetVelocity, Object);
	LUAADD(Physics_SetVelocity, Projectile);

	LUAFUNC int Physics_SetDamping(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		Real linear = CHECK_FLOAT(L, 1);
		Real angular = CHECK_FLOAT(L, 2);

		if(!ptr->GetCollisionPrimitive())
			return 0;
		
		ptr->GetCollisionPrimitive()->GetPhysicObject()->SetDamping(linear, angular);
		ptr->GetCollisionPrimitive()->GetPhysicObject()->SetDamping(linear);

		return 1;
	}
	LUAADD(Physics_SetDamping, Player);
	LUAADD(Physics_SetDamping, Creature);
	LUAADD(Physics_SetDamping, Gameobject);
	LUAADD(Physics_SetDamping, Unit);
	LUAADD(Physics_SetDamping, Object);
	LUAADD(Physics_SetDamping, Projectile);

	LUAFUNC int Physics_SetMass(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		Real mass = CHECK_FLOAT(L, 1);

		if(!ptr->GetCollisionPrimitive())
			return 0;
		
		ptr->GetCollisionPrimitive()->GetPhysicObject()->SetMass(mass);

		return 1;
	}
	LUAADD(Physics_SetMass, Player);
	LUAADD(Physics_SetMass, Creature);
	LUAADD(Physics_SetMass, Gameobject);
	LUAADD(Physics_SetMass, Unit);
	LUAADD(Physics_SetMass, Object);
	LUAADD(Physics_SetMass, Projectile);

	LUAFUNC int Physics_SetInverseMass(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		Real imass = CHECK_FLOAT(L, 1);

		if(!ptr->GetCollisionPrimitive())
			return 0;
		
		ptr->GetCollisionPrimitive()->GetPhysicObject()->SetInverseMass(imass);

		return 1;
	}
	LUAADD(Physics_SetInverseMass, Player);
	LUAADD(Physics_SetInverseMass, Creature);
	LUAADD(Physics_SetInverseMass, Gameobject);
	LUAADD(Physics_SetInverseMass, Unit);
	LUAADD(Physics_SetInverseMass, Object);
	LUAADD(Physics_SetInverseMass, Projectile);

	LUAFUNC int Physics_AddForce(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		Real x = CHECK_FLOAT(L, 1);
		Real y = CHECK_FLOAT(L, 2);
		Real z = CHECK_FLOAT(L, 3);

		if(!ptr->GetCollisionPrimitive())
			return 0;

		ptr->GetCollisionPrimitive()->GetPhysicObject()->AddForce(Vector3(x, y, z));

		return 1;
	}
	LUAADD(Physics_AddForce, Player);
	LUAADD(Physics_AddForce, Creature);
	LUAADD(Physics_AddForce, Gameobject);
	LUAADD(Physics_AddForce, Unit);
	LUAADD(Physics_AddForce, Object);
	LUAADD(Physics_AddForce, Projectile);

	LUAFUNC int Physics_AddForceGenerator(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		const char *name = CHECK_STRING(L, 1);
		uint32 type = CHECK_UINT32(L, 2);
		uint64 guid = CHECK_GUID(L, 3);
		Real x1 = CHECK_FLOAT(L, 4);
		Real y1 = CHECK_FLOAT(L, 5);
		Real z1 = CHECK_FLOAT(L, 6);
		Real x2 = CHECK_FLOAT(L, 7);
		Real y2 = CHECK_FLOAT(L, 8);
		Real z2 = CHECK_FLOAT(L, 9);
		Real constant1 = CHECK_FLOAT(L, 10);
		Real constant2 = CHECK_FLOAT(L, 11);

		if(!ptr->GetCollisionPrimitive())
			return 0;

		if(ptr->GetCollisionPrimitive()->GetPhysicObject()->GetType() != POT_RIGID_BODY)
			return 0;

		RigidBody *body = static_cast<RigidBody*>(ptr->GetCollisionPrimitive()->GetPhysicObject());

		switch(type)
		{
		case 1:
			{
				body->AddForceGenerator(name, new Gravity(Vector3(x1, y1, z1)));
			}break;
		case 2:
			{
				Object *obj = sMap.GetObject(guid);
				if(!obj)
					return 0;

				if(obj->GetCollisionPrimitive()->GetPhysicObject()->GetType() != POT_RIGID_BODY)
					return 0;

				body->AddForceGenerator(name, new Spring(Vector3(x1, y1, z1), static_cast<RigidBody*>(obj->GetCollisionPrimitive()->GetPhysicObject()), Vector3(x2, y2, z2), constant1, constant2));
			}break;
		case 3:
			{
				//body->AddForceGenerator(name, new Explosion());
			}break;
		default:
			break;
		};

		return 1;
	}
	LUAADD(Physics_AddForceGenerator, Player);
	LUAADD(Physics_AddForceGenerator, Creature);
	LUAADD(Physics_AddForceGenerator, Gameobject);
	LUAADD(Physics_AddForceGenerator, Unit);
	LUAADD(Physics_AddForceGenerator, Object);
	LUAADD(Physics_AddForceGenerator, Projectile);

	LUAFUNC int Physics_RemoveForceGenerator(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		const char *name = CHECK_STRING(L, 1);

		if(!ptr->GetCollisionPrimitive())
			return 0;

		if(ptr->GetCollisionPrimitive()->GetPhysicObject()->GetType() != POT_RIGID_BODY)
			return 0;

		RigidBody *body = static_cast<RigidBody*>(ptr->GetCollisionPrimitive()->GetPhysicObject());

		body->RemoveForceGenerator(name);

		return 1;
	}
	LUAADD(Physics_RemoveForceGenerator, Player);
	LUAADD(Physics_RemoveForceGenerator, Creature);
	LUAADD(Physics_RemoveForceGenerator, Gameobject);
	LUAADD(Physics_RemoveForceGenerator, Unit);
	LUAADD(Physics_RemoveForceGenerator, Object);
	LUAADD(Physics_RemoveForceGenerator, Projectile);

	LUAFUNC int Physics_GetCollisionFlag(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		if(!ptr->GetCollisionPrimitive())
			return 0;
		PUSH_INT32(L, ptr->GetCollisionPrimitive()->GetCollisionFlag());
		return 1;
	}
	LUAADD(Physics_GetCollisionFlag, Player);
	LUAADD(Physics_GetCollisionFlag, Creature);
	LUAADD(Physics_GetCollisionFlag, Gameobject);
	LUAADD(Physics_GetCollisionFlag, Unit);
	LUAADD(Physics_GetCollisionFlag, Object);
	LUAADD(Physics_GetCollisionFlag, Projectile);

	LUAFUNC int Physics_SetCollisionFlag(lua_State * L, T * ptr)
	{
		LUAFUNCTHISCHECKNULL
		uint32 val = CHECK_UINT32(L, 1);
		if(!ptr->GetCollisionPrimitive())
			return 0;

		ptr->GetCollisionPrimitive()->SetCollisionFlag(val);
		return 1;
	}
	LUAADD(Physics_SetCollisionFlag, Player);
	LUAADD(Physics_SetCollisionFlag, Creature);
	LUAADD(Physics_SetCollisionFlag, Gameobject);
	LUAADD(Physics_SetCollisionFlag, Unit);
	LUAADD(Physics_SetCollisionFlag, Object);
	LUAADD(Physics_SetCollisionFlag, Projectile);
}