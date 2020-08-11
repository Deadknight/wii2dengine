#ifndef MAP_H
#define MAP_H

class Object;
class TimedObject;
class Gameobject;
class Unit;
class Creature;
class Pet;
class Player;

struct Background
{
	int32 x;
	int32 y;
	int32 rot;
	ML_Sprite *back;
};

class Map : public Singleton < Map >
{
public:
	Map();
	~Map();

	void Load(const char* mapName);

	void UpdateCamera(Real duration, bool spring = false);
	void SetCameraLocation(int32 x, int32 y);
	void SetCameraTarget(int32 x, int32 y);
	void SetCameraSpeed(int32 val) { m_cameraSpeed = val; }
	void LockCamera() { m_lockCamera = true; }
	void UnlockCamera() { m_lockCamera = false; }
	bool CheckInView(int32 x, int32 y, int32 *xO, int32 *yO);
	Vector3* ConvertToVirtualCoordinates(int32 x, int32 y);

	void AddTimedObject(TimedObject *obj);

	Player *GetPlayer(uint32 guid);
	Pet *GetPet(uint32 guid);
	Creature *GetCreature(uint32 guid);
	Gameobject *GetGameobject(uint32 guid);
	Unit *GetUnit(uint64 guid);
	Object *GetGenericObject(uint32 guid);
	Object *GetObject(uint64 guid);

	//Map
	std::map<uint32, Player*>::iterator GetPlayerMapBegin() { return m_plrMap.begin(); }
	std::map<uint32, Player*>::iterator GetPlayerMapEnd() { return m_plrMap.end(); }
	std::map<uint32, Object*>::iterator GetUnitMapBegin() { return m_unitMap.begin(); }
	std::map<uint32, Object*>::iterator GetUnitMapEnd() { return m_unitMap.end(); }
	std::map<uint32, Object*>::iterator GetGameobjectMapBegin() { return m_goMap.begin(); }
	std::map<uint32, Object*>::iterator GetGameobjectMapEnd() { return m_goMap.end(); }

	Player *CreatePlayer();
	Creature *CreateCreature(uint32 entry);
	Pet *CreatePet(uint32 entry);
	Gameobject *CreateGameobject(uint32 entry);
	Object *CreateGenericObject(uint32 entry, uint8 type);

	uint32 GetGuidGo();
	uint32 GetGuidUnit();
	uint32 GetGuidPet();
	uint32 GetGuidPlayer();
	uint32 GetGuidGeneric();

	void Update(Real duration, bool onlyScreen = false);
	void Render(Real duration);
private:
	std::set<Background*> m_backgroundSet;
	std::map<uint32, Object*> m_goMap;
	std::map<uint32, Object*> m_unitMap;	
	std::map<uint32, Pet*> m_petMap;
	std::map<uint32, Player*> m_plrMap;
	std::map<uint32, Object*> m_genericMap;
	std::map<uint32, TimedObject*> m_tempMap;

	//Current camera position
	bool m_lockCamera;
	int32 m_currentX;
	int32 m_currentY;
	int32 m_sizeX;
	int32 m_sizeY;
	int32 m_targetX;
	int32 m_targetY;
	int32 m_cameraSpeed;

	//Guid storage
	uint32 m_highGoGuid;
	uint32 m_highUnitGuid;
	uint32 m_highPetGuid;
	uint32 m_highPlayerGuid;
	uint32 m_highGenericGuid;
	uint32 m_highTimedGuid;

	Mutex m_goGuidLock;
	Mutex m_unitGuidLock;
	Mutex m_petGuidLock;
	Mutex m_playerGuidLock;
	Mutex m_genericGuidLock;

	std::deque<uint32> _reusable_guids_timedobject;
};

#define sMap Map::getSingleton()

#endif
