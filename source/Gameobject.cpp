#include "Stdafx.h"

Gameobject::Gameobject(uint64 guid)
{
	m_objectType = TYPE_PLAYER;
	m_flag = 0;
	m_lastFlag = 0;
	m_spr = NULL;
	
	m_uint32Values = _fields;
	memset(m_uint32Values, 0, (GAMEOBJECT_END) * sizeof(uint32));
}

Gameobject::~Gameobject()
{
}

void Gameobject::Init(const char* name, uint32 entry)
{
	//Load object details here
	Object::Init(name, entry);
	if(cp && cp->GetPhysicObject())
	{
		cp->SetCollisionFlag(COLLISION_FLAG_WORLD);
	}
	std::string nameS = name;
	std::string file = sResourceMgr.GetReadFS() + nameS + ".go";
	std::fstream binary_file(file.c_str(), std::ios::binary | std::ios::in);
	if(!binary_file.is_open())
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Cannot open go file %s\r\n", name);
	int32 length = 0;
	binary_file.read((char*)&length, sizeof(uint32));
	char nameU[255];
	binary_file.read(nameU, length);
	nameU[length] = 0;
	m_sprName = nameU;
	binary_file.read((char*)&length, sizeof(uint32));
	char dir[255];
	binary_file.read(dir, length);
	dir[length] = 0;
	std::string dirS = dir;
	sResourceMgr.SetResourceDir(dirS);

	SpriteProp prop;	
	
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
			ML_AnimateSprite(m_spr, 1, 25); // The sprite[1] will be animated infinitely and between each frames there will be 25 cycles.*/
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
	
	ScriptSystem->OnGameobjectEvent(this, GAMEOBJECT_EVENT_INIT, 0);
	sLuaMgr.OnGameObjectEvent(this, GAMEOBJECT_EVENT_INIT, 0);
}

void Gameobject::Update(Real duration)
{
	GType val(MYTYPE_FLOAT, &duration);
	ScriptSystem->OnGameobjectEvent(this, GAMEOBJECT_EVENT_UPDATE, 1, &val);
	sLuaMgr.OnGameObjectEvent(this, GAMEOBJECT_EVENT_UPDATE, 1, &val);

	//If our state is changed update
	if(m_lastFlag != m_flag || m_spr == NULL)
	{
		std::map<uint32, SpriteInfo*>::iterator itr = m_spriteMap.find(m_flag);
		if(itr != m_spriteMap.end())
			m_spr = itr->second->spr;
	}
}

void Gameobject::Draw(int32 x, int32 y)
{
	if(m_spr)
	{
		//Draw normal sprite
		Quaternion ort = cp->GetPhysicObject()->GetOrientation();
		Vector3 rot;
		ort.toEuler(rot);
		ML_RotateSprite(m_spr, rot.z*180/R_PI, 0);
		ML_DrawSpriteXY(m_spr, x, y);
	}
}

void Gameobject::OnCollide(CollisionPrimitive *cpTarget)
{
	GType val(MYTYPE_OBJECT, cpTarget->GetOwner());
	ScriptSystem->OnGameobjectEvent(this, GAMEOBJECT_EVENT_ON_COLLIDE, 1, &val);
	sLuaMgr.OnGameObjectEvent(this, GAMEOBJECT_EVENT_ON_COLLIDE, 1, &val);
}
