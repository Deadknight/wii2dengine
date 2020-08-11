#include "StdAfx.h"

int ScriptEngine_RegisterCreatureEvent(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(3);
	//GM_CHECK_STRING_PARAM(name, 0);
	GM_CHECK_INT_PARAM(entry, 0);
	GM_CHECK_INT_PARAM(event, 1);
	GM_CHECK_FUNCTION_PARAM(func, 2);

	GetThisPointer<ScriptEngine>(a_thread)->AddCreatureEvent(entry, event, func);
	return GM_OK;
}

int ScriptEngine_RegisterGameobjectEvent(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(3);
	//GM_CHECK_STRING_PARAM(name, 0);
	GM_CHECK_INT_PARAM(entry, 0);
	GM_CHECK_INT_PARAM(event, 1);
	GM_CHECK_FUNCTION_PARAM(func, 2);

	GetThisPointer<ScriptEngine>(a_thread)->AddGameobjectEvent(entry, event, func);
	return GM_OK;
}

int ScriptEngine_RegisterPlayerEvent(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(3);
	//GM_CHECK_STRING_PARAM(name, 0);
	GM_CHECK_INT_PARAM(entry, 0);
	GM_CHECK_INT_PARAM(event, 1);
	GM_CHECK_FUNCTION_PARAM(func, 2);

	GetThisPointer<ScriptEngine>(a_thread)->AddPlayerEvent(entry, event, func);
	return GM_OK;
}

int ScriptEngine_RegisterWeaponEvent(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(3);
	//GM_CHECK_STRING_PARAM(name, 0);
	GM_CHECK_INT_PARAM(entry, 0);
	GM_CHECK_INT_PARAM(event, 1);
	GM_CHECK_FUNCTION_PARAM(func, 2);
	
	GetThisPointer<ScriptEngine>(a_thread)->AddWeaponEvent(entry, event, func);
	return GM_OK;
}

int ScriptEngine_RegisterProjectileEvent(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(3);
	//GM_CHECK_STRING_PARAM(name, 0);
	GM_CHECK_INT_PARAM(entry, 0);
	GM_CHECK_INT_PARAM(event, 1);
	GM_CHECK_FUNCTION_PARAM(func, 2);

	GetThisPointer<ScriptEngine>(a_thread)->AddProjectileEvent(entry, event, func);
	return GM_OK;
}

int ScriptEngine_RegisterMapObjectEvent(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(3);
	//GM_CHECK_STRING_PARAM(name, 0);
	GM_CHECK_INT_PARAM(entry, 0);
	GM_CHECK_INT_PARAM(event, 1);
	GM_CHECK_FUNCTION_PARAM(func, 2);

	GetThisPointer<ScriptEngine>(a_thread)->AddMapObjectEvent(entry, event, func);
	return GM_OK;
}

int ScriptEngine_RegisterScriptObjectEvent(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(3);
	//GM_CHECK_STRING_PARAM(name, 0);
	GM_CHECK_INT_PARAM(entry, 0);
	GM_CHECK_INT_PARAM(event, 1);
	GM_CHECK_FUNCTION_PARAM(func, 2);

	GetThisPointer<ScriptEngine>(a_thread)->AddScriptObjectEvent(entry, event, func);
	return GM_OK;
}

/* Object Functions */

int Object_GetX(gmThread * a_thread)
{
	Object * pThis = GetThisPointer<Object>(a_thread);
	a_thread->PushInt(pThis->GetPosition().x);
	return GM_OK;
}

int Object_GetY(gmThread * a_thread)
{
	Object * pThis = GetThisPointer<Object>(a_thread);
	a_thread->PushInt(pThis->GetPosition().y);
	return GM_OK;
}

int Object_SetPosition(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(2);
	GM_CHECK_INT_PARAM(x, 0);
	GM_CHECK_INT_PARAM(y, 1);

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->SetPosition(x, y, 0);
	a_thread->Nullify();
	return GM_OK;
}

int Object_GetField(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(index, 0);

	Object * pThis = GetThisPointer<Object>(a_thread);
	a_thread->PushInt(pThis->GetUInt32Value(index));
	return GM_OK;
}

int Object_GetRealField(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(index, 0);

	Object * pThis = GetThisPointer<Object>(a_thread);
	a_thread->PushFloat(pThis->GetRealValue(index));
	return GM_OK;
}

int Object_SetField(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(2);
	GM_CHECK_INT_PARAM(index, 0);
	GM_CHECK_INT_PARAM(value, 1);

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->SetUInt32Value(index, value);
	a_thread->Nullify();
	return GM_OK;
}

int Object_SetRealField(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(2);
	GM_CHECK_INT_PARAM(index, 0);
	GM_CHECK_FLOAT_PARAM(value, 1);

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->SetRealValue(index, value);
	a_thread->Nullify();
	return GM_OK;
}

int Object_GetEntry(gmThread * a_thread)
{
	Object * pThis = GetThisPointer<Object>(a_thread);
	a_thread->PushInt(pThis->GetEntry());
	return GM_OK;
}

int Object_GetScale(gmThread * a_thread)
{
	Object * pThis = GetThisPointer<Object>(a_thread);
	a_thread->PushFloat(pThis->GetScale());
	return GM_OK;
}

int Object_SetScale(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_FLOAT_PARAM(value, 0);

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->SetScale(value);
	a_thread->Nullify();
	return GM_OK;
}

/* Unit Functions */

int GM_CDECL Unit_GetHealth(gmThread * a_thread)
{
	Object * pThis = GetThisPointer<Object>(a_thread);
	a_thread->PushInt(pThis->GetUInt32Value(UNIT_FIELD_HEALTH));
	return GM_OK;
}

int GM_CDECL Unit_SetHealth(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(value, 0);

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->SetUInt32Value(UNIT_FIELD_HEALTH, value);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Unit_GetHealthPercent(gmThread * a_thread)
{
	Object * pThis = GetThisPointer<Object>(a_thread);
	uint32 val = (pThis->GetUInt32Value(UNIT_FIELD_HEALTH) * 100) / pThis->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
	a_thread->PushInt(val);
	return GM_OK;
}

int GM_CDECL Unit_GetHealthMax(gmThread * a_thread)
{
	Object * pThis = GetThisPointer<Object>(a_thread);
	a_thread->PushInt(pThis->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
	return GM_OK;
}

int GM_CDECL Unit_SetHealthMax(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(value, 0);

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->SetUInt32Value(UNIT_FIELD_MAXHEALTH, value);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Unit_GetHealthBase(gmThread * a_thread)
{
	Object * pThis = GetThisPointer<Object>(a_thread);
	a_thread->PushInt(pThis->GetUInt32Value(UNIT_FIELD_BASE_HEALTH));
	return GM_OK;
}

int GM_CDECL Unit_SetHealthBase(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(value, 0);

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->SetUInt32Value(UNIT_FIELD_BASE_HEALTH, value);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Unit_GetMana(gmThread * a_thread)
{
	Object * pThis = GetThisPointer<Object>(a_thread);
	a_thread->PushInt(pThis->GetUInt32Value(UNIT_FIELD_MANA));
	return GM_OK;
}

int GM_CDECL Unit_SetMana(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(value, 0);

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->SetUInt32Value(UNIT_FIELD_MANA, value);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Unit_GetManaPercent(gmThread * a_thread)
{
	Object * pThis = GetThisPointer<Object>(a_thread);
	uint32 val = (pThis->GetUInt32Value(UNIT_FIELD_MANA) * 100) / pThis->GetUInt32Value(UNIT_FIELD_MAXMANA);
	a_thread->PushInt(val);
	return GM_OK;
}

int GM_CDECL Unit_GetManaMax(gmThread * a_thread)
{
	Object * pThis = GetThisPointer<Object>(a_thread);
	a_thread->PushInt(pThis->GetUInt32Value(UNIT_FIELD_MAXMANA));
	return GM_OK;
}

int GM_CDECL Unit_SetManaMax(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(value, 0);

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->SetUInt32Value(UNIT_FIELD_MAXMANA, value);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Unit_GetManaBase(gmThread * a_thread)
{
	Object * pThis = GetThisPointer<Object>(a_thread);
	a_thread->PushInt(pThis->GetUInt32Value(UNIT_FIELD_BASE_MANA));
	return GM_OK;
}

int GM_CDECL Unit_SetManaBase(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(value, 0);

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->SetUInt32Value(UNIT_FIELD_BASE_MANA, value);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Unit_AddWeapon(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(2);
	GM_CHECK_STRING_PARAM(name, 0);
	GM_CHECK_INT_PARAM(id, 1);

	Unit * pThis = GetThisPointer<Unit>(a_thread);
	pThis->AddWeapon(name, id);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Unit_SetSelectedWeapon(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(id, 0);

	Unit * pThis = GetThisPointer<Unit>(a_thread);
	pThis->SetSelectedWeapon(id);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Unit_ChangeSprite(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_STRING_PARAM(sprName, 0);

	//Reload sprite here
	a_thread->Nullify();
	return GM_OK;
}

/* Weapon functions */
int GM_CDECL Weapon_GetProjectileName(gmThread * a_thread)
{
	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	a_thread->PushNewString(pThis->GetProjectileName().c_str(), pThis->GetProjectileName().length());
	return GM_OK;
}

int GM_CDECL Weapon_GetProjectileEntry(gmThread * a_thread)
{
	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	a_thread->PushInt(pThis->GetProjectileEntry());
	return GM_OK;
}

int GM_CDECL Weapon_SetProjectileInfo(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(2);
	GM_CHECK_STRING_PARAM(name, 0)
	GM_CHECK_INT_PARAM(entry, 1);

	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	pThis->SetProjectileName(name);
	pThis->SetProjectileEntry(entry);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Weapon_GetCurrentFireCooldown(gmThread * a_thread)
{
	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	a_thread->PushInt(pThis->GetCurrentFireCooldown());
	return GM_OK;
}

int GM_CDECL Weapon_GetFireCooldown(gmThread * a_thread)
{
	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	a_thread->PushInt(pThis->GetFireCooldown());
	return GM_OK;
}

int GM_CDECL Weapon_SetFireCooldown(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_FLOAT_PARAM(val, 0);

	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	pThis->SetFireCooldown(val);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Weapon_GetCurrentReloadCooldown(gmThread * a_thread)
{
	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	a_thread->PushInt(pThis->GetCurrentReloadCooldown());
	return GM_OK;
}

int GM_CDECL Weapon_GetReloadCooldown(gmThread * a_thread)
{
	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	a_thread->PushInt(pThis->GetReloadCooldown());
	return GM_OK;
}

int GM_CDECL Weapon_SetReloadCooldown(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_FLOAT_PARAM(val, 0);

	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	pThis->SetReloadCooldown(val);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Weapon_GetDamage(gmThread * a_thread)
{
	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	a_thread->PushInt(pThis->GetDamage());
	return GM_OK;
}

int GM_CDECL Weapon_SetDamage(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(val, 0);

	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	pThis->SetDamage(val);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Weapon_GetCurrentMagazine(gmThread * a_thread)
{
	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	a_thread->PushInt(pThis->GetCurrentMagazine());
	return GM_OK;
}

int GM_CDECL Weapon_SetCurrentMagazine(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(val, 0);

	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	pThis->SetCurrentMagazine(val);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Weapon_GetMaxMagazine(gmThread * a_thread)
{
	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	a_thread->PushInt(pThis->GetMaxMagazine());
	return GM_OK;
}

int GM_CDECL Weapon_SetMaxMagazine(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(val, 0);

	Weapon * pThis = GetThisPointer<Weapon>(a_thread);
	pThis->SetMaxMagazine(val);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Weapon_CreateProjectile(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(3);
	GM_CHECK_STRING_PARAM(name, 0);
	GM_CHECK_INT_PARAM(entry, 1);
	GM_CHECK_FLOAT_PARAM(lifeTime, 2);

	sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Create projectile\r\n");

	Weapon *pThis = GetThisPointer<Weapon>(a_thread);
	Projectile *p = pThis->CreateProjectile(name, entry, lifeTime);
	/*ScriptSystem->m_userObjects[9]->m_user = p;
	ScriptSystem->m_userObjects[9]->m_userType = ScriptSystem->m_projectileType;
	a_thread->PushUser(ScriptSystem->m_userObjects[9]);*/
	a_thread->Nullify();
	return GM_OK;
}

/* Projectile functions */
int GM_CDECL Projectile_GetLifeTime(gmThread * a_thread)
{
	Projectile *pThis = GetThisPointer<Projectile>(a_thread);
	a_thread->PushFloat(pThis->GetLifeTime());
	return GM_OK;
}

int GM_CDECL Projectile_GetSpeed(gmThread * a_thread)
{
	Projectile *pThis = GetThisPointer<Projectile>(a_thread);
	a_thread->PushFloat(pThis->GetSpeed());
	return GM_OK;
}

int GM_CDECL Projectile_SetSpeed(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_FLOAT_PARAM(val, 0);

	Projectile *pThis = GetThisPointer<Projectile>(a_thread);
	pThis->SetSpeed(val);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Projectile_GetDirectonX(gmThread * a_thread)
{
	Projectile *pThis = GetThisPointer<Projectile>(a_thread);
	Vector3 vec = pThis->GetDirection();
	a_thread->PushFloat(vec.x);
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Get DirectionX\r\n");
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Projectile_GetDirectonY(gmThread * a_thread)
{
	Projectile *pThis = GetThisPointer<Projectile>(a_thread);
	Vector3 vec = pThis->GetDirection();
	a_thread->PushFloat(vec.y);
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Get DirectionY\r\n");
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Projectile_SetDirecton(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(2);
	GM_CHECK_FLOAT_PARAM(x, 0);
	GM_CHECK_FLOAT_PARAM(y, 1);
	
	Projectile *pThis = GetThisPointer<Projectile>(a_thread);
	pThis->SetDirection(x, y, 0);
	a_thread->Nullify();
	return GM_OK;
}

/* MapObject functions */
int GM_CDECL MapObject_SetCanUpdate(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(val, 0);

	MapObject * pThis = GetThisPointer<MapObject>(a_thread);
	pThis->SetCanUpdate(val);
	a_thread->Nullify();
	return GM_OK;
}

/* ScriptObject functions */
int GM_CDECL ScriptObject_SetCanUpdate(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_INT_PARAM(val, 0);

	ScriptObject * pThis = GetThisPointer<ScriptObject>(a_thread);
	pThis->SetCanUpdate(val);
	a_thread->Nullify();
	return GM_OK;
}

/* Physics functions */
int GM_CDECL Physics_SetVelocity(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(3);
	GM_CHECK_FLOAT_PARAM(x, 0);
	GM_CHECK_FLOAT_PARAM(y, 1);
	GM_CHECK_FLOAT_PARAM(z, 2);
	
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Set Direction %f,%f,%f\r\n", x, y, z);

	Object * pThis = GetThisPointer<Object>(a_thread);	
	pThis->GetCollisionPrimitive()->GetPhysicObject()->SetVelocity(x, y, z);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Physics_SetDamping(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(2);
	GM_CHECK_FLOAT_PARAM(linear, 0);
	GM_CHECK_FLOAT_PARAM(angular, 1);

	sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Set Damping\r\n");

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->GetCollisionPrimitive()->GetPhysicObject()->SetDamping(linear, angular);
	pThis->GetCollisionPrimitive()->GetPhysicObject()->SetDamping(linear);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Physics_SetMass(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_FLOAT_PARAM(mass, 0);

	sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Set Mass\r\n");

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->GetCollisionPrimitive()->GetPhysicObject()->SetMass(mass);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Physics_SetInverseMass(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_FLOAT_PARAM(imass, 0);

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->GetCollisionPrimitive()->GetPhysicObject()->SetInverseMass(imass);
	a_thread->Nullify();
	return GM_OK;
}

int GM_CDECL Physics_AddForce(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(3);
	GM_CHECK_FLOAT_PARAM(x, 0);
	GM_CHECK_FLOAT_PARAM(y, 1);
	GM_CHECK_FLOAT_PARAM(z, 2);

	sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Add Force %f,%f,%f\r\n", x, y, z);

	Object * pThis = GetThisPointer<Object>(a_thread);
	pThis->GetCollisionPrimitive()->GetPhysicObject()->AddForce(Vector3(x, y, z));
	a_thread->Nullify();
	return GM_OK;
}

/* All functions */
int GM_CDECL All_RegisterUpdate(gmThread * a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	GM_CHECK_FUNCTION_PARAM(func, 0);

	//Add this function to update
	a_thread->Nullify();
	return GM_OK;
}

/*void Object_GetDot(gmThread * a_thread, gmVariable * a_operands)
{
  //O_GETDOT = 0,       // object, "member"          (tos is a_operands + 2)
  GM_ASSERT(a_operands[0].m_type == ScriptSystem->m_objectType);


  gmUserObject* userObj = (gmUserObject*) GM_OBJECT(a_operands[0].m_value.m_ref);
  Object* obj = (Object*)userObj->m_user;

  if(!obj)
  {
    a_operands[0].Nullify();

    return;
  }
	
  ScriptSystem->CallGMFunction(a_operands[1].GetCStringSafe(), obj, ScriptSystem->m_objectType);
  //a_thread->PushFunction((gmFunctionObject*) GM_OBJECT(a_operands[0].m_value.m_ref));
  //printf("%u", &a_operands[2]);
  //printf("%u", &a_operands[1]);
  //a_operands[0] = scriptObj->GetTableObject()->Get(a_operands[1]);
}


void Object_SetDot(gmThread * a_thread, gmVariable * a_operands)
{
  //O_SETDOT,           // object, value, "member"   (tos is a_operands + 3)
  GM_ASSERT(a_operands[0].m_type == ScriptSystem->m_objectType);

  gmUserObject* userObj = (gmUserObject*) GM_OBJECT(a_operands[0].m_value.m_ref);
  Object* obj = (Object*)userObj->m_user;

  if(obj)
  {
    //obj->GetTableObject()->Set(a_thread->GetMachine(), a_operands[2], a_operands[1]);
  }
}*/

///////////////////////////////////////
///////// General Functions ///////////
///////////////////////////////////////
