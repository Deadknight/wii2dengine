#include "Stdafx.h"

initialiseSingleton( PhysicsMgr );

PhysicsMgr::PhysicsMgr()
{
	fr = NULL;
	colData = NULL;
	cr = NULL;

	m_debugRender = false;
}

PhysicsMgr::~PhysicsMgr()
{
	std::set<CollisionPrimitive*>::iterator itr = m_objectSet.begin();
	for(; itr != m_objectSet.end(); )
	{
		CollisionPrimitive *cp = (*itr);
		itr++;
		delete cp;
	}

	if(fr != NULL)
		delete fr;
	if(colData)
	{
		if(colData->contacts)
			delete colData->contacts;
		delete colData;
	}
	if(cr)
		delete cr;
}

void PhysicsMgr::AddPhysicsObject(CollisionPrimitive *cp)
{
	m_objectSet.insert(cp);
}

void PhysicsMgr::RemovePhysicsObject(CollisionPrimitive *cp)
{
	std::set<CollisionPrimitive*>::iterator itr = m_objectSet.find(cp);
	if(itr != m_objectSet.end())
	{
		m_objectSet.erase(itr);
	}
}

void PhysicsMgr::Clear()
{
	m_objectSet.clear();
}

void PhysicsMgr::Simulate(Real time)
{
	std::set<CollisionPrimitive*>::iterator itr = m_objectSet.begin();
	
	for(; itr != m_objectSet.end(); ++itr)
	{
		//(*itr)->GetPhysicObject()->ClearAccumulator();
		//(*itr)->GetPhysicObject()->CalculateDerivedData();
	}
	
	itr = m_objectSet.begin();
	for(; itr != m_objectSet.end(); ++itr)
	{
		if((*itr)->GetPhysicObject()->Simulate(time))
		{
		}
	}

	//Generate possible contacts (increase the speed of this algorithm) (Quadtree?)
	/*itr = m_objectList.begin();
	std::vector<Contact*> m_tempList;
	for(; itr != m_objectList.end(); ++itr)
	{
		std::vector<PhysicObject*>::iterator itrTarget = itr + 1;
		for(; itrTarget != m_objectList.end(); ++itrTarget)
		{
			Contact *c = new Contact();
			c->SetBodyData(static_cast<RigidBody*>((*itr)), static_cast<RigidBody*>((*itrTarget)), 0.0001f, 0.0001f);
			m_tempList.push_back(c);
		}
	}
	
	ContactResolver *cr new ContactResolver(data.contactCount);
	Contact *contacts = &m_tempList[0];
	cr->SetIterations(m_tempList.size());
	cr->ResolveContacts(contacts, m_tempList.size(), time);
	delete cr;
	std::vector<Contact*>::iterator itrContact = m_tempList.begin();
	for(; itrContact != m_tempList.end();)
	{
		Contact *c = (*itr);
		itr++;
		delete c;
	}
	m_tempList.clear();
	*/
	
	if(m_objectSet.size() > 1)
	{
		itr = m_objectSet.begin();
		for(; itr != m_objectSet.end(); ++itr)
		{
			(*itr)->CalculateInternals();
			itr++;
			std::set<CollisionPrimitive*>::iterator itrTarget = itr;
			itr--;
			for(; itrTarget != m_objectSet.end(); ++itrTarget)
			{
				if((*itr)->HasCollisionFlag((*itrTarget)->GetCollisionFlag()))
				{
					(*itrTarget)->CalculateInternals();
					CollisionDetector::Collide((*itr), (*itrTarget), colData);
				}
			}
		}
		
		if(colData->contactCount > 0)
		{
			cr->SetIterations(colData->contactCount * 4);
			cr->ResolveContacts(colData->GetContactArray(), colData->contactCount, time);
			colData->Reset(0);
		}
	}

	CleanUp();
}

void PhysicsMgr::CleanUp()
{
	/*int size = m_eraseQueue.size();
	for(int i = 0; i < size; i++)
	{
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Delete Loop\r\n");
		CollisionPrimitive *cp = m_eraseQueue[i];
		//delete cp;
		//m_eraseQueue[i] = NULL;
	}
	m_eraseQueue.clear();*/
	
	/*for (std::vector<CollisionPrimitive*>::iterator i = m_eraseQueue.begin(), e = m_eraseQueue.end(); i != e; )
	{
		std::vector<CollisionPrimitive*>::iterator tmp(i++);
		delete *tmp;
		m_eraseQueue.erase(tmp);
	}*/
	
	/*for(std::vector<CollisionPrimitive*>::iterator itr = m_eraseQueue.begin(); itr != m_eraseQueue.end();)
	{
		CollisionPrimitive *cp = (*itr);
		itr++;
		delete cp;
	}
	m_eraseQueue.clear();*/
	
	/*CollisionPrimitive ** arr = &m_eraseQueue[0];
	for(int i = 0; i < m_eraseQueue.size(); i++)
	{
		delete arr[i];
	}
	m_eraseQueue.clear();
	delete arr;*/
	
}

void PhysicsMgr::Render()
{
	if(!m_debugRender)
		return;
	int32 x = 0;
	int32 y = 0;
	std::set<CollisionPrimitive*>::iterator itr = m_objectSet.begin();
	int32 id = 0;
	for(; itr != m_objectSet.end(); ++itr)
	{
		id++;
		CollisionPrimitive *cp = (*itr);
		Vector3 pos = cp->GetPhysicObject()->GetPosition();
		if(sMap.CheckInView(pos.x, pos.y, &x, &y))
		{
			switch(cp->GetType())
			{
			case PPT_POINT:
				{
					ML_DrawRect(x, y, 1, 1, 0xFFFF0000);
				}break;
			case PPT_BOX:
				{
					CollisionBox *cb = static_cast<CollisionBox*>(cp);
					ML_DrawRect(x, y, (cb->halfSize.x*2.0f), (cb->halfSize.y*2.0f), 0xFFFF0000);
				}break;
			case PPT_SPHERE:
				{
					/*CollisionSphere *cs = static_cast<CollisionSphere*>(cp);
					ML_DrawCircle(x, y, cs->radius, 0xFFFF0000);*/
				}break;
			case PPT_PLANE:
				{
					//No plane support for now
				}break;
			};
		}
		x = 0;
		y = 0;
	}
}

void PhysicsMgr::CreateCollisionData()
{
	colData = new CollisionData();
}

void PhysicsMgr::SetCollisionData(Real friction, Real restitution)
{
	colData->friction = friction;
	colData->restitution = restitution;
}

void PhysicsMgr::SetMaxCollisionCount(int val)
{
	colData->Reset(val);
}

void PhysicsMgr::CreateContactResolver()
{
	cr = new ContactResolver(0);
}

void PhysicsMgr::SetContactResolverData(int iterations)
{
	cr->SetIterations(iterations);
}

void PhysicsMgr::SetContactResolverEpsilon(Real velocity, Real position)
{
	cr->SetEpsilon(velocity, position);
}

void PhysicsMgr::CreateFireworkRule(Real minAge, Real maxAge, Vector3 minVelocity, Vector3 maxVelocity, Real damping)
{
	if(fr == NULL)
	{
		fr = new FireworkRule();
		fr->minAge = minAge;
		fr->maxAge = maxAge;
		fr->minVelocity = minVelocity;
		fr->maxVelocity = maxVelocity;
		fr->damping = damping;
	}
}
