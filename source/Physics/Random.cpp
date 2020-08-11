#include "Stdafx.h"

Random::Random()
{
	rand = new MTRand();
}

Random::Random(unsigned seed)
{
	rand = new MTRand(seed);
}

Random::~Random()
{
	delete rand;
}

unsigned Random::rotl(unsigned x)
{ 
	return (x << 1) | (x / (-1u/2+1));
}

unsigned Random::rotr(unsigned x)
{
	return (x >> 1) | (x * (-1u/2+1));
}

unsigned Random::RandomBits()
{
    unsigned result = 0;

    // Rotate the buffer and store it back to itself
    //result = buffer[p1] = _lrotl(buffer[p2], 13) + _lrotl(buffer[p1], 9);
	//result = buffer[p1] = rotl(buffer[p2], 13) + rotl(buffer[p1], 9);

    // Rotate pointers
    /*if (--p1 < 0) p1 = 16;
    if (--p2 < 0) p2 = 16;*/

    // Return result*/
    return result;
}

#ifdef SINGLE_PRECISION
Real Random::randomReal()
{
	return rand->rand();
}
#else
Real Random::RandomReal()
{
	return rand->rand();
}
#endif

Real Random::RandomReal(Real min, Real max)
{
    return rand->rand() * (max-min) + min;
}

Real Random::RandomReal(Real scale)
{
    return rand->rand() * scale;
}

unsigned Random::RandomInt(unsigned max)
{
	if(max == 0)
		return rand->randInt();
	else
		return rand->randInt(max);
}

Real Random::RandomBinomial(Real scale)
{
	return (RandomReal()-RandomReal())*scale;
}

Vector3 Random::RandomVector(Real scale)
{
	return Vector3(
        RandomBinomial(scale),
        RandomBinomial(scale),
        RandomBinomial(scale)
        );
}

Vector3 Random::RandomXZVector(Real scale)
{
	return Vector3(
        RandomBinomial(scale),
        0,
        RandomBinomial(scale)
        );
}

Vector3 Random::RandomVector(const Vector3 &scale)
{
	return Vector3(
        RandomBinomial(scale.x),
        RandomBinomial(scale.y),
        RandomBinomial(scale.z)
        );
}

Vector3 Random::RandomVector(const Vector3 &min, const Vector3 &max)
{
    return Vector3(
        RandomReal(min.x, max.x),
        RandomReal(min.y, max.y),
        RandomReal(min.z, max.z)
        );
}
