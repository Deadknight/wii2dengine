#ifndef QUATERNION_H
#define QUATERNION_H

/**
 * Holds a three degree of freedom orientation. 
 *
 * Quaternions have
 * several mathematical properties that make them useful for
 * representing orientations, but require four items of data to
 * hold the three degrees of freedom. These four items of data can
 * be viewed as the coefficients of a complex number with three
 * imaginary parts. The mathematics of the quaternion is then
 * defined and is roughly correspondent to the math of 3D
 * rotations. A quaternion is only a valid rotation if it is
 * normalised: i.e. it has a length of 1.
 *
 * @note Angular velocity and acceleration can be correctly
 * represented as vectors. Quaternions are only needed for
 * orientation.
 */
class Quaternion
{
public:
    union {
        struct {
            /**
             * Holds the Real component of the quaternion.
             */
            Real r;

            /**
             * Holds the first complex component of the
             * quaternion.
             */
            Real i;

            /**
             * Holds the second complex component of the
             * quaternion.
             */
            Real j;

            /**
             * Holds the third complex component of the
             * quaternion.
             */
            Real k;
        };

        /**
         * Holds the quaternion data in array form.
         */
        Real data[4];
    };

    /**
     * The default constructor creates a quaternion representing
     * a zero rotation.
     */
    Quaternion() : r(1), i(0), j(0), k(0) {}

    /**
     * The explicit constructor creates a quaternion with the given
     * components.         
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
     * and can be zero. This function will not alter the given 
     * values, or normalise the quaternion. To normalise the 
     * quaternion (and make a zero quaternion a legal rotation),
     * use the normalise function.
     *
     * @see normalise
     */
    Quaternion(const Real r, const Real i, const Real j, const Real k) 
        : r(r), i(i), j(j), k(k) 
    {
    }
    
    /**
     * Normalises the quaternion to unit length, making it a valid
     * orientation quaternion.
     */
    void normalise()
    {
        Real d = r*r+i*i+j*j+k*k;

        // Check for zero length quaternion, and use the no-rotation
        // quaternion in that case.
        if (d == 0) { 
            r = 1; 
            return;
        }

        d = ((Real)1.0)/Real_sqrt(d);
        r *= d;
        i *= d;
        j *= d;
        k *= d;
    }

    /**
     * Multiplies the quaternion by the given quaternion.
     *
     * @param multiplier The quaternion by which to multiply.
     */
    void operator *=(const Quaternion &multiplier)
    {
        Quaternion q = *this;
        r = q.r*multiplier.r - q.i*multiplier.i - 
            q.j*multiplier.j - q.k*multiplier.k;
        i = q.r*multiplier.i + q.i*multiplier.r + 
            q.j*multiplier.k - q.k*multiplier.j;
        j = q.r*multiplier.j + q.j*multiplier.r + 
            q.k*multiplier.i - q.i*multiplier.k;
        k = q.r*multiplier.k + q.k*multiplier.r + 
            q.i*multiplier.j - q.j*multiplier.i;
    }

    /**
     * Adds the given vector to this, scaled by the given amount. 
     * This is used to update the orientation quaternion by a rotation
     * and time. 
     *
     * @param vector The vector to add.
     *
     * @param scale The amount of the vector to add.
     */
    void addScaledVector(const Vector3& vector, Real scale)
    {
        Quaternion q(0,
            vector.x * scale,
            vector.y * scale,
            vector.z * scale);
        q *= *this;
        r += q.r * ((Real)0.5);
        i += q.i * ((Real)0.5);
        j += q.j * ((Real)0.5);
        k += q.k * ((Real)0.5);
    }

    void rotateByVector(const Vector3& vector)
    {
        Quaternion q(0, vector.x, vector.y, vector.z);
        (*this) *= q;
    }

	inline void toEuler(Vector3& euler) const
	{
		const Real sqw = r*r;
		const Real sqx = i*i;
		const Real sqy = j*j;
		const Real sqz = k*k;

		// heading = rotation about z-axis
		euler.z = (Real) (atan2(2.0 * (i*j +k*r),(sqx - sqy - sqz + sqw)));

		// bank = rotation about x-axis
		euler.x = (Real) (atan2(2.0 * (j*k +i*r),(-sqx - sqy + sqz + sqw)));

		// attitude = rotation about y-axis
		euler.y = asinf( std::min(std::max(-2.0f * (i*k - j*r),-1.0f), 1.0f) );
	}
};

#endif