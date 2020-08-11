#include "Stdafx.h"

class ScriptEngine;

AIInterface::AIInterface()
{
}

AIInterface::~AIInterface()
{
}

void AIInterface::Init(Unit *un, AI_Type at, MovementType mt)
{
    m_AIType = at;
    m_moveType = mt;
    m_AIState = STATE_IDLE;
    m_Unit = un;
    /*m_walkSpeed = m_Unit->m_walkSpeed*0.001f;//move distance per ms time
    m_runSpeed = m_Unit->m_runSpeed*0.001f;//move distance per ms time
    m_flySpeed = m_Unit->m_flySpeed*0.001f;*/
	m_walkSpeed = m_Unit->m_walkSpeed;
	m_runSpeed = m_Unit->m_runSpeed;
	m_flySpeed = m_Unit->m_flySpeed;
	Vector3 pos = un->GetPosition();
    m_sourceX = pos.x;
    m_sourceY = pos.y;
}

void AIInterface::Init(Unit *un, AI_Type at, MovementType mt, Unit *owner)
{
    m_AIType = at;
    m_moveType = mt;
    m_AIState = STATE_IDLE;
    m_Unit = un;
    m_PetOwner = owner;
    /*m_walkSpeed = m_Unit->m_walkSpeed*0.001f;//move distance per ms time
    m_runSpeed = m_Unit->m_runSpeed*0.001f;//move/ms
    m_flySpeed = m_Unit->m_flySpeed*0.001f;*/
	m_walkSpeed = m_Unit->m_walkSpeed;//move distance per ms time
    m_runSpeed = m_Unit->m_runSpeed;//move/ms
    m_flySpeed = m_Unit->m_flySpeed;
 	Vector3 pos = un->GetPosition();
    m_sourceX = pos.x;
    m_sourceY = pos.y;
}

void AIInterface::HandleEvent(uint32 event, Unit *pUnit, uint32 misc)
{
	if(!m_Unit)
		return;

	if(m_AIType == AITYPE_PASSIVE)
		return;

	if(m_AIState != STATE_EVADE)
	{
		switch(event)
		{
		case EVENT_ENTERCOMBAT:
			{
				if( pUnit == NULL || pUnit->IsDead() || m_Unit->IsDead() ) 
					return;
					
				if(m_Unit->GetType() == TYPE_UNIT)
				{
					if(pUnit->GetType() == TYPE_UNIT)
					{
						GType target(MYTYPE_CREATURE, pUnit);
						ScriptSystem->OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_COMBAT_START, 1, &target);
						sLuaMgr.OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_COMBAT_START, 1, &target);
					}
				}

				if(m_AIState != STATE_ATTACKING)
                    StopMovement(0);

				m_AIState = STATE_ATTACKING;

				if (pUnit->IsPlayer())
				{
						m_Unit->GetAIInterface()->ModThreatByPtr(pUnit, 1);
						/*Group *pGroup = static_cast<Player*>(pUnit)->GetGroup();
						Player *pGroupGuy;
						GroupMembersSet::iterator itr;
						pGroup->Lock();
						for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++) {
								for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
								{
										pGroupGuy = (*itr)->m_loggedInPlayer;
										if( pGroupGuy && pGroupGuy->isAlive() && m_Unit->GetMapMgr() == pGroupGuy->GetMapMgr() && pGroupGuy->GetDistanceSq(pUnit) <= 40*40) //50 yards for now. lets see if it works
										{
												m_Unit->GetAIInterface()->AttackReaction(pGroupGuy, 1, 0);
										}
								}
						}
						pGroup->Unlock();*/
				}
			}break;
		case EVENT_LEAVECOMBAT:
			{
				Unit *target;
				target = FindTarget();
				if(target)
				{
					AttackReaction(target, 1);
					return;
				}

				ADDFLAG(m_movementSpeedFlag,MOVEMENT_SPEED_SPRINT);
                LockAITargets(true);
                m_aiTargets.clear();
                LockAITargets(false);
				SetNextTarget( (Unit*)NULL );
				//m_Unit->CombatStatus.Vanished();

                if(m_AIType == AITYPE_PET)
                {
                    m_AIState = STATE_FOLLOWING;
                    UnitToFollow = m_PetOwner;
                    FollowDistance = 3.0f;
                    m_lastFollowX = m_lastFollowY = 0;
                    HandleEvent(EVENT_FOLLOWOWNER, 0, 0);
                }
                else
                {
                    m_AIState = STATE_EVADE;
                    /*Unit* SavedFollow = UnitToFollow;
                    UnitToFollow = NULL;
                    FollowDistance = 0.0f;
                    m_lastFollowX = m_lastFollowY = 0;
                    if(m_Unit->isAlive())
                    {
                            if(m_returnX != 0.0f && m_returnY != 0.0f && m_returnZ != 0.0f)
                                    MoveTo(m_returnX,m_returnY,m_returnZ,m_Unit->GetSpawnO());
                            else
                            {
                                    MoveTo(m_Unit->GetSpawnX(),m_Unit->GetSpawnY(),m_Unit->GetSpawnZ(),m_Unit->GetSpawnO());
                                    m_returnX=m_Unit->GetSpawnX();
                                    m_returnY=m_Unit->GetSpawnY();
                                    m_returnZ=m_Unit->GetSpawnZ();
                            }
                            Creature *aiowner = static_cast<Creature*>(m_Unit);
                            //clear tagger.
                            aiowner->Tagged = false;
                            aiowner->TaggerGuid = 0;
                            aiowner->SetUInt32Value(UNIT_DYNAMIC_FLAGS,aiowner->GetUInt32Value(UNIT_DYNAMIC_FLAGS) & ~(U_DYN_FLAG_TAGGED_BY_OTHER |U_DYN_FLAG_LOOTABLE));
                            aiowner->m_lootMethod = -1;
                    }*/
					if(m_Unit->GetType() == TYPE_UNIT)
					{
						ScriptSystem->OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_COMBAT_STOP, 0);
						sLuaMgr.OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_COMBAT_STOP, 0);
					}
                }
			}break;
        case EVENT_DAMAGETAKEN:
            {
				if(m_Unit->GetType() == TYPE_UNIT)
				{
					GType dam(MYTYPE_FLOAT, &misc);
					ScriptSystem->OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_DAMAGE_TAKEN, 0, &dam);
					sLuaMgr.OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_DAMAGE_TAKEN, 0, &dam);
				}
                if(!ModThreatByPtr(pUnit, misc))
                {
                    m_aiTargets.insert(TargetMap::value_type(pUnit->GetGUID(), misc));
                }
                //pUnit->CombatStatus.OnDamageDealt( m_Unit );
            }break;
		case EVENT_FOLLOWOWNER:
			{
                m_AIState = STATE_FOLLOWING;
                /*if(m_Unit->IsPet())
                        ((Pet*)m_Unit)->SetPetAction(PET_ACTION_FOLLOW);*/
                UnitToFollow = m_PetOwner;
                m_lastFollowX = m_lastFollowY = 0;
                FollowDistance = 4.0f;
                LockAITargets(true);
                m_aiTargets.clear();
                LockAITargets(false);
                SetNextTarget( (Unit*)NULL );
				m_movementSpeedFlag |= MOVEMENT_SPEED_RUN;
			}break;
		case EVENT_FEAR:
			{
                m_FearTimer = 0;
                SetUnitToFear(pUnit);
				if(m_Unit->GetType() == TYPE_UNIT)
				{
					if(pUnit->GetType() == TYPE_PLAYER)
					{
						GType plr(MYTYPE_PLAYER, pUnit);
						int val = 0;
						GType gVal(MYTYPE_INT, &val);
						ScriptSystem->OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_DAMAGE_TAKEN, 2, &plr, &gVal);
						sLuaMgr.OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_DAMAGE_TAKEN, 2, &plr, &gVal);
					}
					else
					{
						GType cre(MYTYPE_CREATURE, pUnit);
						int val = 0;
						GType gVal(MYTYPE_INT, &val);
						ScriptSystem->OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_DAMAGE_TAKEN, 2, &cre, &gVal);
						sLuaMgr.OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_DAMAGE_TAKEN, 2, &cre, &gVal);
					}
				}
                m_AIState = STATE_FEAR;
                StopMovement(1);
                UnitToFollow_backup = UnitToFollow;
                UnitToFollow = NULL;
                m_lastFollowX = m_lastFollowY = 0;
                FollowDistance_backup = FollowDistance;
                FollowDistance = 0.0f;
                LockAITargets(true);
                m_aiTargets.clear();
                LockAITargets(false);
				m_movementSpeedFlag |= MOVEMENT_SPEED_RUN;
                SetNextTarget( (Unit*)NULL);
			}break;
		case EVENT_UNFEAR:
			{
                UnitToFollow = UnitToFollow_backup;
                FollowDistance = FollowDistance_backup;
                m_AIState = STATE_IDLE;
                SetUnitToFear(NULL);
                StopMovement(1);
			}break;
		case EVENT_WANDER:
			{
                m_WanderTimer = 0;
                m_AIState = STATE_WANDER;
                StopMovement(1);
                UnitToFollow_backup = UnitToFollow;
                UnitToFollow = NULL;
                m_lastFollowX = m_lastFollowY = 0;
                FollowDistance_backup = FollowDistance;
                FollowDistance = 0.0f;
                LockAITargets(true);
                m_aiTargets.clear();
                LockAITargets(false);
				m_movementSpeedFlag |= MOVEMENT_SPEED_RUN;
                SetNextTarget( (Unit*)NULL );
			}break;
		case EVENT_UNWANDER:
			{
				UnitToFollow = UnitToFollow_backup;
				FollowDistance = FollowDistance_backup;
				m_AIState = STATE_IDLE;
				StopMovement(1);
			}break;
		default:
			break;
		};
	}

    switch(event)
    {
        case EVENT_UNITDIED:
        {
			if(m_Unit->GetType() == TYPE_UNIT)
			{
				if (pUnit->GetType() == TYPE_PLAYER)
				{
					GType plr(MYTYPE_PLAYER, pUnit);
					ScriptSystem->OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_DIED, 1, &plr);
					sLuaMgr.OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_DIED, 1, &plr);
				}
				else
				{
					GType cre(MYTYPE_CREATURE, pUnit);
					ScriptSystem->OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_DIED, 1, &cre);
					sLuaMgr.OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_DIED, 1, &cre);
				}
			}
            m_AIState = STATE_IDLE;
            StopMovement(0);
            LockAITargets(true);
            m_aiTargets.clear();
            LockAITargets(false);
            UnitToFollow = NULL;
            UnitToFear = NULL;
            FollowDistance = 0.0f;
            SetNextTarget( (Unit*)NULL );
   
            m_currentWaypoint = 0;
        }break;
    }
}

void AIInterface::Update(Real time)
{
    _UpdateTimer(time);
    _UpdateTargets();
    if(m_Unit->IsAlive() && m_AIState != STATE_IDLE
            && m_AIState != STATE_FOLLOWING && m_AIState != STATE_FEAR
            && m_AIState != STATE_WANDER && m_AIState != STATE_SCRIPTMOVE)
    {
        if(m_AIType == AITYPE_PET )
        {
            /*if(!m_Unit->bInvincible && m_Unit->IsPet()) 
            {
                    Pet * pPet = static_cast<Pet*>(m_Unit);

                    if(pPet->GetPetAction() == PET_ACTION_ATTACK || pPet->GetPetState() != PET_STATE_PASSIVE)
                    {
                            _UpdateCombat(p_time);
                    }
            }
            //we just use any creature as a pet guardian
            else if(!m_Unit->IsPet())
            {
                    _UpdateCombat(p_time);
            }*/
        }
        else
        {
            _UpdateCombat(time);
        }
    }
    _UpdateMovement(time);
    /*if(m_AIState==STATE_EVADE)
    {
        tdist = m_Unit->GetDistanceSq(m_returnX,m_returnY,m_returnZ);
        if(tdist <= 4.0f)
        {
            m_AIState = STATE_IDLE;
            m_returnX = m_returnY = m_returnZ = 0.0f;
			m_movementSpeedFlag |= MOVEMENT_SPEED_RUN;
            // Set health to full if they at there last location before attacking
            if(m_AIType != AITYPE_PET && !skip_reset_hp)
                m_Unit->SetHealth(m_Unit->GetMaxHealth());
        }
        else
        {
            if( m_creatureState == STOPPED )
            {
                // return to the home
                if( m_returnX == 0.0f && m_returnY == 0.0f )
                {
                    m_returnX = m_Unit->GetSpawnX();
                    m_returnY = m_Unit->GetSpawnY();
                    m_returnZ = m_Unit->GetSpawnZ();
                }
                MoveTo(m_returnX, m_returnY);
            }
        }
    }
    if(m_fleeTimer)
    {
        if(m_fleeTimer > time)
        {
            m_fleeTimer -= time;
            _CalcDestinationAndMove(GetNextTarget(), 5.0f);
        }
        else
        {
            m_fleeTimer = 0;
            SetNextTarget(FindTargetForSpell(m_nextSpell));
        }
    }*/
}

void AIInterface::_UpdateTimer(Real time)
{
	//Target Timer
    if(m_updateTargetsTimer > time)
    {
        m_updateTargetsTimer -= time;
    }
	else
    {
        m_updateTargets = true;
        m_updateTargetsTimer = TARGET_UPDATE_INTERVAL_ON_PLAYER * 2 - m_updateTargetsTimer - time;
    }
}

void AIInterface::_UpdateTargets()
{
    if( m_Unit->IsPlayer() || (m_AIType != AITYPE_PET && (m_combatFlag & CF_DISABLE_TARGETING)))
            return;
			
    TargetMap::iterator itr, it2;
    // Find new Assist Targets and remove old ones
    if(m_AIState == STATE_FLEEING)
    {
		FindFriends(100.0f/*10.0*/);
    }
    else if(m_AIState != STATE_IDLE && m_AIState != STATE_SCRIPTIDLE)
    {
        FindFriends(64.0f/*8.0f*/);
    }
    if( m_updateTargets )
    {
        m_updateTargets = false;
        LockAITargets(true);
        for(itr = m_aiTargets.begin(); itr != m_aiTargets.end();)
        {
            it2 = itr++;
            Unit *ai_t = sMap.GetUnit( it2->first );
            if (ai_t == NULL)
			{
                m_aiTargets.erase( it2 );
            } 
			else 
			{
                if(!ai_t->IsAlive() || (m_Unit->GetDistanceSq(ai_t) >= 6400.0f)) {
                        m_aiTargets.erase( it2 );
                }
            }
        }
        LockAITargets(false);
       
        /*if(m_aiTargets.size() == 0 
            && m_AIState != STATE_IDLE && m_AIState != STATE_FOLLOWING
            && m_AIState != STATE_EVADE && m_AIState != STATE_FEAR
            && m_AIState != STATE_WANDER && m_AIState != STATE_SCRIPTIDLE)
        {
            Unit* target = NULL;
            if (m_outOfCombatRange && _CalcDistanceFromHome() < m_outOfCombatRange)
                target = FindTarget();

            if(target != NULL)
                AttackReaction(target, 1, 0);
        }
        else-*/ if(m_aiTargets.size() == 0 && (m_AIType == AITYPE_PET && ((m_Unit->IsPet() && static_cast<Pet*>(m_Unit)->GetPetState() == PET_STATE_AGGRESSIVE) || (!m_Unit->IsPet() && !(m_combatFlag & CF_DISABLE_MELEE)))))
        {
			Unit* target = FindTarget();
			if( target )
			{
				AttackReaction(target, 1);
			}
        }
    }
    // Find new Targets when we are ooc
    if((m_AIState == STATE_IDLE || m_AIState == STATE_SCRIPTIDLE))
    {
		Unit* target = FindTarget();
		if(target)
		{
			AttackReaction(target, 1);
		}
    }
}

void AIInterface::_UpdateCombat(Real time)
{
    if( m_AIType != AITYPE_PET && (m_combatFlag & CF_DISABLE_COMBAT) )
        return;

    if( GetNextTarget() == m_Unit )
        SetNextTarget( GetMostHated() );

    uint16 agent = static_cast<uint16>( m_aiCurrentAgent );

	/*if(m_AIType != AITYPE_PET
       && m_AIState != STATE_EVADE
       && m_AIState != STATE_SCRIPTMOVE
       && (m_outOfCombatRange && m_Unit->GetDistanceSq(m_returnX,m_returnY,m_returnZ) > m_outOfCombatRange))
    {
        HandleEvent( EVENT_LEAVECOMBAT, m_Unit, 0 );
    }
    else*/ if( GetNextTarget() == NULL && m_AIState != STATE_FOLLOWING && m_AIState != STATE_SCRIPTMOVE )
    {
        SetNextTarget(GetMostHated());
        if(GetNextTarget() == NULL)
        {
            HandleEvent(EVENT_LEAVECOMBAT, m_Unit, 0);
        }
    }
    /*if (sWorld.Collision)
	{
           
            if ( m_Unit->GetMapMgr() != NULL && GetNextTarget() != NULL )
            {
                    if (!m_moveFly)
                    {
                            Real target_land_z = CollideInterface.GetHeight(m_Unit->GetMapId(), GetNextTarget()->GetPositionX(), GetNextTarget()->GetPositionY(), GetNextTarget()->GetPositionZ() + 2.0f);
                            if ( target_land_z == NO_WMO_HEIGHT )
                                    target_land_z = m_Unit->GetMapMgr()->GetLandHeight(GetNextTarget()->GetPositionX(), GetNextTarget()->GetPositionY());
                            if (fabs(GetNextTarget()->GetPositionZ() - target_land_z) > _CalcCombatRange(GetNextTarget(), false))
                            {
                                    if ( GetNextTarget()->GetTypeId() != TYPEID_PLAYER )
                                    {
                                            if ( target_land_z > m_Unit->GetMapMgr()->GetWaterHeight(GetNextTarget()->GetPositionX(), GetNextTarget()->GetPositionY()) )
                                                    HandleEvent( EVENT_LEAVECOMBAT, m_Unit, 0); //bugged npcs, probably db fault
                                    }
                                    else if (static_cast<Player*>(GetNextTarget())->GetSession() != NULL)
                                    {
                                            MovementInfo* mi=static_cast<Player*>(GetNextTarget())->GetSession()->GetMovementInfo();
                                            if ( mi != NULL && !(mi->flags & MOVEFLAG_FALLING) && !(mi->flags & MOVEFLAG_SWIMMING) && !(mi->flags & MOVEFLAG_LEVITATE))
                                                    HandleEvent( EVENT_LEAVECOMBAT, m_Unit, 0);
                                    }
                            }
                    }
            }
    }*/
    if (GetNextTarget() != NULL && GetNextTarget()->GetType() == TYPE_UNIT && m_AIState == STATE_EVADE)
        HandleEvent( EVENT_LEAVECOMBAT, m_Unit, 0);
    bool cansee;
    if(GetNextTarget())
    {
        if( m_Unit->GetType() == TYPE_UNIT )
            cansee = static_cast<Creature*>(m_Unit)->CanSee(GetNextTarget());
        else
            cansee = static_cast<Player*>(m_Unit)->CanSee(GetNextTarget());
    }
    else 
    {
        if(GetNextTarget())
            SetNextTarget((Unit*)NULL);
        cansee = false;
    }
    if(cansee && GetNextTarget() && GetNextTarget()->IsAlive() && m_AIState != STATE_EVADE /*&& !m_Unit->IsCasting()*/)
    {
        if( agent == AGENT_NULL /*|| (m_AIType == AITYPE_PET && !m_nextSpell)*/) // allow pets autocast
        {
            /*if( !m_nextSpell )
                m_nextSpell = this->getSpell();*/
            if(m_canFlee && !m_hasFleed
                && ((m_Unit->GetUInt32Value( UNIT_FIELD_HEALTH ) / m_Unit->GetUInt32Value( UNIT_FIELD_MAXHEALTH )) < m_FleeHealth ))
                agent = AGENT_FLEE;
            else if(m_canCallForHelp
                && !m_hasCalledForHelp)
                agent = AGENT_CALLFORHELP;
            /*else if(m_nextSpell)
            {
                if(m_nextSpell->agent != AGENT_NULL)
                {
                    agent = m_nextSpell->agent;
                }
                else
                {
                    agent = AGENT_MELEE;
                }
            }*/
            else
            {
                agent = AGENT_MELEE;
            }
		}
        if(agent == AGENT_RANGED || agent == AGENT_MELEE)
        {
            if(m_canRangedAttack)
            {
                agent = AGENT_MELEE;
                if(GetNextTarget()->GetType() == TYPE_PLAYER)
                {
                    Real dist = m_Unit->GetDistanceSq(GetNextTarget());
                    if( /*static_cast< Player* >( GetNextTarget() )->m_currentMovement == MOVE_ROOT ||*/ dist >= 64.0f )
                    {
                        agent = AGENT_RANGED;
                    }
                }
                /*else if( GetNextTarget()->m_canMove == false || m_Unit->GetDistanceSq(GetNextTarget()) >= 64.0f )
                {
					agent = AGENT_RANGED;
                }*/
            }
            else
            {
                agent = AGENT_MELEE;
            }
        }
        if((m_combatFlag & CF_DISABLE_MELEE) && agent == AGENT_MELEE)
            agent = AGENT_NULL;       
        if((m_combatFlag & CF_DISABLE_RANGED) && agent == AGENT_RANGED)
            agent = AGENT_NULL;
        if((m_combatFlag & CF_DISABLE_SPELL) && agent == AGENT_SPELL)
            agent = AGENT_NULL;
        switch(agent)
        {
        case AGENT_MELEE:
			{
				Real combatReach[2]; // Calculate Combat Reach
				Real distance = m_Unit->GetDistance2d(GetNextTarget());
				combatReach[0] = GetNextTarget()->GetModelHalfSize();
				combatReach[1] = _CalcCombatRange(GetNextTarget(), false);
				if(distance <= combatReach[1] + DISTANCE_TO_SMALL_TO_WALK) // Target is in Range -> Attack
				{
					if(UnitToFollow != NULL)
					{
						UnitToFollow = NULL;
						m_lastFollowX = m_lastFollowY = 0;
					}
                       
					FollowDistance = 0.0f;
					if(m_Unit->IsAttackReady() && !m_fleeTimer)
					{
						m_creatureState = ATTACKING;
						bool infront = m_Unit->IsInFront(GetNextTarget());
						if(!infront)
						{
							SetInFront(GetNextTarget());
							infront = true;                                                     
						}
						if(infront)
						{
							m_Unit->SetAttackTimer(0);
							m_Unit->Strike(GetNextTarget(), MELEE);
						}
					}
				}
				else // Target out of Range -> Run to it
				{
					Real dist;
					if( m_Unit->GetModelHalfSize() > GetNextTarget()->GetModelHalfSize() )
						dist = m_Unit->GetModelHalfSize(); 
					else 
						dist = GetNextTarget()->GetModelHalfSize();
					m_movementSpeedFlag |= MOVEMENT_SPEED_RUN;
					_CalcDestinationAndMove(GetNextTarget(), dist);
				}
			}break;
        case AGENT_RANGED:
            {
                Real combatReach[2]; // Calculate Combat Reach
                Real distance = m_Unit->GetDistance2d(GetNextTarget());
                combatReach[0] = 8.0f;
                combatReach[1] = 30.0f;
                if(distance >= combatReach[0] && distance <= combatReach[1]) // Target is in Range -> Attack
                {
                    if(UnitToFollow != NULL)
                    {
                        UnitToFollow = NULL;
                        m_lastFollowX = m_lastFollowY = 0;
                    }
                   
                    FollowDistance = 0.0f;
                    if(m_Unit->IsAttackReady() && !m_fleeTimer)
                    {
                        m_creatureState = ATTACKING;
                        bool infront = m_Unit->IsInFront(GetNextTarget());
                        if(!infront) // set InFront
                        {
                            SetInFront(GetNextTarget());
                            infront = true;                                                     
                        }
                        if(infront)
                        {
                            m_Unit->SetAttackTimer(0);
							m_Unit->Strike(GetNextTarget(), RANGED);
                        }
                    }
                }
                else // Target out of Range -> Run to it
                {
                    //calculate next move
                    Real dist;
                    if(distance < combatReach[0])// Target is too near
                        dist = 9.0f;
                    else
                        dist = 20.0f;
					ADDFLAG(m_movementSpeedFlag, MOVEMENT_SPEED_RUN);
                    _CalcDestinationAndMove(GetNextTarget(), dist);
                }
            }break;
        case AGENT_SPELL:
            {
			}break;
        case AGENT_FLEE:
            {
				REMOVEFLAG(m_movementSpeedFlag, MOVEMENT_SPEED_RUN);
                if(m_fleeTimer == 0)
                    m_fleeTimer = m_FleeDuration;
                _CalcDestinationAndMove(GetNextTarget(), 5.0f);
                if(!m_hasFleed)
				{
					if(m_Unit->GetType() == TYPE_UNIT)
					{
						if (GetNextTarget()->GetType() == TYPE_PLAYER)
						{
							GType plr(MYTYPE_PLAYER, GetNextTarget());
							ScriptSystem->OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_FLEE, 1, &plr);
							sLuaMgr.OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_FLEE, 1, &plr);
						}
						else
						{
							GType cre(MYTYPE_CREATURE, GetNextTarget());
							ScriptSystem->OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_FLEE, 1, &cre);
							sLuaMgr.OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_FLEE, 1, &cre);
						}
					}
				}
                m_AIState = STATE_FLEEING;
                SetNextTarget((Unit*)NULL);
                m_hasFleed = true;
            }break;
        case AGENT_CALLFORHELP:
            {
                FindFriends( 64.0f /*8.0f*/ );
                m_hasCalledForHelp = true; // We only want to call for Help once in a Fight.
				if(m_Unit->GetType() == TYPE_UNIT)
				{
					ScriptSystem->OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_CALLFORHELP, 0);
					sLuaMgr.OnCreatureEvent(static_cast<Creature*>(m_Unit), CREATURE_EVENT_ON_CALLFORHELP, 0);
				}
            }break;
        }
    }
    else if(!GetNextTarget() || !GetNextTarget()->IsAlive() || !cansee)
    {
        SetNextTarget((Unit*)NULL);
    }
}

void AIInterface::AttackReaction(Unit* pUnit, uint32 damage_dealt)
{
    if(m_AIState == STATE_EVADE || !pUnit || !pUnit->IsAlive() || m_Unit->IsDead() || m_Unit == pUnit)
        return;
    /*if( sWorld.Collision && pUnit->IsPlayer() )
    {
            if ( m_Unit->GetMapMgr() != NULL )
            {
                    if (!m_moveFly)
                    {
                            Real target_land_z = CollideInterface.GetHeight(m_Unit->GetMapId(), pUnit->GetPositionX(), pUnit->GetPositionY(), pUnit->GetPositionZ() + 2.0f);
                            if ( target_land_z == NO_WMO_HEIGHT )
                                    target_land_z = m_Unit->GetMapMgr()->GetLandHeight(pUnit->GetPositionX(), pUnit->GetPositionY());
                            if (fabs(pUnit->GetPositionZ() - target_land_z) > _CalcCombatRange(pUnit, false) )
                            {
                                    if ( pUnit->GetTypeId()!=TYPEID_PLAYER && target_land_z > m_Unit->GetMapMgr()->GetWaterHeight(pUnit->GetPositionX(), pUnit->GetPositionY()) )
                                            return;
                                    else if( static_cast<Player*>(pUnit)->GetSession() != NULL )
                                    {
                                            MovementInfo* mi=static_cast<Player*>(pUnit)->GetSession()->GetMovementInfo();
                                            if ( mi != NULL && !(mi->flags & MOVEFLAG_FALLING) && !(mi->flags & MOVEFLAG_SWIMMING) && !(mi->flags & MOVEFLAG_LEVITATE))
                                                    return;
                                    }
                            }
                    }
            }
    }*/
    if( (m_AIState == STATE_IDLE || m_AIState == STATE_FOLLOWING) && m_Unit->GetAIInterface()->GetAllowedToEnterCombat())
    {
        WipeTargetList();
       
        HandleEvent(EVENT_ENTERCOMBAT, pUnit, 0);
    }
    HandleEvent(EVENT_DAMAGETAKEN, pUnit, _CalcThreat(damage_dealt, pUnit));
}

void AIInterface::OnDeath(Object* pKiller)
{
    if(pKiller->GetType() == TYPE_PLAYER || pKiller->GetType() == TYPE_UNIT)
        HandleEvent(EVENT_UNITDIED, static_cast<Unit*>(pKiller), 0);
    else
        HandleEvent(EVENT_UNITDIED, m_Unit, 0);
}

bool AIInterface::UnsafeCanOwnerAttackUnit(Unit *pUnit)
{
	if( !Faction::IsHostile(m_Unit,pUnit ))
        return false;
    if( !pUnit->IsAlive() )
        return false;
    //don't attack owner
	/*if( m_Unit->GetCreatedByGUID() == pUnit->GetGUID() )
            return false; 
    //don't agro neutrals
    if( ( pUnit->IsPlayer() || pUnit->IsPet() )
            && m_Unit->m_factionDBC
            && m_Unit->m_factionDBC->RepListId == -1 
            && m_Unit->m_faction->HostileMask == 0 
            && m_Unit->m_faction->FriendlyMask == 0
            )
                    return false;
    else if( ( m_Unit->IsPlayer() || m_Unit->IsPet() )
                    && pUnit->m_factionDBC
                    && pUnit->m_factionDBC->RepListId == -1 
                    && pUnit->m_faction->HostileMask == 0 
                    && pUnit->m_faction->FriendlyMask == 0
                    )
                    return false;
    //make sure we do not agro flying stuff
    if( abs( pUnit->GetPositionZ() - m_Unit->GetPositionZ() ) > _CalcCombatRange( pUnit, false ) )
            return false; //blizz has this set to 250 but uses pathfinding*/
    return true;
}

Unit* AIInterface::FindTarget()
{
    if( !m_AllowedToEnterCombat ) 
        return NULL;
        
	Unit* target = NULL;
    Real distance = 999999.0f; // that should do it.. :p
	std::map<uint32, Object*>::iterator itr, itr2;
	std::map<uint32, Player*>::iterator pitr, pitr2;
    Unit *pUnit;
    Real dist;

	if(m_Unit->HasFlag(OBJECT_FIELD_FLAG, (OBJECT_FLAG_NOT_ATTACKABLE | OBJECT_FLAG_NOT_SELECTABLE)))
        return NULL;
    
    //we have a high chance that we will agro a player
    for(pitr2 = sMap.GetPlayerMapBegin(); pitr2 != sMap.GetPlayerMapEnd();)
    {
        pitr = pitr2;
        ++pitr2;
        pUnit = static_cast<Unit*>(pitr->second);
   
		if(UnsafeCanOwnerAttackUnit( pUnit ) == false)
            continue;

        dist = m_Unit->GetDistance2dSq(pUnit);
        if(dist > distance)      // we want to find the CLOSEST target
            continue;
        if(dist <= _CalcAggroRange(pUnit) )
        {
            /*if (sWorld.Collision) 
			{
                if( CollideInterface.CheckLOS( m_Unit->GetMapId( ), m_Unit->GetPositionNC( ), pUnit->GetPositionNC( ) ) )
                {
                    distance = dist;
                    target = pUnit;
                }
            }
			else
			{*/
                distance = dist;
                target = pUnit;
            //}
        }
    }
    //a lot less times are check inter faction mob wars :)
    if( m_updateTargetsTimer2 < getMSTime() )
    {
        m_updateTargetsTimer2 = getMSTime() + TARGET_UPDATE_INTERVAL;
        for(itr2 = sMap.GetUnitMapBegin(); itr2 != sMap.GetUnitMapEnd();)
        {
            itr = itr2;
            ++itr2;
            if(!(itr->second->IsUnit()))
                continue;
            pUnit = static_cast<Unit*>(itr->second);
            if(UnsafeCanOwnerAttackUnit( pUnit ) == false)
                continue;
            //on blizz there is no Z limit check
            dist = m_Unit->GetDistance2dSq(pUnit);

            if(dist > distance)      // we want to find the CLOSEST target
                continue;

            if(dist <= _CalcAggroRange(pUnit))
            {
                /*if (sWorld.Collision) 
				{
                    if( CollideInterface.CheckLOS( m_Unit->GetMapId( ), m_Unit->GetPositionNC( ), pUnit->GetPositionNC( ) ) )
                    {
						distance = dist;
						target = pUnit;
                    }
                } 
				else 
				{*/
                    distance = dist;
                    target = pUnit;
                //}
            }
        }
    }
    if( target )
    {
        AttackReaction(target, 1);
    }
    return target;
}

bool AIInterface::FindFriends(Real dist)
{
	return false;
}

Real AIInterface::_CalcAggroRange(Unit* target)
{
    //Find some calculation to here now it defaults to
	Real AggroRange = 320.0f;
    return (AggroRange * AggroRange);
}

void AIInterface::_CalcDestinationAndMove(Unit *target, Real dist)
{
    if(m_movementSpeedFlag & MOVEMENT_SPEED_NOT)
    {
        StopMovement(0); //Just Stop
        return;
    }
       
    if( target && ( target->GetType() == TYPE_UNIT || target->GetType() == TYPE_PLAYER) )
    {
		Vector3 myPos = m_Unit->GetPosition();
		Vector3 pos = target->GetPosition();
        Real ResX = pos.x;

		if( abs(m_lastTargetX - ResX) < DISTANCE_TO_SMALL_TO_WALK && m_creatureState == MOVING)
                return;
		
        m_lastTargetX = ResX;
        Real ResY = pos.y;
		Real x;
		Real y = 0;
		if(m_movementSpeedFlag & MOVEMENT_SPEED_FLY)
		{
			/*Real angle = m_Unit->CalcAngle(myPos.x,myPos.y, ResX, ResY) * Real(M_PI) / 180.0f;
			Real x = dist * cosf(angle);
			Real y = dist * sinf(angle);
			if(target->GetType() == TYPE_PLAYER)
			{
				// cater for moving player vector based on orientation
				x -= cosf(angle);
				y -= sinf(angle);
			}*/
			x = dist;
		}
		else
		{
			x = dist;
		}
        m_nextPosX = ResX - x;
        m_nextPosY = ResY - y;
    }
    else
    {
        target = NULL;
		Vector3 pos = m_Unit->GetPosition();
        m_nextPosX = pos.x;
        m_nextPosY = pos.y;
    }

    if(m_creatureState != MOVING)
        UpdateMove();
}

Real AIInterface::_CalcCombatRange(Unit* target, bool ranged)
{
    if(!target)
    {
        return 0;
    }
    Real range = 0.0f;
    Real rang = 0.0f;
    if(ranged)
    {
        rang = 5.0f;
    }
    Real selfreach = 1;
    Real targetradius;
    targetradius = target->GetModelHalfSize();
    Real selfradius;
    selfradius = m_Unit->GetModelHalfSize();
    range = targetradius + selfreach + selfradius + rang;
    return range;
}

bool AIInterface::StopMovement(uint32 time)
{
    m_moveTimer = time; //set pause after stopping
    m_creatureState = STOPPED;
    m_destinationX = m_destinationY = 0;
    m_nextPosX = m_nextPosY = 0;
    m_timeMoved = 0;
    m_timeToMove = 0;
    return true;
}

void AIInterface::MoveTo(Real x, Real y)
{
	Vector3 pos = m_Unit->GetPosition();
    m_sourceX = pos.x;
    m_sourceY = pos.y;
	if(m_movementSpeedFlag & MOVEMENT_SPEED_NOT)
	{
        StopMovement(0); //Just Stop
        return;
	}
	m_nextPosX = x;
	m_nextPosY = y;

    if ( m_creatureState != MOVING )
        UpdateMove();
}

uint32 AIInterface::GetMoveFlags()
{
    uint32 MoveFlags = 0;
    /*if(m_movementSpeedFlag & MOVEMENT_SPEED_FLY) //Fly
    {
        m_flySpeed = m_Unit->m_flySpeed*0.001f;
    }
    else if(m_movementSpeedFlag & MOVEMENT_SPEED_SPRINT) //Sprint
    {
        m_runSpeed = (m_Unit->m_runSpeed+5.0f)*0.001f;
    }
    else if(m_movementSpeedFlag & MOVEMENT_SPEED_RUN) //Run
    {
		m_runSpeed = m_Unit->m_runSpeed*0.001f;
    }
    m_walkSpeed = m_Unit->m_walkSpeed*0.001f;//move distance per ms time*/

	if(m_movementSpeedFlag & MOVEMENT_SPEED_FLY) //Fly
    {
        m_flySpeed = m_Unit->m_flySpeed;
    }
    else if(m_movementSpeedFlag & MOVEMENT_SPEED_SPRINT) //Sprint
    {
        m_runSpeed = (m_Unit->m_runSpeed+5.0f);
    }
    else if(m_movementSpeedFlag & MOVEMENT_SPEED_RUN) //Run
    {
		m_runSpeed = m_Unit->m_runSpeed;
    }
    m_walkSpeed = m_Unit->m_walkSpeed;//move distance per ms time
    return MoveFlags;
}

void AIInterface::UpdateMove()
{
    //this should NEVER be called directly !!!!!!
    //use MoveTo()
    Real distance = m_Unit->GetDistance2d(m_nextPosX,m_nextPosY);
   
    if(distance < DISTANCE_TO_SMALL_TO_WALK) 
        return; //we don't want little movements here and there
    m_destinationX = m_nextPosX;
    m_destinationY = m_nextPosY;
   
    /*if(m_moveFly != true)
    {
            if(m_Unit->GetMapMgr())
            {
                    Real adt_Z = m_Unit->GetMapMgr()->GetLandHeight(m_destinationX, m_destinationY);
                    if(fabsf(adt_Z - m_destinationZ) < 3.0f)
                            m_destinationZ = adt_Z;
            }
    }*/

#ifdef USE_REAL_TIMERS
	Real moveTime;
#else
    uint32 moveTime;
#endif

#ifdef USE_REAL_TIMERS
	if(m_movementSpeedFlag & MOVEMENT_SPEED_FLY)
        moveTime = (Real) (distance / m_flySpeed);
    else if(m_movementSpeedFlag & MOVEMENT_SPEED_RUN)
        moveTime = (Real) (distance / m_runSpeed);
    else moveTime = (Real) (distance / m_walkSpeed);
#else
	if(m_movementSpeedFlag & MOVEMENT_SPEED_FLY)
        moveTime = (uint32) (distance / m_flySpeed);
    else if(m_movementSpeedFlag & MOVEMENT_SPEED_RUN)
        moveTime = (uint32) (distance / m_runSpeed);
    else moveTime = (uint32) (distance / m_walkSpeed);
#endif
    m_totalMoveTime = moveTime;
    m_timeToMove = moveTime;
    m_timeMoved = 0;
    if(m_moveTimer == 0)
    {
        m_moveTimer =  UNIT_MOVEMENT_INTERPOLATE_INTERVAL; // update every few msecs
    }
    m_creatureState = MOVING;
}

void AIInterface::_UpdateMovement(Real p_time)
{
    if(!m_Unit->IsAlive())
    {
        StopMovement(0);
        return;
    }
#ifdef USE_REAL_TIMERS
	Real timediff = 0;
#else
    uint32 timediff = 0;
#endif
    if(m_moveTimer > 0)
    {
        if(p_time >= m_moveTimer)
        {
            timediff = p_time - m_moveTimer;
            m_moveTimer = 0;
        }
        else
            m_moveTimer -= p_time;
    }
    if(m_timeToMove > 0)
    {
        m_timeMoved = m_timeToMove <= p_time + m_timeMoved ? m_timeToMove : p_time + m_timeMoved;
    }
        
	if(m_creatureState == MOVING)
    {
        if(!m_moveTimer)
        {
            if(m_timeMoved == m_timeToMove) //reached destination
            {
                if(m_moveType == MOVEMENTTYPE_WANTEDWP)//We reached wanted wp stop now
                    m_moveType = MOVEMENTTYPE_DONTMOVEWP;
                /*Real wayO = 0.0f;
                if((GetWayPointsCount() != 0) && (m_AIState == STATE_IDLE || m_AIState == STATE_SCRIPTMOVE)) //if we attacking don't use wps
                {
                    WayPoint* wp = getWayPoint(getCurrentWaypoint());
                    if(wp)
                    {
                            CALL_SCRIPT_EVENT(m_Unit, OnReachWP)(wp->id, !m_moveBackward);
                            if(((Creature*)m_Unit)->has_waypoint_text)
                                    objmgr.HandleMonsterSayEvent(((Creature*)m_Unit), MONSTER_SAY_EVENT_RANDOM_WAYPOINT);
                            //Lets face to correct orientation
                            wayO = wp->o;
                            m_moveTimer = wp->waittime; //wait before next move
                            if(!m_moveBackward)
                            {
                                    if(wp->forwardemoteoneshot)
                                    {
                                            GetUnit()->Emote(EmoteType(wp->forwardemoteid));
                                    }
                                    else
                                    {
                                            if(GetUnit()->GetUInt32Value(UNIT_NPC_EMOTESTATE) != wp->forwardemoteid)
                                            {
                                                    GetUnit()->SetUInt32Value(UNIT_NPC_EMOTESTATE, wp->forwardemoteid);
                                            }
                                    }
                            }
                            else
                            {
                                    if(wp->backwardemoteoneshot)
                                    {
                                            GetUnit()->Emote(EmoteType(wp->backwardemoteid));
                                    }
                                    else
                                    {
                                            if(GetUnit()->GetUInt32Value(UNIT_NPC_EMOTESTATE) != wp->backwardemoteid)
                                            {
                                                    GetUnit()->SetUInt32Value(UNIT_NPC_EMOTESTATE, wp->backwardemoteid);
                                            }
                                    }
                            }
                    }
                    else
                            m_moveTimer = RandomUInt(m_moveRun ? 5000 : 10000); // wait before next move
                }*/
                m_creatureState = STOPPED;
                REMOVEFLAG(m_movementSpeedFlag, MOVEMENT_SPEED_SPRINT);
				m_Unit->SetPosition(m_destinationX, m_destinationY, 0);
                m_destinationX = m_destinationY = 0;
                m_timeMoved = 0;
                m_timeToMove = 0;
            }
            else
            {
				Vector3 myPos = m_Unit->GetPosition();
                Real q = (Real)m_timeMoved / (Real)m_timeToMove;
                Real x = myPos.x + (m_destinationX - myPos.x) * q;
                Real y = myPos.y + (m_destinationY - myPos.y) * q;
                /*if (sWorld.Collision) {
					           
                }*/
                m_Unit->SetPosition(x, y, 0);
               
                m_timeToMove -= m_timeMoved;
                m_timeMoved = 0;
                m_moveTimer = (UNIT_MOVEMENT_INTERPOLATE_INTERVAL < m_timeToMove) ? UNIT_MOVEMENT_INTERPOLATE_INTERVAL : m_timeToMove;
            }
            if(m_nextPosX != 0.0f && m_nextPosY != 0.0f)
            {
                UpdateMove();
            }
        }
    }
    else if(m_creatureState == STOPPED && (m_AIState == STATE_IDLE || m_AIState == STATE_SCRIPTMOVE) && !m_moveTimer && !m_timeToMove && UnitToFollow == NULL) //creature is stopped and out of Combat
    {
        if(UnitToFollow == 0)
        {
            // no formation, use waypoints
            /*int destpoint = -1;
            // If creature has no waypoints just wander aimlessly around spawnpoint
            if(GetWayPointsCount()== 0) //no waypoints
            {
                return;                                                                                                                                                                                                                                                                                           
            }                                                                                                                                                                                                                                                                                                                 
            else //we do have waypoints
            {
                if(m_moveType == MOVEMENTTYPE_RANDOMWP) //is random move on if so move to a random waypoint
                {
                    if(GetWayPointsCount() > 1)
                            destpoint = RandomUInt((uint32)GetWayPointsCount());
                }
                else if (m_moveType == MOVEMENTTYPE_CIRCLEWP) //random move is not on lets follow the path in circles
                {
                    // 1 -> 10 then 1 -> 10
                    m_currentWaypoint++;
                    if (m_currentWaypoint > GetWayPointsCount()) m_currentWaypoint = 1; //Happens when you delete last wp seems to continue ticking
                    destpoint = m_currentWaypoint;
                    m_moveBackward = false;
                }
                else if(m_moveType == MOVEMENTTYPE_WANTEDWP)//Move to wanted wp
                {
                    if(m_currentWaypoint)
                    {
                        if(GetWayPointsCount() > 0)
                        {
                            destpoint = m_currentWaypoint;
                        }
                        else
                            destpoint = -1;
                    }
                }
                else if(m_moveType == MOVEMENTTYPE_FORWARDTHANSTOP)// move to end, then stop
                {
                    ++m_currentWaypoint;
                    if(m_currentWaypoint > GetWayPointsCount())
                    {
                        //hmm maybe we should stop being path walker since we are waiting here anyway
                        destpoint = -1;
                    }
                    else
                            destpoint = m_currentWaypoint;
                }
                else if(m_moveType != MOVEMENTTYPE_QUEST && m_moveType != MOVEMENTTYPE_DONTMOVEWP)//4 Unused
                {
                        // 1 -> 10 then 10 -> 1
                        if (m_currentWaypoint > GetWayPointsCount()) m_currentWaypoint = 1; //Happens when you delete last wp seems to continue ticking
                        if (m_currentWaypoint == GetWayPointsCount()) // Are we on the last waypoint? if so walk back
                                m_moveBackward = true;
                        if (m_currentWaypoint == 1) // Are we on the first waypoint? if so lets goto the second waypoint
                                m_moveBackward = false;
                        if (!m_moveBackward) // going 1..n
                                destpoint = ++m_currentWaypoint;
                        else                            // going n..1
                                destpoint = --m_currentWaypoint;
                }
                if(destpoint != -1)
                {
                    WayPoint* wp = getWayPoint(destpoint);
                    if(wp)
                    {
                            if(!m_moveBackward)
                            {
                                    if((wp->forwardskinid != 0) && (GetUnit()->GetUInt32Value(UNIT_FIELD_DISPLAYID) != wp->forwardskinid))
                                    {
                                            GetUnit()->SetUInt32Value(UNIT_FIELD_DISPLAYID, wp->forwardskinid);
                                            GetUnit()->EventModelChange();
                                    }
                            }
                            else
                            {
                                    if((wp->backwardskinid != 0) && (GetUnit()->GetUInt32Value(UNIT_FIELD_DISPLAYID) != wp->backwardskinid))
                                    {
                                            GetUnit()->SetUInt32Value(UNIT_FIELD_DISPLAYID, wp->backwardskinid);
                                            GetUnit()->EventModelChange();
                                    }
                            }
                            m_moveFly = (wp->flags == 768) ? 1 : 0;
                            m_moveRun = (wp->flags == 256) ? 1 : 0;
                            MoveTo(wp->x, wp->y, wp->z, 0);
                    }
                }
            }*/
        }
    }
    //Fear Code
    if(m_AIState == STATE_FEAR && UnitToFear != NULL && m_creatureState == STOPPED)
    {
        if(getMSTime() > m_FearTimer)   // Wait at point for x ms ;)
        {
        }
    }
    // Wander AI movement code
    if(m_AIState == STATE_WANDER && m_creatureState == STOPPED)
    {
        if(getMSTime() < m_WanderTimer) // is it time to move again?
                return;
    }
        //Unit Follow Code
    if(UnitToFollow != NULL)
    {
        /*if(m_AIState == STATE_IDLE || m_AIState == STATE_FOLLOWING)
        {
            Real dist = m_Unit->GetDistanceSq(UnitToFollow);
            // re-calculate orientation based on target's movement
            if(m_lastFollowX != UnitToFollow->GetPositionX() ||
                    m_lastFollowY != UnitToFollow->GetPositionY())
            {
                    Real dx = UnitToFollow->GetPositionX() - m_Unit->GetPositionX();
                    Real dy = UnitToFollow->GetPositionY() - m_Unit->GetPositionY();
                    if(dy != 0.0f)
                    {
                            Real angle = atan2(dx,dy);
                            m_Unit->SetOrientation(angle);
                    }
                    m_lastFollowX = UnitToFollow->GetPositionX();
                    m_lastFollowY = UnitToFollow->GetPositionY();
            }
            if (dist > (FollowDistance*FollowDistance)) //if out of range
            {
                m_AIState = STATE_FOLLOWING;
               
                if(dist > 25.0f) //25 yard away lets run else we will loose the them
                    m_moveRun = true;
                else 
                    m_moveRun = false;
                if(m_AIType == AITYPE_PET || UnitToFollow == m_formationLinkTarget) //Unit is Pet/formation
                {
                    if(dist > 900.0f)
                            m_moveSprint = true;
                    Real delta_x = UnitToFollow->GetPositionX();
                    Real delta_y = UnitToFollow->GetPositionY();
                    Real d = 3;
                    if(m_formationLinkTarget)
                            d = m_formationFollowDistance;
                    MoveTo(delta_x+(d*(cosf(m_fallowAngle+UnitToFollow->GetOrientation()))),
                            delta_y+(d*(sinf(m_fallowAngle+UnitToFollow->GetOrientation()))),
                            UnitToFollow->GetPositionZ(),UnitToFollow->GetOrientation());                           
                }
                else
                {
                    _CalcDestinationAndMove(UnitToFollow, FollowDistance);
                }
            }
        }*/
	}
}

uint32 AIInterface::GetThreatByGUID(uint64 guid)
{
    Unit *obj = sMap.GetUnit(guid);
    if(obj)
        return GetThreatByPtr(obj);
    return 0;
}

uint32 AIInterface::GetThreatByPtr(Unit* obj)
{
    if(!obj)
        return 0;
    TargetMap::iterator it = m_aiTargets.find(obj->GetGUID());
    if(it != m_aiTargets.end())
    {
		return it->second;
    }
    return 0;
}

Unit *AIInterface::GetMostHated()
{
	std::pair<Unit*, int32> currentTarget;
    currentTarget.first = 0;
    currentTarget.second = -1;
    LockAITargets(true);
    TargetMap::iterator it2 = m_aiTargets.begin();
    TargetMap::iterator itr;
    for(; it2 != m_aiTargets.end();)
    {
        itr = it2;
        ++it2;
        // this is a much slower version then the previous one but it causes a lot of crashes and that is above speed right now.
        Unit *ai_t = sMap.GetUnit( itr->first );
        if( !ai_t || !ai_t->IsAlive() /*|| !isAttackable( m_Unit, ai_t )*/ )
        {
            if( GetNextTarget() == ai_t )
                SetNextTarget( (Unit*)NULL );
            m_aiTargets.erase(itr);
            continue;
        }
        if(itr->second > currentTarget.second)
        {
            /* new target */
            currentTarget.first = ai_t;
            currentTarget.second = itr->second;
            m_currentHighestThreat = currentTarget.second;
        }
    }
    LockAITargets(false);
    return currentTarget.first;
}

bool AIInterface::ModThreatByGUID(uint64 guid, int32 mod)
{
    if (!m_aiTargets.size())
        return false;
 
    Unit *obj = sMap.GetUnit(guid);
    if(obj)
        return ModThreatByPtr(obj, mod);
    return false;
}

bool AIInterface::ModThreatByPtr(Unit* obj, int32 mod)
{
    if(!obj)
        return false;
    LockAITargets(true);
    int32 tempthreat;
    TargetMap::iterator it = m_aiTargets.find(obj->GetGUID());
    if(it != m_aiTargets.end())
    {
        it->second += mod;
        if (it->second < 1)
                it->second = 1;
        tempthreat = it->second;
        if (tempthreat < 1)
                tempthreat = 1;
        if(tempthreat > m_currentHighestThreat)
        {
            m_currentHighestThreat = tempthreat;
            SetNextTarget(obj);
        }
    }
    else
    {
        m_aiTargets.insert( std::make_pair( obj->GetGUID(), mod ) );
        tempthreat = mod;
        if (tempthreat < 1)
            tempthreat = 1;
        if(tempthreat > m_currentHighestThreat)
        {
            m_currentHighestThreat = tempthreat;
            SetNextTarget(obj);
        }
    }
    LockAITargets(false);
    if(obj == GetNextTarget())
    {
        // check for a possible decrease in threat.
        if(mod < 0)
        {
            SetNextTarget(GetMostHated());
            //if there is no more new targets then we can walk back home ?
            if(!GetNextTarget())
                HandleEvent(EVENT_LEAVECOMBAT, m_Unit, 0);
        }
    }
    return true;
}

void AIInterface::RemoveThreatByGUID(uint64 guid)
{
    if (!m_aiTargets.size())
        return;
    Unit *obj = sMap.GetUnit(guid);
    if(obj)
        RemoveThreatByPtr(obj);
}

void AIInterface::RemoveThreatByPtr(Unit* obj)
{
    if(!obj)
        return;
    LockAITargets(true);
    TargetMap::iterator it = m_aiTargets.find(obj->GetGUID());
    if(it != m_aiTargets.end())
    {
        m_aiTargets.erase(it);
        //check if we are in combat and need a new target
        if(obj==GetNextTarget())
        {
            SetNextTarget(GetMostHated());
            //if there is no more new targets then we can walk back home ?
            if(!GetNextTarget())
                HandleEvent(EVENT_LEAVECOMBAT, m_Unit, 0);
        }
    }
    LockAITargets(false);
}

void AIInterface::WipeHateList()
{
    for(TargetMap::iterator itr = m_aiTargets.begin(); itr != m_aiTargets.end(); ++itr)
            itr->second = 0;
    m_currentHighestThreat = 0;
}

void AIInterface::ClearHateList() //without leaving combat
{
    for(TargetMap::iterator itr = m_aiTargets.begin(); itr != m_aiTargets.end(); ++itr)
            itr->second = 1;
    m_currentHighestThreat = 1;
}

void AIInterface::WipeTargetList()
{
    SetNextTarget( (Unit*)NULL );
    m_currentHighestThreat = 0;
    LockAITargets( true );
    m_aiTargets.clear();
    LockAITargets( false );
    //m_Unit->CombatStatus.Vanished();
}

uint32 AIInterface::_CalcThreat(uint32 damage, Unit* Attacker)
{
    if(!Attacker)
        return 0; // No attacker means no threat and we prevent crashes this way
    
	/*if(m_Unit->m_faction != NULL && Attacker->m_faction != NULL)
            if (isSameFaction(m_Unit,Attacker))
                    return 0;*/
   
    int32 mod = 0;
    mod += damage;
    if (mod < 1)
            mod = 1;

    return mod;
}

void AIInterface::WipeReferences()
{
    m_currentHighestThreat = 0;
    LockAITargets(true);
    m_aiTargets.clear();
    LockAITargets(false);
    SetNextTarget((Unit*)NULL);
    UnitToFear = 0;
    UnitToFollow = 0;
    //Clear targettable
	std::map<uint32, Object*>::iterator itr = sMap.GetUnitMapBegin();
	for(; itr != sMap.GetUnitMapEnd(); ++itr)
	{
		if(itr->second->IsUnit() && static_cast<Unit*>(itr->second)->GetAIInterface())
			static_cast<Unit*>(itr->second)->GetAIInterface()->RemoveThreatByPtr(m_Unit);
	}
}

Unit* AIInterface::GetNextTarget()
{
    if (m_nextTarget && m_Unit) 
		return sMap.GetUnit(m_nextTarget);

    return NULL;
}

void AIInterface::SetNextTarget(Unit *nextTarget) 
{
    if (nextTarget)
        SetNextTarget(nextTarget->GetGUID());
    else
        SetNextTarget((uint64)NULL);
}

void AIInterface::SetNextTarget (uint64 nextTarget) 
{
    m_nextTarget = nextTarget; 
}
