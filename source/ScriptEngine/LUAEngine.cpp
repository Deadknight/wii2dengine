#include "StdAfx.h"

#ifdef WIN32
#pragma warning(disable:4129)
#pragma warning(disable:4244)
#endif

#if PLATFORM != PLATFORM_WIN32
#include <dirent.h>
#endif

LuaEngine g_luaMgr;

template<typename T> const char * GetTClassName() { return "UNKNOWN"; }
template<> const char * GetTClassName<Creature>() { return "Creature"; }
template<> const char * GetTClassName<Gameobject>() { return "Gameobject"; }
template<> const char * GetTClassName<Player>() { return "Player"; }
template<> const char * GetTClassName<Unit>() { return "Unit"; }
template<> const char * GetTClassName<Object>() { return "Object"; }
template<> const char * GetTClassName<Weapon>() { return "Weapon"; }
template<> const char * GetTClassName<Projectile>() { return "Projectile"; }
template<> const char * GetTClassName<MapObject>() { return "MapObject"; }
template<> const char * GetTClassName<ScriptObject>() { return "ScriptObject"; }

#define LUAOBJECTFUNCTIONDEFINES \
	{ "GetType",					&luaObject::Object_GetType					}, \
	{ "GetX",						&luaObject::Object_GetX						}, \
	{ "GetY",						&luaObject::Object_GetY						}, \
	{ "SetPosition",				&luaObject::Object_SetPosition				}, \
	{ "GetField",					&luaObject::Object_GetField					}, \
	{ "GetRealField",				&luaObject::Object_GetRealField				}, \
	{ "SetField",					&luaObject::Object_SetField					}, \
	{ "SetRealField",				&luaObject::Object_SetRealField				}, \
	{ "GetEntry",					&luaObject::Object_GetEntry					}

#define LUAUNITFUNCTIONDEFINES \
	{ "GetHealth",					&luaUnit::Unit_GetHealth					}, \
	{ "SetHealth",					&luaUnit::Unit_SetHealth					}, \
	{ "GetHealthPercent",			&luaUnit::Unit_GetHealthPercent				}, \
	{ "GetHealthMax",				&luaUnit::Unit_GetHealthMax					}, \
	{ "SetHealthMax",				&luaUnit::Unit_SetHealthMax					}, \
	{ "GetHealthBase",				&luaUnit::Unit_GetHealthBase				}, \
	{ "SetHealthBase",				&luaUnit::Unit_SetHealthBase				}, \
	{ "GetMana",					&luaUnit::Unit_GetMana						}, \
	{ "SetMana",					&luaUnit::Unit_SetMana						}, \
	{ "GetManaPercent",				&luaUnit::Unit_GetManaPercent				}, \
	{ "GetManaMax",					&luaUnit::Unit_GetManaMax					}, \
	{ "SetManaMax",					&luaUnit::Unit_SetManaMax					}, \
	{ "GetManaBase",				&luaUnit::Unit_GetManaBase					}, \
	{ "SetManaBase",				&luaUnit::Unit_SetManaBase					}, \
	{ "AddWeapon",					&luaUnit::Unit_AddWeapon					}, \
	{ "SetSelectedWeapon",			&luaUnit::Unit_SetSelectedWeapon			}, \
	{ "ChangeSprite",				&luaUnit::Unit_ChangeSprite					}

#define LUAPHYSICSFUNCTIONDEFINES \
	{ "SetVelocity",				&luaPhysics::Physics_SetVelocity				}, \
	{ "SetDamping",					&luaPhysics::Physics_SetDamping					}, \
	{ "SetMass",					&luaPhysics::Physics_SetMass					}, \
	{ "SetInverseMass",				&luaPhysics::Physics_SetInverseMass				}, \
	{ "AddForce",					&luaPhysics::Physics_AddForce					}, \
	{ "AddForceGenerator",			&luaPhysics::Physics_AddForceGenerator			}, \
	{ "RemoveForceGenerator",		&luaPhysics::Physics_RemoveForceGenerator		}

#define LUAWEAPONFUNCTIONDEFINES \
	{ "GetProjectileEntry",							&luaWeapon::Weapon_GetProjectileName		}, \
	{ "GetProjectileName",							&luaWeapon::Weapon_GetProjectileEntry		}, \
	{ "SetProjectileInfo",							&luaWeapon::Weapon_SetProjectileInfo		}, \
	{ "GetCurrentFireCooldown",						&luaWeapon::Weapon_GetCurrentFireCooldown	}, \
	{ "GetFireCooldown",							&luaWeapon::Weapon_GetFireCooldown			}, \
	{ "SetFireCooldown",							&luaWeapon::Weapon_SetFireCooldown			}, \
	{ "GetCurrentReloadCooldown",					&luaWeapon::Weapon_GetCurrentReloadCooldown }, \
	{ "GetReloadCooldown",							&luaWeapon::Weapon_GetReloadCooldown		}, \
	{ "SetReloadCooldown",							&luaWeapon::Weapon_SetReloadCooldown		}, \
	{ "GetDamage",									&luaWeapon::Weapon_GetDamage				}, \
	{ "SetDamage",									&luaWeapon::Weapon_SetDamage				}, \
	{ "GetCurrentMagazine",							&luaWeapon::Weapon_GetCurrentMagazine		}, \
	{ "SetCurrentMagazine",							&luaWeapon::Weapon_SetCurrentMagazine		}, \
	{ "GetMaxMagazine",								&luaWeapon::Weapon_GetMaxMagazine			}, \
	{ "SetMaxMagazine",								&luaWeapon::Weapon_SetMaxMagazine			}, \
	{ "CreateProjectile",							&luaWeapon::Weapon_CreateProjectile			}

#define LUAPROJECTILEFUNCTIONDEFINES \
	{ "GetLifeTime",				&luaProjectile::Projectile_GetLifeTime			}, \
	{ "GetSpeed",					&luaProjectile::Projectile_GetSpeed				}, \
	{ "SetSpeed",					&luaProjectile::Projectile_SetSpeed				}, \
	{ "GetDirectionX",				&luaProjectile::Projectile_GetDirectonX			}, \
	{ "GetDirectionY",				&luaProjectile::Projectile_GetDirectonY			}, \
	{ "SetDirection",				&luaProjectile::Projectile_SetDirecton			}


RegType<Player> LUAPlayerMethods[] = 
{
	LUAOBJECTFUNCTIONDEFINES,
	LUAUNITFUNCTIONDEFINES,
	//{ "RegisterUpdate",				All_RegisterUpdate				},
	LUAPHYSICSFUNCTIONDEFINES,
	{ NULL, NULL },
};

RegType<Creature> LUACreatureMethods[] = 
{
	LUAOBJECTFUNCTIONDEFINES,
	LUAUNITFUNCTIONDEFINES,
	//{ "RegisterUpdate",				All_RegisterUpdate				},
	LUAPHYSICSFUNCTIONDEFINES,
	{ NULL, NULL },
};

RegType<Gameobject> LUAGOMethods[] = 
{
	LUAOBJECTFUNCTIONDEFINES,
	LUAPHYSICSFUNCTIONDEFINES,
	{ NULL, NULL },
};

RegType<Unit> LUAUnitMethods[] = 
{
	LUAOBJECTFUNCTIONDEFINES,
	LUAUNITFUNCTIONDEFINES,
	//{ "RegisterUpdate",				All_RegisterUpdate				},
	LUAPHYSICSFUNCTIONDEFINES,
};

RegType<Object> LUAObjectMethods[] = 
{
	LUAOBJECTFUNCTIONDEFINES,
	LUAPHYSICSFUNCTIONDEFINES,
	{ NULL, NULL },
};

RegType<Weapon> LUAWeaponMethods[] = 
{
	LUAWEAPONFUNCTIONDEFINES,
	{ NULL, NULL },
};

RegType<Projectile> LUAProjectileMethods[] = 
{
	LUAOBJECTFUNCTIONDEFINES,
	LUAPROJECTILEFUNCTIONDEFINES,
	LUAPHYSICSFUNCTIONDEFINES,
	{ NULL, NULL },
};

RegType<MapObject> LUAMapObjectMethods[] = 
{
	{ "SetCanUpdate",				&luaMapObject::MapObject_SetCanUpdate			},
	{ NULL, NULL },
};

RegType<ScriptObject> LUAScriptObjectMethods[] = 
{
	{ "SetCanUpdate",				&luaScriptObject::ScriptObject_SetCanUpdate			},
	{ NULL, NULL },
};

template<typename T> RegType<T>* GetMethodTable() { return NULL; }
template<> RegType<Player>* GetMethodTable<Player>() { return LUAPlayerMethods; }
template<> RegType<Creature>* GetMethodTable<Creature>() { return LUACreatureMethods; }
template<> RegType<Gameobject>* GetMethodTable<Gameobject>() { return LUAGOMethods; }
template<> RegType<Unit>* GetMethodTable<Unit>() { return LUAUnitMethods; }
template<> RegType<Object>* GetMethodTable<Object>() { return LUAObjectMethods; }
template<> RegType<Weapon>* GetMethodTable<Weapon>() { return LUAWeaponMethods; }
template<> RegType<Projectile>* GetMethodTable<Projectile>() { return LUAProjectileMethods; }
template<> RegType<MapObject>* GetMethodTable<MapObject>() { return LUAMapObjectMethods; }
template<> RegType<ScriptObject>* GetMethodTable<ScriptObject>() { return LUAScriptObjectMethods; }

void report(lua_State * L)
{
	uint32 count = 20;
	const char * msg= lua_tostring(L,-1);
	while(msg && count > 0)
	{
		lua_pop(L,-1);
		printf("\t%s\n", msg);
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "LuaEngine: Error %s\r\n", msg);
		msg=lua_tostring(L,-1);
		count--;
	}
}

void LuaEngine::ScriptLoadDir(char* Dirname, LUALoadScripts *pak)
{
	#ifdef WIN32
		Log.Success("LuaEngine", "Scanning Directory %s", Dirname);
		HANDLE hFile;
		WIN32_FIND_DATA FindData;
		memset(&FindData,0,sizeof(FindData));

		char SearchName[MAX_PATH];
	        
		strcpy(SearchName,Dirname);
		strcat(SearchName,"\\*.*");

		hFile = FindFirstFile(SearchName,&FindData);
		FindNextFile(hFile, &FindData);
	    
		while( FindNextFile(hFile, &FindData) )
		{
			if( FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) //Credits for this 'if' go to Cebernic from ArcScripts Team. Thanks, you saved me some work ;-)
			{
				strcpy(SearchName,Dirname);
				strcat(SearchName,"\\");
				strcat(SearchName,FindData.cFileName);
				ScriptLoadDir(SearchName, pak);
			}
			else
			{
						string fname = Dirname;
						fname += "\\";
						fname += FindData.cFileName;

			  		int len = strlen(fname.c_str());
					  int i=0;
					  char ext[MAX_PATH];
					  
					  while(len > 0)
					  {  
					   ext[i++] = fname[--len];
					   if(fname[len] == '.')
		  		   break;
	  			  }
	  			  ext[i++] = '\0';
	  			  if ( !_stricmp(ext,"aul.") ) pak->luaFiles.insert(fname);
			}
		}
	  FindClose(hFile);
	#else
		/*char *pch=strrchr(Dirname,'/');
		if (strcmp(Dirname, "..")==0 || strcmp(Dirname, ".")==0) return; //Against Endless-Loop
		if (pch != NULL && (strcmp(pch, "/..")==0 || strcmp(pch, "/.")==0 || strcmp(pch, "/.svn")==0)) return;
		struct dirent ** list;
		int filecount = scandir(Dirname, &list, 0, 0);

		if(filecount <= 0 || !list)
			return;

		struct stat attributes;
		bool err;
		Log.Success("LuaEngine", "Scanning Directory %s", Dirname);
		while(filecount--)
		{
			char dottedrelpath[200];
			sprintf(dottedrelpath, "%s/%s", Dirname, list[filecount]->d_name);
			if(stat(dottedrelpath, &attributes) == -1) {
				err=true;
				Log.Error("LuaEngine","Error opening %s: %s\n", dottedrelpath, strerror(errno));
			} else err=false;

			if (!err && S_ISDIR(attributes.st_mode))
			{
				ScriptLoadDir((char *)dottedrelpath, pak); //Subdirectory
			} else {
				char* ext = strrchr(list[filecount]->d_name, '.');
				if(ext != NULL && !strcmp(ext, ".lua"))
				{
					pak->luaFiles.insert(dottedrelpath);
				}
			}

			free(list[filecount]);
		}
		free(list);*/
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_INFO, "LUAEngine: Loading Scripts\r\n");	
	DIR_ITER* dirIter = diropen(Dirname);
	if(dirIter)
	{
        char filename[MAXPATHLEN];
        struct stat filestat;

        int i, res;
		char *ext;
        for(i=0; i < MAXLUAFILE; i++)
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
			if(ext != NULL && !strcmp(ext, ".lua"))
			{
				std::string full_path = "sd:/scripts/" + std::string(filename);
				sLog.outString(LOGTYPE_ALL, LOGLEVEL_INFO, "LUAEngine: Adding Script %s\r\n", full_path.c_str());
				pak->luaFiles.insert(full_path);
			}			
		}
		dirclose(dirIter);		
	}
			
	#endif
}

void LuaEngine::LoadScripts(const char* root)
{
	LUALoadScripts rtn;
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_INFO, "LUAEngine: Scanning Script-Directories...\r\n");
	ScriptLoadDir((char*)root, &rtn);

	unsigned int cnt_uncomp=0;

	luaL_openlibs(lu);
	RegisterCoreFunctions();
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_INFO, "LuaEngine: Loading Scripts...\r\n");

	char filename[200];

	for(std::set<std::string>::iterator itr = rtn.luaFiles.begin(); itr != rtn.luaFiles.end(); ++itr)
	{ 
		strcpy(filename, itr->c_str());
		if(luaL_loadfile(lu, filename) != 0)
		{
#ifdef WIN32
			sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "LUAEngine: loading %s failed.(could not load)\r\n", itr->c_str());
			SetConsoleTextAttribute(stdout_handle, (WORD)TRED);
#else
			sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "LUAEngine: \033[22;31m loading %s failed.(could not load)", itr->c_str());
			printf("\033[22;31m");
#endif
			report(lu);
#ifdef WIN32
			SetConsoleTextAttribute(stdout_handle, (WORD)TWHITE);
#else
			printf("\033[01;37m");
#endif
		}
		else
		{
			if(lua_pcall(lu, 0, 0, 0) != 0)
			{
#ifdef WIN32
				sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "LUAEngine: %s failed.(could not run)\r\n", itr->c_str());
				SetConsoleTextAttribute(stdout_handle, (WORD)TRED);
#else
				sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "LUAEngine: \033[22;31m %s failed.(could not run)\r\n", itr->c_str());
				printf("\033[22;31m");

#endif

				report(lu);
#ifdef WIN32
				SetConsoleTextAttribute(stdout_handle, (WORD)TWHITE);
#else
				printf("\033[01;37m");
#endif
			}
			else
					sLog.outString(LOGTYPE_ALL, LOGLEVEL_DEBUG, "LUAEngine: loaded %s.\r\n", itr->c_str());
		}
		cnt_uncomp++;
	}
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_INFO, "LUAEngine: Loaded %u Lua scripts.\r\n", cnt_uncomp);
}

//LuaEngine Methods Implementation

bool LuaEngine::BeginCall(const char * func) 
{
	std::string sFuncName = std::string(func);
	char * copy = strdup(func);
	char * token = strtok(copy,".:");
	bool colon = false;
	if (strpbrk(func,".:") == NULL )
		lua_getglobal(lu,func);
	else
	{
		lua_getglobal(lu, "_G"); //start out with the global table.
		int top = 1;
		while (token != NULL)
		{
			lua_getfield(lu, -1, token); //get the (hopefully) table/func
			if ((int)sFuncName.find(token)-1 > 0) //if it isn't the first token
			{
				if (sFuncName.at(sFuncName.find(token)-1) == '.') //if it was a .
					colon = false;
				else if (sFuncName.at(sFuncName.find(token)-1) == ':')
					colon = true;
			}
			else //if it IS the first token, we're OK to remove the "_G" from the stack
				colon = false;

			if (lua_isfunction(lu,-1) && !lua_iscfunction(lu,-1)) //if it's a Lua function
			{
				lua_replace(lu,top);
				if (colon)
				{
					lua_pushvalue(lu, -1); //make the table the first arg
					lua_replace(lu,top+1);
					lua_settop(lu,top+1);
				}
				else
					lua_settop(lu,top);
				break; //we don't need anything else
			}
			else if(lua_istable(lu,-1) )
				token = strtok(NULL,".:");
		}
	}
	return colon;
}

bool LuaEngine::ExecuteCall(uint8 params, uint8 res)
{
	bool ret = true;
	if(lua_pcall(lu,params,res,0) )
	{
		report(lu);
		ret = false;
	}
	return ret;
}

void LuaEngine::EndCall(uint8 res) 
{
	for(int i = res; i > 0; i--)
	{
		if(!lua_isnone(lu,res))
			lua_remove(lu,res);
	}
}

void LuaEngine::PushUnit(Object * unit, lua_State * L) 
{
	Unit * pUnit = NULL;
	if(unit != NULL && unit->IsUnit() ) 
		pUnit = static_cast<Unit*>(unit);
	if(L == NULL)
		Lunar<Unit>::push(lu,pUnit);
	else
		Lunar<Unit>::push(L,pUnit);
}

void LuaEngine::PushGO(Object *go, lua_State *L)
{
	Gameobject * pGo = NULL;
	if(go != NULL && go->IsGameobject() )
		pGo = static_cast<Gameobject*>(go);
	if(L == NULL)
		Lunar<Gameobject>::push(lu,pGo);
	else
		Lunar<Gameobject>::push(L,pGo);
}

void LuaEngine::PushGUID(uint64 guid, lua_State * L) 
{
	if(L == NULL)
		GUID_MGR::push(lu,guid);
	else
		GUID_MGR::push(L,guid);
}

void LuaEngine::CallFunction(const char * FuncName, int ref)
{
	//m_Lock.Acquire();
	int top = lua_gettop(lu);
	int args = 0;
	std::string sFuncName = std::string(FuncName); //for convenience of string funcs
	char * copy = strdup(FuncName);
	char * token = strtok(copy, ".:"); //we should strtok on the copy
	bool colon = false; //whether we should keep or remove the previous table
	if (strpbrk(FuncName,".:") == NULL)
		lua_getglobal(lu,FuncName);
	else
	{
		lua_getglobal(lu, "_G"); //start out with the global table.
		while (token != NULL)
		{
			lua_getfield(lu, -1, token); //get the (hopefully) table/func
			if ((int)sFuncName.find(token)-1 > 0) //if it isn't the first token
			{
				if (sFuncName.at(sFuncName.find(token)-1) == '.') //if it was a .
					colon = false;
				else if (sFuncName.at(sFuncName.find(token)-1) == ':')
					colon = true;
			}
			else //if it IS the first token, we're OK to remove the "_G" from the stack
				colon = false;

			if (lua_isfunction(lu,-1) && !lua_iscfunction(lu,-1)) //if it's a Lua function
			{
				if (colon)
				{
					lua_pushvalue(lu, -2); //make the table the first arg
					lua_remove(lu, -3); //remove the thing we copied from (just to keep stack nice)
					++args;
				}
				else
				{
					lua_remove(lu, -2);
				}
				break; //we don't need anything else
			}
			else if (lua_istable(lu,-1))
			{
					token = strtok(NULL, ".:");
			}
		}
	}
	lua_rawgeti(lu, LUA_REGISTRYINDEX, ref);
	lua_State * M = lua_tothread(lu, -1); //repeats, args
	int thread = lua_gettop(lu);
	int repeats = luaL_checkinteger(M, 1); //repeats, args
	int nargs = lua_gettop(M)-1;
	if (nargs != 0) //if we HAVE args...
	{
		for (int i = 2; i <= nargs+1; i++)
		{
			lua_pushvalue(M,i);
		}
		lua_xmove(M, lu, nargs);
	}
	if (--repeats == 0) //free stuff, then
	{
		free((void*)FuncName);
		luaL_unref(lu, LUA_REGISTRYINDEX, ref);
	}
	else
	{
		lua_remove(M, 1); //args
		lua_pushinteger(M, repeats); //args, repeats
		lua_insert(M, 1); //repeats, args
	}
	lua_remove(lu, thread); //now we can remove the thread object
	int r = lua_pcall(lu,nargs+args,0,0);
	if (r)
		report(lu);

	free((void*)copy);
	lua_settop(lu,top);
	//m_Lock.Release();
}

void LuaEngine::FillVariable(void *val, MYTYPE type)
{
	if(!val)
		return;
	switch(type)
	{
	case MYTYPE_INT:
		{
			int32 *val = (int32*)val;
			PushInt(*val);
		} break;
	case MYTYPE_FLOAT:
		{
			float *val = (float*)val;
			PushFloat(*val);
		} break;
	case MYTYPE_STRING:
		{
			std::string *val = (std::string*)val;
			PushString((*val).c_str());
		} break;
	case MYTYPE_CREATURE:
		Lunar<Creature>::push(lu, static_cast<Creature*>(val));
		break;
	case MYTYPE_GAMEOBJECT:
		Lunar<Gameobject>::push(lu, static_cast<Gameobject*>(val));
		break;
	case MYTYPE_PLAYER:
		Lunar<Player>::push(lu, static_cast<Player*>(val));
		break;
	case MYTYPE_UNIT:
		Lunar<Unit>::push(lu, static_cast<Unit*>(val));
		break;
	case MYTYPE_OBJECT:
		Lunar<Object>::push(lu, static_cast<Object*>(val));
		break;
	case MYTYPE_WEAPON:
		Lunar<Weapon>::push(lu, static_cast<Weapon*>(val));
		break;
	case MYTYPE_PROJECTILE:
		Lunar<Projectile>::push(lu, static_cast<Projectile*>(val));
		break;
	case MYTYPE_MAPOBJECT:
		Lunar<MapObject>::push(lu, static_cast<MapObject*>(val));
		break;
	case MYTYPE_SCRIPTOBJECT:
		Lunar<ScriptObject>::push(lu, static_cast<ScriptObject*>(val));
		break;
	default:
		break;
	};
}

void LuaEngine::OnPlayerEvent(Player * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...)
{
	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from Player!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<Player>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

void LuaEngine::OnPlayerEvent(Player * pUnit, uint32 EventType, uint32 ArgCount, ...)
{
	LuaPlayerBinding *binding = getPlayerBinding(pUnit->GetEntry());
	if(!binding)
		return;
	if(!binding->Functions[EventType])
		return;
	
	const char* FunctionName = binding->Functions[EventType];

	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from Player!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<Player>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

void LuaEngine::OnCreatureEvent(Creature * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...)
{
	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from Creature!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<Creature>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

void LuaEngine::OnCreatureEvent(Creature * pUnit, uint32 EventType, uint32 ArgCount, ...)
{
	LuaCreatureBinding *binding = getCreatureBinding(pUnit->GetEntry());
	if(!binding)
		return;
	if(!binding->Functions[EventType])
		return;
	
	const char* FunctionName = binding->Functions[EventType];

	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from Creature!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<Creature>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

void LuaEngine::OnGameObjectEvent(Gameobject * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...)
{
	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from Gameobject!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<Gameobject>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

void LuaEngine::OnGameObjectEvent(Gameobject * pUnit, uint32 EventType, uint32 ArgCount, ...)
{
	LuaGameObjectBinding *binding = getGameObjectBinding(pUnit->GetEntry());
	if(!binding)
		return;
	if(!binding->Functions[EventType])
		return;
	
	const char* FunctionName = binding->Functions[EventType];

	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from Gameobject!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<Gameobject>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

void LuaEngine::OnWeaponEvent(Weapon * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...)
{
	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from Weapon!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<Weapon>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

void LuaEngine::OnWeaponEvent(Weapon * pUnit, uint32 EventType, uint32 ArgCount, ...)
{
	LuaWeaponBinding *binding = getWeaponBinding(pUnit->GetId());
	if(!binding)
		return;
	if(!binding->Functions[EventType])
		return;
	
	const char* FunctionName = binding->Functions[EventType];

	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from Weapon!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<Weapon>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

void LuaEngine::OnProjectileEvent(Projectile * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...)
{
	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from Projectile!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<Projectile>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

void LuaEngine::OnProjectileEvent(Projectile * pUnit, uint32 EventType, uint32 ArgCount, ...)
{
	LuaProjectileBinding *binding = getProjectileBinding(pUnit->GetEntry());
	if(!binding)
		return;
	if(!binding->Functions[EventType])
		return;
	
	const char* FunctionName = binding->Functions[EventType];

	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from Projectile!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<Projectile>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

void LuaEngine::OnMapObjectEvent(MapObject * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...)
{
	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from MapObject!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<MapObject>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

void LuaEngine::OnMapObjectEvent(MapObject * pUnit, uint32 EventType, uint32 ArgCount, ...)
{
	LuaMapObjectBinding *binding = getMapObjectBinding(pUnit->GetEntry());
	if(!binding)
		return;
	if(!binding->Functions[EventType])
		return;
	
	const char* FunctionName = binding->Functions[EventType];

	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from MapObject!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<MapObject>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

void LuaEngine::OnScriptObjectEvent(ScriptObject * pUnit, const char * FunctionName, uint32 EventType, uint32 ArgCount, ...)
{
	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from ScriptObject!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<ScriptObject>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

void LuaEngine::OnScriptObjectEvent(ScriptObject * pUnit, uint32 EventType, uint32 ArgCount, ...)
{
	LuaScriptObjectBinding *binding = getScriptObjectBinding(pUnit->GetEntry());
	if(!binding)
		return;
	if(!binding->Functions[EventType])
		return;
	
	const char* FunctionName = binding->Functions[EventType];

	if(FunctionName == NULL)
		return;

	//m_Lock.Acquire();
	lua_pushstring(lu, FunctionName);
	lua_gettable(lu, LUA_GLOBALSINDEX);
	if(lua_isnil(lu,-1))
	{
		printf("Tried to call invalid LUA function '%s' from ScriptObject!\n", FunctionName);
		//m_Lock.Release();
		return;
	}

	Lunar<ScriptObject>::push(lu, pUnit);
	int i = 0;
	if(ArgCount > 0)
	{
		va_list ap;
		va_start(ap, ArgCount);
		GType *type = NULL;
		type = va_arg(ap, GType*);
		for(; i < ArgCount; i++)
		{
			FillVariable(type->data, type->type);
			type = va_arg(ap, GType*);
		}
		va_end(ap);
	}
	
	int r = lua_pcall(lu,i+1,LUA_MULTRET,0);
	if(r)
		report(lu);

	//m_Lock.Release();
}

static int RegisterPlayerEvent(lua_State * L);
static int RegisterCreatureEvent(lua_State * L);
static int RegisterGameObjectEvent(lua_State * L);
static int RegisterWeaponEvent(lua_State * L);
static int RegisterProjectileEvent(lua_State * L);
static int RegisterMapObjectEvent(lua_State * L);
static int RegisterScriptObjectEvent(lua_State * L);
static int SuspendLuaThread(lua_State * L);

void LuaEngine::RegisterCoreFunctions()
{
	lua_register(lu,"RegisterPlayerEvent",RegisterPlayerEvent);
	lua_register(lu,"RegisterCreatureEvent",RegisterCreatureEvent);
	lua_register(lu,"RegisterGameObjectEvent",RegisterGameObjectEvent);
	lua_register(lu,"RegisterWeaponEvent",RegisterWeaponEvent);
	lua_register(lu,"RegisterProjectileEvent",RegisterProjectileEvent);
	lua_register(lu,"RegisterMapObjectEvent",RegisterMapObjectEvent);
	lua_register(lu,"RegisterScriptObjectEvent",RegisterScriptObjectEvent);
	lua_register(lu,"SuspendThread",&SuspendLuaThread);

	luaGlobalFunctions::Register(lu);

	Lunar<Player>::Register(lu);
	Lunar<Creature>::Register(lu);
	Lunar<Gameobject>::Register(lu);
	Lunar<Unit>::Register(lu);
	Lunar<Object>::Register(lu);
	Lunar<Weapon>::Register(lu);
	Lunar<Projectile>::Register(lu);
	Lunar<MapObject>::Register(lu);
	Lunar<ScriptObject>::Register(lu);

	GUID_MGR::Register(lu);

	//set the suspendluathread a coroutine function
	lua_getglobal(lu,"coroutine");
	if(lua_istable(lu,-1) )
	{
		lua_pushcfunction(lu,SuspendLuaThread);
		lua_setfield(lu,-2,"wait");
		lua_pushcfunction(lu,SuspendLuaThread);
		lua_setfield(lu,-2,"WAIT");
	}
	lua_pop(lu,1);
}

static int RegisterPlayerEvent(lua_State * L)
{
	int entry = luaL_checkint(L, 1);
	int ev = luaL_checkint(L, 2);
	const char * str = luaL_checkstring(L, 3);

	if(!entry || !ev || !str)
		return 0;
	int top = lua_gettop(L);
	char * copy = strdup(str);
	char * token = strtok(copy, ".:");
	if( strpbrk(str,".:") == NULL)
	{
		lua_getglobal(L,str);
		if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			sLuaMgr.RegisterEvent(REGTYPE_PLAYER,entry,ev,str);
		else
		{
			luaL_error(L,"LuaEngineMgr : RegisterPlayerEvent failed! %s is not a valid Lua function. \n",str);
		}
	}
	else
	{
		lua_getglobal(L,"_G");
		while(token != NULL)
		{
			lua_getfield(L,-1,token);
			if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			{
				sLuaMgr.RegisterEvent(REGTYPE_PLAYER,entry,ev,str);
				break;
			}
			else if(lua_istable(L,-1) )
			{
				token = strtok(NULL,".:");
				continue;
			}
			else
			{
				luaL_error(L,"LuaEngineMgr : RegisterPlayerEvent failed! %s is not a valid Lua function. \n",token);
				break;
			}
		}
	}
	free((void*)copy);
	lua_settop(L,top);
	return 0;
}

static int RegisterCreatureEvent(lua_State * L)
{
	int entry = luaL_checkint(L, 1);
	int ev = luaL_checkint(L, 2);
	const char * str = luaL_checkstring(L, 3);

	if(!entry || !ev || !str)
		return 0;
	int top = lua_gettop(L);
	char * copy = strdup(str);
	char * token = strtok(copy, ".:");
	if( strpbrk(str,".:") == NULL)
	{
		lua_getglobal(L,str);
		if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			sLuaMgr.RegisterEvent(REGTYPE_CREATURE,entry,ev,str);
		else
		{
			luaL_error(L,"LuaEngineMgr : RegisterCreatureEvent failed! %s is not a valid Lua function. \n",str);
		}
	}
	else
	{
		lua_getglobal(L,"_G");
		while(token != NULL)
		{
			lua_getfield(L,-1,token);
			if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			{
				sLuaMgr.RegisterEvent(REGTYPE_CREATURE,entry,ev,str);
				break;
			}
			else if(lua_istable(L,-1) )
			{
				token = strtok(NULL,".:");
				continue;
			}
			else
			{
				luaL_error(L,"LuaEngineMgr : RegisterCreatureEvent failed! %s is not a valid Lua function. \n",token);
				break;
			}
		}
	}
	free((void*)copy);
	lua_settop(L,top);
	return 0;
}

static int RegisterGameObjectEvent(lua_State * L)
{
	int entry = luaL_checkint(L, 1);
	int ev = luaL_checkint(L, 2);
	const char * str = luaL_checkstring(L, 3);

	if(!entry || !ev || !str)
		return 0;

	int top = lua_gettop(L);
	char * copy = strdup(str);
	char * token = strtok(copy,".:");
	if( strpbrk(str,".:") == NULL)
	{
		lua_getglobal(L,str);
		if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			sLuaMgr.RegisterEvent(REGTYPE_GO,entry,ev,str);
		else
		{
			luaL_error(L,"LuaEngineMgr : RegisterGameObjectEvent failed! %s is not a valid Lua function. \n",copy);
		}
	}
	else
	{
		lua_getglobal(L,"_G");
		while(token != NULL)
		{
			lua_getfield(L,-1,token);
			if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			{
				sLuaMgr.RegisterEvent(REGTYPE_GO,entry,ev,str);
				break;
			}
			else if(lua_istable(L,-1) )
			{
				token = strtok(NULL,".:");
				continue;
			}
			else
			{
				luaL_error(L,"LuaEngineMgr : RegisterGameObjectEvent failed! %s is not a valid Lua function. \n",token);
				break;
			}
		}
	}
	free((void*)copy);
	lua_settop(L,top);
	return 0;
}

static int RegisterWeaponEvent(lua_State * L)
{
	int entry = luaL_checkint(L, 1);
	int ev = luaL_checkint(L, 2);
	const char * str = luaL_checkstring(L, 3);

	if(!entry || !ev || !str)
		return 0;

	int top = lua_gettop(L);
	char * copy = strdup(str);
	char * token = strtok(copy,".:");
	if( strpbrk(str,".:") == NULL)
	{
		lua_getglobal(L,str);
		if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			sLuaMgr.RegisterEvent(REGTYPE_WEAPON,entry,ev,str);
		else
		{
			luaL_error(L,"LuaEngineMgr : RegisterWeaponEvent failed! %s is not a valid Lua function. \n",copy);
		}
	}
	else
	{
		lua_getglobal(L,"_G");
		while(token != NULL)
		{
			lua_getfield(L,-1,token);
			if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			{
				sLuaMgr.RegisterEvent(REGTYPE_WEAPON,entry,ev,str);
				break;
			}
			else if(lua_istable(L,-1) )
			{
				token = strtok(NULL,".:");
				continue;
			}
			else
			{
				luaL_error(L,"LuaEngineMgr : RegisterWeaponEvent failed! %s is not a valid Lua function. \n",token);
				break;
			}
		}
	}
	free((void*)copy);
	lua_settop(L,top);
	return 0;
}

static int RegisterProjectileEvent(lua_State * L)
{
	int entry = luaL_checkint(L, 1);
	int ev = luaL_checkint(L, 2);
	const char * str = luaL_checkstring(L, 3);

	if(!entry || !ev || !str)
		return 0;

	int top = lua_gettop(L);
	char * copy = strdup(str);
	char * token = strtok(copy,".:");
	if( strpbrk(str,".:") == NULL)
	{
		lua_getglobal(L,str);
		if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			sLuaMgr.RegisterEvent(REGTYPE_PROJECTILE,entry,ev,str);
		else
		{
			luaL_error(L,"LuaEngineMgr : RegisterProjectileEvent failed! %s is not a valid Lua function. \n",copy);
		}
	}
	else
	{
		lua_getglobal(L,"_G");
		while(token != NULL)
		{
			lua_getfield(L,-1,token);
			if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			{
				sLuaMgr.RegisterEvent(REGTYPE_PROJECTILE,entry,ev,str);
				break;
			}
			else if(lua_istable(L,-1) )
			{
				token = strtok(NULL,".:");
				continue;
			}
			else
			{
				luaL_error(L,"LuaEngineMgr : RegisterProjectileEvent failed! %s is not a valid Lua function. \n",token);
				break;
			}
		}
	}
	free((void*)copy);
	lua_settop(L,top);
	return 0;
}

static int RegisterMapObjectEvent(lua_State * L)
{
	int entry = luaL_checkint(L, 1);
	int ev = luaL_checkint(L, 2);
	const char * str = luaL_checkstring(L, 3);

	if(!entry || !ev || !str)
		return 0;

	int top = lua_gettop(L);
	char * copy = strdup(str);
	char * token = strtok(copy,".:");
	if( strpbrk(str,".:") == NULL)
	{
		lua_getglobal(L,str);
		if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			sLuaMgr.RegisterEvent(REGTYPE_MAPOBJECT,entry,ev,str);
		else
		{
			luaL_error(L,"LuaEngineMgr : RegisterMapObjectEvent failed! %s is not a valid Lua function. \n",copy);
		}
	}
	else
	{
		lua_getglobal(L,"_G");
		while(token != NULL)
		{
			lua_getfield(L,-1,token);
			if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			{
				sLuaMgr.RegisterEvent(REGTYPE_MAPOBJECT,entry,ev,str);
				break;
			}
			else if(lua_istable(L,-1) )
			{
				token = strtok(NULL,".:");
				continue;
			}
			else
			{
				luaL_error(L,"LuaEngineMgr : RegisterMapObjectEvent failed! %s is not a valid Lua function. \n",token);
				break;
			}
		}
	}
	free((void*)copy);
	lua_settop(L,top);
	return 0;
}

static int RegisterScriptObjectEvent(lua_State * L)
{
	int entry = luaL_checkint(L, 1);
	int ev = luaL_checkint(L, 2);
	const char * str = luaL_checkstring(L, 3);

	if(!entry || !ev || !str)
		return 0;

	int top = lua_gettop(L);
	char * copy = strdup(str);
	char * token = strtok(copy,".:");
	if( strpbrk(str,".:") == NULL)
	{
		lua_getglobal(L,str);
		if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			sLuaMgr.RegisterEvent(REGTYPE_SCRIPTOBJECT,entry,ev,str);
		else
		{
			luaL_error(L,"LuaEngineMgr : RegisterScriptObjectEvent failed! %s is not a valid Lua function. \n",copy);
		}
	}
	else
	{
		lua_getglobal(L,"_G");
		while(token != NULL)
		{
			lua_getfield(L,-1,token);
			if(lua_isfunction(L,-1) && !lua_iscfunction(L,-1) )
			{
				sLuaMgr.RegisterEvent(REGTYPE_SCRIPTOBJECT,entry,ev,str);
				break;
			}
			else if(lua_istable(L,-1) )
			{
				token = strtok(NULL,".:");
				continue;
			}
			else
			{
				luaL_error(L,"LuaEngineMgr : RegisterScriptObjectEvent failed! %s is not a valid Lua function. \n",token);
				break;
			}
		}
	}
	free((void*)copy);
	lua_settop(L,top);
	return 0;
}

static int SuspendLuaThread(lua_State * L) {
	lua_State * thread = (lua_isthread(L,1)) ? lua_tothread(L,1) : NULL;
	if(thread == NULL) {
		return luaL_error(L,"LuaEngineMgr","SuspendLuaThread expected Lua coroutine, got NULL. \n");
	}
	int waitime = luaL_checkinteger(L,2);
	if(waitime <= 0) {
		return luaL_error(L,"LuaEngineMgr","SuspendLuaThread expected timer > 0 instead got (%d) \n",waitime);
	}
	lua_pushvalue(L,1);
	int ref = luaL_ref(L,LUA_REGISTRYINDEX);
	if(ref == LUA_REFNIL || ref == LUA_NOREF)
		return luaL_error(L,"Error in SuspendLuaThread! Failed to create a valid reference.");
	/*TimedEvent * evt = TimedEvent::Allocate(thread,new CallbackP2<LuaEngine,lua_State*,int>(&g_luaMgr,&LuaEngine::ResumeLuaThread,thread,ref),0,waitime,1);
	sWorld.event_AddEvent(evt);*/
	lua_remove(L,1); // remove thread object
	lua_remove(L,1); // remove timer.
	//All that remains now are the extra arguments passed to this function.
	lua_xmove(L,thread,lua_gettop(L));
	g_luaMgr.getPendingThreadSet().insert(thread);
	return lua_yield(thread,lua_gettop(L));
}

#ifdef CPPSCRIPTING

CreatureAIScript * CreateLuaCreature(Creature * src)
{
	LuaCreature * script = NULL;
	if(src != NULL)
	{
		uint32 id = src->GetEntry();
		uint64 guid = src->GetGUID();
		LuaUnitBinding * pBinding = sLuaMgr.getUnitBinding(id);
		if( pBinding != NULL)
		{
			typedef std::multimap<uint32,LuaCreature*> CRCMAP;
			CRCMAP & cMap = sLuaMgr.getLuCreatureMap();
			CRCMAP::iterator itr = cMap.find(id);
			CRCMAP::iterator itend = cMap.upper_bound(id);
			for(; itr != itend; ++itr)
			{
				//grab the 1st and initalize
				if(itr->second == NULL)
				{
					script = itr->second = new LuaCreature(src);
					break;
				}
				if(itr->second != NULL && itr->second->GetUnit() != NULL && itr->second->GetUnit()->GetGUID() == guid)
					script = itr->second;
			}
			if(script == NULL)
			{
				script = new LuaCreature(src);
				cMap.insert(make_pair(id,script));
			}
			script->m_binding = pBinding;
		}
	}
	return script;
}

GameObjectAIScript * CreateLuaGameObject(Gameobject * src)
{
	LuaGameObject * script = NULL;
	if(src == NULL) 
	{
		uint32 id = src->GetInfo()->ID;
		uint64 guid = src->GetGUID();
		LuaGameObjectBinding * pBinding = NULL;
		pBinding = sLuaMgr.getGameObjectBinding(id);
		if( pBinding != NULL) 
		{
			typedef multimap<uint32,LuaGameObject*> GMAP;
			GMAP & gMap = sLuaMgr.getLuGameObjectMap();
			GMAP::iterator itr = gMap.find(id);
			GMAP::iterator itend = gMap.upper_bound(id);
			for(; itr != itend; ++itr)
			{
				if(itr->second != NULL && itr->second->getGO() != NULL && itr->second->getGO()->GetGUID() == guid)
					script = itr->second;
			}
			if(script == NULL)
			{
				script = new LuaGameObject(src);
				gMap.insert(make_pair(id,script));
			}
			script->m_binding = pBinding;
			
		}
	}
	return script;
}

#endif

void LuaEngine::Startup()
{
	Sleep(1200);
	//Create a new global state that will server as the lua universe.
	lu = lua_open();

	LoadScripts("sd:/scripts/");

#ifdef CPPSCRIPTING
	// stuff is registered, so lets go ahead and make our emulated C++ scripted lua classes.
	for(UnitBindingMap::iterator itr = m_unitBinding.begin(); itr != m_unitBinding.end(); ++itr)
	{
		m_scriptMgr->register_creature_script( itr->first, CreateLuaCreature );
		sLuaMgr.getLuCreatureMap().insert(make_pair(itr->first,(LuaCreature*)NULL));
	}

	for(GameObjectBindingMap::iterator itr = m_gameobjectBinding.begin(); itr != m_gameobjectBinding.end(); ++itr)
	{
		m_scriptMgr->register_gameobject_script( itr->first, CreateLuaGameObject );
		sLuaMgr.getLuGameObjectMap().insert(make_pair(itr->first,(LuaGameObject*)NULL));
	}
#endif
}

void LuaEngine::RegisterEvent(uint8 regtype, uint32 id, uint32 evt, const char *func) 
{
	if(func != NULL && evt) 
	{
		switch(regtype) 
		{
		case REGTYPE_PLAYER:
			{
				if(id && evt < PLAYER_EVENT_COUNT) {
					LuaPlayerBinding * bind = getPlayerBinding(id);
					if(bind == NULL) {
						LuaPlayerBinding nbind;
						memset(&nbind,0,sizeof(LuaPlayerBinding));
						nbind.Functions[evt] = strdup(func);
						m_playerBinding.insert(std::make_pair(id,nbind));
					}
					else
					{
						if(bind->Functions[evt] != NULL)
							free((void*)bind->Functions[evt]);
						bind->Functions[evt] = strdup(func);
					}
				}
			}break;
		case REGTYPE_CREATURE: 
			{
				if(id && evt < CREATURE_EVENT_COUNT) {
					LuaCreatureBinding * bind = getCreatureBinding(id);
					if(bind == NULL) {
						LuaCreatureBinding nbind;
						memset(&nbind,0,sizeof(LuaCreatureBinding));
						nbind.Functions[evt] = strdup(func);
						m_creatureBinding.insert(std::make_pair(id,nbind));
					}
					else
					{
						if(bind->Functions[evt] != NULL)
							free((void*)bind->Functions[evt]);
						bind->Functions[evt] = strdup(func);
					}
				}
			}break;
		case REGTYPE_GO:
			{
				if(id && evt < GAMEOBJECT_EVENT_COUNT) {
					LuaGameObjectBinding * bind = getGameObjectBinding(id);
					if(bind == NULL) {
						LuaGameObjectBinding nbind;
						memset(&nbind,0,sizeof(LuaGameObjectBinding));
						nbind.Functions[evt] = strdup(func);
						m_gameobjectBinding.insert(std::make_pair(id,nbind));
					}
					else {
						if(bind->Functions[evt] != NULL)
							free( (void*)bind->Functions[evt]);
						bind->Functions[evt] = strdup(func);
					}
				}
			}break;
		case REGTYPE_WEAPON:
			{
				if(id && evt < WEAPON_EVENT_COUNT) {
					LuaWeaponBinding * bind = getWeaponBinding(id);
					if(bind == NULL) {
						LuaWeaponBinding nbind;
						memset(&nbind,0,sizeof(LuaWeaponBinding));
						nbind.Functions[evt] = strdup(func);
						m_weaponBinding.insert(std::make_pair(id,nbind));
					}
					else {
						if(bind->Functions[evt] != NULL)
							free( (void*)bind->Functions[evt]);
						bind->Functions[evt] = strdup(func);
					}
				}
			}break;
		case REGTYPE_PROJECTILE:
			{
				if(id && evt < PROJECTILE_EVENT_COUNT) {
					LuaProjectileBinding * bind = getProjectileBinding(id);
					if(bind == NULL) {
						LuaProjectileBinding nbind;
						memset(&nbind,0,sizeof(LuaProjectileBinding));
						nbind.Functions[evt] = strdup(func);
						m_projectileBinding.insert(std::make_pair(id,nbind));
					}
					else {
						if(bind->Functions[evt] != NULL)
							free( (void*)bind->Functions[evt]);
						bind->Functions[evt] = strdup(func);
					}
				}
			}break;
		case REGTYPE_MAPOBJECT:
			{
				if(id && evt < MAPOBJECT_EVENT_COUNT) {
					LuaMapObjectBinding * bind = getMapObjectBinding(id);
					if(bind == NULL) {
						LuaMapObjectBinding nbind;
						memset(&nbind,0,sizeof(LuaMapObjectBinding));
						nbind.Functions[evt] = strdup(func);
						m_mapobjectBinding.insert(std::make_pair(id,nbind));
					}
					else {
						if(bind->Functions[evt] != NULL)
							free( (void*)bind->Functions[evt]);
						bind->Functions[evt] = strdup(func);
					}
				}
			}break;
		case REGTYPE_SCRIPTOBJECT:
			{
				if(id && evt < SCRIPTOBJECT_EVENT_COUNT) {
					LuaScriptObjectBinding * bind = getScriptObjectBinding(id);
					if(bind == NULL) {
						LuaScriptObjectBinding nbind;
						memset(&nbind,0,sizeof(LuaScriptObjectBinding));
						nbind.Functions[evt] = strdup(func);
						m_scriptobjectBinding.insert(std::make_pair(id,nbind));
					}
					else {
						if(bind->Functions[evt] != NULL)
							free( (void*)bind->Functions[evt]);
						bind->Functions[evt] = strdup(func);
					}
				}
			}break;
		}
	}
}

void LuaEngine::Unload()
{
	lua_close(lu); // clean up the engine of any existing defined variables
	{
		PlayerBindingMap::iterator itr = this->m_playerBinding.begin();
		for(; itr != m_playerBinding.end(); ++itr)
		{
			for(int i = 0; i < PLAYER_EVENT_COUNT; ++i) 
			{
				if(itr->second.Functions[i] != NULL)
					free((void*)itr->second.Functions[i]);
			}
		}
		m_playerBinding.clear();
	}	
	{
		CreatureBindingMap::iterator itr = this->m_creatureBinding.begin();
		for(; itr != m_creatureBinding.end(); ++itr)
		{
			for(int i = 0; i < CREATURE_EVENT_COUNT; ++i) 
			{
				if(itr->second.Functions[i] != NULL)
					free((void*)itr->second.Functions[i]);
			}
		}
		m_creatureBinding.clear();
	}
	{
		GameObjectBindingMap::iterator itr = this->m_gameobjectBinding.begin();
		for(; itr != m_gameobjectBinding.end(); ++itr)
		{
			for(int i = 0; i < GAMEOBJECT_EVENT_COUNT; ++i) 
			{
				if(itr->second.Functions[i] != NULL)
					free((void*)itr->second.Functions[i]);
			}
		}
		m_gameobjectBinding.clear();
	}
	{
		WeaponBindingMap::iterator itr = this->m_weaponBinding.begin();
		for(; itr != m_weaponBinding.end(); ++itr)
		{
			for(int i = 0; i < WEAPON_EVENT_COUNT; ++i) 
			{
				if(itr->second.Functions[i] != NULL)
					free((void*)itr->second.Functions[i]);
			}
		}
		m_weaponBinding.clear();
	}
	{
		ProjectileBindingMap::iterator itr = this->m_projectileBinding.begin();
		for(; itr != m_projectileBinding.end(); ++itr)
		{
			for(int i = 0; i < PROJECTILE_EVENT_COUNT; ++i) 
			{
				if(itr->second.Functions[i] != NULL)
					free((void*)itr->second.Functions[i]);
			}
		}
		m_projectileBinding.clear();
	}
	{
		MapObjectBindingMap::iterator itr = this->m_mapobjectBinding.begin();
		for(; itr != m_mapobjectBinding.end(); ++itr)
		{
			for(int i = 0; i < MAPOBJECT_EVENT_COUNT; ++i) 
			{
				if(itr->second.Functions[i] != NULL)
					free((void*)itr->second.Functions[i]);
			}
		}
		m_mapobjectBinding.clear();
	}
	{
		ScriptObjectBindingMap::iterator itr = this->m_scriptobjectBinding.begin();
		for(; itr != m_scriptobjectBinding.end(); ++itr)
		{
			for(int i = 0; i < SCRIPTOBJECT_EVENT_COUNT; ++i) 
			{
				if(itr->second.Functions[i] != NULL)
					free((void*)itr->second.Functions[i]);
			}
		}
		m_scriptobjectBinding.clear();
	}

	m_pendingThreads.clear();
}

void LuaEngine::Restart()
{
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_INFO, "LuaEngine: Restarting Engine.\r\n");
	if(getLock().AttemptAcquire() && getcoLock().AttemptAcquire() )
	{
		Unload();
		lu = lua_open();
		LoadScripts("sd:/");

#ifdef CPPSCRIPTING
		for(UnitBindingMap::iterator itr = m_unitBinding.begin(); itr != m_unitBinding.end(); ++itr)
		{
			typedef multimap<uint32,LuaCreature*> CMAP;
			CMAP & cMap = sLuaMgr.getLuCreatureMap();
			CMAP::iterator it = cMap.find(itr->first);
			CMAP::iterator itend = cMap.upper_bound(itr->first);
			if(it == cMap.end() )
			{
				m_scriptMgr->register_creature_script(itr->first,CreateLuaCreature);
				cMap.insert(make_pair(itr->first,(LuaCreature*)NULL));
			}
			else
			{
				for(;it != itend; ++it) 
				{
					if(it->second != NULL)
						it->second->m_binding = &itr->second;
				}
			}
		}
		for(GameObjectBindingMap::iterator itr = m_gameobjectBinding.begin(); itr != m_gameobjectBinding.end(); ++itr)
		{
			typedef multimap<uint32,LuaGameObject*> GMAP;
			GMAP & gMap = sLuaMgr.getLuGameObjectMap();
			GMAP::iterator it = gMap.find(itr->first);
			GMAP::iterator itend = gMap.upper_bound(itr->first);
			if(it == gMap.end() )
			{
				m_scriptMgr->register_gameobject_script(itr->first,CreateLuaGameObject);
				gMap.insert(make_pair(itr->first,(LuaGameObject*)NULL));
			}
			else
			{
				for(;it != itend; ++it)
				{
					if(it->second != NULL)
						it->second->m_binding = &itr->second;
				}
			}
		}
#endif
		getLock().Release();
		getcoLock().Release();
	}
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_INFO, "LuaEngine: Done restarting engine.");
}

void LuaEngine::ResumeLuaThread(lua_State * thread,int ref) {
	CLuaThread * p_thread = new CLuaThread(thread,ref);
	ThreadPool.ExecuteTask(p_thread); // p_thread gets deleted automatically when it finishes its task :)
}
