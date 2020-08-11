#ifndef _VECTOR3_H_
#define _VECTOR3_H_

/**
 * Holds the value for energy under which a body will be put to
 * sleep. This is a global value for the whole solution.  By
 * default it is 0.1, which is fine for simulation when gravity is
 * about 20 units per second squared, masses are about one, and
 * other forces are around that of gravity. It may need tweaking
 * if your simulation is drastically different to this.
 */
extern Real sleepEpsilon;

/**
 * Sets the current sleep epsilon value: the kinetic energy under
 * which a body may be put to sleep. Bodies are put to sleep if
 * they appear to have a stable kinetic energy less than this
 * value. For simulations that often have low values (such as slow
 * moving, or light objects), this may need reducing.
 *
 * The value is global; all bodies will use it.
 *
 * @see sleepEpsilon
 *
 * @see getSleepEpsilon
 *
 * @param value The sleep epsilon value to use from this point
 * on.
 */
void setSleepEpsilon(Real value);

/**
 * Gets the current value of the sleep epsilon parameter.
 *
 * @see sleepEpsilon
 *
 * @see setSleepEpsilon
 *
 * @return The current value of the parameter.
 */
Real getSleepEpsilon();

class Vector3
{
public:
	Real x, y, z;        

	inline Vector3() {}
	
	inline Vector3( Real nx, Real ny, Real nz ) : x(nx), y(ny), z(nz) {}
	
	inline Vector3( Real v[3] ) : x(v[0]), y(v[1]), z(v[2]) {}
	
	inline Vector3( int v[3] ): x((Real)v[0]), y((Real)v[1]), z((Real)v[2]) {}
	
	inline Vector3( const Real* const v ) : x(v[0]), y(v[1]), z(v[2]) {}
	
	inline Vector3( const Vector3& v ) : x(v.x), y(v.y), z(v.z) {}
	
	inline Real operator [] ( unsigned i ) const
	{
		return *(&x+i);
	}
	
	inline Real& operator [] ( unsigned i )
	{
		return *(&x+i);
	}
	
	inline Vector3& operator = ( const Vector3& v )
	{
		x = v.x;
		y = v.y;
		z = v.z;            
		
		return *this;
	}
	
	inline bool operator == ( const Vector3& v ) const
	{
		return ( x == v.x && y == v.y && z == v.z );
	}
	
	inline bool operator != ( const Vector3& v ) const
	{
		return ( x != v.x || y != v.y || z != v.z );
	}
	
	// arithmetic operations
	inline Vector3 operator + ( const Vector3& v ) const
	{		
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	
	inline Vector3 operator - ( const Vector3& v ) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	
	inline Vector3 operator * ( Real f ) const
	{
		return Vector3(x * f, y * f, z * f);
	}
	
	inline Vector3 operator * ( const Vector3& v) const
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}
	
	inline Vector3 operator / ( Real f ) const
	{
		f = 1.0f / f;		
		return Vector3(x * f, y * f, z * f);
	}
	
	inline Vector3 operator - () const
	{
		return Vector3( -x, -y, -z);
	}
	
	inline friend Vector3 operator * ( Real f, const Vector3& v )
	{
		return Vector3(f * v.x, f * v.y, f * v.z);
	}
	
	// arithmetic updates
	inline Vector3& operator += ( const Vector3& v )
	{
		x += v.x;
		y += v.y;
		z += v.z;
		
		return *this;
	}
	
	inline Vector3& operator -= ( const Vector3& v )
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		
		return *this;
	}
	
	inline Vector3& operator *= ( Real f )
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}
	
	inline Vector3& operator /= ( Real f )
	{
		f = 1.0f / f;
		
		x *= f;
		y *= f;
		z *= f;
		
		return *this;
	}
	
	inline void operator %=(const Vector3 &vector)
	{
		*this = vectorProduct(vector);
	}

	inline Vector3 operator%(const Vector3 &vector) const
	{
		return Vector3(y*vector.z-z*vector.y, 
					   z*vector.x-x*vector.z, 
					   x*vector.y-y*vector.x);
	}	
	
	void addScaledVector(const Vector3& vector, Real scale)
	{
		x += vector.x * scale;
		y += vector.y * scale;
		z += vector.z * scale;
	}
	
	inline Real length () const
	{
		return (Real)sqrt( x * x + y * y + z * z );
	}
	
	inline Real squaredLength () const
	{
		return x * x + y * y + z * z;
	}
	
	inline Real dotProduct(const Vector3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline Real scalarProduct(const Vector3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}	
	
	inline Vector3 & normalise()
	{
		Real f = (Real)sqrt( x * x + y * y + z * z );
		
		// Will also work for zero-sized vectors, but will change nothing
		if ( f > 1e-06f )
		{
			f = 1.0f / f;
			x *= f;
			y *= f;
			z *= f;
		}
		
		return *this;
	}
	
	inline Vector3 vectorProduct( const Vector3& v ) const
	{
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}	
	
	inline Vector3 crossProduct( const Vector3& v ) const
	{
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	
	inline Vector3 componentProduct(const Vector3 &v) const
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}
	
	inline void ComponentProductUpdate(const Vector3 &vector)
	{
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
	}	
	
	inline Vector3 midPoint( const Vector3& v ) const
	{
		return Vector3( ( x + v.x ) * 0.5f, ( y + v.y ) * 0.5f, ( z + v.z ) * 0.5f );
	}
	
	inline bool operator < ( const Vector3& v ) const
	{
		return ( x < v.x && y < v.y && z < v.z );
	}
	
	inline bool operator > ( const Vector3& v ) const
	{
		return ( x > v.x && y > v.y && z > v.z );
	}
	
	inline void makeFloor( const Vector3& v )
	{
		if( v.x < x ) x = v.x;
		if( v.y < y ) y = v.y;
		if( v.z < z ) z = v.z;
	}
	
	inline void makeCeil( const Vector3& v )
	{
		if( v.x > x ) x = v.x;
		if( v.y > y ) y = v.y;
		if( v.z > z ) z = v.z;
	}
	
	inline Vector3 perpendicular(void)
	{
		static Real fSquareZero = 1e-06f * 1e-06f;
		
		Vector3 perp = this->crossProduct( Vector3::UNIT_X );
		
		// Check length
		if( perp.squaredLength() < fSquareZero )
		{
		/* This vector is the Y axis multiplied by a scalar, so we have 
		to use another axis.
			*/
			perp = this->crossProduct( Vector3::UNIT_Y );
		}
		
		return perp;
	}
	
	inline void clear() 
	{ 
		x = y = z = 0;
	}

	/** Flips all the components of the vector. */
	inline void invert()
	{
		x = -x;
		y = -y;
		x = -z;
	}	
	
	// special points
	static const Vector3 ZERO;
	static const Vector3 UNIT_X;
	static const Vector3 UNIT_Y;
	static const Vector3 UNIT_Z;
	static const Vector3 UNIT_SCALE;
	static const Vector3 GRAVITY;
	static const Vector3 HIGH_GRAVITY;
	static const Vector3 UP;
	static const Vector3 RIGHT;
	static const Vector3 OUT;
	static const Vector3 X;
	static const Vector3 Y;
	static const Vector3 Z;
};

#endif // _VECTOR3_H_

