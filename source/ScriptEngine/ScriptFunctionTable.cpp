#include "StdAfx.h"

void ScriptEngine::SetCreatureFunctionTable()
{
	static gmFunctionEntry table[] = {
		{ "GetX",						Object_GetX						},
		{ "GetY",						Object_GetY						},
		{ "SetPosition",				Object_SetPosition				},
		{ "GetField",					Object_GetField					},
		{ "GetRealField",				Object_GetRealField				},
		{ "SetField",					Object_SetField					},
		{ "SetRealField",				Object_SetRealField				},
		{ "GetEntry",					Object_GetEntry					},
		//{ "SetEntry",					Object_SetEntry					},
		{ "GetHealth",					Unit_GetHealth					},
		{ "SetHealth",					Unit_SetHealth					},
		{ "GetHealthPercent",			Unit_GetHealthPercent			},
		{ "GetHealthMax",				Unit_GetHealthMax				},
		{ "SetHealthMax",				Unit_SetHealthMax				},
		{ "GetHealthBase",				Unit_GetHealthBase				},
		{ "SetHealthBase",				Unit_SetHealthBase				},
		{ "GetMana",					Unit_GetMana					},
		{ "SetMana",					Unit_SetMana					},
		{ "GetManaPercent",				Unit_GetManaPercent				},
		{ "GetManaMax",					Unit_GetManaMax					},
		{ "SetManaMax",					Unit_SetManaMax					},
		{ "GetManaBase",				Unit_GetManaBase				},
		{ "SetManaBase",				Unit_SetManaBase				},
		{ "AddWeapon",					Unit_AddWeapon					},
		{ "SetSelectedWeapon",			Unit_SetSelectedWeapon			},
		{ "ChangeSprite",				Unit_ChangeSprite				},
		{ "RegisterUpdate",				All_RegisterUpdate				},
	};

	m_machine->RegisterTypeLibrary(m_creatureType, table, sizeof(table) / sizeof(table[0]));
}

void ScriptEngine::SetGameobjectFunctionTable()
{
	static gmFunctionEntry table[] = {
		{ "GetX",						Object_GetX						},
		{ "GetY",						Object_GetY						},
		{ "SetPosition",				Object_SetPosition				},
		{ "GetField",					Object_GetField					},
		{ "GetRealField",				Object_GetRealField				},
		{ "SetField",					Object_SetField					},
		{ "SetRealField",				Object_SetRealField				},
		{ "GetEntry",					Object_GetEntry					},
		//{ "SetEntry",					Object_SetEntry					},
	};

	m_machine->RegisterTypeLibrary(m_gameobjectType, table, sizeof(table) / sizeof(table[0]));
}

void ScriptEngine::SetPlayerFunctionTable()
{
	static gmFunctionEntry table[] = {
		{ "GetX",						Object_GetX						},
		{ "GetY",						Object_GetY						},
		{ "SetPosition",				Object_SetPosition				},
		{ "GetField",					Object_GetField					},
		{ "GetRealField",				Object_GetRealField				},
		{ "SetField",					Object_SetField					},
		{ "SetRealField",				Object_SetRealField				},
		{ "GetEntry",					Object_GetEntry					},
		//{ "SetEntry",					Object_SetEntry					},
		{ "GetHealth",					Unit_GetHealth					},
		{ "SetHealth",					Unit_SetHealth					},
		{ "GetHealthPercent",			Unit_GetHealthPercent			},
		{ "GetHealthMax",				Unit_GetHealthMax				},
		{ "SetHealthMax",				Unit_SetHealthMax				},
		{ "GetHealthBase",				Unit_GetHealthBase				},
		{ "SetHealthBase",				Unit_SetHealthBase				},
		{ "GetMana",					Unit_GetMana					},
		{ "SetMana",					Unit_SetMana					},
		{ "GetManaPercent",				Unit_GetManaPercent				},
		{ "GetManaMax",					Unit_GetManaMax					},
		{ "SetManaMax",					Unit_SetManaMax					},
		{ "GetManaBase",				Unit_GetManaBase				},
		{ "SetManaBase",				Unit_SetManaBase				},
		{ "AddWeapon",					Unit_AddWeapon					},
		{ "SetSelectedWeapon",			Unit_SetSelectedWeapon			},
		{ "ChangeSprite",				Unit_ChangeSprite				},
		{ "RegisterUpdate",				All_RegisterUpdate				},
	};

	m_machine->RegisterTypeLibrary(m_playerType, table, sizeof(table) / sizeof(table[0]));
}

void ScriptEngine::SetWeaponFunctionTable()
{
	static gmFunctionEntry table[] = {
		{ "GetProjectileEntry",							Weapon_GetProjectileName		},
		{ "GetProjectileName",							Weapon_GetProjectileEntry		},
		{ "SetProjectileInfo",							Weapon_SetProjectileInfo		},
		{ "GetCurrentFireCooldown",						Weapon_GetCurrentFireCooldown	},
		{ "GetFireCooldown",							Weapon_GetFireCooldown			},
		{ "SetFireCooldown",							Weapon_SetFireCooldown			},
		{ "GetCurrentReloadCooldown",					Weapon_GetCurrentReloadCooldown },
		{ "GetReloadCooldown",							Weapon_GetReloadCooldown		},
		{ "SetReloadCooldown",							Weapon_SetReloadCooldown		},
		{ "GetDamage",									Weapon_GetDamage				},
		{ "SetDamage",									Weapon_SetDamage				},
		{ "GetCurrentMagazine",							Weapon_GetCurrentMagazine		},
		{ "SetCurrentMagazine",							Weapon_SetCurrentMagazine		},
		{ "GetMaxMagazine",								Weapon_GetMaxMagazine			},
		{ "SetMaxMagazine",								Weapon_SetMaxMagazine			},
		{ "CreateProjectile",							Weapon_CreateProjectile			},
	};

	m_machine->RegisterTypeLibrary(m_weaponType, table, sizeof(table) / sizeof(table[0]));
}

void ScriptEngine::SetProjectileFunctionTable()
{
	static gmFunctionEntry table[] = {
		{ "GetX",						Object_GetX						},
		{ "GetY",						Object_GetY						},
		{ "SetPosition",				Object_SetPosition				},
		{ "GetField",					Object_GetField					},
		{ "GetRealField",				Object_GetRealField				},
		{ "SetField",					Object_SetField					},
		{ "SetRealField",				Object_SetRealField				},
		{ "GetEntry",					Object_GetEntry					},
		{ "GetLifeTime",				Projectile_GetLifeTime			},
		{ "GetSpeed",					Projectile_GetSpeed				},
		{ "SetSpeed",					Projectile_SetSpeed				},
		{ "GetDirectionX",				Projectile_GetDirectonX			},
		{ "GetDirectionY",				Projectile_GetDirectonY			},
		{ "SetDirection",				Projectile_SetDirecton			},
		{ "SetVelocity",				Physics_SetVelocity				},
		{ "SetDamping",					Physics_SetDamping				},
		{ "SetMass",					Physics_SetMass					},
		{ "SetInverseMass",				Physics_SetInverseMass			},
		{ "AddForce",					Physics_AddForce				},
	};

	m_machine->RegisterTypeLibrary(m_projectileType, table, sizeof(table) / sizeof(table[0]));
}

void ScriptEngine::SetMapObjectFunctionTable()
{

}

void ScriptEngine::SetScriptObjectFunctionTable()
{

}

void ScriptEngine::SetScriptEngineFunctionTable()
{
	static gmFunctionEntry table[] = {
		{ "RegisterCreatureEvent",					ScriptEngine_RegisterCreatureEvent			},
		{ "RegisterGameobjectEvent",				ScriptEngine_RegisterGameobjectEvent		},
		{ "RegisterPlayerEvent",					ScriptEngine_RegisterPlayerEvent			},
		{ "RegisterWeaponEvent",					ScriptEngine_RegisterWeaponEvent			},
		{ "RegisterProjectileEvent",				ScriptEngine_RegisterProjectileEvent		},
		{ "RegisterMapObjectEvent",					ScriptEngine_RegisterProjectileEvent		},
		{ "RegisterScriptObjectEvent",				ScriptEngine_RegisterProjectileEvent		},
	};

	m_machine->RegisterTypeLibrary(m_scriptEngineType, table, sizeof(table) / sizeof(table[0]));

	// Register Normal Functions
	/*m_machine->RegisterLibraryFunction("Rand", GM_RAND, 0, 0);
	m_machine->RegisterLibraryFunction("sprintf", GM_RAND, 0, 0);
	m_machine->RegisterLibraryFunction("GetDistance", GM_GetDistance, 0, 0);*/
	
}



