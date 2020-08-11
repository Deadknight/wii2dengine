#include "Stdafx.h"

extern WPads Wiimote[WPAD_MAX_WIIMOTES];
extern Nunchuks Nunchuk[WPAD_MAX_WIIMOTES];
extern CPads CPad[WPAD_MAX_WIIMOTES];
extern GH Guitar[WPAD_MAX_WIIMOTES];
extern GC_Pads Pad[4];

Player::Player(uint64 guid)
{
	m_objectType = TYPE_PLAYER;
	m_valuesCount = PLAYER_END;
	m_uint32Values = _fields;
	memset(m_uint32Values, 0, (PLAYER_END) * sizeof(uint32));
	SetGUID(guid);
	SpriteProp prop;
	cursor = sResourceMgr.GetSpriteByName("crosshair", &prop, MEMORY_PERMANENT);
}

Player::~Player()
{

}

void Player::Init(const char* name, uint32 entry)
{
	Unit::Init(name, entry);
	if(cp && cp->GetPhysicObject())
	{
		cp->GetPhysicObject()->SetInverseMass(0);
		cp->GetPhysicObject()->SetDamping(0, 0);
		cp->SetCollisionFlag(COLLISION_FLAG_PLAYER);
	}
	ScriptSystem->OnPlayerEvent(this, PLAYER_EVENT_INIT, 0);
	sLuaMgr.OnPlayerEvent(this, PLAYER_EVENT_INIT, 0);
}

void Player::Update(Real duration)
{
	GType val(MYTYPE_FLOAT, &duration);
	ScriptSystem->OnPlayerEvent(this, PLAYER_EVENT_UPDATE, 1, &val);
	sLuaMgr.OnPlayerEvent(this, PLAYER_EVENT_UPDATE, 1, &val);	
	UpdateControllers();
	UpdateMovement(duration);

	Unit::Update(duration);
}

void Player::UpdateControllers()
{
	m_flag = 0;
	uint32 m_playerId = GetLowGUID();
	//Nunchuck
	if(Nunchuk[m_playerId].Held.C)
	{
		sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "Crouch\r\n");
		m_flag |= MOVEMENT_FLAG_CROUCH;
	}
	else if(Nunchuk[m_playerId].Held.Z)
		m_flag |= MOVEMENT_FLAG_JUMP;
	
	if(Nunchuk[m_playerId].Stick.Magnitude > 0.3)
	{
		if(Nunchuk[m_playerId].Stick.Angle > 70.0f && Nunchuk[m_playerId].Stick.Angle < 110.0f)
			m_flag |= MOVEMENT_FLAG_RIGHT;
		else if(Nunchuk[m_playerId].Stick.Angle > 160.0f && Nunchuk[m_playerId].Stick.Angle < 200.0f)
			m_flag |= MOVEMENT_FLAG_DOWN;
		else if(Nunchuk[m_playerId].Stick.Angle > 250.0f && Nunchuk[m_playerId].Stick.Angle < 290.0f)
			m_flag |= MOVEMENT_FLAG_LEFT;
		else if(Nunchuk[m_playerId].Stick.Angle > -20.0f && Nunchuk[m_playerId].Stick.Angle < 20.0f)
			m_flag |= MOVEMENT_FLAG_UP;
		else
			m_flag |= MOVEMENT_FLAG_IDLE;
	}
	else
		m_flag |= MOVEMENT_FLAG_IDLE;
		
	//If we are not jumping or crouching
	if(!(m_flag & MOVEMENT_FLAG_CROUCH || m_flag & MOVEMENT_FLAG_JUMP))
	{
		if(Nunchuk[m_playerId].Stick.Magnitude > 0.3)
			m_flag |= MOVEMENT_FLAG_RUN;
		else
			m_flag |= MOVEMENT_FLAG_WALK;
	}

	//Wiimote update
	//if(Wiimote[m_playerId].Held.Home) { ML_ReturnToWii(); }
	if(Wiimote[m_playerId].Held.A) { /*sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "A pressed\r\n");*/ m_flag |= STATE_RELOADING; }
	if(Wiimote[m_playerId].Held.B) { /*sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "Fire pressed\r\n");*/ m_flag |= STATE_FIREING; }
	if(Wiimote[m_playerId].Held.One) { sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "1 pressed\r\n"); }
	if(Wiimote[m_playerId].Held.Two) { sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "2 pressed\r\n");; }
	if(Wiimote[m_playerId].Held.Plus) { sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "+ pressed\r\n"); }
	if(Wiimote[m_playerId].Held.Minus) { sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "- pressed\r\n"); }
	if(Wiimote[m_playerId].Held.Left) { sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "Left pressed\r\n"); }
	if(Wiimote[m_playerId].Held.Right) { sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "Right pressed\r\n"); }
	if(Wiimote[m_playerId].Held.Up) { sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "Up pressed\r\n"); }
	if(Wiimote[m_playerId].Held.Down) { sLog.outString(LOGTYPE_CONSOLE, LOGLEVEL_ERROR, "Down pressed\r\n"); }

	//Calculate upper body and look position
	//simple check for now add cotan calculation later
	//cursor x1,y1 and player virtual x0,y0
	//       ------- x1,y1
	//       |-   /
	//       |   /            x1-x0/y1-y0 = tan(x)
	//       |  /
	//       | /
	//x0, y0 |/

	Real cursorX = Wiimote[m_playerId].IR.X;
	Real cursorY = Wiimote[m_playerId].IR.Y;
	Vector3 playerPosReal = GetPosition();
	int32 playerPosVirtualX = 0;
	int32 playerPosVirtualY = 0;
	sMap.CheckInView(playerPosReal.x, playerPosReal.y, &playerPosVirtualX, &playerPosVirtualY);
	m_direction.x = cursorX - playerPosVirtualX;
	m_direction.y = cursorY - playerPosVirtualY;
	m_direction.z = 0;
	if(cursorX > playerPosVirtualX)
	{
		if(cursorY == playerPosVirtualY)
		{
			m_flag |= LOOK_POSITION_E;
		}
		else if(cursorY > playerPosVirtualY)
		{
			m_flag |= LOOK_POSITION_SE;
		}
		else
		{
			m_flag |= LOOK_POSITION_NE;
		}
	}
	else if(cursorX == playerPosVirtualX)
	{
		if(cursorY == playerPosVirtualY)
		{
			//This is center search for it
			m_flag |= LOOK_POSITION_W;
		}
		else if(cursorY > playerPosVirtualY)
		{
			m_flag |= LOOK_POSITION_S;
		}
		else
		{
			m_flag |= LOOK_POSITION_N;
		}
	}
	else
	{
		
		if(cursorY == playerPosVirtualY)
		{
			m_flag |= LOOK_POSITION_W;
		}
		else if(cursorY > playerPosVirtualY)
		{
			m_flag |= LOOK_POSITION_SW;
		}
		else
		{
			m_flag |= LOOK_POSITION_NW;
		}
	}

	//Render cursor
	ML_MoveSpriteWiimoteIR(cursor, m_playerId);
	ML_RotateSprite(cursor, Wiimote[m_playerId].Orient.Roll, 0);
	ML_DrawSprite(cursor);
}

void Player::UpdateMovement(Real duration)
{
	int delta = duration * m_runSpeed;
	Vector3 pos = GetPosition();
	if(m_flag & MOVEMENT_FLAG_RIGHT)
	{
		pos.x += delta;
	}
	else if(m_flag & MOVEMENT_FLAG_LEFT)
	{
		pos.x -= delta;
	}
	SetPosition(pos.x, pos.y, pos.z);
}

void Player::OnCollide(CollisionPrimitive *cpTarget)
{
	GType val(MYTYPE_OBJECT, cpTarget->GetOwner());
	ScriptSystem->OnPlayerEvent(this, PLAYER_EVENT_ON_COLLIDE, 1, &val);
	sLuaMgr.OnPlayerEvent(this, PLAYER_EVENT_ON_COLLIDE, 1, &val);
}
