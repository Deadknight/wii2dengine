#include "Stdafx.h"

#define ANIMATION_FRAME 4

Unit::Unit()
{
	m_sprName = "";
	m_sprType = SPR_TYPE_MONO;
	m_upperSpr = NULL;
	m_spr = NULL;
	m_sprInfo = NULL;
	m_photo = NULL;
	m_flag = 0;
	m_lastFlag = 0;
	
	m_walkSpeed = 1;
	m_runSpeed = 300;
	m_sprintSpeed = 5;
	m_flySpeed = 6;	

	m_weaponSet.clear();
	m_selectedWeapon = NULL;

    m_aiInterface = new AIInterface();
    m_aiInterface->Init(this, AITYPE_AGRO, MOVEMENTTYPE_NONE);
}

Unit::~Unit()
{
	std::map<uint32, SpriteInfo*>::iterator itr = m_spriteMap.begin();
	for(; itr != m_spriteMap.end(); )
	{
		SpriteInfo *si = itr->second;
		++itr;
		delete si->spr;
		delete si;
	}
}

void Unit::Init(const char* name, uint32 entry)
{
	//Load object details here
	Object::Init(name, entry);

	std::string nameS = name;
	std::string file = sResourceMgr.GetReadFS() + nameS + ".unit";
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_DEBUG, "Loading unit file %s\r\n", file.c_str());
	std::fstream binary_file(file.c_str(), std::ios::binary | std::ios::in);
	if(!binary_file.is_open())
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Cannot open unit file %s\r\n", name);
	int32 length = 0;
	binary_file.read((char*)&length, sizeof(uint32));
	char nameU[255];
	binary_file.read(nameU, length);
	nameU[length] = 0;
	m_sprName = nameU;
	binary_file.read((char*)&length, sizeof(uint32));
	if(length > 0)
	{	
		char dir[255];
		binary_file.read(dir, length);
		dir[length] = 0;
		std::string dirS = dir;
		sResourceMgr.SetResourceDir(dirS);
		binary_file.read((char*)&length, sizeof(uint32));
	}
	
	SpriteProp prop;	
	
	binary_file.read((char*)&length, sizeof(uint32));
	if(length > 0)
	{	
		char photo[255];
		binary_file.read(photo, length);
		photo[length] = 0;
		std::string photoS = photo;
		m_photo = sResourceMgr.GetSpriteByName(photoS, &prop, MEMORY_MAP);
	}

	int32 dual = 0;
	binary_file.read((char*)&dual, sizeof(uint32));
	binary_file.read((char*)&length, sizeof(uint32));
	for(int32 i = 0; i < length; i++)
	{		
		int32 sprFlag = 0;
		binary_file.read((char*)&sprFlag, sizeof(uint32));

		uint8 flipX = 0;
		binary_file.read((char*)&flipX, sizeof(uint8));
		uint8 flipY = 0;
		binary_file.read((char*)&flipY, sizeof(uint8));
		
		int32 charLength = 0;
		binary_file.read((char*)&charLength, sizeof(uint32));

		char sprName[255];
		binary_file.read(sprName, charLength);
		sprName[charLength] = 0;
		std::string sprNameS = sprName;

		binary_file.read((char*)&charLength, sizeof(uint32));

		char sprFullPath[255];
		binary_file.read(sprFullPath, charLength);
		sprFullPath[charLength] = 0;

		m_spr = sResourceMgr.GetSpriteByName(sprNameS, &prop, MEMORY_MAP);
		if(prop.animated)
		{
			ML_InitTile(m_spr, prop.sizeX, prop.sizeY); // We init the tile system of the sprite : 48 is the width of a tile, 96 its height.
			ML_AnimateSprite(m_spr, 1, ANIMATION_FRAME); // The sprite will be animated infinitely and between each frames there will be 25 cycles.*/
			if(flipX > 0)
				ML_FlipSpriteX(m_spr, true);
			if(flipY > 0)
				ML_FlipSpriteY(m_spr, true);
		}
		SpriteInfo *si = new SpriteInfo();
		//si->body Generate this;
		si->spr = m_spr;
		si->centerX = prop.centerX;
		si->centerY = prop.centerY;
		m_spriteMap.insert(std::make_pair(sprFlag, si));

		if(!cp)
			InitPhysics(&prop);
	}

	sResourceMgr.SetResourceDir(sResourceMgr.GetResourceDefaultDir());

	binary_file.close();
}

void Unit::Update(Real duration)
{
	m_flag |= STATE_NONE;
	m_aiInterface->Update(static_cast<uint32>(duration));
	
	/*Write tile reporting to mllib
	 *It will be like this ML_AnimateSprite(Sprite pointer, count, cycle, return functionpointer);
	 *This function will be used to track movements like, turning, but it might not be needed.
	 */
	//If our state is changed update
	
	sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "Last Flag:%u,Flag:%u\r\n", m_lastFlag, m_flag);
	if(m_lastFlag != m_flag || m_spr == NULL)
	{
		m_lastFlag = m_flag;
		sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "State Change\r\n");
		if(m_sprType == SPR_TYPE_DUAL)
		{
			std::map<uint32, SpriteInfo*>::iterator itr = m_spriteMap.find((m_flag & LOOK_POSITION_MASK));
			if(itr != m_spriteMap.end())
				m_upperSpr = itr->second->spr;			
		}
		std::map<uint32, SpriteInfo*>::iterator itr = m_spriteMap.find(m_flag);
		if(itr != m_spriteMap.end())
		{
			m_spr = itr->second->spr;
			m_sprInfo = itr->second;
		}
		else
		{
			itr = m_spriteMap.begin();
			uint32 maxVal = 0;
			for(; itr != m_spriteMap.end(); ++itr)
			{
				if(itr->first != 0)
				{
					uint32 temp = itr->first & m_flag;
					if(temp && temp > maxVal)
					{
						maxVal = temp;
						m_spr = itr->second->spr;
						m_sprInfo = itr->second;
					}
				}
			}
		}
	}
	else
		sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "No State Change\r\n");

	//Update weapons
	/*std::set<Weapon*>::iterator itr = m_weaponSet.begin();
	for(; itr != m_weaponSet.end(); ++itr)
	{
		(*itr)->Update(duration);
	}*/
	if(m_selectedWeapon)
		m_selectedWeapon->Update(duration);

	UpdateState(duration);
}

void Unit::UpdateState(Real duration)
{
	//We are firing yehuu
	if(m_flag & STATE_FIREING)
	{
		if(m_selectedWeapon)
		{
			m_selectedWeapon->Fire();
		}
	}
	if(m_flag & STATE_RELOADING)
	{
		if(m_selectedWeapon)
		{
			m_selectedWeapon->Reload();
		}
	}
}

void Unit::Draw(int32 x, int32 y)
{
	if(m_spr)
	{
		if(m_sprType == SPR_TYPE_DUAL)
		{
			int32 upX = m_upperSprRelativePosition.x + x;
			int32 upY = m_upperSprRelativePosition.y + y;
			//Draw upper sprite if we have
			ML_DrawSpriteXY(m_upperSpr, upX, upY);
		}
		//Draw normal sprite
		/*Vector3 rot = cp->GetPhysicObject()->GetRotation();
		Real val = rot.z*180/R_PI;
		if(val > 360)
		{
			val = (Real) (((int)val) % 360);
			cp->GetPhysicObject()->SetRotation(0, 0, R_PI*val/180);
		}
		ML_RotateSprite(m_spr, rot.z*180/R_PI, 0);*/
		Quaternion ort = cp->GetPhysicObject()->GetOrientation();
		Vector3 rot;
		ort.toEuler(rot);
		ML_RotateSprite(m_spr, rot.z*180/R_PI, 0);
		ML_DrawSpriteXY(m_spr, x /*- m_sprInfo->centerX*/, y /*- m_sprInfo->centerY*/);
	}
	else
		sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "No Sprite \r\n");
}

void Unit::SetScale(Real scale)
{
	Object::SetScale(scale);
	if(m_spr)
	{
		if(m_sprType == SPR_TYPE_DUAL)
		{
			ML_SetSpriteScale(m_upperSpr, scale, scale);
		}
		//Draw normal sprite
		ML_DrawSpriteXY(m_spr, scale, scale);
	}
}

bool Unit::CanSee(Unit *target)
{
	return Faction::IsHostile(this, target);
	//return true;
}

bool Unit::IsAttackReady()
{
	return (getMSTime() >= m_attackTimer) ? true : false;
}

void Unit::AddWeapon(std::string name, uint32 id)
{
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Add weapon %s\r\n", name.c_str());
	Weapon *w = new Weapon(this, id, name);
	w->Init();
	/*w->SetMaxMagazine(50);
	w->SetCurrentMagazine(50);
	w->SetReloadCooldown(4);
	w->SetFireCooldown(0.4f);*/
	m_weaponSet.insert(w);
	m_selectedWeapon = w;
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Add weapon end %s\r\n", name.c_str());
}

void Unit::SetSelectedWeapon(uint32 id)
{
return;
sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Add weapon end a\r\n");
	std::set<Weapon*>::const_iterator itr = m_weaponSet.begin();
	for(; itr != m_weaponSet.end(); itr++)
	{
		Weapon *w = (*itr);
		if(w->GetId() == id)
		{
			sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "select weapon %d\r\n", id);
			m_selectedWeapon = w;
		}
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Add weapon end \r\n");
	}
	if(itr == m_weaponSet.end())
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Cannot select weapon %d\r\n", id);
}

void Unit::Strike(Unit *target, uint8 type)
{
}


