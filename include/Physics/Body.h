#ifndef BODY_H
#define BODY_H

class ForceGenerator;

struct RigidBodyForce
{
	std::string name;
	ForceGenerator *rbfg;
};

class RigidBody : public PhysicObject
{
public:
    /**
     * @name Constructor and Destructor
     *
     * There are no data members in the rigid body class that are
     * created on the heap. So all data storage is handled
     * automatically.
     */
	RigidBody();
	~RigidBody() { }

	typedef std::set<RigidBodyForce*> RBFGSET;

    /**
     * @name Integration and Simulation Functions
     *
     * These functions are used to simulate the rigid body's
     * motion over time. A normal application sets up one or more
     * rigid bodies, applies permanent forces (i.e. gravity), then
     * adds transient forces each frame, and integrates, prior to
     * rendering.
     *
     * Currently the only integration function provided is the
     * first order Newton Euler method.
     */

	/**
     * Calculates internal data from state data. This should be called
     * after the body's state is altered directly (it is called
     * automatically during integration). If you change the body's state
     * and then intend to integrate before querying any data (such as
     * the transform matrix), then you can ommit this step.
     */
    void CalculateDerivedData();

    /**
     * Integrates the rigid body forward in time by the given amount.
     * This function uses a Newton-Euler integration method, which is a
     * linear approximation to the correct integral. For this reason it
     * may be inaccurate in some cases.
     */
    bool Simulate(Real duration);

    /**
     * @name Accessor Functions for the Rigid Body's State
     *
     * These functions provide access to the rigid body's
     * characteristics or state. These data can be accessed
     * individually, or en masse as an array of values
     * (e.g. getCharacteristics, getState). When setting new data,
     * make sure the calculateInternals function, or an
     * integration routine, is called before trying to get data
     * from the body, since the class contains a number of
     * dependent values that will need recalculating.
     */

    /**
     * Sets the mass of the rigid body.
     *
     * @param mass The new mass of the body. This may not be zero.
     * Small masses can produce unstable rigid bodies under
     * simulation.
     *
     * @warning This invalidates internal data for the rigid body.
     * Either an integration function, or the calculateInternals
     * function should be called before trying to get any settings
     * from the rigid body.
     */
    void SetMass(const Real mass);

    /**
     * Gets the mass of the rigid body.
     *
     * @return The current mass of the rigid body.
     */
    Real GetMass() const;

    /**
     * Sets the inverse mass of the rigid body.
     *
     * @param inverseMass The new inverse mass of the body. This
     * may be zero, for a body with infinite mass
     * (i.e. unmovable).
     *
     * @warning This invalidates internal data for the rigid body.
     * Either an integration function, or the calculateInternals
     * function should be called before trying to get any settings
     * from the rigid body.
     */
    void SetInverseMass(const Real inverseMass);

    /**
     * Gets the inverse mass of the rigid body.
     *
     * @return The current inverse mass of the rigid body.
     */
    Real GetInverseMass() const;

    /**
     * Returns true if the mass of the body is not-infinite.
     */
    bool HasFiniteMass() const;

    /**
     * Sets the intertia tensor for the rigid body.
     *
     * @param inertiaTensor The inertia tensor for the rigid
     * body. This must be a full rank matrix and must be
     * invertible.
     *
     * @warning This invalidates internal data for the rigid body.
     * Either an integration function, or the calculateInternals
     * function should be called before trying to get any settings
     * from the rigid body.
     */
    void SetInertiaTensor(const Matrix3 &inertiaTensor);

    /**
     * Copies the current inertia tensor of the rigid body into
     * the given matrix.
     *
     * @param inertiaTensor A pointer to a matrix to hold the
     * current inertia tensor of the rigid body. The inertia
     * tensor is expressed in the rigid body's local space.
     */
    void GetInertiaTensor(Matrix3 *inertiaTensor) const;

    /**
     * Gets a copy of the current inertia tensor of the rigid body.
     *
     * @return A new matrix containing the current intertia
     * tensor. The inertia tensor is expressed in the rigid body's
     * local space.
     */
    Matrix3 GetInertiaTensor() const;

    /**
     * Copies the current inertia tensor of the rigid body into
     * the given matrix.
     *
     * @param inertiaTensor A pointer to a matrix to hold the
     * current inertia tensor of the rigid body. The inertia
     * tensor is expressed in world space.
     */
    void GetInertiaTensorWorld(Matrix3 *inertiaTensor) const;

    /**
     * Gets a copy of the current inertia tensor of the rigid body.
     *
     * @return A new matrix containing the current intertia
     * tensor. The inertia tensor is expressed in world space.
     */
    Matrix3 GetInertiaTensorWorld() const;

    /**
     * Sets the inverse intertia tensor for the rigid body.
     *
     * @param inverseInertiaTensor The inverse inertia tensor for
     * the rigid body. This must be a full rank matrix and must be
     * invertible.
     *
     * @warning This invalidates internal data for the rigid body.
     * Either an integration function, or the calculateInternals
     * function should be called before trying to get any settings
     * from the rigid body.
     */
    void SetInverseInertiaTensor(const Matrix3 &inverseInertiaTensor);

    /**
     * Copies the current inverse inertia tensor of the rigid body
     * into the given matrix.
     *
     * @param inverseInertiaTensor A pointer to a matrix to hold
     * the current inverse inertia tensor of the rigid body. The
     * inertia tensor is expressed in the rigid body's local
     * space.
     */
    void GetInverseInertiaTensor(Matrix3 *inverseInertiaTensor) const;

    /**
     * Gets a copy of the current inverse inertia tensor of the
     * rigid body.
     *
     * @return A new matrix containing the current inverse
     * intertia tensor. The inertia tensor is expressed in the
     * rigid body's local space.
     */
    Matrix3 GetInverseInertiaTensor() const;

    /**
     * Copies the current inverse inertia tensor of the rigid body
     * into the given matrix.
     *
     * @param inverseInertiaTensor A pointer to a matrix to hold
     * the current inverse inertia tensor of the rigid body. The
     * inertia tensor is expressed in world space.
     */
    void GetInverseInertiaTensorWorld(Matrix3 *inverseInertiaTensor) const;

    /**
     * Gets a copy of the current inverse inertia tensor of the
     * rigid body.
     *
     * @return A new matrix containing the current inverse
     * intertia tensor. The inertia tensor is expressed in world
     * space.
     */
    Matrix3 GetInverseInertiaTensorWorld() const;

    /**
     * Sets both linear and angular damping in one function call.
     *
     * @param linearDamping The speed that velocity is shed from
     * the rigid body.
     *
     * @param angularDamping The speed that rotation is shed from
     * the rigid body.
     *
     * @see setLinearDamping
     * @see setAngularDamping
     */
    void SetDamping(const Real linearDamping, const Real angularDamping);

    /**
     * Sets the linear damping for the rigid body.
     *
     * @param linearDamping The speed that velocity is shed from
     * the rigid body.
     *
     * @see setAngularDamping
     */
    void SetLinearDamping(const Real linearDamping);

    /**
     * Gets the current linear damping value.
     *
     * @return The current linear damping value.
     */
    Real GetLinearDamping() const;

    /**
     * Sets the angular damping for the rigid body.
     *
     * @param angularDamping The speed that rotation is shed from
     * the rigid body.
     *
     * @see setLinearDamping
     */
    void SetAngularDamping(const Real angularDamping);

    /**
     * Gets the current angular damping value.
     *
     * @return The current angular damping value.
     */
    Real GetAngularDamping() const;

    /**
     * Sets the position of the rigid body.
     *
     * @param position The new position of the rigid body.
     */
    void SetPosition(const Vector3 &position);

    /**
     * Sets the position of the rigid body by component.
     *
     * @param x The x coordinate of the new position of the rigid
     * body.
     *
     * @param y The y coordinate of the new position of the rigid
     * body.
     *
     * @param z The z coordinate of the new position of the rigid
     * body.
     */
    void SetPosition(const Real x, const Real y, const Real z);

    /**
     * Fills the given vector with the position of the rigid body.
     *
     * @param position A pointer to a vector into which to write
     * the position.
     */
    void GetPosition(Vector3 *position) const;

    /**
     * Gets the position of the rigid body.
     *
     * @return The position of the rigid body.
     */
    Vector3 GetPosition() const;

    /**
     * Sets the orientation of the rigid body.
     *
     * @param orientation The new orientation of the rigid body.
     *
     * @note The given orientation does not need to be normalised,
     * and can be zero. This function automatically constructs a
     * valid rotation quaternion with (0,0,0,0) mapping to
     * (1,0,0,0).
     */
    void SetOrientation(const Quaternion &orientation);

    /**
     * Sets the orientation of the rigid body by component.
     *
     * @param r The Real component of the rigid body's orientation
     * quaternion.
     *
     * @param i The first complex component of the rigid body's
     * orientation quaternion.
     *
     * @param j The second complex component of the rigid body's
     * orientation quaternion.
     *
     * @param k The third complex component of the rigid body's
     * orientation quaternion.
     *
     * @note The given orientation does not need to be normalised,
     * and can be zero. This function automatically constructs a
     * valid rotation quaternion with (0,0,0,0) mapping to
     * (1,0,0,0).
     */
    void SetOrientation(const Real r, const Real i,
        const Real j, const Real k);

    /**
     * Fills the given quaternion with the current value of the
     * rigid body's orientation.
     *
     * @param orientation A pointer to a quaternion to receive the
     * orientation data.
     */
    void GetOrientation(Quaternion *orientation) const;

    /**
     * Gets the orientation of the rigid body.
     *
     * @return The orientation of the rigid body.
     */
    Quaternion GetOrientation() const;

    /**
     * Fills the given matrix with a transformation representing
     * the rigid body's orientation.
     *
     * @note Transforming a direction vector by this matrix turns
     * it from the body's local space to world space.
     *
     * @param matrix A pointer to the matrix to fill.
     */
    void GetOrientation(Matrix3 *matrix) const;

    /**
     * Fills the given matrix data structure with a transformation
     * representing the rigid body's orientation.
     *
     * @note Transforming a direction vector by this matrix turns
     * it from the body's local space to world space.
     *
     * @param matrix A pointer to the matrix to fill.
     */
    void GetOrientation(Real matrix[9]) const;

    /**
     * Fills the given matrix with a transformation representing
     * the rigid body's position and orientation.
     *
     * @note Transforming a vector by this matrix turns it from
     * the body's local space to world space.
     *
     * @param transform A pointer to the matrix to fill.
     */
    void GetTransform(Matrix4 *transform) const;

    /**
     * Fills the given matrix data structure with a
     * transformation representing the rigid body's position and
     * orientation.
     *
     * @note Transforming a vector by this matrix turns it from
     * the body's local space to world space.
     *
     * @param matrix A pointer to the matrix to fill.
     */
    void GetTransform(Real matrix[16]) const;

    /**
     * Fills the given matrix data structure with a
     * transformation representing the rigid body's position and
     * orientation. The matrix is transposed from that returned
     * by getTransform. This call returns a matrix suitable
     * for applying as an OpenGL transform.
     *
     * @note Transforming a vector by this matrix turns it from
     * the body's local space to world space.
     *
     * @param matrix A pointer to the matrix to fill.
     */
    void GetGLTransform(float matrix[16]) const;

    /**
     * Gets a transformation representing the rigid body's
     * position and orientation.
     *
     * @note Transforming a vector by this matrix turns it from
     * the body's local space to world space.
     *
     * @return The transform matrix for the rigid body.
     */
    Matrix4 GetTransform() const;

    /**
     * Converts the given point from world space into the body's
     * local space.
     *
     * @param point The point to covert, given in world space.
     *
     * @return The converted point, in local space.
     */
    Vector3 GetPointInLocalSpace(const Vector3 &point) const;

    /**
     * Converts the given point from world space into the body's
     * local space.
     *
     * @param point The point to covert, given in local space.
     *
     * @return The converted point, in world space.
     */
    Vector3 GetPointInWorldSpace(const Vector3 &point) const;

    /**
     * Converts the given direction from world space into the
     * body's local space.
     *
     * @note When a direction is converted between frames of
     * reference, there is no translation required.
     *
     * @param direction The direction to covert, given in world
     * space.
     *
     * @return The converted direction, in local space.
     */
    Vector3 GetDirectionInLocalSpace(const Vector3 &direction) const;

    /**
     * Converts the given direction from world space into the
     * body's local space.
     *
     * @note When a direction is converted between frames of
     * reference, there is no translation required.
     *
     * @param direction The direction to covert, given in local
     * space.
     *
     * @return The converted direction, in world space.
     */
    Vector3 GetDirectionInWorldSpace(const Vector3 &direction) const;

    /**
     * Sets the velocity of the rigid body.
     *
     * @param velocity The new velocity of the rigid body. The
     * velocity is given in world space.
     */
    void SetVelocity(const Vector3 &velocity);

    /**
     * Sets the velocity of the rigid body by component. The
     * velocity is given in world space.
     *
     * @param x The x coordinate of the new velocity of the rigid
     * body.
     *
     * @param y The y coordinate of the new velocity of the rigid
     * body.
     *
     * @param z The z coordinate of the new velocity of the rigid
     * body.
     */
    void SetVelocity(const Real x, const Real y, const Real z);

    /**
     * Fills the given vector with the velocity of the rigid body.
     *
     * @param velocity A pointer to a vector into which to write
     * the velocity. The velocity is given in world local space.
     */
    void GetVelocity(Vector3 *velocity) const;

    /**
     * Gets the velocity of the rigid body.
     *
     * @return The velocity of the rigid body. The velocity is
     * given in world local space.
     */
    Vector3 GetVelocity() const;

    /**
     * Applies the given change in velocity.
     */
    void AddVelocity(const Vector3 &deltaVelocity);

    /**
     * Sets the rotation of the rigid body.
     *
     * @param rotation The new rotation of the rigid body. The
     * rotation is given in world space.
     */
    void SetRotation(const Vector3 &rotation);

    /**
     * Sets the rotation of the rigid body by component. The
     * rotation is given in world space.
     *
     * @param x The x coordinate of the new rotation of the rigid
     * body.
     *
     * @param y The y coordinate of the new rotation of the rigid
     * body.
     *
     * @param z The z coordinate of the new rotation of the rigid
     * body.
     */
    void SetRotation(const Real x, const Real y, const Real z);

    /**
     * Fills the given vector with the rotation of the rigid body.
     *
     * @param rotation A pointer to a vector into which to write
     * the rotation. The rotation is given in world local space.
     */
    void GetRotation(Vector3 *rotation) const;

    /**
     * Gets the rotation of the rigid body.
     *
     * @return The rotation of the rigid body. The rotation is
     * given in world local space.
     */
    Vector3 GetRotation() const;

    /**
     * Applies the given change in rotation.
     */
    void AddRotation(const Vector3 &deltaRotation);

    /**
     * Returns true if the body is awake and responding to
     * integration.
     *
     * @return The awake state of the body.
     */
    bool GetAwake() const
    {
        return isAwake;
    }

    /**
     * Sets the awake state of the body. If the body is set to be
     * not awake, then its velocities are also cancelled, since
     * a moving body that is not awake can cause problems in the
     * simulation.
     *
     * @param awake The new awake state of the body.
     */
    void SetAwake(const bool awake=true);

    /**
     * Returns true if the body is allowed to go to sleep at
     * any time.
     */
    bool GetCanSleep() const
    {
        return canSleep;
    }

    /**
     * Sets whether the body is ever allowed to go to sleep. Bodies
     * under the player's control, or for which the set of
     * transient forces applied each frame are not predictable,
     * should be kept awake.
     *
     * @param canSleep Whether the body can now be put to sleep.
     */
    void SetCanSleep(const bool canSleep=true);

	/**
     * @name Retrieval Functions for Dynamic Quantities
     *
     * These functions provide access to the acceleration
     * properties of the body. The acceleration is generated by
     * the simulation from the forces and torques applied to the
     * rigid body. Acceleration cannot be directly influenced, it
     * is set during integration, and represent the acceleration
     * experienced by the body of the previous simulation step.
     */

    /**
     * Fills the given vector with the current accumulated value
     * for linear acceleration. The acceleration accumulators
     * are set during the integration step. They can be read to
     * determine the rigid body's acceleration over the last
     * integration step. The linear acceleration is given in world
     * space.
     *
     * @param linearAcceleration A pointer to a vector to receive
     * the linear acceleration data.
     */
    void GetLastFrameAcceleration(Vector3 *linearAcceleration) const;

    /**
     * Gets the current accumulated value for linear
     * acceleration. The acceleration accumulators are set during
     * the integration step. They can be read to determine the
     * rigid body's acceleration over the last integration
     * step. The linear acceleration is given in world space.
     *
     * @return The rigid body's linear acceleration.
     */
    Vector3 GetLastFrameAcceleration() const;

    /**
     * @name Force, Torque and Acceleration Set-up Functions
     *
     * These functions set up forces and torques to apply to the
     * rigid body.
     */
    /*@{*/

    /**
     * Clears the forces and torques in the accumulators. This will
     * be called automatically after each intergration step.
     */
    void ClearAccumulators();

    /**
     * Adds the given force to centre of mass of the rigid body.
     * The force is expressed in world-coordinates.
     *
     * @param force The force to apply.
     */
    void AddForce(const Vector3 &force);

    /**
     * Adds the given force to the given point on the rigid body.
     * Both the force and the
     * application point are given in world space. Because the
     * force is not applied at the centre of mass, it may be split
     * into both a force and torque.
     *
     * @param force The force to apply.
     *
     * @param point The location at which to apply the force, in
     * world-coordinates.
     */
    void AddForceAtPoint(const Vector3 &force, const Vector3 &point);

    /**
     * Adds the given force to the given point on the rigid body.
     * The direction of the force is given in world coordinates,
     * but the application point is given in body space. This is
     * useful for spring forces, or other forces fixed to the
     * body.
     *
     * @param force The force to apply.
     *
     * @param point The location at which to apply the force, in
     * body-coordinates.
     */
    void AddForceAtBodyPoint(const Vector3 &force, const Vector3 &point);

	void AddForceGenerator(std::string name, ForceGenerator* rbfg);
	void RemoveForceGenerator(std::string name);
	//This function is not safe
	void RemoveForceGenerator(ForceGenerator *rbfg);
	void ClearForceGenerators();

    /**
     * Adds the given torque to the rigid body.
     * The force is expressed in world-coordinates.
     *
     * @param torque The torque to apply.
     */
    void AddTorque(const Vector3 &torque);

    /**
     * Sets the constant acceleration of the rigid body.
     *
     * @param acceleration The new acceleration of the rigid body.
     */
    void SetAcceleration(const Vector3 &acceleration);

    /**
     * Sets the constant acceleration of the rigid body by component.
     *
     * @param x The x coordinate of the new acceleration of the rigid
     * body.
     *
     * @param y The y coordinate of the new acceleration of the rigid
     * body.
     *
     * @param z The z coordinate of the new acceleration of the rigid
     * body.
     */
    void SetAcceleration(const Real x, const Real y, const Real z);

    /**
     * Fills the given vector with the acceleration of the rigid body.
     *
     * @param acceleration A pointer to a vector into which to write
     * the acceleration. The acceleration is given in world local space.
     */
    void GetAcceleration(Vector3 *acceleration) const;

    /**
     * Gets the acceleration of the rigid body.
     *
     * @return The acceleration of the rigid body. The acceleration is
     * given in world local space.
     */
    Vector3 GetAcceleration() const;

protected:
	RBFGSET rbfgList;

    /**
     * Holds the inverse of the mass of the rigid body. It
     * is more useful to hold the inverse mass because
     * integration is simpler, and because in real time
     * simulation it is more useful to have bodies with
     * infinite mass (immovable) than zero mass
     * (completely unstable in numerical simulation).
     */
    Real inverseMass;

	/**
     * Holds the inverse of the body's inertia tensor. The
     * intertia tensor provided must not be degenerate
     * (that would mean the body had zero inertia for
     * spinning along one axis). As long as the tensor is
     * finite, it will be invertible. The inverse tensor
     * is used for similar reasons to the use of inverse
     * mass.
     *
     * The inertia tensor, unlike the other variables that
     * define a rigid body, is given in body space.
     *
     * @see inverseMass
     */
    Matrix3 inverseInertiaTensor;

    /**
     * Holds the amount of damping applied to linear
     * motion.  Damping is required to remove energy added
     * through numerical instability in the integrator.
     */
    Real linearDamping;

    /**
     * Holds the amount of damping applied to angular
     * motion.  Damping is required to remove energy added
     * through numerical instability in the integrator.
     */
    Real angularDamping;

    /**
     * Holds the linear position of the rigid body in
     * world space.
     */
    Vector3 position;

    /**
     * Holds the angular orientation of the rigid body in
     * world space.
     */
    Quaternion orientation;

    /**
     * Holds the linear velocity of the rigid body in
     * world space.
     */
    Vector3 velocity;

    /**
     * Holds the angular velocity, or rotation, or the
     * rigid body in world space.
     */
    Vector3 rotation;

    /**
     * @name Derived Data
     *
     * These data members hold information that is derived from
     * the other data in the class.
     */

    /**
     * Holds the inverse inertia tensor of the body in world
     * space. The inverse inertia tensor member is specified in
     * the body's local space.
     *
     * @see inverseInertiaTensor
     */
    Matrix3 inverseInertiaTensorWorld;

    /**
     * Holds the amount of motion of the body. This is a recency
     * weighted mean that can be used to put a body to sleap.
     */
    Real motion;

    /**
     * A body can be put to sleep to avoid it being updated
     * by the integration functions or affected by collisions
     * with the world.
     */
    bool isAwake;

    /**
     * Some bodies may never be allowed to fall asleep.
     * User controlled bodies, for example, should be
     * always awake.
     */
    bool canSleep;

    /**
     * Holds a transform matrix for converting body space into
     * world space and vice versa. This can be achieved by calling
     * the getPointIn*Space functions.
     *
     * @see getPointInLocalSpace
     * @see getPointInWorldSpace
     * @see getTransform
     */
    Matrix4 transformMatrix;

    /**
     * @name Force and Torque Accumulators
     *
     * These data members store the current force, torque and
     * acceleration of the rigid body. Forces can be added to the
     * rigid body in any order, and the class decomposes them into
     * their constituents, accumulating them for the next
     * simulation step. At the simulation step, the accelerations
     * are calculated and stored to be applied to the rigid body.
     */

    /**
     * Holds the accumulated force to be applied at the next
     * integration step.
     */
    Vector3 forceAccum;

    /**
     * Holds the accumulated torque to be applied at the next
     * integration step.
     */
    Vector3 torqueAccum;

   /**
     * Holds the acceleration of the rigid body.  This value
     * can be used to set acceleration due to gravity (its primary
     * use), or any other constant acceleration.
     */
    Vector3 acceleration;

    /**
     * Holds the linear acceleration of the rigid body, for the
     * previous frame.
     */
    Vector3 lastFrameAcceleration;
};

#endif
