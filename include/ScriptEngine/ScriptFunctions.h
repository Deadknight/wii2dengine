#ifndef SCRIPT_FUNCTIONS_H
#define SCRIPT_FUNCTIONS_H

#include "ScriptEngine.h"

/* Helper Functions */
template<class T>
T * GetThisPointer(gmThread * a_thread)
{
	return (T*)a_thread->ThisUser();
}

/* Script Engine Functions */
	int GM_CDECL ScriptEngine_RegisterCreatureEvent(gmThread * a_thread);
	int GM_CDECL ScriptEngine_RegisterGameobjectEvent(gmThread * a_thread);
	int GM_CDECL ScriptEngine_RegisterPlayerEvent(gmThread * a_thread);
	int GM_CDECL ScriptEngine_RegisterWeaponEvent(gmThread * a_thread);
	int GM_CDECL ScriptEngine_RegisterProjectileEvent(gmThread * a_thread);
	int GM_CDECL ScriptEngine_RegisterMapObjectEvent(gmThread * a_thread);
	int GM_CDECL ScriptEngine_RegisterScriptObjectEvent(gmThread * a_thread);

/* Object Functions */
	int GM_CDECL Object_GetX(gmThread * a_thread);
	int GM_CDECL Object_GetY(gmThread * a_thread);
	int GM_CDECL Object_SetPosition(gmThread * a_thread);
	int GM_CDECL Object_GetField(gmThread * a_thread);
	int GM_CDECL Object_GetRealField(gmThread * a_thread);
	int GM_CDECL Object_SetField(gmThread * a_thread);
	int GM_CDECL Object_SetRealField(gmThread * a_thread);
	int GM_CDECL Object_GetEntry(gmThread * a_thread);
	int GM_CDECL Object_GetScale(gmThread * a_thread);
	int GM_CDECL Object_SetScale(gmThread * a_thread);

/* Unit Functions */
	int GM_CDECL Unit_GetHealth(gmThread * a_thread);
	int GM_CDECL Unit_SetHealth(gmThread * a_thread);
	int GM_CDECL Unit_GetHealthPercent(gmThread * a_thread);
	int GM_CDECL Unit_GetHealthMax(gmThread * a_thread);
	int GM_CDECL Unit_SetHealthMax(gmThread * a_thread);
	int GM_CDECL Unit_GetHealthBase(gmThread * a_thread);
	int GM_CDECL Unit_SetHealthBase(gmThread * a_thread);
	int GM_CDECL Unit_GetMana(gmThread * a_thread);
	int GM_CDECL Unit_SetMana(gmThread * a_thread);
	int GM_CDECL Unit_GetManaPercent(gmThread * a_thread);
	int GM_CDECL Unit_GetManaMax(gmThread * a_thread);
	int GM_CDECL Unit_SetManaMax(gmThread * a_thread);
	int GM_CDECL Unit_GetManaBase(gmThread * a_thread);
	int GM_CDECL Unit_SetManaBase(gmThread * a_thread);
	int GM_CDECL Unit_AddWeapon(gmThread * a_thread);
	int GM_CDECL Unit_SetSelectedWeapon(gmThread * a_thread);
	int GM_CDECL Unit_ChangeSprite(gmThread * a_thread);

/* Weapon Functions */

	int GM_CDECL Weapon_GetProjectileEntry(gmThread * a_thread);
	int GM_CDECL Weapon_GetProjectileName(gmThread * a_thread);
	int GM_CDECL Weapon_SetProjectileInfo(gmThread * a_thread);
	int GM_CDECL Weapon_GetCurrentFireCooldown(gmThread * a_thread);
	int GM_CDECL Weapon_GetFireCooldown(gmThread * a_thread);
	int GM_CDECL Weapon_SetFireCooldown(gmThread * a_thread);
	int GM_CDECL Weapon_GetCurrentReloadCooldown(gmThread * a_thread);
	int GM_CDECL Weapon_GetReloadCooldown(gmThread * a_thread);
	int GM_CDECL Weapon_SetReloadCooldown(gmThread * a_thread);
	int GM_CDECL Weapon_GetDamage(gmThread * a_thread);
	int GM_CDECL Weapon_SetDamage(gmThread * a_thread);
	int GM_CDECL Weapon_GetCurrentMagazine(gmThread * a_thread);
	int GM_CDECL Weapon_SetCurrentMagazine(gmThread * a_thread);
	int GM_CDECL Weapon_GetMaxMagazine(gmThread * a_thread);
	int GM_CDECL Weapon_SetMaxMagazine(gmThread * a_thread);
	int GM_CDECL Weapon_CreateProjectile(gmThread * a_thread);

/* Projectile Functions */

	int GM_CDECL Projectile_GetLifeTime(gmThread * a_thread);
	int GM_CDECL Projectile_GetSpeed(gmThread * a_thread);
	int GM_CDECL Projectile_SetSpeed(gmThread * a_thread);
	int GM_CDECL Projectile_GetDirectonX(gmThread * a_thread);
	int GM_CDECL Projectile_GetDirectonY(gmThread * a_thread);
	int GM_CDECL Projectile_SetDirecton(gmThread * a_thread);

/* MapObject Functions */

	int GM_CDECL MapObject_SetCanUpdate(gmThread * a_thread);

/* ScriptObject Functions */

	int GM_CDECL ScriptObject_SetCanUpdate(gmThread * a_thread);

/* Physics Functions */
	
	int GM_CDECL Physics_SetVelocity(gmThread * a_thread);
	int GM_CDECL Physics_SetDamping(gmThread * a_thread);
	int GM_CDECL Physics_SetMass(gmThread * a_thread);
	int GM_CDECL Physics_SetInverseMass(gmThread * a_thread);
	int GM_CDECL Physics_AddForce(gmThread * a_thread);

/* All functions */
	int GM_CDECL All_RegisterUpdate(gmThread * a_thread);

#endif

