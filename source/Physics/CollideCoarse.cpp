#include "Stdafx.h"

BoundingSphere::BoundingSphere(const Vector3 &centre, Real radius)
{
    BoundingSphere::centre = centre;
    BoundingSphere::radius = radius;
}

BoundingSphere::BoundingSphere(const BoundingSphere &one, const BoundingSphere &two)
{
    Vector3 centreOffset = two.centre - one.centre;
    Real distance = centreOffset.squaredLength();
    Real radiusDiff = two.radius - one.radius;

    // Check if the larger sphere encloses the small one
    if (radiusDiff*radiusDiff >= distance)
    {
        if (one.radius > two.radius) 
        { 
            centre = one.centre;
            radius = one.radius;
        }
        else
        {
            centre = two.centre;
            radius = two.radius;
        }
    }

    // Otherwise we need to work with partially 
    // overlapping spheres
    else
    {
        distance = Real_sqrt(distance);
        radius = (distance + one.radius + two.radius) * ((Real)0.5);

        // The new centre is based on one's centre, moved towards
        // two's centre by an ammount proportional to the spheres'
        // radii.
        centre = one.centre;
        if (distance > 0)
        {
            centre += centreOffset * ((radius - one.radius)/distance);
        }
    }
    
}

bool BoundingSphere::Overlaps(const BoundingSphere *other) const
{
    Real distanceSquared = (centre - other->centre).squaredLength();
    return distanceSquared < (radius+other->radius)*(radius+other->radius);
}

Real BoundingSphere::GetGrowth(const BoundingSphere &other) const
{
    BoundingSphere newSphere(*this, other);

    // We return a value proportional to the change in surface
    // area of the sphere.
    return newSphere.radius*newSphere.radius - radius*radius;
}
