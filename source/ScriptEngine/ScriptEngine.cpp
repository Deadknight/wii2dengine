#include "StdAfx.h"
ScriptEngine * ScriptSystem;

#ifndef WIN32
#include <dirent.h>
#endif

#define USELOCK
#define USEGENERALLOCK

ScriptEngine::ScriptEngine()
{
	m_creatureType = m_gameobjectType = m_playerType = m_unitType = m_weaponType = m_projectileType = 
		m_mapobjectType = m_scriptobjectType = m_scriptEngineType = -1;
	m_machine = 0;
}

ScriptEngine::~ScriptEngine()
{
	if(m_machine)
	{
		//for(uint32 i = 0; i < 10; ++i)
			//m_machine->DestructDeleteObject(m_userObjects[i]);
		//m_machine->GetGC()->DestructAll();
		
		delete m_machine;
	}
}

void ScriptEngine::Reload(const char* root)
{
	if(m_machine)
	{
		m_creatureType = m_gameobjectType = m_playerType = m_unitType = m_weaponType = m_projectileType =
			m_mapobjectType = m_scriptobjectType = m_scriptEngineType = -1;
		for(int i = 0; i < 10; ++i)
			m_userObjects[i] = 0;

		m_creatureMap.clear();
		m_gameobjectMap.clear();
		m_playerMap.clear();
		m_weaponMap.clear();
		m_projectileMap.clear();
		m_mapobjectMap.clear();
		m_scriptobjectMap.clear();
		
		m_machine->ResetAndFreeMemory();
		delete m_machine;

		m_machine = 0;
	}

	m_machine = new gmMachine;
	m_machine->SetDebugMode(true);
	
	/* create our types */
	m_creatureType = m_machine->CreateUserType("Creature");
	m_gameobjectType = m_machine->CreateUserType("Gameobject");
	m_playerType = m_machine->CreateUserType("Player");
	m_unitType = m_machine->CreateUserType("Unit");
	m_weaponType = m_machine->CreateUserType("Weapon");
	m_projectileType = m_machine->CreateUserType("Projectile");
	m_mapobjectType = m_machine->CreateUserType("MapObject");
	m_scriptobjectType = m_machine->CreateUserType("ScriptObject");
	m_scriptEngineType = m_machine->CreateUserType("ScriptEngine");

	m_allowedTypes.push_back(m_creatureType);
	m_allowedTypes.push_back(m_gameobjectType);
	m_allowedTypes.push_back(m_playerType);
	m_allowedTypes.push_back(m_weaponType);
	m_allowedTypes.push_back(m_projectileType);
	m_allowedTypes.push_back(m_mapobjectType);
	m_allowedTypes.push_back(m_scriptobjectType);
	m_allowedTypes.push_back(m_scriptEngineType);

	/* register all our functions inside the machine */
	SetCreatureFunctionTable();
	SetGameobjectFunctionTable();
	SetPlayerFunctionTable();
	SetWeaponFunctionTable();
	SetProjectileFunctionTable();
	SetMapObjectFunctionTable();
	SetScriptObjectFunctionTable();
	SetScriptEngineFunctionTable();

	/*// Bind Get dot operator for our type
	m_machine->RegisterTypeOperator(m_objectType, O_GETDOT, NULL, Object_GetDot); 
	// Bind Set dot operator for our type
	m_machine->RegisterTypeOperator(m_objectType, O_SETDOT, NULL, Object_SetDot); */

	/* allocate our user data variables */
	for(int i = 0; i < 10; ++i)
	{
		m_userObjects[i] = m_machine->AllocUserObject(this, m_scriptEngineType);
		m_machine->AddCPPOwnedGMObject(m_userObjects[i]);
	}

	sLog.outString(LOGTYPE_ALL, LOGLEVEL_INFO, "Compiling GameMonkey Scripts...\r\n");

#ifdef WIN32
	/* compile the scripts */
	WIN32_FIND_DATA fd;
	HANDLE f = FindFirstFile(_T("Program Files\\CustomItem\\scripts\\*.gm"), &fd);
	if(f != INVALID_HANDLE_VALUE)
	{
		do 
		{
#ifdef UNICODE
			std::wstring fname = _T("Program Files/CustomItem/scripts/");
#else
			std::string fname = "scripts/";
#endif
			fname += fd.cFileName;

#ifdef UNICODE
			std::string fnameA (fname.begin(), fname.end());
#else
			std::string fnameA = fname;
#endif
			ExecuteScriptFile(fnameA.c_str());
		} while(FindNextFile(f, &fd));
		FindClose(f);
	}
#else
	/* compile scripts */
	/*struct dirent ** list;
	int filecount = scandir("scripts/", &list, 0, 0);
	if(!filecount || !list || filecount < 0)
		return;

	char * ext;
	while(filecount--)
	{
		ext = strrchr(list[filecount]->d_name, '.');
		if(ext != NULL && !strcmp(ext, ".gm"))
		{
			string full_path = "scripts/" + string(list[filecount]->d_name);
			ExecuteScriptFile(full_path.c_str());
		}
		free(list[filecount]);
	}
	free(list);*/
	
	//libogc implementation
	DIR_ITER* dirIter = diropen(root);
	if(dirIter)
	{
        char filename[MAXPATHLEN];
        struct stat filestat;

        int i, res;
		char *ext;
        for(i=0; i < MAXGMFILE; i++)
        {
			res = dirnext(dirIter,filename,&filestat);

			if(res != 0)
				break;

			if(strcmp(filename,".") == 0)
			{
				i--;
				continue;
			}
			
			ext = strrchr(filename, '.');
			if(ext != NULL && !strcmp(ext, ".gm"))
			{
				std::string full_path = "scripts/" + std::string(filename);
				sLog.outString(LOGTYPE_ALL, LOGLEVEL_INFO, "Compiling Script %s\r\n", full_path.c_str());
				ExecuteScriptFile(full_path.c_str());
			}			
		}
		dirclose(dirIter);		
	}
	
#endif

	sLog.outString(LOGTYPE_ALL, LOGLEVEL_INFO, "Scripts compiled.\r\n");
}

void ScriptEngine::ExecuteScriptFile(const char * filename)
{
	char * data;
	FILE * f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	data = new char[size+1];
	fread(data, 1, size, f);
	data[size] = 0;

	fclose(f);

	/* setup 'this' pointer */
	m_userObjects[0]->m_user = this;
	m_userObjects[0]->m_userType = m_scriptEngineType;

	/* set 'this' variable */
	m_variables[0].SetUser(m_userObjects[0]);

	int threadid;
	printf("  %s: ", strstr(filename, "/")+1);
	int no_errors = m_machine->ExecuteString(data, &threadid, true, filename, &m_variables[0]);
	bool first=true;
#ifdef WIN32
	FILE *fp = fopen("/Program Files/CustomItem/scripts/error.txt", "a");
	if(no_errors || m_machine->GetLog().GetEntry(first))
	{
		//printf("Errors occured while compiling %s.\n", filename);
		std::string errors = DumpErrors();
		fprintf(fp, "Filename: %s\n%s", filename, errors.c_str());
	}
	//else printf("%u errors.\n", no_errors);
	fclose(fp);
#else
	if(no_errors || m_machine->GetLog().GetEntry(first))
	{
		std::string errors = DumpErrors();
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "GameMonkey: Filename->%s\r\n%s\r\n", filename, errors.c_str());
	}
	else
	{
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_INFO, "%u errors\r\n", no_errors);
	}
#endif

	delete [] data;
}

std::string ScriptEngine::DumpErrors()
{
	//sLog.outString(LOGTYPE_ALL, LOGLEVEL_DEBUG,"Dumping errors from script action: \r\n");
	
	bool first = true;
	const char * message = m_machine->GetLog().GetEntry(first);
	first = false;
	std::stringstream messagestream;
	while(message)
	{
		messagestream << message;
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "GameMonkey: GM_Debug:  %s\r\n", message);
		message = m_machine->GetLog().GetEntry(first);
	}
	//sLog.outString(LOGTYPE_ALL, LOGLEVEL_DEBUG, "End of error dump.\r\n");
	m_machine->GetLog().Reset();  //if not reset, will repeat last error over and over again

	return messagestream.str();
}

void ScriptEngine::DoGMCall(gmFunctionObject * obj, uint32 ArgumentCount, int * return_value)
{
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_DEBUG, "GMDebug function Start:%s\r\n", obj->GetDebugName());
	gmCall call;
	if(call.BeginFunction(m_machine, obj, m_variables[0], false))
	{
		for(uint32 i = 0; i < ArgumentCount; ++i)
			call.AddParam(m_variables[1+i]);

		m_userObjectCounter = ArgumentCount + 1;
		call.End();

		if(return_value != 0)
		{
			int v;
			if(call.GetReturnedInt(v))
				*return_value = v;
			else
				*return_value = 1;
		}

		DumpErrors();
	}
	else
	{
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Could not find function!\r\n");
		DumpErrors();
	}
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_DEBUG, "GMDebug function End:%s\r\n", obj->GetDebugName());
}

void ScriptEngine::FillVariable(int index, void *val, MYTYPE type)
{
	switch(type)
	{
	case MYTYPE_INT:
		SetVariable(index, val, GM_INT);
		break;
	case MYTYPE_FLOAT:
		SetVariable(index, val, GM_FLOAT);
		break;
	case MYTYPE_STRING:
		SetVariable(index, val, GM_STRING);
		break;
	case MYTYPE_CREATURE:
		SetVariable(index, val, m_creatureType);
		break;
	case MYTYPE_GAMEOBJECT:
		SetVariable(index, val, m_gameobjectType);
		break;
	case MYTYPE_PLAYER:
		SetVariable(index, val, m_playerType);
		break;
	case MYTYPE_UNIT:
		SetVariable(index, val, m_unitType);
		break;
	case MYTYPE_WEAPON:
		SetVariable(index, val, m_weaponType);
		break;
	case MYTYPE_PROJECTILE:
		SetVariable(index, val, m_projectileType);
		break;
	case MYTYPE_MAPOBJECT:
		SetVariable(index, val, m_mapobjectType);
		break;
	case MYTYPE_SCRIPTOBJECT:
		SetVariable(index, val, m_scriptobjectType);
		break;
	default:
		break;
	};
}

bool ScriptEngine::OnCreatureEvent(Creature *pCreature, gmFunctionObject *pointer)
{
	if(!m_creatureMap.size())
		return false;

#ifdef USELOCK
	m_creatureLock.Acquire();
#endif
	SetVariable(0, pCreature, m_creatureType);
	DoGMCall(pointer, 0, 0);
#ifdef USELOCK
	m_creatureLock.Release();
#endif
	return true;
}

bool ScriptEngine::OnCreatureEvent(Creature *pCreature, uint32 Event, uint32 ArgCount, ...)
{
	if(!m_creatureMap.size())
		return false;

	ScriptMap::iterator itr = m_creatureMap.find(pCreature->GetEntry());
	if(itr == m_creatureMap.end())
		return false;

	std::map<uint32, gmFunctionObject*>::iterator it2 = itr->second.find(Event);
	if(it2 == itr->second.end() )
		return false;

#ifdef USELOCK
	m_creatureLock.Acquire();
#endif
	int i = 0;
	SetVariable(0, pCreature, m_creatureType);
	i++;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(int j = 0; j < ArgCount; j++)
		{
			if(i > 9)
				break;

			FillVariable(i, type->data, type->type);
			i++;
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	DoGMCall(it2->second, i, 0);
#ifdef USELOCK
	m_creatureLock.Release();
#endif
	return true;
}

bool ScriptEngine::OnGameobjectEvent(Gameobject *pGameobject, gmFunctionObject *pointer)
{
	if(!m_gameobjectMap.size())
		return false;

#ifdef USELOCK
	m_gameobjectLock.Acquire();
#endif
	SetVariable(0, pGameobject, m_gameobjectType);
	DoGMCall(pointer, 0, 0);
#ifdef USELOCK
	m_gameobjectLock.Release();
#endif
	return true;
}

bool ScriptEngine::OnGameobjectEvent(Gameobject *pGameobject, uint32 Event, uint32 ArgCount, ...)
{
	if(!m_gameobjectMap.size())
		return false;

	ScriptMap::iterator itr = m_gameobjectMap.find(pGameobject->GetEntry());
	if(itr == m_gameobjectMap.end())
		return false;

	std::map<uint32, gmFunctionObject*>::iterator it2 = itr->second.find(Event);
	if(it2 == itr->second.end() )
		return false;

#ifdef USELOCK
	m_gameobjectLock.Acquire();
#endif
	int i = 0;
	SetVariable(0, pGameobject, m_gameobjectType);
	i++;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(int j = 0; j < ArgCount; j++)
		{
			if(i > 9)
				break;

			FillVariable(i, type->data, type->type);
			i++;
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	DoGMCall(it2->second, i, 0);
#ifdef USELOCK
	m_gameobjectLock.Release();
#endif
	return true;
}

bool ScriptEngine::OnPlayerEvent(Player *pPlayer, gmFunctionObject *pointer)
{
	if(!m_playerMap.size())
		return false;

#ifdef USELOCK
	m_playerLock.Acquire();
#endif
	SetVariable(0, pPlayer, m_playerType);
	DoGMCall(pointer, 0, 0);
#ifdef USELOCK
	m_playerLock.Release();
#endif
	return true;
}

bool ScriptEngine::OnPlayerEvent(Player *pPlayer, uint32 Event, uint32 ArgCount, ...)
{
	if(!m_playerMap.size())
		return false;

	ScriptMap::iterator itr = m_playerMap.find(pPlayer->GetEntry());
	if(itr == m_playerMap.end())
		return false;

	std::map<uint32, gmFunctionObject*>::iterator it2 = itr->second.find(Event);
	if(it2 == itr->second.end() )
		return false;

#ifdef USELOCK
	m_playerLock.Acquire();
#endif
	int i = 0;
	SetVariable(0, pPlayer, m_playerType);
	i++;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(int j = 0; j < ArgCount; j++)
		{
			if(i > 9)
				break;

			FillVariable(i, type->data, type->type);
			i++;
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	DoGMCall(it2->second, i, 0);
#ifdef USELOCK
	m_playerLock.Release();
#endif
	return true;
}

bool ScriptEngine::OnWeaponEvent(Weapon *pWeapon, gmFunctionObject *pointer)
{
	if(!m_weaponMap.size())
		return false;

#ifdef USELOCK
	m_weaponLock.Acquire();
#endif
	SetVariable(0, pWeapon, m_weaponType);
	DoGMCall(pointer, 0, 0);
#ifdef USELOCK
	m_weaponLock.Release();
#endif
	return true;
}

bool ScriptEngine::OnWeaponEvent(Weapon *pWeapon, uint32 Event, uint32 ArgCount, ...)
{
	if(!m_weaponMap.size())
		return false;

	ScriptMap::iterator itr = m_weaponMap.find(pWeapon->GetId());
	if(itr == m_weaponMap.end())
		return false;

	std::map<uint32, gmFunctionObject*>::iterator it2 = itr->second.find(Event);
	if(it2 == itr->second.end() )
		return false;

#ifdef USELOCK
	m_weaponLock.Acquire();
#endif
	int i = 0;
	SetVariable(0, pWeapon, m_weaponType);
	i++;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(int j = 0; j < ArgCount; j++)
		{
			if(i > 9)
				break;

			FillVariable(i, type->data, type->type);
			i++;
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	DoGMCall(it2->second, i, 0);
#ifdef USELOCK
	m_weaponLock.Release();
#endif
	return true;
}

bool ScriptEngine::OnProjectileEvent(Projectile *pProjectile, gmFunctionObject *pointer)
{
	if(!m_projectileMap.size())
		return false;

#ifdef USELOCK
	m_projectileLock.Acquire();
#endif
	SetVariable(0, pProjectile, m_projectileType);
	DoGMCall(pointer, 0, 0);
#ifdef USELOCK
	m_projectileLock.Release();
#endif
	return true;
}

bool ScriptEngine::OnProjectileEvent(Projectile *pProjectile, uint32 Event, uint32 ArgCount, ...)
{
	if(!m_projectileMap.size())
		return false;

	ScriptMap::iterator itr = m_projectileMap.find(pProjectile->GetEntry());
	if(itr == m_projectileMap.end())
		return false;

	std::map<uint32, gmFunctionObject*>::iterator it2 = itr->second.find(Event);
	if(it2 == itr->second.end() )
		return false;

#ifdef USELOCK
	m_projectileLock.Acquire();
#endif
	int i = 0;
	SetVariable(0, pProjectile, m_projectileType);
	i++;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(int j = 0; j < ArgCount; j++)
		{
			if(i > 9)
				break;

			FillVariable(i, type->data, type->type);
			i++;
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	DoGMCall(it2->second, i, 0);
#ifdef USELOCK
	m_projectileLock.Release();
#endif
	return true;
}

bool ScriptEngine::OnMapObjectEvent(MapObject *pMapObject, gmFunctionObject *pointer)
{
	if(!m_mapobjectMap.size())
		return false;

#ifdef USELOCK
	m_mapobjectLock.Acquire();
#endif
	SetVariable(0, pMapObject, m_mapobjectType);
	DoGMCall(pointer, 0, 0);
#ifdef USELOCK
	m_mapobjectLock.Release();
#endif
	return true;
}

bool ScriptEngine::OnMapObjectEvent(MapObject *pMapObject, uint32 Event, uint32 ArgCount, ...)
{
	if(!m_mapobjectMap.size())
		return false;

	ScriptMap::iterator itr = m_mapobjectMap.find(pMapObject->GetEntry());
	if(itr == m_mapobjectMap.end())
		return false;

	std::map<uint32, gmFunctionObject*>::iterator it2 = itr->second.find(Event);
	if(it2 == itr->second.end() )
		return false;

#ifdef USELOCK
	m_mapobjectLock.Acquire();
#endif
	int i = 0;
	SetVariable(0, pMapObject, m_mapobjectType);
	i++;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(int j = 0; j < ArgCount; j++)
		{
			if(i > 9)
				break;

			FillVariable(i, type->data, type->type);
			i++;
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	DoGMCall(it2->second, i, 0);
#ifdef USELOCK
	m_mapobjectLock.Release();
#endif
	return true;
}

bool ScriptEngine::OnScriptObjectEvent(ScriptObject *pScriptObject, gmFunctionObject *pointer)
{
	if(!m_scriptobjectMap.size())
		return false;

#ifdef USELOCK
	m_scriptobjectLock.Acquire();
#endif
	SetVariable(0, pScriptObject, m_scriptobjectType);
	DoGMCall(pointer, 0, 0);
#ifdef USELOCK
	m_scriptobjectLock.Release();
#endif
	return true;
}

bool ScriptEngine::OnScriptObjectEvent(ScriptObject *pScriptObject, uint32 Event, uint32 ArgCount, ...)
{
	if(!m_scriptobjectMap.size())
		return false;

	ScriptMap::iterator itr = m_scriptobjectMap.find(pScriptObject->GetEntry());
	if(itr == m_scriptobjectMap.end())
		return false;

	std::map<uint32, gmFunctionObject*>::iterator it2 = itr->second.find(Event);
	if(it2 == itr->second.end() )
		return false;

#ifdef USELOCK
	m_scriptobjectLock.Acquire();
#endif
	int i = 0;
	SetVariable(0, pScriptObject, m_scriptobjectType);
	i++;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(int j = 0; j < ArgCount; j++)
		{
			if(i > 9)
				break;

			FillVariable(i, type->data, type->type);
			i++;
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	DoGMCall(it2->second, i, 0);
#ifdef USELOCK
	m_scriptobjectLock.Release();
#endif
	return true;
}

/*bool ScriptEngine::OnLayerEvent(Layer *pLayer, Object * pObject, uint32 Event)
{
	if(!m_layerMap.size())
		return false;

	ScriptMap::iterator itr = m_layerMap.find(pObject->GetObjectType());
	if(itr == m_layerMap.end())
		return false;

	std::map<uint32, gmFunctionObject*>::iterator it2 = itr->second.find(Event);
	if(it2 == itr->second.end() )
		return false;

	m_lock.Acquire();
	//This variable
	SetVariable(0, pLayer, m_layerType);
	//Arguments
	SetVariable(1, pLayer, m_layerType);
	SetVariable(2, pObject, m_objectType);

	DoGMCall(it2->second, 2, 0);
	m_lock.Release();
	return true;
}*/

/*bool ScriptEngine::OnLayerEventArg(Creature * pCreature, uint32 Argument, uint32 Event)
{
	if(!m_unitMap.size())
		return false;

	ScriptMap::iterator itr = m_unitMap.find(pCreature->GetEntry());
	if(itr == m_unitMap.end())
		return false;

	map<uint32, gmFunctionObject*>::iterator it2 = itr->second.find(Event);
	if(it2 == itr->second.end() )
		return false;

	gmFunctionObject * obj = it2->second;
	m_lock.Acquire();

	ASSERT(obj->GetType() == GM_FUNCTION);

	SetVariable(0, pCreature, m_unitType);
	gmCall call;
	if(call.BeginFunction(m_machine, obj, m_variables[0], false))
	{
		call.AddParamInt(Argument);
		m_userObjectCounter = 2;
		call.End();
		DumpErrors();
	}
	else
	{
		printf("Could not find function!");
		DumpErrors();
	}

	m_lock.Release();
	return true;
}*/

/*bool ScriptEngine::OnLayerEvent(Object * pObject, gmFunctionObject * pointer)
{
	if(!m_layerMap.size())
		return false;

	m_lock.Acquire();
	SetVariable(0, pObject, m_layerType);
	DoGMCall(pointer, 0, 0);
	m_lock.Release();
	return true;
}*/

bool ScriptEngine::HasEventType(uint32 Entry, uint32 Event)
{
/*	ScriptMap::iterator itr = m_layerMap.find(Entry);
	if(itr == m_layerMap.end())
		return false;

	if(itr->second.find(Event) != itr->second.end())
		return false;

	return true;*/
	return true;
}

bool ScriptEngine::CallGMFunction(const char * name, void* forthis, gmType type)
{
	m_lock.Acquire();
	gmStringObject * fname = m_machine->AllocStringObject(name,strlen(name));
	ASSERT(fname);
	gmCall call;
	m_userObjectCounter=1;
	m_userObjects[0]->m_user = forthis;
	m_userObjects[0]->m_userType = type;

	m_variables[0].SetUser(m_userObjects[0]);
	if(call.BeginGlobalFunction(m_machine, fname, m_variables[0], false))
	{
		call.End();
		DumpErrors();
		m_lock.Release();
		return true;
	}	

	m_lock.Release();
	return false;
}
