#ifndef AIINTERFACE_H
#define AIINTERFACE_H

class Unit;
class ScriptEngine;

#ifdef M_PI
#undef M_PI
#endif
#define M_PI       3.14159265358979323846
#define UNIT_MOVEMENT_INTERPOLATE_INTERVAL 400/*750*/ // ms smoother server/client side moving vs less cpu/ less b/w
#define TARGET_UPDATE_INTERVAL_ON_PLAYER 1000 // we most likely will have to kill players and only then check mobs
#define TARGET_UPDATE_INTERVAL 5000 // this is a multiple of PLAYER_TARGET_UPDATE_INTERVAL
#define USE_REAL_TIMERS

#define DISTANCE_TO_SMALL_TO_WALK 2.0f //this is required so creature will not try to reposition itself to obtain perfect combat range. Not using this might lead to exploits

enum AI_Type
{
    AITYPE_AGRO, //Classic attack target
    AITYPE_SOCIAL, //Npc
    AITYPE_PET, //Pet
    AITYPE_GUARDIAN, //we got a master but he cannot control us, we follow and battle opposite factions
    AITYPE_PASSIVE
};

enum AI_Agent
{
    AGENT_NULL,
    AGENT_MELEE,
    AGENT_RANGED,
    AGENT_FLEE,
    AGENT_SPELL,
    AGENT_CALLFORHELP
};

enum AI_State
{
    STATE_IDLE,
    STATE_ATTACKING,
    STATE_CASTING,
    STATE_FLEEING,
    STATE_FOLLOWING,
    STATE_EVADE,
    STATE_MOVEWP,
    STATE_FEAR,
    STATE_WANDER,
    STATE_STOPPED,
    STATE_SCRIPTMOVE,
    STATE_SCRIPTIDLE
};

enum CreatureState
{
    STOPPED,
    MOVING,
    ATTACKING
};

enum AiEvents
{
    EVENT_ENTERCOMBAT,
    EVENT_LEAVECOMBAT,
    EVENT_DAMAGETAKEN,
    EVENT_FEAR,
    EVENT_UNFEAR,
    EVENT_FOLLOWOWNER,
    EVENT_WANDER,
    EVENT_UNWANDER,
    EVENT_UNITDIED
};

enum MovementType
{
    MOVEMENTTYPE_NONE,
    MOVEMENTTYPE_RANDOMWP,
    MOVEMENTTYPE_CIRCLEWP,
    MOVEMENTTYPE_WANTEDWP,
    MOVEMENTTYPE_DONTMOVEWP,
    MOVEMENTTYPE_SPECIAL
};

enum MovementSpeed
{
	MOVEMENT_SPEED_NOT = 0x1,
	MOVEMENT_SPEED_WALK = 0x2,
	MOVEMENT_SPEED_RUN = 0x4,
	MOVEMENT_SPEED_SPRINT = 0x8,
	MOVEMENT_SPEED_FLY = 0x10,
	MOVEMENT_SPEED_CLEAR = 0xF0
};

enum CombatFlag
{
	CF_DISABLE_COMBAT = 0x1,
	CF_DISABLE_MELEE = 0x2,
	CF_DISABLE_RANGED = 0x4,
	CF_DISABLE_SPELL = 0x8,
	CF_DISABLE_TARGETING = 0x10
};

//typedef __gnu_cxx::hash_map<uint64, int32> TargetMap;
typedef std::map<uint64, int32> TargetMap;

class AIInterface
{
public:
	AIInterface();
	~AIInterface();
	
	//Init
	void Init(Unit *un, AI_Type at, MovementType mt);
	void Init(Unit *un, AI_Type at, MovementType mt, Unit *owner); // used for pets
	Unit *GetUnit() { return m_Unit; }
	Unit *GetPetOwner() { return m_PetOwner; }	

	//Event
	void HandleEvent(uint32 event, Unit *pUnit, uint32 misc);

	//Threat
	void AttackReaction(Unit *pUnit, uint32 damage_dealt);

	//Update
	void Update(Real time);
	virtual void _UpdateCombat(Real time);

	//Movement
	void MoveTo(float x, float y);
	void UpdateMove();
	bool StopMovement(uint32 time);
	uint32 GetMoveFlags();

	DEDOSAN_INLINE void AddStopTime(uint32 Time) { m_moveTimer += Time; }

	void _CalcDestinationAndMove(Unit *target, Real dist);
	float _CalcCombatRange(Unit* target, bool ranged);	
	
		//Movement Waypoint
	uint32 GetCurrentWaypoint() { return m_currentWaypoint; }
    void ChangeWayPointID(uint32 oldwpid, uint32 newwpid);
	void SetWaypointToMove(uint32 id) { m_currentWaypoint = id; }

    void SetAllowedToEnterCombat(bool val) { m_AllowedToEnterCombat = val; }
    DEDOSAN_INLINE bool GetAllowedToEnterCombat(void) { return m_AllowedToEnterCombat; }
	DEDOSAN_INLINE void SetAIState(AI_State newstate) { m_AIState = newstate; }
	DEDOSAN_INLINE uint8 getAIState() { return static_cast<uint8>( m_AIState ); }
	DEDOSAN_INLINE uint8 getAIType() { return static_cast<uint8>( m_AIType ); }
	void SetAIType( AI_Type at ){ m_AIType = at; }
    DEDOSAN_INLINE void LockAITargets(bool lock) 
    { 
        lock? m_aiTargetsLock.Acquire(): m_aiTargetsLock.Release(); 
    };

    Unit* GetNextTarget();
    void SetNextTarget(Unit *nextTarget);
    void SetNextTarget(uint64 nextTarget);
	void SetInFront(Unit *target) { return; }
	Unit* FindTarget();
	bool FindFriends(Real dist);
	float _CalcAggroRange(Unit* target);

	void OnDeath(Object *pKiller);
	bool UnsafeCanOwnerAttackUnit(Unit *pUnit);
	
	//Fear
	void SetUnitToFear(Unit *pUnit) { UnitToFear = pUnit; }

protected:
    void _UpdateTargets();
    void _UpdateMovement(Real time);
    void _UpdateTimer(Real time);

	//Timers
#ifdef USE_REAL_TIMERS
	Real m_updateTargetsTimer;
	Real m_updateTargetsTimer2;
#else
	uint32 m_updateTargetsTimer;
	uint32 m_updateTargetsTimer2;
#endif
	bool m_updateTargets;

	//Combat
	uint32 m_outOfCombatRange;
	uint32 m_combatFlag;
	bool m_canRangedAttack;
	bool m_AllowedToEnterCombat;

	//Flee
	bool m_canFlee;
	bool m_hasFleed;
	uint32 m_FleeHealth;
#ifdef USE_REAL_TIMERS
	Real m_FleeDuration;
	Real m_fleeTimer;
#else
	uint32 m_FleeDuration;
	uint32 m_fleeTimer;
#endif
	
	//Fear
#ifdef USE_REAL_TIMERS
	Real m_FearTimer;
#else
	uint32 m_FearTimer;
#endif
	Unit *UnitToFear;
	
	//Wander
#ifdef USE_REAL_TIMERS
	Real m_WanderTimer;
#else
	uint32 m_WanderTimer;
#endif

	//Call for help
	bool m_canCallForHelp;
	bool m_hasCalledForHelp;

    //Movement
	uint32 m_movementSpeedFlag;
	uint32 m_moveType;
    uint32 m_currentWaypoint;
    bool m_moveBackward;
#ifdef USE_REAL_TIMERS
    Real m_timeToMove;
    Real m_timeMoved;
    Real m_moveTimer;
	Real m_totalMoveTime;
#else
    uint32 m_timeToMove;
    uint32 m_timeMoved;
    uint32 m_moveTimer;
	uint32 m_totalMoveTime;
#endif
	Unit *UnitToFollow;
	Unit *UnitToFollow_backup;
	Real FollowDistance;
	Real FollowDistance_backup;
	Unit *m_PetOwner;

	//Movement Extra
	Real m_lastTargetX;
	Real m_nextPosX;
	Real m_nextPosY;
	Real m_destinationX;
	Real m_destinationY;
    Real m_lastFollowX;
    Real m_lastFollowY;
    Real m_sourceX, m_sourceY;
	Real m_flySpeed;
	Real m_walkSpeed;
	Real m_runSpeed;

	//Threat
	uint32 GetThreatByGUID(uint64 guid);
	uint32 GetThreatByPtr(Unit* obj);
	Unit *GetMostHated();
	bool ModThreatByGUID(uint64 guid, int32 mod);
	bool ModThreatByPtr(Unit* obj, int32 mod);
	void RemoveThreatByGUID(uint64 guid);
	void RemoveThreatByPtr(Unit* obj);
	void WipeHateList();
	void ClearHateList();
	void WipeTargetList();
	uint32 _CalcThreat(uint32 damage, Unit* Attacker);
	void WipeReferences();
	int32 m_currentHighestThreat;

private:
	Unit *m_Unit;
	uint64 m_nextTarget;

    Mutex m_aiTargetsLock;
    TargetMap m_aiTargets;
    AI_Type m_AIType;
    AI_State m_AIState;
    AI_Agent m_aiCurrentAgent;
	uint32 m_creatureState;
};

#endif
