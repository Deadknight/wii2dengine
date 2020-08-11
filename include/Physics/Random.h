#ifndef _RANDOM_H
#define _RANDOM_H

/**
 * Keeps track of one random stream: i.e. a seed and its output.
 * This is used to get random numbers. Rather than a funcion, this
 * allows there to be several streams of repeatable random numbers
 * at the same time. Uses the RandRotB algorithm.
 */
class Random
{
public:

	/** 
	 * Creates a new random number stream with a seed based on
	 * timing data.
	 */
	Random();

	/** 
	 * Creates a new random stream with the given seed.
	 */
	Random(unsigned seed);
	
	~Random();

	/**
	 * Returns the next random bitstring from the stream. This is
	 * the fastest method.
	 */
	unsigned rotl(unsigned x);
	unsigned rotr(unsigned x);
	unsigned RandomBits();

	/**
	 * Returns a random floating point number between 0 and 1.
	 */
	Real RandomReal();

    /**
     * Returns a random floating point number between 0 and scale.
     */
    Real RandomReal(Real scale);

    /**
     * Returns a random floating point number between min and max.
     */
    Real RandomReal(Real min, Real max);

	/**
	 * Returns a random integer less than the given value.
	 */
	unsigned RandomInt(unsigned max);

	/**
	 * Returns a random binomially distributed number between -scale 
	 * and +scale.
	 */
	Real RandomBinomial(Real scale);

	/**
	 * Returns a random vector where each component is binomially
	 * distributed in the range (-scale to scale) [mean = 0.0f].
	 */
	Vector3 RandomVector(Real scale);

	/**
	 * Returns a random vector where each component is binomially
	 * distributed in the range (-scale to scale) [mean = 0.0f],
	 * where scale is the corresponding component of the given
	 * vector.
	 */
	Vector3 RandomVector(const Vector3 &scale);

    /**
     * Returns a random vector in the cube defined by the given
     * minimum and maximum vectors. The probability is uniformly
     * distributed in this region.
     */
    Vector3 RandomVector(const Vector3 &min, const Vector3 &max);

	/**
	 * Returns a random vector where each component is binomially
	 * distributed in the range (-scale to scale) [mean = 0.0f],
	 * except the y coordinate which is zero.
	 */
	Vector3 RandomXZVector(Real scale);

private:
	// Internal mechanics
	int p1, p2;
	unsigned buffer[17];
	MTRand *rand;
};

#endif // CYCLONE_BODY_H
