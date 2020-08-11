#ifndef __LUA_OBJECTS_H
#define __LUA_OBJECTS_H

#ifdef CPPSCRIPTING

class LuaCreature : public CreatureAIScript
{
public:
	LuaCreature(Creature* creature) : CreatureAIScript(creature) {};
	~LuaCreature() {};
	DEDOSAN_INLINE void SetUnit(Creature * ncrc) { _unit = ncrc; }
	void OnCombatStart(Unit* mTarget)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_ENTER_COMBAT] != NULL)
		{
			uint8 args = 0;
			if( sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_ENTER_COMBAT]) )
				args++;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_ENTER_COMBAT);
			sLuaMgr.PUSH_UNIT(mTarget);
			args+=3;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}

	void OnCombatStop(Unit* mTarget)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_LEAVE_COMBAT] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_LEAVE_COMBAT]))
				args++;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_LEAVE_COMBAT);
			sLuaMgr.PUSH_UNIT(mTarget);
			args+=3;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}

	void OnTargetDied(Unit* mTarget)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_TARGET_DIED] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_TARGET_DIED]) )
				args++;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_TARGET_DIED);
			sLuaMgr.PUSH_UNIT(mTarget);
			args+=3;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}

	void OnDied(Unit *mKiller)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_DIED] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_DIED]) )
				args++;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_DIED);
			sLuaMgr.PUSH_UNIT(mKiller);
			args+=3;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnTargetParried(Unit* mTarget)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_TARGET_PARRIED] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_TARGET_PARRIED]))
				args++;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_TARGET_PARRIED);
			sLuaMgr.PUSH_UNIT(mTarget);
			args+=3;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnTargetDodged(Unit* mTarget)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_TARGET_DODGED] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_TARGET_DODGED]))
				args++;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_TARGET_DODGED);
			sLuaMgr.PUSH_UNIT(mTarget);
			args+=3;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnTargetBlocked(Unit* mTarget, int32 iAmount)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_TARGET_BLOCKED] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_TARGET_BLOCKED]) )
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_TARGET_BLOCKED);
			sLuaMgr.PUSH_UNIT(mTarget);
			sLuaMgr.PUSH_INT(iAmount);
			args+=4;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnTargetCritHit(Unit* mTarget, float fAmount)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_TARGET_CRIT_HIT] != NULL)
		{
			uint8 args = 0;
			if( sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_TARGET_CRIT_HIT]) )
				args++;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_TARGET_CRIT_HIT);
			sLuaMgr.PUSH_UNIT(mTarget);
			sLuaMgr.PUSH_FLOAT(fAmount);
			args+=4;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnParried(Unit* mTarget)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_PARRY] != NULL)
		{
			uint8 args = 0;
			if( sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_PARRY]))
				args++;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_PARRY);
			sLuaMgr.PUSH_UNIT(mTarget);
			args+=3;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnDodged(Unit* mTarget)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_DODGED] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_DODGED]))
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_DODGED);
			sLuaMgr.PUSH_UNIT(mTarget);
			args+=3;
			sLuaMgr.ExecuteCall(3);
		}
		RELEASE_LOCK
	}
	void OnBlocked(Unit* mTarget, int32 iAmount)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_BLOCKED] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_BLOCKED]) )
				args++;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_BLOCKED);
			sLuaMgr.PUSH_UNIT(mTarget);
			sLuaMgr.PUSH_INT(iAmount);
			args+=4;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnCritHit(Unit* mTarget, float fAmount)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_CRIT_HIT] != NULL)
		{
			uint8 args = 0;
			if( sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_CRIT_HIT]))
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_CRIT_HIT);
			sLuaMgr.PUSH_UNIT(mTarget);
			sLuaMgr.PUSH_FLOAT(fAmount);
			args+=4;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnHit(Unit* mTarget, float fAmount)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_HIT] != NULL)
		{
			uint8 args = 0;
			if( sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_HIT]) )
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_HIT);
			sLuaMgr.PUSH_UNIT(mTarget);
			sLuaMgr.PUSH_FLOAT(fAmount);
			args+=4;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnAssistTargetDied(Unit* mAssistTarget)
	{
		
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_ASSIST_TARGET_DIED] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_ASSIST_TARGET_DIED]))
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_ASSIST_TARGET_DIED);
			sLuaMgr.PUSH_UNIT(mAssistTarget);
			args+=3;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnFear(Unit* mFeared, uint32 iSpellId)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_FEAR] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_FEAR]))
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_FEAR);
			sLuaMgr.PUSH_UNIT(mFeared);
			sLuaMgr.PUSH_UINT(iSpellId);
			args+=4;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnFlee(Unit* mFlee)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_FLEE] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_FLEE]))
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_FLEE);
			sLuaMgr.PUSH_UNIT(mFlee);
			args+=3;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnCallForHelp()
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_CALL_FOR_HELP] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_CALL_FOR_HELP]))
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_CALL_FOR_HELP);
			args+=2;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnLoad()
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_LOAD] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_LOAD]))
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_LOAD);
			args+=2;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnReachWP(uint32 iWaypointId, bool bForwards)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_REACH_WP] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_REACH_WP]))
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_REACH_WP);
			sLuaMgr.PUSH_UINT(iWaypointId);
			sLuaMgr.PUSH_BOOL(bForwards);
			args+=4;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnLootTaken(Player* pPlayer, ItemPrototype *pItemPrototype)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_LOOT_TAKEN] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_LOOT_TAKEN]))
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_LOOT_TAKEN);
			sLuaMgr.PUSH_UNIT(pPlayer);
			sLuaMgr.PUSH_UINT(pItemPrototype->ItemId);
			args+=4;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void AIUpdate()
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_AIUPDATE] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_AIUPDATE]))
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_AIUPDATE);
			args+=2;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnEmote(Player * pPlayer, EmoteType Emote)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_EMOTE] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_EMOTE]))
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_EMOTE);
			sLuaMgr.PUSH_UNIT(pPlayer);
			sLuaMgr.PUSH_INT((int32)Emote);
			args+=4;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnDamageTaken(Unit* mAttacker, float fAmount)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[CREATURE_EVENT_ON_DAMAGE_TAKEN] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[CREATURE_EVENT_ON_DAMAGE_TAKEN]))
				++args;
			sLuaMgr.PUSH_UNIT(_unit);
			sLuaMgr.PUSH_INT(CREATURE_EVENT_ON_DAMAGE_TAKEN);
			sLuaMgr.PUSH_UNIT(mAttacker);
			sLuaMgr.PUSH_FLOAT(fAmount);
			args+=4;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void StringFunctionCall(const char * pFunction)
	{
		
		CHECK_BINDING_ACQUIRELOCK
		uint8 args = 0;
		if(sLuaMgr.BeginCall(pFunction))
			++args;
		sLuaMgr.PUSH_UNIT(_unit);
		++args;
		sLuaMgr.ExecuteCall(args);
		RELEASE_LOCK
	}

	void Destroy()
	{
		typedef std::multimap<uint32,LuaCreature*> CMAP;
		CMAP & cMap = sLuaMgr.getLuCreatureMap();
		CMAP::iterator itr = cMap.find(_unit->GetEntry());
		CMAP::iterator itend = cMap.upper_bound(_unit->GetEntry());
		CMAP::iterator it;
		for(;itr != cMap.end() && itr != itend;)
		{
			it = itr++;
			if(it->second != NULL && it->second == this)
				cMap.erase(it);
		}
		delete this;
	}
	LuaUnitBinding * m_binding;
};

class LuaGameObject : public GameObjectAIScript
{
public:
	LuaGameObject(GameObject * go) : GameObjectAIScript(go) {}
	~LuaGameObject() {}
	DEDOSAN_INLINE GameObject * getGO() { return _gameobject; }
	void OnCreate()
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[GAMEOBJECT_EVENT_ON_CREATE] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[GAMEOBJECT_EVENT_ON_CREATE]))
				++args;
			sLuaMgr.PUSH_GO(_gameobject);
			args++;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnSpawn()
	{
		
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[GAMEOBJECT_EVENT_ON_SPAWN] != NULL)
		{
			uint8 args = 0;
			if( sLuaMgr.BeginCall(m_binding->Functions[GAMEOBJECT_EVENT_ON_SPAWN]))
				++args;
			sLuaMgr.PUSH_GO(_gameobject);
			++args;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnDespawn()
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[GAMEOBJECT_EVENT_ON_DESPAWN] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[GAMEOBJECT_EVENT_ON_DESPAWN]) )
				++args;
			sLuaMgr.PUSH_GO(_gameobject);
			++args;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnLootTaken(Player * pLooter, ItemPrototype *pItemInfo)
	{
		
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[GAMEOBJECT_EVENT_ON_LOOT_TAKEN] != NULL)
		{
			uint8 args = 0;
			if(sLuaMgr.BeginCall(m_binding->Functions[GAMEOBJECT_EVENT_ON_LOOT_TAKEN]))
				++args;
			sLuaMgr.PUSH_GO(_gameobject);
			sLuaMgr.PUSH_UINT(GAMEOBJECT_EVENT_ON_LOOT_TAKEN);
			sLuaMgr.PUSH_UNIT(pLooter);
			sLuaMgr.PUSH_UINT(pItemInfo->ItemId);
			args+=4;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void OnActivate(Player * pPlayer)
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[GAMEOBJECT_EVENT_ON_USE] != NULL)
		{
			uint8 args = 0;
			sLuaMgr.BeginCall(m_binding->Functions[GAMEOBJECT_EVENT_ON_USE]);
			sLuaMgr.PUSH_GO(_gameobject);
			sLuaMgr.PUSH_UINT(GAMEOBJECT_EVENT_ON_USE);
			sLuaMgr.PUSH_UNIT(pPlayer);
			args+=3;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	
	void AIUpdate()
	{
		CHECK_BINDING_ACQUIRELOCK
		if (m_binding->Functions[GAMEOBJECT_EVENT_AIUPDATE] != NULL)
		{
			uint8 args = 0;
			sLuaMgr.BeginCall(m_binding->Functions[GAMEOBJECT_EVENT_AIUPDATE]);
			sLuaMgr.PUSH_GO(_gameobject);
			++args;
			sLuaMgr.ExecuteCall(args);
		}
		RELEASE_LOCK
	}
	void Destroy ()
	{
		typedef std::multimap<uint32,LuaGameObject*> GMAP;
		GMAP & gMap = sLuaMgr.getLuGameObjectMap();
		GMAP::iterator itr = gMap.find(_gameobject->GetEntry());
		GMAP::iterator itend = gMap.upper_bound(_gameobject->GetEntry());
		GMAP::iterator it;
		//uint64 guid = _gameobject->GetGUID(); Unused?
		for(; itr != itend;)
		{
			it = itr++;
			if(it->second != NULL && it->second == this)
				gMap.erase(it);
		}
		delete this;
	}
	LuaGameObjectBinding * m_binding;
};

#endif

#endif
