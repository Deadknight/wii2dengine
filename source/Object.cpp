#include "Stdafx.h"

Object::Object()
{
	cp = NULL;
}

Object::~Object()
{
}

void Object::Init(const char* name, uint32 entry)
{
	SetEntry(entry);
}

void Object::InitPhysics(SpriteProp *prop)
{
	switch(prop->physicsObjectType)
	{
	case PPT_POINT:
		{
			cp = new CollisionPoint();
			//cp->GetPhysicObject()->SetPosition(prop->x, prop->y, 0);
		}break;
	case PPT_BOX:
		{
			Real halfX = ceil(((Real)prop->physicsWidth)/2.0f);
			Real halfY = ceil(((Real)prop->physicsHeight)/2.0f);

			cp = new CollisionBox();
			//cp->GetPhysicObject()->SetPosition(prop->x + halfX, prop->y + halfY, 0);
			CollisionBox *cb = static_cast<CollisionBox*>(cp);
			cb->halfSize.x = halfX;
			cb->halfSize.y = halfY;
			cb->halfSize.z = 0;
			sLog.outString(LOGTYPE_ALL, LOGLEVEL_DEBUG, "Loading box physics %f,%f\r\n", cb->halfSize.x, cb->halfSize.y);
			
		}break;
	case PPT_SPHERE:
		{
			Real radius = 0;
			Real halfRadius = 0;
			//Try to fix inconvenient values
			if(prop->physicsWidth > prop->physicsHeight)
				radius = prop->physicsWidth;
			else
				radius = prop->physicsHeight;

			halfRadius = radius / 2;

			cp = new CollisionSphere();
			//cp->GetPhysicObject()->SetPosition(prop->x, prop->y, 0);
			CollisionSphere *cs = static_cast<CollisionSphere*>(cp);
			cs->radius = radius;
			sLog.outString(LOGTYPE_ALL, LOGLEVEL_DEBUG, "Loading sphere physics %f\r\n", radius);
		}break;
	case PPT_PLANE:
		{
			//No support for planes now
		}break;
	default:
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Cannot load collision primitve\r\n");
		break;
	};
	
	if(cp)
	{
		cp->SetOwner(this);
		cp->GetPhysicObject()->SetCanSleep(false);
		cp->GetPhysicObject()->SetDamping(0.995f, 0.995f);
		cp->GetPhysicObject()->SetDamping(0.995f);
		SetPosition(localPos);
		sPhysicsMgr.AddPhysicsObject(cp);
		//We dont want units to move
		if(m_objectType == TYPE_PLAYER || m_objectType == TYPE_UNIT)
			cp->SetAllowedToHandleCollision(false);
	}
}

void Object::Draw(int32 x, int32 y)
{
}

Vector3 Object::GetPosition()
{
	if(cp != NULL)
		return cp->GetPhysicObject()->GetPosition();
	else
		return localPos;
}

void Object::SetPosition(Vector3 pos)
{
	if(cp != NULL)
		cp->GetPhysicObject()->SetPosition(pos);
	else
		localPos = pos;
}

void Object::SetPosition(int32 x, int32 y, int32 z)
{
	if(cp != NULL)
		cp->GetPhysicObject()->SetPosition(x, y, z);
	else
	{
		localPos.x = x;
		localPos.y = y;
		localPos.z = z;
	}
}

Real Object::GetRotation()
{
	if(cp != NULL)
		return cp->GetPhysicObject()->GetRotation().z;
	
	return 0;
}

void Object::SetRotation(Real rot)
{
	if(cp != NULL)
		cp->GetPhysicObject()->SetRotation(0, 0, rot);
}

float Object::CalcAngle( float Position1X, float Position1Y, float Position2X, float Position2Y )
{
    float dx = Position2X-Position1X;
    float dy = Position2Y-Position1Y;
    double angle= 0.0f;
    // Calculate angle
    if (dx == 0.0)
    {
        if (dy == 0.0)
            angle = 0.0;
        else if (dy > 0.0)
            angle = M_PI * 0.5 /* / 2 */;
        else
            angle = M_PI * 3.0 * 0.5/* / 2 */;
    }
    else if (dy == 0.0)
    {
        if (dx > 0.0)
            angle = 0.0;
        else
            angle = M_PI;
    }
    else
    {
		if (dx < 0.0)
			angle = atanf(dy/dx) + M_PI;
		else if (dy < 0.0)
			angle = atanf(dy/dx) + (2*M_PI);
		else
			angle = atanf(dy/dx);
    }
    // Convert to degrees
    angle = angle * float(180 / M_PI);
    // Return
    return float(angle);
}

float Object::CalcRadAngle( float Position1X, float Position1Y, float Position2X, float Position2Y )
{
    double dx = double(Position2X-Position1X);
    double dy = double(Position2Y-Position1Y);
    double angle= 0.0;
    // Calculate angle
    if (dx == 0.0)
    {
        if (dy == 0.0)
            angle = 0.0;
        else if (dy > 0.0)
            angle = M_PI * 0.5/*/ 2.0*/;
        else
            angle = M_PI * 3.0 * 0.5/*/ 2.0*/;
    }
    else if (dy == 0.0)
    {
        if (dx > 0.0)
            angle = 0.0;
        else
            angle = M_PI;
    }
    else
    {
        if (dx < 0.0)
            angle = atan(dy/dx) + M_PI;
        else if (dy < 0.0)
            angle = atan(dy/dx) + (2*M_PI);
        else
            angle = atan(dy/dx);
    }
    // Return
    return float(angle);
}

float Object::GetEasyAngle( float angle )
{
    while ( angle < 0 ) {
        angle = angle + 360;
    }
    while ( angle >= 360 ) {
        angle = angle - 360;
    }
    return angle;
}

bool Object::inArc(float Position1X, float Position1Y, float FOV, float Orientation, float Position2X, float Position2Y )
{
    float angle = CalcAngle( Position1X, Position1Y, Position2X, Position2Y );
    float lborder = GetEasyAngle( ( Orientation - (FOV*0.5f/*/2*/) ) );
    float rborder = GetEasyAngle( ( Orientation + (FOV*0.5f/*/2*/) ) );
    //sLog.outDebug("Orientation: %f Angle: %f LeftBorder: %f RightBorder %f",Orientation,angle,lborder,rborder);
    if(((angle >= lborder) && (angle <= rborder)) || ((lborder > rborder) && ((angle < rborder) || (angle > lborder))))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Object::IsInFront(Object* target)
{
    return true;
}

bool Object::IsInBack(Object* target)
{
    return true;
}

bool Object::isInArc(Object* target , float angle, float orientationAngle) // angle in degrees
{
	Vector3 pos = GetPosition();
	Vector3 tPos = target->GetPosition();
    return inArc( pos.x , pos.y , angle , orientationAngle , tPos.x , tPos.y );
}

bool Object::HasInArc( float degrees, float orientationAngle, Object* target )
{
    return isInArc(target, degrees, orientationAngle);
}
