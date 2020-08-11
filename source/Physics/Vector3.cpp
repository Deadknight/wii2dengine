#include "Stdafx.h"

const Vector3 Vector3::ZERO( 0, 0, 0 );
const Vector3 Vector3::UNIT_X( 1, 0, 0 );
const Vector3 Vector3::UNIT_Y( 0, 1, 0 );
const Vector3 Vector3::UNIT_Z( 0, 0, 1 );
const Vector3 Vector3::UNIT_SCALE(1, 1, 1);
const Vector3 Vector3::GRAVITY = Vector3(0, -9.81, 0);
const Vector3 Vector3::HIGH_GRAVITY = Vector3(0, -19.62, 0);
const Vector3 Vector3::UP = Vector3(0, 1, 0);
const Vector3 Vector3::RIGHT = Vector3(1, 0, 0);
const Vector3 Vector3::OUT = Vector3(0, 0, 1);
const Vector3 Vector3::X = Vector3(0, 1, 0);
const Vector3 Vector3::Y = Vector3(1, 0, 0);
const Vector3 Vector3::Z = Vector3(0, 0, 1);

/*
 * Definition of the sleep epsilon extern.
 */
Real sleepEpsilon = ((Real)0.3);

/*
 * Functions to change sleepEpsilon.
 */
void setSleepEpsilon(Real value)
{
    sleepEpsilon = value;
}

Real getSleepEpsilon()
{
    return sleepEpsilon;
}
