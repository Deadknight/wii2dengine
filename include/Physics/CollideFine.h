#ifndef COLLIDE_FINE_H
#define COLLIDE_FINE_H

// Forward declarations of primitive friends
class IntersectionTests;
class CollisionDetector;
class Object;

enum PHYSIC_PRIMITIVE_TYPE
{
	PPT_POINT,
	PPT_BOX,
	PPT_SPHERE,
	PPT_PLANE
};

/**
 * Represents a primitive to detect collisions against.
 */
class CollisionPrimitive
{
public:
	virtual ~CollisionPrimitive()
	{
		if(primitiveType == PPT_POINT)
		{
			delete p;
			p = NULL;
		}
		else
		{
			delete body;
			body = NULL;
		}
	}
    /**
     * This class exists to help the collision detector
     * and intersection routines, so they should have
     * access to its data.
     */
    friend class IntersectionTests;
    friend class CollisionDetector;

    /**
     * The rigid body that is represented by this primitive.
     */
	union
	{
		RigidBody * body;
		Particle * p;
	};

    /** 
     * The offset of this primitive from the given rigid body.
     */
    Matrix4 offset;

    /**
     * Calculates the internals for the primitive.
     */
    void CalculateInternals();

    /**
     * This is a convenience function to allow access to the
     * axis vectors in the transform for this primitive.
     */
    Vector3 GetAxis(unsigned index) const
    {
        return transform.getAxisVector(index);
    }

    /**
     * Returns the resultant transform of the primitive, calculated from
     * the combined offset of the primitive and the transform 
     * (orientation + position) of the rigid body to which it is 
     * attached.
     */
    const Matrix4& GetTransform() const
    {
        return transform;
    }

	int GetType() { return primitiveType; }
	int GetCollisionFlag() const { return collisionFlag; }
	void SetCollisionFlag(int val) { collisionFlag = val; }
	void AddCollisionFlag(int val) { collisionFlag |= val; }
	void RemoveCollisionFlag(int val) { collisionFlag &= ~val; }
	bool HasCollisionFlag(int val) { return (collisionFlag & val); }
	int GetAllowedToHandleCollision() const { return allowedToHandleCollision; }
	void SetAllowedToHandleCollision(int val) { allowedToHandleCollision = val; }
	bool IsAllowedToHandleCollision(int val) const { return (allowedToHandleCollision & val); }
	PhysicObject* GetPhysicObject() const { if(primitiveType == PPT_POINT) { return p; } else { return body; } }
	Object *GetOwner() { return owner; }
	void SetOwner(Object *o) { owner = o; }

protected:
    /**
     * The resultant transform of the primitive. This is 
     * calculated by combining the offset of the primitive
     * with the transform of the rigid body.
     */
    Matrix4 transform;

	int primitiveType;
	int collisionFlag;
	int allowedToHandleCollision;
	Object *owner;
};

/*
 * Represents a point which can be particle
 * for collision detection
 **/
class CollisionPoint : public CollisionPrimitive
{
public:
	CollisionPoint()
	{
		owner = NULL;
		primitiveType = PPT_POINT;
		p = new Particle();
		collisionFlag = 0;
		allowedToHandleCollision = 0x0FFFFFFF;
	}
};

/**
 * Represents a rigid body that can be treated as a sphere
 * for collision detection.
 */
class CollisionSphere : public CollisionPrimitive
{
public:
	CollisionSphere()
	{
		owner = NULL;
		primitiveType = PPT_SPHERE;
		body = new RigidBody();
		collisionFlag = 0;
		allowedToHandleCollision = 0x0FFFFFFF;
	}

	bool Init()
	{
		//http://www.physicsforums.com/showthread.php?t=159293
		//http://www.gamedev.net/community/forums/topic.asp?topic_id=57001
		//2*M*R^2/5
		Matrix3 tensor;
		tensor.SetSphereInertiaTensor(radius, body->GetMass());
		body->SetInertiaTensor(tensor);
		return true;
	}
	
	bool Init(int mass)
	{
		//http://www.physicsforums.com/showthread.php?t=159293
		//http://www.gamedev.net/community/forums/topic.asp?topic_id=57001
		//2*M*R^2/5
		Matrix3 tensor;
		tensor.SetSphereInertiaTensor(radius, mass);
		body->SetInertiaTensor(tensor);
		return true;
	}	

    /**
     * The radius of the sphere.
     */
    Real radius;
};

/**
 * The plane is not a primitive: it doesn't represent another
 * rigid body. It is used for contacts with the immovable
 * world geometry.
 */
class CollisionPlane : public CollisionPrimitive
{
public:
	CollisionPlane()
	{
		owner = NULL;
		primitiveType = PPT_PLANE;
		body = new RigidBody();
		collisionFlag = 0;
		allowedToHandleCollision = 0x0FFFFFFF;
	}

    /** 
     * The plane normal
     */
    Vector3 direction;

    /**
     * The distance of the plane from the origin.
     */
    Real offset;

	/*
	 * Plane type, if 0 plane, if 1 half space
	 */
	bool plane;
};

/**
 * Represents a rigid body that can be treated as an aligned bounding
 * box for collision detection.
 */
class CollisionBox : public CollisionPrimitive
{
public:
	CollisionBox()
	{
		owner = NULL;
		primitiveType = PPT_BOX;
		body = new RigidBody();
		collisionFlag = 0;
		allowedToHandleCollision = 0x0FFFFFFF;
	}

	bool Init()
	{
		Matrix3 tensor;
		tensor.setBlockInertiaTensor(halfSize, body->GetMass());
		body->SetInertiaTensor(tensor);
		return true;
	}
	
	bool Init(int mass)
	{
		Matrix3 tensor;
		tensor.setBlockInertiaTensor(halfSize, mass);
		body->SetInertiaTensor(tensor);
		return true;
	}	

    /** 
     * Holds the half-sizes of the box along each of its local axes.
     */
    Vector3 halfSize;
};

/**
 * A wrapper class that holds fast intersection tests. These
 * can be used to drive the coarse collision detection system or
 * as an early out in the full collision tests below.
 */
class IntersectionTests
{
public:

    static bool SphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane);

    static bool SphereAndSphere(const CollisionSphere &one, const CollisionSphere &two);

    static bool BoxAndBox(const CollisionBox &one, const CollisionBox &two);

    /**
     * Does an intersection test on an arbitrarily aligned box and a
     * half-space. 
     *
     * The box is given as a transform matrix, including
     * position, and a vector of half-sizes for the extend of the
     * box along each local axis.
     *
     * The half-space is given as a direction (i.e. unit) vector and the
     * offset of the limiting plane from the origin, along the given 
     * direction.
     */
    static bool BoxAndHalfSpace(const CollisionBox &box, const CollisionPlane &plane);
};

/**
 * A helper structure that contains information for the detector to use
 * in building its contact data.
 */
struct CollisionData
{
    /** 
     * Holds the base of the collision data: the first contact
     * in the array. This is used so that the contact pointer (below)
     * can be incremented each time a contact is detected, while
     * this pointer points to the first contact found.
     */
	CollisionData()
	{
		contacts = new Contact();
	}

    //Contact *contactArray;
	std::vector<Contact> contactArray;

    /** Holds the contact array to write into. */
    Contact *contacts;

    /** Holds the maximum number of contacts the array can take. */
    int contactsLeft;

    /** Holds the number of contacts found so far. */
    unsigned contactCount;

    /** Holds the friction value to write into any collisions. */
    Real friction;

    /** Holds the restitution value to write into any collisions. */
    Real restitution;

    /** 
     * Holds the collision tolerance, even uncolliding objects this
     * close should have collisions generated.
     */
    Real tolerance;

    /**
     * Checks if there are more contacts available in the contact
     * data.
     */
    bool HasMoreContacts()
    {
        return contactsLeft > 0;
    }

	Contact* GetContactArray()
	{
		return &contactArray[0];
	}

    /**
     * Resets the data so that it has no used contacts recorded.
     */
    void Reset(unsigned maxContacts)
    {
        contactsLeft = maxContacts;
        contactCount = 0;
		/*std::vector<Contact*>::iterator itr = contactArray.begin();
		for(; itr != contactArray.end(); )
		{
			Contact *c = (*itr);
			++itr;
			delete c;
		}*/
		contactArray.clear();
		if(contacts)
			delete contacts;
		contacts = new Contact();
    }

    /**
     * Notifies the data that the given number of contacts have
     * been added.
     */
    void AddContacts(unsigned count)
    {
        // Reduce the number of contacts remaining, add number used
        contactsLeft -= count;
        contactCount += count;

        // Move the array forward
		contactArray.push_back(*contacts);
		contacts = new Contact();
		//contacts += count;
    }  
};

/**
 * A wrapper class that holds the fine grained collision detection 
 * routines.
 *
 * Each of the functions has the same format: it takes the details
 * of two objects, and a pointer to a contact array to fill. It 
 * returns the number of contacts it wrote into the array.
 */
class CollisionDetector
{
public:

    static unsigned SphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane, CollisionData *data);

    static unsigned SphereAndTruePlane(const CollisionSphere &sphere, const CollisionPlane &plane, CollisionData *data);

    static unsigned SphereAndSphere(const CollisionSphere &one, const CollisionSphere &two, CollisionData *data);

	static unsigned SphereAndPoint(const CollisionSphere &sphere, const CollisionPoint &point, CollisionData *data);
        
    /**
     * Does a collision test on a collision box and a plane representing 
     * a half-space (i.e. the normal of the plane 
     * points out of the half-space).
     */
    static unsigned BoxAndHalfSpace(const CollisionBox &box, const CollisionPlane &plane, CollisionData *data);

	static unsigned BoxAndBox(const CollisionBox &one, const CollisionBox &two, CollisionData *data);

	static unsigned BoxAndPoint(const CollisionBox &box, const CollisionPoint &point, CollisionData *data);

	static unsigned BoxAndSphere(const CollisionBox &box, const CollisionSphere &sphere, CollisionData *data);

	static unsigned Collide(CollisionPrimitive *prim1, CollisionPrimitive *prim2, CollisionData *data);
	
	static void EmptyFunction(CollisionPrimitive* prim1, CollisionPrimitive *prim2) { }
};

#endif
