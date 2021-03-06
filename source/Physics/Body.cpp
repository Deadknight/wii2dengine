#include "Stdafx.h"

/**
 * Internal function that checks the validity of an inverse inertia tensor.
 */
static inline void _CheckInverseInertiaTensor(const Matrix3 &iitWorld)
{
    // TODO: Perform a validity check in an assert.
}

/**
 * Internal function to do an intertia tensor transform by a quaternion.
 * Note that the implementation of this function was created by an
 * automated code-generator and optimizer.
 */
static inline void _TransformInertiaTensor(Matrix3 &iitWorld,
                                           const Quaternion &q,
                                           const Matrix3 &iitBody,
                                           const Matrix4 &rotmat)
{
    Real t4 = rotmat.data[0]*iitBody.data[0]+
        rotmat.data[1]*iitBody.data[3]+
        rotmat.data[2]*iitBody.data[6];
    Real t9 = rotmat.data[0]*iitBody.data[1]+
        rotmat.data[1]*iitBody.data[4]+
        rotmat.data[2]*iitBody.data[7];
    Real t14 = rotmat.data[0]*iitBody.data[2]+
        rotmat.data[1]*iitBody.data[5]+
        rotmat.data[2]*iitBody.data[8];
    Real t28 = rotmat.data[4]*iitBody.data[0]+
        rotmat.data[5]*iitBody.data[3]+
        rotmat.data[6]*iitBody.data[6];
    Real t33 = rotmat.data[4]*iitBody.data[1]+
        rotmat.data[5]*iitBody.data[4]+
        rotmat.data[6]*iitBody.data[7];
    Real t38 = rotmat.data[4]*iitBody.data[2]+
        rotmat.data[5]*iitBody.data[5]+
        rotmat.data[6]*iitBody.data[8];
    Real t52 = rotmat.data[8]*iitBody.data[0]+
        rotmat.data[9]*iitBody.data[3]+
        rotmat.data[10]*iitBody.data[6];
    Real t57 = rotmat.data[8]*iitBody.data[1]+
        rotmat.data[9]*iitBody.data[4]+
        rotmat.data[10]*iitBody.data[7];
    Real t62 = rotmat.data[8]*iitBody.data[2]+
        rotmat.data[9]*iitBody.data[5]+
        rotmat.data[10]*iitBody.data[8];

    iitWorld.data[0] = t4*rotmat.data[0]+
        t9*rotmat.data[1]+
        t14*rotmat.data[2];
    iitWorld.data[1] = t4*rotmat.data[4]+
        t9*rotmat.data[5]+
        t14*rotmat.data[6];
    iitWorld.data[2] = t4*rotmat.data[8]+
        t9*rotmat.data[9]+
        t14*rotmat.data[10];
    iitWorld.data[3] = t28*rotmat.data[0]+
        t33*rotmat.data[1]+
        t38*rotmat.data[2];
    iitWorld.data[4] = t28*rotmat.data[4]+
        t33*rotmat.data[5]+
        t38*rotmat.data[6];
    iitWorld.data[5] = t28*rotmat.data[8]+
        t33*rotmat.data[9]+
        t38*rotmat.data[10];
    iitWorld.data[6] = t52*rotmat.data[0]+
        t57*rotmat.data[1]+
        t62*rotmat.data[2];
    iitWorld.data[7] = t52*rotmat.data[4]+
        t57*rotmat.data[5]+
        t62*rotmat.data[6];
    iitWorld.data[8] = t52*rotmat.data[8]+
        t57*rotmat.data[9]+
        t62*rotmat.data[10];
}

/**
 * Inline function that creates a transform matrix from a
 * position and orientation.
 */
static inline void _CalculateTransformMatrix(Matrix4 &transformMatrix,
                                             const Vector3 &position,
                                             const Quaternion &orientation)
{
    transformMatrix.data[0] = 1-2*orientation.j*orientation.j-
        2*orientation.k*orientation.k;
    transformMatrix.data[1] = 2*orientation.i*orientation.j -
        2*orientation.r*orientation.k;
    transformMatrix.data[2] = 2*orientation.i*orientation.k +
        2*orientation.r*orientation.j;
    transformMatrix.data[3] = position.x;

    transformMatrix.data[4] = 2*orientation.i*orientation.j +
        2*orientation.r*orientation.k;
    transformMatrix.data[5] = 1-2*orientation.i*orientation.i-
        2*orientation.k*orientation.k;
    transformMatrix.data[6] = 2*orientation.j*orientation.k -
        2*orientation.r*orientation.i;
    transformMatrix.data[7] = position.y;

    transformMatrix.data[8] = 2*orientation.i*orientation.k -
        2*orientation.r*orientation.j;
    transformMatrix.data[9] = 2*orientation.j*orientation.k +
        2*orientation.r*orientation.i;
    transformMatrix.data[10] = 1-2*orientation.i*orientation.i-
        2*orientation.j*orientation.j;
    transformMatrix.data[11] = position.z;
}

/*
 * --------------------------------------------------------------------------
 * FUNCTIONS DECLARED IN HEADER:
 * --------------------------------------------------------------------------
 */

RigidBody::RigidBody()
{
	objectType = POT_RIGID_BODY;
	velocity = Vector3(0, 0, 0);
	rotation = Vector3(0, 0, 0);
	forceAccum = Vector3(0, 0, 0);
	torqueAccum = Vector3(0, 0, 0);
	acceleration = Vector3(0, 0, 0);
	isAwake = false;
	canSleep = true;	
}

void RigidBody::CalculateDerivedData()
{
    orientation.normalise();

    // Calculate the transform matrix for the body.
    _CalculateTransformMatrix(transformMatrix, position, orientation);

    // Calculate the inertiaTensor in world space.
    _TransformInertiaTensor(inverseInertiaTensorWorld,
        orientation,
        inverseInertiaTensor,
        transformMatrix);
}

bool RigidBody::Simulate(Real duration)
{
    if (!isAwake) return false;	
	
	//Update RigidBody Forces
	RBFGSET::iterator itr = rbfgList.begin();
	for(; itr != rbfgList.end(); ++itr)
	{
		(*itr)->rbfg->UpdateForce(this, duration);
	}

    // Calculate linear acceleration from force inputs.
    lastFrameAcceleration = acceleration;
    lastFrameAcceleration.addScaledVector(forceAccum, inverseMass);
	
    // Calculate angular acceleration from torque inputs.
    Vector3 angularAcceleration =
        inverseInertiaTensorWorld.transform(torqueAccum);

    // Adjust velocities
    // Update linear velocity from both acceleration and impulse.
    velocity.addScaledVector(lastFrameAcceleration, duration);

    // Update angular velocity from both acceleration and impulse.
    rotation.addScaledVector(angularAcceleration, duration);

    // Impose drag.
    velocity *= Real_pow(linearDamping, duration);
    rotation *= Real_pow(angularDamping, duration);

    // Adjust positions
    // Update linear position.
    position.addScaledVector(velocity, duration);

    // Update angular position.
    orientation.addScaledVector(rotation, duration);

    // Impose drag.
    velocity *= Real_pow(linearDamping, duration);
    rotation *= Real_pow(angularDamping, duration);

    // Normalise the orientation, and update the matrices with the new
    // position and orientation
    CalculateDerivedData();

    // Clear accumulators.
    ClearAccumulators();

    // Update the kinetic energy store, and possibly put the body to
    // sleep.
    if (canSleep) {
        Real currentMotion = velocity.scalarProduct(velocity) +
            rotation.scalarProduct(rotation);

        Real bias = Real_pow(0.5, duration);
        motion = bias*motion + (1-bias)*currentMotion;

        if (motion < sleepEpsilon) SetAwake(false);
        else if (motion > 10 * sleepEpsilon) motion = 10 * sleepEpsilon;
    }

	return true;
}

void RigidBody::SetMass(const Real mass)
{
    assert(mass != 0);
    RigidBody::inverseMass = ((Real)1.0)/mass;
}

Real RigidBody::GetMass() const
{
    if (inverseMass == 0) {
        return REAL_MAX;
    } else {
        return ((Real)1.0)/inverseMass;
    }
}

void RigidBody::SetInverseMass(const Real inverseMass)
{
    RigidBody::inverseMass = inverseMass;
}

Real RigidBody::GetInverseMass() const
{
    return inverseMass;
}

bool RigidBody::HasFiniteMass() const
{
    return inverseMass >= 0.0f;
}

void RigidBody::SetInertiaTensor(const Matrix3 &inertiaTensor)
{
    inverseInertiaTensor.setInverse(inertiaTensor);
    _CheckInverseInertiaTensor(inverseInertiaTensor);
}

void RigidBody::GetInertiaTensor(Matrix3 *inertiaTensor) const
{
    inertiaTensor->setInverse(inverseInertiaTensor);
}

Matrix3 RigidBody::GetInertiaTensor() const
{
    Matrix3 it;
    GetInertiaTensor(&it);
    return it;
}

void RigidBody::GetInertiaTensorWorld(Matrix3 *inertiaTensor) const
{
    inertiaTensor->setInverse(inverseInertiaTensorWorld);
}

Matrix3 RigidBody::GetInertiaTensorWorld() const
{
    Matrix3 it;
    GetInertiaTensorWorld(&it);
    return it;
}

void RigidBody::SetInverseInertiaTensor(const Matrix3 &inverseInertiaTensor)
{
    _CheckInverseInertiaTensor(inverseInertiaTensor);
    RigidBody::inverseInertiaTensor = inverseInertiaTensor;
}

void RigidBody::GetInverseInertiaTensor(Matrix3 *inverseInertiaTensor) const
{
    *inverseInertiaTensor = RigidBody::inverseInertiaTensor;
}

Matrix3 RigidBody::GetInverseInertiaTensor() const
{
    return inverseInertiaTensor;
}

void RigidBody::GetInverseInertiaTensorWorld(Matrix3 *inverseInertiaTensor) const
{
    *inverseInertiaTensor = inverseInertiaTensorWorld;
}

Matrix3 RigidBody::GetInverseInertiaTensorWorld() const
{
    return inverseInertiaTensorWorld;
}

void RigidBody::SetDamping(const Real linearDamping,
               const Real angularDamping)
{
    RigidBody::linearDamping = linearDamping;
    RigidBody::angularDamping = angularDamping;
}

void RigidBody::SetLinearDamping(const Real linearDamping)
{
    RigidBody::linearDamping = linearDamping;
}

Real RigidBody::GetLinearDamping() const
{
    return linearDamping;
}

void RigidBody::SetAngularDamping(const Real angularDamping)
{
    RigidBody::angularDamping = angularDamping;
}

Real RigidBody::GetAngularDamping() const
{
    return angularDamping;
}

void RigidBody::SetPosition(const Vector3 &position)
{
    RigidBody::position = position;
}

void RigidBody::SetPosition(const Real x, const Real y, const Real z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void RigidBody::GetPosition(Vector3 *position) const
{
    *position = RigidBody::position;
}

Vector3 RigidBody::GetPosition() const
{
    return position;
}

void RigidBody::SetOrientation(const Quaternion &orientation)
{
    RigidBody::orientation = orientation;
    RigidBody::orientation.normalise();
}

void RigidBody::SetOrientation(const Real r, const Real i,
                   const Real j, const Real k)
{
    orientation.r = r;
    orientation.i = i;
    orientation.j = j;
    orientation.k = k;
    orientation.normalise();
}

void RigidBody::GetOrientation(Quaternion *orientation) const
{
    *orientation = RigidBody::orientation;
}

Quaternion RigidBody::GetOrientation() const
{
    return orientation;
}

void RigidBody::GetOrientation(Matrix3 *matrix) const
{
    GetOrientation(matrix->data);
}

void RigidBody::GetOrientation(Real matrix[9]) const
{
    matrix[0] = transformMatrix.data[0];
    matrix[1] = transformMatrix.data[1];
    matrix[2] = transformMatrix.data[2];

    matrix[3] = transformMatrix.data[4];
    matrix[4] = transformMatrix.data[5];
    matrix[5] = transformMatrix.data[6];

    matrix[6] = transformMatrix.data[8];
    matrix[7] = transformMatrix.data[9];
    matrix[8] = transformMatrix.data[10];
}

void RigidBody::GetTransform(Matrix4 *transform) const
{
    memcpy(transform, &transformMatrix.data, sizeof(Matrix4));
}

void RigidBody::GetTransform(Real matrix[16]) const
{
    memcpy(matrix, transformMatrix.data, sizeof(Real)*12);
    matrix[12] = matrix[13] = matrix[14] = 0;
    matrix[15] = 1;
}

void RigidBody::GetGLTransform(float matrix[16]) const
{
    matrix[0] = (float)transformMatrix.data[0];
    matrix[1] = (float)transformMatrix.data[4];
    matrix[2] = (float)transformMatrix.data[8];
    matrix[3] = 0;

    matrix[4] = (float)transformMatrix.data[1];
    matrix[5] = (float)transformMatrix.data[5];
    matrix[6] = (float)transformMatrix.data[9];
    matrix[7] = 0;

    matrix[8] = (float)transformMatrix.data[2];
    matrix[9] = (float)transformMatrix.data[6];
    matrix[10] = (float)transformMatrix.data[10];
    matrix[11] = 0;

    matrix[12] = (float)transformMatrix.data[3];
    matrix[13] = (float)transformMatrix.data[7];
    matrix[14] = (float)transformMatrix.data[11];
    matrix[15] = 1;
}

Matrix4 RigidBody::GetTransform() const
{
    return transformMatrix;
}


Vector3 RigidBody::GetPointInLocalSpace(const Vector3 &point) const
{
    return transformMatrix.transformInverse(point);
}

Vector3 RigidBody::GetPointInWorldSpace(const Vector3 &point) const
{
    return transformMatrix.transform(point);
}

Vector3 RigidBody::GetDirectionInLocalSpace(const Vector3 &direction) const
{
    return transformMatrix.transformInverseDirection(direction);
}

Vector3 RigidBody::GetDirectionInWorldSpace(const Vector3 &direction) const
{
    return transformMatrix.transformDirection(direction);
}


void RigidBody::SetVelocity(const Vector3 &velocity)
{
    RigidBody::velocity = velocity;
}

void RigidBody::SetVelocity(const Real x, const Real y, const Real z)
{
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
}

void RigidBody::GetVelocity(Vector3 *velocity) const
{
    *velocity = RigidBody::velocity;
}

Vector3 RigidBody::GetVelocity() const
{
    return velocity;
}

void RigidBody::AddVelocity(const Vector3 &deltaVelocity)
{
    velocity += deltaVelocity;
}

void RigidBody::SetRotation(const Vector3 &rotation)
{
    RigidBody::rotation = rotation;
}

void RigidBody::SetRotation(const Real x, const Real y, const Real z)
{
    rotation.x = x;
    rotation.y = y;
    rotation.z = z;
}

void RigidBody::GetRotation(Vector3 *rotation) const
{
    *rotation = RigidBody::rotation;
}

Vector3 RigidBody::GetRotation() const
{
    return rotation;
}

void RigidBody::AddRotation(const Vector3 &deltaRotation)
{
    rotation += deltaRotation;
	/*if(rotation.z > R_PI)
	{
		rotation.z = rotation.z - R_PI;
	}*/
}

void RigidBody::SetAwake(const bool awake)
{
    if (awake) {
        isAwake= true;

        // Add a bit of motion to avoid it falling asleep immediately.
        motion = sleepEpsilon*2.0f;
    } else {
        isAwake = false;
        velocity.clear();
        rotation.clear();
    }
}

void RigidBody::SetCanSleep(const bool canSleep)
{
    RigidBody::canSleep = canSleep;

    if (!canSleep && !isAwake) SetAwake();
}


void RigidBody::GetLastFrameAcceleration(Vector3 *acceleration) const
{
    *acceleration = lastFrameAcceleration;
}

Vector3 RigidBody::GetLastFrameAcceleration() const
{
    return lastFrameAcceleration;
}

void RigidBody::ClearAccumulators()
{
    forceAccum.clear();
    torqueAccum.clear();
}

void RigidBody::AddForce(const Vector3 &force)
{
    forceAccum += force;
    isAwake = true;
}

void RigidBody::AddForceAtBodyPoint(const Vector3 &force,
                                    const Vector3 &point)
{
    // Convert to coordinates relative to center of mass.
    Vector3 pt = GetPointInWorldSpace(point);
    AddForceAtPoint(force, pt);

    isAwake = true;
}

void RigidBody::AddForceAtPoint(const Vector3 &force,
                                const Vector3 &point)
{
    // Convert to coordinates relative to center of mass.
    Vector3 pt = point;
    pt -= position;

    forceAccum += force;
    torqueAccum += pt % force;

    isAwake = true;
}

void RigidBody::AddForceGenerator(std::string name, ForceGenerator* rbfg)
{
	RigidBodyForce *rbf = new RigidBodyForce();
	rbf->name = name;
	rbf->rbfg = rbfg;
	rbfgList.insert(rbf);
}

void RigidBody::RemoveForceGenerator(std::string name)
{
	RigidBodyForce *rbf = NULL;
	RBFGSET::iterator itr = rbfgList.begin();
	for(; itr != rbfgList.end(); )
	{
		if((*itr)->name == name)
		{
			rbf = (*itr);
			break;
		}
	}
	if(rbf)
	{
		delete rbf->rbfg;
		delete rbf;
		rbfgList.erase(itr);
	}
}

void RigidBody::RemoveForceGenerator(ForceGenerator *rbfg)
{
	RigidBodyForce *rbf = NULL;
	RBFGSET::iterator itr = rbfgList.begin();
	for(; itr != rbfgList.end(); )
	{
		if((*itr)->rbfg == rbfg)
		{
			rbf = (*itr);
			break;
		}
	}
	if(rbf)
	{
		delete rbf->rbfg;
		delete rbf;
		rbfgList.erase(itr);
	}
}

void RigidBody::ClearForceGenerators()
{
	RBFGSET::iterator itr = rbfgList.begin();
	for(; itr != rbfgList.end(); )
	{
		RigidBodyForce *rbf = (*itr);
		++itr;
		delete rbf->rbfg;
		delete rbf;
	}
	rbfgList.clear(); 
}

void RigidBody::AddTorque(const Vector3 &torque)
{
    torqueAccum += torque;
    isAwake = true;
}

void RigidBody::SetAcceleration(const Vector3 &acceleration)
{
    RigidBody::acceleration = acceleration;
}

void RigidBody::SetAcceleration(const Real x, const Real y, const Real z)
{
    acceleration.x = x;
    acceleration.y = y;
    acceleration.z = z;
}

void RigidBody::GetAcceleration(Vector3 *acceleration) const
{
    *acceleration = RigidBody::acceleration;
}

Vector3 RigidBody::GetAcceleration() const
{
    return acceleration;
}
