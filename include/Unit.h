#ifndef UNIT_H
#define UNIT_H

class AIInterface;

enum LOOK_POSITION
{
	LOOK_POSITION_N			= 0x1,
	LOOK_POSITION_NE		= 0x2,
	LOOK_POSITION_E			= 0x4,
	LOOK_POSITION_SE		= 0x8,
	LOOK_POSITION_S			= 0x10,
	LOOK_POSITION_SW		= 0x20,
	LOOK_POSITION_W			= 0x40,
	LOOK_POSITION_NW		= 0x80,
	LOOK_POSITION_MASK      = 0xFF
};

enum MOVEMENT_FLAG
{
	MOVEMENT_FLAG_IDLE		= 0x100,
	MOVEMENT_FLAG_RIGHT		= 0x200,
	MOVEMENT_FLAG_LEFT		= 0x400,
	MOVEMENT_FLAG_UP		= 0x800,
	MOVEMENT_FLAG_DOWN		= 0x800,
	MOVEMENT_FLAG_JUMP		= 0x1000,
	MOVEMENT_FLAG_CROUCH	= 0x2000,
	MOVEMENT_FLAG_WALK		= 0x4000,
	MOVEMENT_FLAG_RUN		= 0x8000,
	MOVEMENT_FLAG_SPECIAL	= 0x10000
};

enum STATE
{
	STATE_NONE				= 0x20000,
	STATE_JUMP_START		= 0x40000,
	STATE_FALLING			= 0x80000,
	STATE_FALL_LAND			= 0x100000,
	STATE_SWIMMING			= 0x200000,
	STATE_CLIMBING			= 0x400000,
	STATE_FIREING			= 0x800000,
	STATE_RELOADING			= 0x1000000,
	STATE_DIED				= 0x2000000
};

enum SPR_TYPE
{
	//Just static image
	SPR_TYPE_STATIC,
	//It can move but has one part on body
	SPR_TYPE_MONO,
	//It can move and has two part of body for 8 direction
	SPR_TYPE_DUAL
};

enum WeaponDamageType
{
    MELEE   = 0,
    RANGED  = 1
};

class Unit : public Object
{
public:
	Unit();
	virtual ~Unit();

	virtual void Init(const char* name, uint32 entry);
	virtual void Draw(int32 x, int32 y);
	virtual void Update(Real duration);
	virtual void UpdateState(Real duration);

	virtual void SetScale(Real scale);

	Vector3 GetDirection() { return m_direction; }
	uint32 GetSpriteFlag() { return m_flag; }

	//Variables that change
	bool IsAlive() { return (GetUInt32Value(UNIT_FIELD_HEALTH) > 0); }
	bool IsDead() { return !IsAlive(); }
	
	//Speed
	Real m_walkSpeed;
	Real m_runSpeed;
	Real m_sprintSpeed;
	Real m_flySpeed;

	//Combat Variables
	virtual bool CanSee(Unit *target);
	bool IsAttackReady();
	void SetAttackTimer(uint32 val) { m_attackTimer = val; }
	void AddWeapon(std::string name, uint32 id);
	void SetSelectedWeapon(uint32 id);

	void Strike(Unit *target, uint8 type);
	AIInterface* GetAIInterface() { return m_aiInterface; }

protected:
	AIInterface *m_aiInterface;

	std::set<Weapon*> m_weaponSet;
	Weapon *m_selectedWeapon;

	//Combat
	uint32 m_attackTimer;

	//Render
	Vector3 m_direction;
	std::string m_sprName;
	uint8 m_sprType;
	uint32 m_flag;
	ML_Sprite* m_upperSpr;
	Vector3 m_upperSprRelativePosition;
	ML_Sprite* m_spr;
	SpriteInfo* m_sprInfo;
	ML_Sprite* m_photo;
	uint32 m_lastFlag;
	std::map<uint32, SpriteInfo*> m_spriteMap;
};

#endif
