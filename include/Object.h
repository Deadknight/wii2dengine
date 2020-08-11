#ifndef _OBJECT_H
#define _OBJECT_H

enum HIGHGUID_TYPE
{
	HIGHGUID_TYPE_PLAYER                    = 0x00000000,
	HIGHGUID_TYPE_GAMEOBJECT                = 0xF1100000,
	HIGHGUID_TYPE_UNIT                      = 0xF1300000,
	HIGHGUID_TYPE_PET                       = 0xF1400000,
	HIGHGUID_TYPE_VEHICLE                   = 0xF1500000,
	HIGHGUID_TYPE_MAP						= 0xF1600000,
	HIGHGUID_TYPE_SCRIPT					= 0xF1700000,
	HIGHGUID_TYPE_SOUND						= 0xF1800000,
	//===============================================
	HIGHGUID_TYPE_MASK                      = 0xFFF00000,
	LOWGUID_ENTRY_MASK                      = 0x00FFFFFF,
};

#define GET_TYPE_FROM_GUID(x) (GUID_HIPART((x)) & HIGHGUID_TYPE_MASK)
#define GET_LOWGUID_PART(x) (GUID_LOPART((x)) & LOWGUID_ENTRY_MASK)

enum OBJECT_TYPE
{
    TYPE_PLAYER,
    TYPE_UNIT,
    TYPE_GAMEOBJECT,
    TYPE_EVENT,
    TYPE_SCRIPT,
    TYPE_MAP,
    TYPE_SOUND,
	TYPE_TIMEDOBJECT
};

enum UPDATE_FIELDS
{
	OBJECT_FIELD_GUID,
	OBJECT_FIELD_GUID_1,
	OBJECT_FIELD_ENTRY,
	BASIC_END,
	OBJECT_FIELD_SCALE = BASIC_END,
	OBJECT_FIELD_FLAG,
	OBJECT_END,
	UNIT_FIELD_HEALTH = OBJECT_END,
	UNIT_FIELD_BASE_HEALTH,
	UNIT_FIELD_MAXHEALTH,
	UNIT_FIELD_MANA,
	UNIT_FIELD_BASE_MANA,
	UNIT_FIELD_MAXMANA,
	UNIT_FIELD_LEVEL,
	UNIT_FIELD_FACTION,
	UNIT_FIELD_FACTION_HOSTILE_MASK,
	UNIT_END,
	PLAYER_CURRENT_WEAPON = UNIT_END,
	PLAYER_END,
	GAMEOBJECT_FIELD_HEALTH	= OBJECT_END,
	GAMEOBJECT_FIELD_BASE_HEALTH,
	GAMEOBJECT_FIELD_MAXHEALTH,
	GAMEOBJECT_FIELD_FLAGS,
	GAMEOBJECT_END
};

enum OBJECT_FLAGS
{
	OBJECT_FLAG_NOT_ATTACKABLE,
	OBJECT_FLAG_NOT_SELECTABLE
};

enum COLLISION_FLAG
{
	COLLISION_FLAG_PLAYER		= 0x1,
	COLLISION_FLAG_CREATURE		= 0x2,
	COLLISION_FLAG_GAMEOBJECT	= 0x4,
	COLLISION_FLAG_WORLD		= 0x8,
	COLLISION_FLAG_ALL			= 0x0FFFFFFF
};

#define LOWGUID                                   OBJECT_FIELD_GUID
#define HIGHGUID                                  ( OBJECT_FIELD_GUID + 1 )

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Init(const char* name, uint32 entry);
	virtual void InitPhysics(SpriteProp *prop);
	//Draw uses screen coordinates, not world coordinates
	virtual void Draw(int32 x, int32 y);
	virtual void Update(Real duration) { }
	virtual void OnCollide(CollisionPrimitive *cpTarget) { }

	//Getter/Setters
#ifndef USING_BIG_ENDIAN
	const uint64& GetGUID() const { return *((uint64*)m_uint32Values); }
#else
	const uint64 GetGUID() const { return GetUInt64Value(0); }
#endif
    void SetGUID( uint64 GUID ){ SetUInt64Value( OBJECT_FIELD_GUID, GUID );  }
    const uint32 GetLowGUID() const { return m_uint32Values[ LOWGUID ]; }
    uint32 GetHighGUID(){ return m_uint32Values[ HIGHGUID ]; }
    void SetLowGUID( uint32 val ){ m_uint32Values[ LOWGUID ] = val; }
    void SetHighGUID( uint32 val ){ m_uint32Values[ HIGHGUID ] = val; }
	uint8 GetType() { return m_objectType; }
	CollisionPrimitive* GetCollisionPrimitive() { return cp; }
	void SetCollisionPrimitive(CollisionPrimitive *cpP) { cp = cpP; }
	uint8 GetObjectType() { return m_objectType; }
	Vector3 GetPosition();
	void SetPosition(Vector3 pos);
	void SetPosition(int32 x, int32 y, int32 z);
	Real GetRotation();
	void SetRotation(Real rot);
	
	uint32 GetEntry() { return m_uint32Values[OBJECT_FIELD_ENTRY]; }
	void SetEntry(uint32 entry) { m_uint32Values[OBJECT_FIELD_ENTRY] = entry; }
	Real GetScale() { return m_realValues[OBJECT_FIELD_SCALE]; }
	void SetScale(Real value) { m_realValues[OBJECT_FIELD_SCALE] = value; }

#ifdef USING_BIG_ENDIAN
    __inline const uint64 GetUInt64Value( uint32 index ) const
#else
	DEDOSAN_INLINE const uint64& GetUInt64Value( uint32 index ) const
#endif
	{
#ifdef USING_BIG_ENDIAN
		/* these have to be swapped here :< */
		return uint64((uint64(m_uint32Values[index+1]) << 32) | m_uint32Values[index]);
#else
		return *((uint64*)&(m_uint32Values[ index ]));
#endif
	}

	void SetUInt64Value(const uint32 index, const uint64 value)
	{
		#ifndef USING_BIG_ENDIAN
			if(m_uint32Values[index] == GUID_LOPART(value) && m_uint32Values[index+1] == GUID_HIPART(value))
				return;

			m_uint32Values[ index ] = *((uint32*)&value);
			m_uint32Values[ index + 1 ] = *(((uint32*)&value) + 1);
		#else
			m_uint32Values[index] = value & 0xffffffff;
			m_uint32Values[index+1] = (value >> 32) & 0xffffffff;
		#endif
	}

	uint32 GetUInt32Value(const uint32 index) { return m_uint32Values[index]; }
	void SetUInt32Value(const uint32 index, const uint32 value) { m_uint32Values[index] = value; }
	Real GetRealValue(const uint32 index) { return m_realValues[index]; }
	void SetRealValue(const uint32 index, const Real value) { m_realValues[index] = value; }
    bool HasFlag( const uint32 index, uint32 flag ) const { return (m_uint32Values[index] & flag) != 0; }
	void SetFlag(const uint32 index, const uint32 newFlag) { m_uint32Values[ index ] |= newFlag; }
	void RemoveFlag(const uint32 index, uint32 oldFlag) { m_uint32Values[ index ] &= ~oldFlag; }
	
	//Checks
	bool IsUnit() { return (m_objectType == TYPE_UNIT); }
	bool IsPlayer() { return (m_objectType == TYPE_PLAYER); }
	bool IsGameobject() { return (m_objectType == TYPE_GAMEOBJECT); }
	bool IsPet() { return (GET_TYPE_FROM_GUID(GetGUID()) == HIGHGUID_TYPE_PET); }

	//TODO
	Real GetModelHalfSize() { return 0.5f; }

	//Distance Calculations
	const Real GetDistanceSq(Object *obj)
	{
		Vector3 one = GetPosition();
		Vector3 two = obj->GetPosition();
		Real deltaX = one.x - two.x;
		Real deltaY = one.y - two.y;
		Real deltaZ = one.z - two.z;

		return (deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
	}

	const Real GetDistanceSq(Vector3 val)
	{
		Vector3 one = GetPosition();
		Real deltaX = one.x - val.x;
		Real deltaY = one.y - val.y;
		Real deltaZ = one.z - val.z;

		return (deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
	}

	const Real GetDistance2dSq(Object *obj)
	{
		Vector3 one = GetPosition();
		Vector3 two = obj->GetPosition();
		Real deltaX = one.x - two.x;
		Real deltaY = one.y - two.y;

		return (deltaX*deltaX + deltaY*deltaY);
	}

	const Real GetDistance2dSq(Vector3 val)
	{
		Vector3 one = GetPosition();
		Real deltaX = one.x - val.x;
		Real deltaY = one.y - val.y;

		return (deltaX*deltaX + deltaY*deltaY);
	}

	const Real GetDistance1dSq(Object *obj)
	{
		Vector3 one = GetPosition();
		Vector3 two = obj->GetPosition();
		Real deltaX = one.x - two.x;

		return (deltaX*deltaX);
	}

	const Real GetDistance1dSq(Vector3 val)
	{
		Vector3 one = GetPosition();
		Real deltaX = one.x - val.x;

		return (deltaX*deltaX);
	}

	const Real GetDistance(Object *obj)
	{
		Vector3 one = GetPosition();
		Vector3 two = obj->GetPosition();
		Real deltaX = one.x - two.x;
		Real deltaY = one.y - two.y;
		Real deltaZ = one.z - two.z;

		return sqrtf(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
	}

	const Real GetDistance(Vector3 val)
	{
		Vector3 one = GetPosition();
		Real deltaX = one.x - val.x;
		Real deltaY = one.y - val.y;
		Real deltaZ = one.z - val.z;

		return sqrtf(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
	}

	const Real GetDistance2d(Object *obj)
	{
		Vector3 one = GetPosition();
		Vector3 two = obj->GetPosition();
		Real deltaX = one.x - two.x;
		Real deltaY = one.y - two.y;

		return sqrtf(deltaX*deltaX + deltaY*deltaY);
	}

	const Real GetDistance2d(Vector3 val)
	{
		Vector3 one = GetPosition();
		Real deltaX = one.x - val.x;
		Real deltaY = one.y - val.y;

		return sqrtf(deltaX*deltaX + deltaY*deltaY);
	}
	
	const Real GetDistance2d(Real x, Real y)
	{
		Vector3 one = GetPosition();
		Real deltaX = one.x - x;
		Real deltaY = one.y - y;

		return sqrtf(deltaX*deltaX + deltaY*deltaY);
	}	

	const Real GetDistance1d(Object *obj)
	{
		Vector3 one = GetPosition();
		Vector3 two = obj->GetPosition();
		Real deltaX = one.x - two.x;

		return deltaX;
	}

	const Real GetDistance1d(Vector3 val)
	{
		Vector3 one = GetPosition();
		Real deltaX = one.x - val.x;

		return deltaX;
	}
	
	float CalcAngle( float Position1X, float Position1Y, float Position2X, float Position2Y );
	float CalcRadAngle( float Position1X, float Position1Y, float Position2X, float Position2Y );
	float GetEasyAngle( float angle );
	bool inArc(float Position1X, float Position1Y, float FOV, float Orientation, float Position2X, float Position2Y );
	bool IsInFront(Object* target);
	bool IsInBack(Object* target);
	bool isInArc(Object* target , float angle, float orientationAngle);
	bool HasInArc( float degrees, float orientationAngle, Object* target );
protected:
	uint8 m_objectType;
	uint32 m_valuesCount;
	union
	{
		uint32* m_uint32Values;
		Real* m_realValues;
    };
	CollisionPrimitive *cp;
	//This is only used to define a object without physics body
	Vector3 localPos;
};

#endif
