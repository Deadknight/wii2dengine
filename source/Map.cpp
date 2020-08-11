#include "Stdafx.h"

initialiseSingleton( Map );

Map::Map()
{
	m_currentX = 320;
	m_currentY = 240;
	m_targetX = 320;
	m_targetY = 240;
	m_cameraSpeed = 300;
	//Size is fixed on wii
	m_sizeX = 320;
	m_sizeY = 240;
	m_lockCamera = false;

	m_highGoGuid = 0;
	m_highUnitGuid = 0;
	m_highPetGuid = 0;
	m_highPlayerGuid = -1;
	m_highGenericGuid = 0;
	m_highTimedGuid = 0;
}

Map::~Map()
{
}

void Map::Load(const char* mapName)
{
	//Destroy created resources
	sResourceMgr.DestroyFlag(MEMORY_MAP);

	//Initialize guids
	m_highGoGuid = 0;
	m_highUnitGuid = 0;
	m_highPetGuid = 0;
	m_highPlayerGuid = -1;
	m_highGenericGuid = 0;
	m_highTimedGuid = 0;

	_reusable_guids_timedobject.clear();

	//Load Map
	std::fstream binary_file(mapName, std::ios::binary | std::ios::in);
	if(!binary_file.is_open())
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Cannot open map file %s\r\n", mapName);
		
	int elementNumber = 0;
	binary_file.read((char*)&elementNumber, sizeof(uint32)); //loading max value

	int32 temp = 0;
	//Background
	int32 count = 0;
	binary_file.read((char*)&count, sizeof(uint32));
	for(int32 i = 0; i < count; i++)
	{
		int32 strLen = 0;
		binary_file.read((char*)&strLen, sizeof(uint32));
		char file[255];
		binary_file.read(file, strLen);
		file[strLen] = 0;
		int32 x = 0;
		int32 y = 0;
		int32 rot = 0;
		binary_file.read((char*)&x, sizeof(int32));
		binary_file.read((char*)&y, sizeof(int32));
		binary_file.read((char*)&rot, sizeof(int32));
		Background *b = new Background();
		b->x = x;
		b->y = y;
		b->rot = rot;

		std::string filename = file;
		SpriteProp prop;
		b->back = sResourceMgr.GetSpriteByName(filename.c_str(), &prop, MEMORY_MAP);
		if(b->back)
		{
			m_backgroundSet.insert(b);
			ML_RotateSprite(b->back, b->rot, 0);
		}
	}

	//Objects
	count = 0;
	binary_file.read((char*)&count, sizeof(uint32));
			
	for(int32 i = 0; i < count; i++)
	{
		uint32 entry = 0;
		binary_file.read((char*)&entry, sizeof(uint32));
		int32 mass = 0;
		binary_file.read((char*)&mass, sizeof(int32));
		int32 inverseMass = -1;
		binary_file.read((char*)&inverseMass, sizeof(int32));
		int32 type = 0;
		binary_file.read((char*)&type, sizeof(int32));
		int32 strLen = 0;
		binary_file.read((char*)&strLen, sizeof(uint32));
		char file[255];
		binary_file.read(file, strLen);
		file[strLen] = 0;
		Object *obj = NULL;
		int eventType = 0;
		switch(type)
		{
		case TYPE_PLAYER:
			{
			}break;
		case TYPE_UNIT:
			{
				obj = CreateCreature(entry);
				int32 nameLen = 0;
				binary_file.read((char*)&nameLen, sizeof(uint32));
				if(nameLen > 0)
				{
					char name[255];
					binary_file.read(name, nameLen);
					name[nameLen] = 0;
					static_cast<Creature*>(obj)->SetName(name);
				}
				uint32 faction = 0;
				binary_file.read((char*)&faction, sizeof(uint32));
				obj->SetUInt32Value(UNIT_FIELD_FACTION, faction);
				if(faction & FACTION_PLAYER || faction & FACTION_PLAYER_NPC)
					obj->SetUInt32Value(UNIT_FIELD_FACTION_HOSTILE_MASK, FACTION_PLAYER_HOSTILE_MASK);
				else
					obj->SetUInt32Value(UNIT_FIELD_FACTION_HOSTILE_MASK, FACTION_CREATURE_HOSTILE_MASK);
			}break;
		case TYPE_GAMEOBJECT:
			{
				obj = CreateGameobject(entry);
				int32 nameLen = 0;
				binary_file.read((char*)&nameLen, sizeof(uint32));
				if(nameLen > 0)
				{
					char name[255];
					binary_file.read(name, nameLen);
					name[nameLen] = 0;
					static_cast<Gameobject*>(obj)->SetName(name);
				}
			}break;
		case TYPE_EVENT:
			{
				binary_file.read((char*)&eventType, sizeof(uint32));
			}break;
		case TYPE_SCRIPT:
			{
				obj = CreateGenericObject(entry, type);
				int32 type = 0;
				binary_file.read((char*)&type, sizeof(uint32));
				static_cast<ScriptObject*>(obj)->SetType(type);
			}break;
		case TYPE_MAP:
			{
				obj = CreateGenericObject(entry, type);
				uint8 repeat = 0;
				binary_file.read((char*)&repeat, sizeof(uint8));
				uint8 breakable = 0;
				binary_file.read((char*)&breakable, sizeof(uint8));
				static_cast<MapObject*>(obj)->SetCanRepeat(repeat);
				static_cast<MapObject*>(obj)->SetCanBreakable(breakable);
			}break;
		case TYPE_SOUND:
			{
				obj = CreateGenericObject(entry, type);
				int32 nameLen = 0;
				binary_file.read((char*)&nameLen, sizeof(uint32));
				if(nameLen > 0)
				{
					char name[255];
					binary_file.read(name, nameLen);
					name[nameLen] = 0;
					static_cast<SoundObject*>(obj)->SetName(name);
				}
				int32 soundFileLen = 0;
				binary_file.read((char*)&soundFileLen, sizeof(uint32));
				if(soundFileLen > 0)
				{
					char soundFile[255];
					binary_file.read(soundFile, soundFileLen);
					soundFile[soundFileLen] = 0;
					static_cast<SoundObject*>(obj)->SetFilename(soundFile);
				}
				int32 type = 0;
				binary_file.read((char*)&type, sizeof(uint32));
				static_cast<SoundObject*>(obj)->SetType(type);
				uint8 loop = 0;
				binary_file.read((char*)&loop, sizeof(uint8));
				static_cast<SoundObject*>(obj)->SetLoop(loop);
			}break;
		};

		int32 x = 0;
		int32 y = 0;
		int32 width = 0;
		int32 height = 0;
		int32 displaywidth = 0;
		int32 displayheight = 0;
		int32 rot = 0;
		binary_file.read((char*)&x, sizeof(int32));
		binary_file.read((char*)&y, sizeof(int32));
		binary_file.read((char*)&width, sizeof(uint32));
		binary_file.read((char*)&height, sizeof(uint32));
		binary_file.read((char*)&displaywidth, sizeof(uint32));
		binary_file.read((char*)&displayheight, sizeof(uint32));
		binary_file.read((char*)&rot, sizeof(int32));

		switch(type)
		{
		case TYPE_PLAYER:
			{
			}break;
		case TYPE_UNIT:
			{
				Creature *cre = static_cast<Creature*>(obj);
				cre->Init(file, entry);
				cre->SetPosition(x, y, 0);
				if(cre->GetCollisionPrimitive())
					cre->GetCollisionPrimitive()->GetPhysicObject()->SetMass(mass);
				m_unitMap.insert(std::make_pair(cre->GetLowGUID(), cre));
			}break;
		case TYPE_GAMEOBJECT:
			{
				Gameobject *go = static_cast<Gameobject*>(obj);
				go->Init(file, entry);
				go->SetPosition(x, y, 0);
				go->SetRotation(rot);
				m_goMap.insert(std::make_pair(go->GetLowGUID(), go));
			}break;
		case TYPE_EVENT:
			{
				if(eventType == MAP_EVENT_LEVEL_START)
				{
					obj = CreatePlayer();
					Player *plr = static_cast<Player*>(obj);
					plr->SetPosition(x, y, 0);
					plr->Init("marco", 1);
					//plr->AddWeapon("MachineGun", 1);
					m_plrMap.insert(std::make_pair(plr->GetLowGUID(), plr));
#ifdef DEBUG
					_break();
#endif
				}
			}break;
		case TYPE_SCRIPT:
			{
				ScriptObject *so = static_cast<ScriptObject*>(obj);
				so->Init("script", entry);
				so->SetPosition(x, y, 0);
				m_genericMap.insert(std::make_pair(so->GetLowGUID(), so));
			}break;
		case TYPE_MAP:
			{
				MapObject *mo = static_cast<MapObject*>(obj);
				mo->Init(file, entry);
				mo->SetPosition(x, y, 0);
				m_genericMap.insert(std::make_pair(mo->GetLowGUID(), mo));
			}break;
		case TYPE_SOUND:
			{
				SoundObject *so = static_cast<SoundObject*>(obj);
				so->Init("sound", entry);
				so->SetPosition(x, y, 0);
				m_genericMap.insert(std::make_pair(so->GetLowGUID(), so));
			}break;
		};
	}

    //Physics
	count = 0;
	binary_file.read((char*)&count, sizeof(uint32));
	for(int32 i = 0; i < count; i++)
	{
		int32 type = 0;
		binary_file.read((char*)&type, sizeof(uint32));
		int32 mass = 0;
		binary_file.read((char*)&mass, sizeof(int32));
		int32 inverseMass = -1;
		binary_file.read((char*)&inverseMass, sizeof(int32));
		int32 x = 0;
		binary_file.read((char*)&x, sizeof(int32));
		int32 y = 0;
		binary_file.read((char*)&y, sizeof(int32));
		uint32 width = 0;
		binary_file.read((char*)&width, sizeof(uint32));
		uint32 height = 0;
		binary_file.read((char*)&height, sizeof(uint32));
		uint32 rot = 0;
		binary_file.read((char*)&rot, sizeof(uint32));

		switch(type)
		{
		case PPT_POINT:
			{
				CollisionPoint *cp = new CollisionPoint();
				cp->GetPhysicObject()->SetPosition(x, y, 0);
				cp->GetPhysicObject()->SetRotation(0, 0, rot);
				if(inverseMass != -1)
					cp->GetPhysicObject()->SetInverseMass(inverseMass);
				else
					cp->GetPhysicObject()->SetMass(mass);
				cp->SetCollisionFlag(COLLISION_FLAG_WORLD);
				sPhysicsMgr.AddPhysicsObject(cp);
			}break;
		case PPT_BOX:
			{
				CollisionBox *cb = new CollisionBox();
				cb->halfSize.x = width/2;
				cb->halfSize.y = height/2;
				cb->GetPhysicObject()->SetPosition(x + cb->halfSize.x, y + cb->halfSize.y, 0);
				cb->GetPhysicObject()->SetRotation(0, 0, rot);	
				if(inverseMass != -1)
					cb->GetPhysicObject()->SetInverseMass(inverseMass);
				else
					cb->GetPhysicObject()->SetMass(mass);
				cb->SetCollisionFlag(COLLISION_FLAG_WORLD);
				sPhysicsMgr.AddPhysicsObject(cb);
			}break;
		case PPT_SPHERE:
			{
				CollisionSphere *cs = new CollisionSphere();
				cs->GetPhysicObject()->SetPosition(x, y, 0);
				cs->GetPhysicObject()->SetRotation(0, 0, rot);
				cs->radius = width;
				if(inverseMass != -1)
					cs->GetPhysicObject()->SetInverseMass(inverseMass);
				else
					cs->GetPhysicObject()->SetMass(mass);
				cs->SetCollisionFlag(COLLISION_FLAG_WORLD);
				sPhysicsMgr.AddPhysicsObject(cs);
			}break;
		case PPT_PLANE:
			{
				//We dont support this for now
			}break;
		};
    }
}

void Map::UpdateCamera(Real duration, bool spring)
{
	//Camera will follow player
	if(!m_lockCamera) //For scripts
	{
		//When we reach ten pixel before camera
		//First get look position of all players
		uint32 wCount = 0;
		uint32 eCount = 0;
		Vector3 totalPos;
		totalPos.x = 0;
		totalPos.y = 0;
		totalPos.z = 0;
		uint32 plrSize = m_plrMap.size();
		if(!plrSize)
			return;

		std::map<uint32, Player*>::iterator itr = m_plrMap.begin();
		for(; itr != m_plrMap.end(); ++itr)
		{
			Player *plr = itr->second;
			Vector3 pos = plr->GetPosition();
			totalPos.x += pos.x;
			totalPos.y += pos.y;
			totalPos.z += pos.z;
			if(plr->GetSpriteFlag() & LOOK_POSITION_E)
				eCount++;
			else
				wCount++;
		}

		int32 xPos = totalPos.x / plrSize;
		int32 yPos = totalPos.y / plrSize;
		int32 zPos = totalPos.z / plrSize;
		if(spring)
		{
			if(eCount >= 0)
			{
				m_targetX = xPos + 15;
				m_targetY = yPos - 15;
			}
			else
			{
				m_targetX = xPos - 15;
				m_targetY = yPos - 15;
			}
		}
		else
		{
			if(eCount >= 0)
			{
				m_currentX = xPos + 15;
				m_currentY = yPos - 15;
			}
			else
			{
				m_currentX = xPos - 15;
				m_currentY = yPos - 15;
			}		
		}
	}
	
	if(spring && (m_currentX != m_targetX || m_currentY != m_targetY))
	{
		int32 delta = m_cameraSpeed*duration;
		int32 difX = m_targetX - m_currentX;
		int32 difY = m_targetY - m_currentY;
		if(difX != 0)
		{
			if(difX > 0)
			{
				if(delta < abs(difX))
					m_currentX += delta;
				else
					m_currentX += difX;			
			}
			else
			{
				if(delta < abs(difX))
					m_currentX -= delta;
				else
					m_currentX += difX;					
			}
		}
		if(difY != 0)
		{
			if(difY > 0)
			{
				if(delta < abs(difY))
					m_currentY += delta;
				else
					m_currentY += difY;
			}
			else
			{
				if(delta < abs(difY))
					m_currentY -= delta;
				else
					m_currentY += difY;			
			}
		}
	}
}

void Map::SetCameraLocation(int32 x, int32 y)
{
	m_currentX = x;
	m_currentY = y;
}

void Map::SetCameraTarget(int32 x, int32 y)
{
	m_targetX = x;
	m_targetY = y;
}

bool Map::CheckInView(int32 x, int32 y, int32 *xO, int32 *yO)
{
    int32 minX = m_currentX - m_sizeX;
    int32 maxX = m_currentX + m_sizeX;
    int32 minY = m_currentY - m_sizeY;
    int32 maxY = m_currentY + m_sizeY;
    if ((x > minX || x < maxX) && (y > minY || y < maxY))
    {
        *xO = x - minX;
        *yO = y - minY;
        return true;
    }
    *xO = 0;
    *yO = 0;
    return false;
}

void Map::AddTimedObject(TimedObject *obj)
{
	uint32 lowGuid;
	if(_reusable_guids_timedobject.size())
	{
		lowGuid = _reusable_guids_timedobject.front();
		_reusable_guids_timedobject.pop_front();
	}
	else
	{
		m_highTimedGuid++;
		lowGuid = m_highTimedGuid;
	}
	m_tempMap.insert(std::make_pair(lowGuid,obj));
}

Vector3* Map::ConvertToVirtualCoordinates(int32 x, int32 y)
{
    int32 minX = m_currentX - m_sizeX;
    int32 minY = m_currentY - m_sizeY;

    return new Vector3(x + minX, y + minY, 0);
}

Player* Map::GetPlayer(uint32 guid)
{
	std::map<uint32, Player*>::iterator itr = m_plrMap.begin();
	for(; itr != m_plrMap.end(); ++itr)
	{
		if(itr->first == guid)
			return static_cast<Player*>(itr->second);
	}
	return NULL;
}

Creature* Map::GetCreature(uint32 guid)
{
	std::map<uint32, Object*>::iterator itr = m_unitMap.begin();
	for(; itr != m_unitMap.end(); ++itr)
	{
		if(itr->first == guid)
			return static_cast<Creature*>(itr->second);
	}
	return NULL;
}

Pet* Map::GetPet(uint32 guid)
{
	std::map<uint32, Pet*>::iterator itr = m_petMap.begin();
	for(; itr != m_petMap.end(); ++itr)
	{
		if(itr->first == guid)
			return static_cast<Pet*>(itr->second);
	}
	return NULL;
}

Gameobject *Map::GetGameobject(uint32 guid)
{
	std::map<uint32, Object*>::iterator itr = m_goMap.begin();
	for(; itr != m_goMap.end(); ++itr)
	{
		if(itr->first == guid)
			return static_cast<Gameobject*>(itr->second);
	}
	return NULL;
}

Unit* Map::GetUnit(uint64 guid)
{
    if ( guid == 0 )
            return NULL;

    switch(GET_TYPE_FROM_GUID(guid))
    {
    case HIGHGUID_TYPE_UNIT:
        return GetCreature( GET_LOWGUID_PART(guid) );
        break;
    case HIGHGUID_TYPE_PLAYER:
        return GetPlayer( (uint32)guid );
        break;
    case HIGHGUID_TYPE_PET:
        return GetPet( GET_LOWGUID_PART( guid ) );
        break;
    }
    return NULL;
}

Object* Map::GetGenericObject(uint32 guid)
{
	std::map<uint32, Object*>::iterator itr = m_genericMap.begin();
	for(; itr != m_genericMap.end(); ++itr)
	{
		if(itr->first == guid)
			return itr->second;
	}
	return NULL;
}

Object* Map::GetObject(uint64 guid)
{
    switch(GET_TYPE_FROM_GUID(guid))
    {
	case HIGHGUID_TYPE_GAMEOBJECT:
		return GetGameobject( GET_LOWGUID_PART(guid) );
		break;
	case HIGHGUID_TYPE_MAP:
	case HIGHGUID_TYPE_SCRIPT:
	case HIGHGUID_TYPE_SOUND:
		return GetGenericObject( GET_LOWGUID_PART(guid) );
		break;
	default:
		return GetUnit(guid);
		break;
    }
    return NULL;
}

Player *Map::CreatePlayer()
{
    uint64 newguid = (uint64)HIGHGUID_TYPE_PLAYER << 32;

    newguid |= GetGuidPlayer();
    return new Player(newguid);
}

Creature *Map::CreateCreature(uint32 entry)
{
    uint64 newguid = (uint64)HIGHGUID_TYPE_UNIT << 32;

    newguid |= GetGuidUnit();
	Creature *cre = new Creature(newguid);
	cre->SetEntry(entry);
    return cre;
}

Pet *Map::CreatePet(uint32 entry)
{
    uint64 newguid = (uint64)HIGHGUID_TYPE_PET << 32;

    newguid |= GetGuidPet();
	Pet *pet = new Pet(newguid);
	pet->SetEntry(entry);
    return pet;
}

Gameobject *Map::CreateGameobject(uint32 entry)
{
    uint64 newguid = (uint64)HIGHGUID_TYPE_GAMEOBJECT << 32;

    newguid |= GetGuidGo();
	Gameobject *go = new Gameobject(newguid);
	go->SetEntry(entry);
    return go;
}

Object *Map::CreateGenericObject(uint32 entry, uint8 type)
{
	uint64 newguid = 0;
	switch(type)
	{
	case TYPE_EVENT:
		{
		}break;
	case TYPE_SCRIPT:
		{
			newguid = (uint64)HIGHGUID_TYPE_SCRIPT << 32;
			newguid |= GetGuidGeneric();
			ScriptObject *so = new ScriptObject(newguid);
			return so;
		}break;
	case TYPE_MAP:
		{
			newguid = (uint64)HIGHGUID_TYPE_MAP << 32;
			newguid |= GetGuidGeneric();
			MapObject *mo = new MapObject(newguid);
			return mo;
		}break;
	case TYPE_SOUND:
		{
			newguid = (uint64)HIGHGUID_TYPE_MAP << 32;
			newguid |= GetGuidGeneric();
			SoundObject *so = new SoundObject(newguid);
			return so;
		}break;
	}
	return NULL;
}

uint32 Map::GetGuidGo()
{
	int retVal = 0;
	m_goGuidLock.Acquire();
	m_highGoGuid++;
	retVal = m_highGoGuid;
	m_goGuidLock.Release();
	return retVal;
}

uint32 Map::GetGuidUnit()
{
	int retVal = 0;
	m_unitGuidLock.Acquire();
	m_highUnitGuid++;
	retVal = m_highUnitGuid;
	m_unitGuidLock.Release();
	return retVal;
}

uint32 Map::GetGuidPet()
{
	int retVal = 0;
	m_petGuidLock.Acquire();
	m_highPetGuid++;
	retVal = m_highPetGuid;
	m_petGuidLock.Release();
	return retVal;
}

uint32 Map::GetGuidPlayer()
{
	int retVal = 0;
	m_playerGuidLock.Acquire();
	m_highPlayerGuid++;
	retVal = m_highPlayerGuid;
	m_playerGuidLock.Release();
	return retVal;
}

uint32 Map::GetGuidGeneric()
{
	int retVal = 0;
	m_genericGuidLock.Acquire();
	m_highGenericGuid++;
	retVal = m_highGenericGuid;
	m_genericGuidLock.Release();
	return retVal;
}

void Map::Update(Real duration, bool onlyScreen)
{
	UpdateCamera(duration, false);
	int32 x = 0;
	int32 y = 0;
	std::map<uint32, Player*>::iterator itrPlr = m_plrMap.begin();
	for(; itrPlr != m_plrMap.end(); ++itrPlr)
	{
		if(onlyScreen)
		{
			Vector3 pos = itrPlr->second->GetPosition();
			if(CheckInView(pos.x, pos.y, &x, &y))
				itrPlr->second->Update(duration);
		}
		else
			itrPlr->second->Update(duration);
	}

	std::map<uint32, Object*>::iterator itrUnit = m_unitMap.begin();
	for(; itrUnit != m_unitMap.end(); ++itrUnit)
	{
		if(onlyScreen)
		{
			Vector3 pos = itrUnit->second->GetPosition();
			if(CheckInView(pos.x, pos.y, &x, &y))
				itrUnit->second->Update(duration);
		}
		else
			itrUnit->second->Update(duration);
	}

	std::map<uint32, Pet*>::iterator itrPet = m_petMap.begin();
	for(; itrPet != m_petMap.end(); ++itrPet)
	{
		if(onlyScreen)
		{
			Vector3 pos = itrPet->second->GetPosition();
			if(CheckInView(pos.x, pos.y, &x, &y))
				itrPet->second->Update(duration);
		}
		else
			itrPet->second->Update(duration);
	}

	std::map<uint32, Object*>::iterator itrGo = m_goMap.begin();
	for(; itrGo != m_goMap.end(); ++itrGo)
	{
		if(onlyScreen)
		{
			Vector3 pos = itrGo->second->GetPosition();
			if(CheckInView(pos.x, pos.y, &x, &y))
				itrGo->second->Update(duration);
		}
		else
			itrGo->second->Update(duration);
	}

	std::map<uint32, Object*>::iterator itrO = m_genericMap.begin();
	for(; itrO != m_genericMap.end(); ++itrO)
	{
		if(onlyScreen)
		{
			Vector3 pos = itrO->second->GetPosition();
			if(CheckInView(pos.x, pos.y, &x, &y))
				itrO->second->Update(duration);
		}
		else
			itrO->second->Update(duration);
	}

	std::set<uint32> eraseSet;
	std::map<uint32, TimedObject*>::iterator itrTemp = m_tempMap.begin();
	for(; itrTemp != m_tempMap.end(); ++itrTemp)
	{
		if(itrTemp->second->GetLifeTime() <= 0)
		{
			eraseSet.insert(itrTemp->first);
		}
		else
		{
			if(onlyScreen)
			{
				Vector3 pos = itrTemp->second->GetPosition();
				if(CheckInView(pos.x, pos.y, &x, &y))
					itrTemp->second->Update(duration);
			}
			else
				itrTemp->second->Update(duration);
		}
	}

	std::set<uint32>::iterator itrErase = eraseSet.begin();
	for(; itrErase != eraseSet.end(); ++itrErase)
	{
		std::map<uint32, TimedObject*>::iterator itrDel = m_tempMap.find((*itrErase));
		if(itrDel != m_tempMap.end())
		{
			TimedObject *to = itrDel->second;
			m_tempMap.erase((*itrErase));
			_reusable_guids_timedobject.push_back((*itrErase));
			delete to;
		}
		else
			sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Cannot delete %d\r\n", (*itrErase));		
	}
	eraseSet.clear();
}

void Map::Render(Real duration)
{
	int32 x = 0;
	int32 y = 0;

	std::set<Background*>::iterator itrBack = m_backgroundSet.begin();
	for(; itrBack != m_backgroundSet.end(); ++itrBack)
	{
		Background* bck = (*itrBack);
		if(CheckInView(bck->x, bck->y, &x, &y))
		{
			ML_DrawSpriteXY(bck->back, x, y);
		}
	}

	std::map<uint32, Object*>::iterator itrO = m_genericMap.begin();
	for(; itrO != m_genericMap.end(); ++itrO)
	{
		Vector3 pos = itrO->second->GetPosition();
		if(CheckInView(pos.x, pos.y, &x, &y))
			itrO->second->Draw(x, y);
	}

	std::map<uint32, Object*>::iterator itrGo = m_goMap.begin();
	for(; itrGo != m_goMap.end(); ++itrGo)
	{
		Vector3 pos = itrGo->second->GetPosition();
		if(CheckInView(pos.x, pos.y, &x, &y))
			itrGo->second->Draw(x, y);
	}
	
	std::map<uint32, Object*>::iterator itrUnit = m_unitMap.begin();
	for(; itrUnit != m_unitMap.end(); ++itrUnit)
	{
		Vector3 pos = itrUnit->second->GetPosition();
		if(CheckInView(pos.x, pos.y, &x, &y))
			itrUnit->second->Draw(x, y);
	}	
	
	std::map<uint32, Pet*>::iterator itrPet = m_petMap.begin();
	for(; itrPet != m_petMap.end(); ++itrPet)
	{
		Vector3 pos = itrPet->second->GetPosition();
		if(CheckInView(pos.x, pos.y, &x, &y))
			itrPet->second->Draw(x, y);
	}	
	
	std::map<uint32, Player*>::iterator itrPlr = m_plrMap.begin();
	for(; itrPlr != m_plrMap.end(); ++itrPlr)
	{	
		Vector3 pos = itrPlr->second->GetPosition();
		if(CheckInView(pos.x, pos.y, &x, &y))
			itrPlr->second->Draw(x, y);
	}

	std::map<uint32, TimedObject*>::iterator itrTemp = m_tempMap.begin();
	for(; itrTemp != m_tempMap.end(); ++itrTemp)
	{
		Vector3 pos = itrTemp->second->GetPosition();
		if(CheckInView(pos.x, pos.y, &x, &y))
		{
			itrTemp->second->Draw(x, y);
		}
	}

	sPhysicsMgr.Render();
}
