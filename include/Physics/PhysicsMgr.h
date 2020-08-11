#ifndef _PHYSICS_MGR_H
#define _PHYSICS_MGR_H

class PhysicsMgr : public Singleton< PhysicsMgr >
{
public:
	PhysicsMgr();
	~PhysicsMgr();

	void AddPhysicsObject(CollisionPrimitive *cp);
	void RemovePhysicsObject(CollisionPrimitive *cp);
	void Clear();
	void Simulate(Real time);
	void CleanUp();
	void Render();

	//Collision
	void CreateCollisionData();
	void SetCollisionData(Real friction, Real restitution);
	void SetMaxCollisionCount(int val);
	CollisionData *GetCollisionData() { return colData; }
	void CreateContactResolver();
	void SetContactResolverData(int iterations);
	void SetContactResolverEpsilon(Real velocity, Real position);
	ContactResolver* GetContactResolver() { return cr; }

	//Firework
	void CreateFireworkRule(Real minAge, Real maxAge, Vector3 minVelocity, Vector3 maxVelocity, Real damping);
	FireworkRule *GetFireworkRule() { return fr; }

	//Render
	void SetDebugRender(bool val) { m_debugRender = val; }

private:
	std::set<CollisionPrimitive*> m_objectSet;
	//std::deque<CollisionPrimitive*> m_eraseQueue;
	//std::queue<CollisionPrimitive*> m_eraseQueue;
	std::vector<CollisionPrimitive*> m_eraseQueue;

	CollisionData *colData;
	ContactResolver *cr;

	FireworkRule *fr;
	Vector3 m_gravity;

	bool m_debugRender;
};

#define sPhysicsMgr PhysicsMgr::getSingleton()

#endif
