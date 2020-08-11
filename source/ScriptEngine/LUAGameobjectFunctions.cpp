#include "Stdafx.h"

namespace luaGameObject
{
	//int GossipCreateMenu(lua_State * L, GameObject * ptr)
	//{
	//	int text_id = luaL_checkint(L, 1);
	//	Player * target = CHECK_PLAYER(L,2);
 //		int autosend = luaL_checkint(L, 3);
	//	if (!target || !ptr)
	//		return 0;
	//    
	//	objmgr.CreateGossipMenuForPlayer(&Menu, ptr->GetGUID(), text_id, target);
	//	if(autosend)
	//		Menu->SendTo(target);
	//	return 0;
	//}

	//int GossipMenuAddItem(lua_State * L, GameObject * ptr)
	//{
	//	int icon = luaL_checkint(L, 1);
	//	const char * menu_text = luaL_checkstring(L, 2);
	//	int IntId = luaL_checkint(L, 3);
	//	int extra = luaL_checkint(L, 4);

	//	Menu->AddItem(icon, menu_text, IntId, extra);
	//	return 0;
	//}

	//int GossipSendMenu(lua_State * L, GameObject * ptr)
	//{
	//	Player * target = CHECK_PLAYER(L,1);
	//	if (!target)
	//		return 0;
	//	Menu->SendTo(target);
	//	return 0;
	//}

	//int GossipComplete(lua_State * L, GameObject * ptr)
	//{
	//	Player * target = CHECK_PLAYER(L,1);
	//	if (!target)
	//		return 0;
 //		target->Gossip_Complete();
 //		return 0;
	//}

	//int GossipSendPOI(lua_State * L, GameObject * ptr)
	//{
	//	Player * plr = CHECK_PLAYER(L,1);
	//	float x = CHECK_FLOAT(L, 2);
	//	float y = CHECK_FLOAT(L, 3);
	//	int icon = luaL_checkint(L, 4);
	//	int flags = luaL_checkint(L, 5);
	//	int data = luaL_checkint(L, 6);
	//	const char * name = luaL_checkstring(L, 7);
	//	if (!plr)
	//		return 0;

	//	plr->Gossip_SendPOI(x, y, icon, flags, data, name);
	//	return 0;
	//}

	//int RegisterAIUpdate(lua_State *L, GameObject * ptr)
	//{
	//	CHECK_TYPEID(TYPEID_GAMEOBJECT);
	//	uint32 time = CHECK_ULONG(L,1);
	//	sEventMgr.AddEvent(ptr,&GameObject::CallScriptUpdate, EVENT_SCRIPT_UPDATE_EVENT, time, 0, 0);
	//	return 0;
	//}

	//int ModAIUpdate(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID(TYPEID_GAMEOBJECT);
	//	uint32 newtime = CHECK_ULONG(L,1);
	//	sEventMgr.ModifyEventTimeAndTimeLeft(ptr, EVENT_SCRIPT_UPDATE_EVENT, newtime);
	//	return 0;
	//}

	//int RemoveAIUpdate(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID(TYPEID_GAMEOBJECT);
	//	sEventMgr.RemoveEvents(ptr, EVENT_SCRIPT_UPDATE_EVENT);
	//	return 0;
	//}

	///*int EventCastSpell(lua_State * L, GameObject * ptr)
	//{
	//	uint32 guid = luaL_checkint(L,1);
	//	uint32 sp = luaL_checkint(L,2);
	//	uint32 delay = luaL_checkint(L,3);
	//	uint32 repeats = luaL_checkint(L,4);
	//	if(guid && sp && delay)
	//	{
	//		sEventMgr.AddEvent(ptr,&GameObject::EventCastSpell,guid,sp,false,EVENT_GAMEOBJECT_UPDATE,delay,repeats,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	//	}
	//	return 0;
	//}*/

	//int GetMapId(lua_State * L, GameObject * ptr)
	//{
	//	(ptr != NULL) ? lua_pushinteger(L,ptr->GetMapId()) : lua_pushnil(L);
	//	return 1;
	//}

	//int RemoveFromWorld(lua_State * L, GameObject * ptr)
	//{
	//	if(ptr)
	//		ptr->RemoveFromWorld(true);
	//	return 0;
	//}

	//int GetName(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID(TYPEID_GAMEOBJECT);
	//	if (!ptr->GetInfo())
	//		return 0;
	//	lua_pushstring(L,ptr->GetInfo()->Name);
	//	return 1;
	//}

	//int Teleport(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID(TYPEID_GAMEOBJECT);
	//	Player* target = CHECK_PLAYER(L,1);
	//	uint32 mapId = CHECK_ULONG(L,2);
	//	float posX = CHECK_FLOAT(L, 3);
	//	float posY = CHECK_FLOAT(L, 4);
	//	float posZ = CHECK_FLOAT(L, 5);
	//	float Orientation = (float)luaL_optnumber(L, 6, 0.0f);
	//	if (!target)
	//		return 0;
	//	LocationVector vec(posX, posY, posZ, Orientation);
	//	target->SafeTeleport(mapId, 0, vec);
	//	return 0;
	//}

	//int GetCreatureNearestCoords(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	float x = CHECK_FLOAT(L,1);
	//	float y = CHECK_FLOAT(L,2);
	//	float z = CHECK_FLOAT(L,3);
	//	uint32 entryid = CHECK_ULONG(L,4);
	//	if (!entryid)
	//		lua_pushnil(L);
	//	else
	//	{
	//		Creature * crc = ptr->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x, y, z, entryid);
	//		if(crc != NULL)
	//			PUSH_UNIT(L,crc);
	//		else
	//			lua_pushnil(L);
	//	}
	//	return 1;
	//}

	//int GetGameObjectNearestCoords(lua_State *L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	float x = CHECK_FLOAT(L,1);
	//	float y = CHECK_FLOAT(L,2);
	//	float z = CHECK_FLOAT(L,3);
	//	uint32 entryid = CHECK_ULONG(L,4);
	//	if (!entryid) 
	//		lua_pushnil(L);
	//	else
	//	{
	//		GameObject * go = ptr->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(x, y, z, entryid);
	//		if(go != NULL)
	//			PUSH_GO(L,go);
	//		else
	//			lua_pushnil(L);
	//	}
	//	return 1;
	//}

	//int GetClosestPlayer(lua_State * L, GameObject * ptr)
	//{
	//	if (!ptr)
	//		return 0;
	//	float d2 = 0;
	//	float dist = 0;
	//	Player * ret = NULL;

	//	for (set<Object*>::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd();)
	//	{
	//		d2 = (static_cast<Player*>(*itr))->GetDistanceSq(ptr);
	//		if (!ret||d2<dist)
	//		{
	//			dist=d2;
	//			ret=static_cast< Player* >(*itr);
	//		}
	//	}
	//	if (ret == NULL)
	//		lua_pushnil(L);
	//	else
	//		PUSH_UNIT(L,ret);
	//	return 1;
	//}

	//int GetDistance(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	Unit * target = CHECK_UNIT(L, 1);
	//	lua_pushnumber(L,ptr->GetDistance2dSq(target));
	//	return 1;
	//}

	//int IsInWorld(lua_State * L, GameObject * ptr)
	//{
	//	if (ptr)
	//	{
	//		if(ptr->IsInWorld())
	//		{
	//			lua_pushboolean(L, 1);
	//			return 1;
	//		}
	//	}
	//	lua_pushboolean(L, 0);
	//	return 1;
	//}

	//int GetZoneId(lua_State *L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	lua_pushinteger(L, ptr->GetZoneId());
	//	return 1;
	//}

	//int PlaySoundToSet(lua_State * L, GameObject * ptr)
	//{
	//	if (!ptr) return 0;
	//	int soundid = luaL_checkint(L,1);
	//	ptr->PlaySoundToSet(soundid);
	//	return 0;
	//}

	//int SpawnCreature(lua_State * L, GameObject * ptr)
	//{
	//	if (ptr == NULL) return 0;
	//	uint32 entry_id = luaL_checkint(L, 1);
	//	float x = CHECK_FLOAT(L, 2);
	//	float y = CHECK_FLOAT(L, 3);
	//	float z = CHECK_FLOAT(L, 4);
	//	float o = CHECK_FLOAT(L, 5);
	//	uint32 faction = luaL_checkint(L, 6);
	//	uint32 duration = luaL_checkint(L, 7);

	//	if (!entry_id || !faction) //Shady: is it really required?
	//	{
	//		lua_pushnil(L);
	//		return 1;
	//	}
	//	CreatureProto *p = CreatureProtoStorage.LookupEntry(entry_id);
	//    
	//	if (p == NULL)
	//	  return 0;

	//	Creature *pCreature = ptr->GetMapMgr()->CreateCreature(entry_id);
	//	if(pCreature == NULL)
	//	{
	//		lua_pushnil(L);
	//		return 1;
	//	}
	//	pCreature->spawnid = 0;
	//	pCreature->m_spawn = 0;
	//	pCreature->Load(p,x,y,z);
	//	if (faction)
	//		pCreature->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE,faction);
	//	pCreature->_setFaction();
	//	pCreature->SetMapId(ptr->GetMapId());
	//	pCreature->SetOrientation(o);
	//	pCreature->Despawn(duration, 0);
	//	pCreature->SetInstanceID(ptr->GetInstanceID());
	//	pCreature->PushToWorld(ptr->GetMapMgr());
	//	if (duration)
	//	{
	//		pCreature->Despawn(duration,0);
	//	}
	//	PUSH_UNIT(L,pCreature);
	//	return 1;
	//}

	//int SpawnGameObject(lua_State * L, GameObject * ptr)
	//{
	//	if (ptr == NULL) return 0;
	//	uint32 entry_id = CHECK_ULONG(L,1);
	//	float x = CHECK_FLOAT(L, 2);
	//	float y = CHECK_FLOAT(L, 3);
	//	float z = CHECK_FLOAT(L, 4);
	//	float o = CHECK_FLOAT(L, 5);
	//	uint32 duration = luaL_checkint(L, 6);
	//	float scale = (float)luaL_optnumber(L,7,1.0f);
	//	if (!entry_id || !duration)
	//	{
	//		lua_pushnil(L);
	//		return 1;
	//	}

	//	GameObjectInfo *goi = GameObjectNameStorage.LookupEntry(entry_id);
	//	if (goi == NULL)
	//	{
	//		dropWarning("Invalid GameObject ID specified: %u", entry_id);
	//		lua_error(L);
	//		return 0;
	//	}
	//	GameObject *pC = ptr->GetMapMgr()->CreateGameObject(entry_id);
	//	if(pC == NULL)
	//	{
	//		lua_pushnil(L);
	//		return 1;
	//	}
	//	pC->m_spawn=0;
	//	pC->CreateFromProto(entry_id, ptr->GetMapId(), (float)x, (float)y, (float)z, (float)o);
	//	pC->SetMapId(ptr->GetMapId());
	//	pC->SetInstanceID(ptr->GetInstanceID());
	//	pC->SetFloatValue(OBJECT_FIELD_SCALE_X, scale);
	//	pC->Spawn(ptr->GetMapMgr());
	//	if(duration)
	//	{
	//		sEventMgr.AddEvent(pC, &GameObject::ExpireAndDelete, EVENT_GAMEOBJECT_UPDATE, duration, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	//	}
	//	PUSH_GO(L,pC);
	//	return 1;
	//}

	//int CalcDistance(lua_State * L, GameObject * ptr)
	//{
	//	Object * ob = CHECK_OBJECT(L,1);
	//	if (ob && ptr)
	//		lua_pushnumber(L, ptr->CalcDistance(ob));
	//	return 1;
	//}

	//int GetSpawnX(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET_INT(TYPEID_GAMEOBJECT);
	//	lua_pushnumber(L,ptr->GetSpawnX());
	//	return 1;
	//}

	//int GetSpawnY(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET_INT(TYPEID_GAMEOBJECT);
	//	lua_pushnumber(L,ptr->GetSpawnY());
	//	return 1;
	//}

	//int GetSpawnZ(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET_INT(TYPEID_GAMEOBJECT);
	//	lua_pushnumber(L,ptr->GetSpawnZ());
	//	return 1;
	//}

	//int GetSpawnO(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET_INT(TYPEID_GAMEOBJECT);
	//	lua_pushnumber(L,ptr->GetSpawnO());
	//	return 1;
	//}

	//int GetX(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET_INT(TYPEID_GAMEOBJECT);
	//	lua_pushnumber(L,ptr->GetPositionX());
	//	return 1;
	//}

	//int GetY(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET_INT(TYPEID_GAMEOBJECT);
	//	lua_pushnumber(L,ptr->GetPositionY());
	//	return 1;
	//}

	//int GetZ(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET_INT(TYPEID_GAMEOBJECT);if(ptr)
	//	lua_pushnumber(L,ptr->GetPositionZ());
	//	return 1;
	//}

	//int GetO(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET_INT(TYPEID_GAMEOBJECT);
	//	lua_pushnumber(L,ptr->GetOrientation());
	//	return 1;
	//}

	//int GetInRangePlayersCount(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET_INT(TYPEID_GAMEOBJECT);
	//	lua_pushnumber(L,ptr->GetInRangePlayersCount());
	//	return 1;
	//}

	//int GetEntry(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET_INT(TYPEID_GAMEOBJECT);
	//	lua_pushnumber(L,ptr->GetEntry());
	//	return 1;
	//}

	//int SetOrientation(lua_State * L, GameObject * ptr)
	//{
	//	float newo = CHECK_FLOAT(L, 1);
	//	if (!newo | !ptr)
	//		return 0;
	//	ptr->SetOrientation(newo);
	//	return 0;
	//}

	//int CalcRadAngle(lua_State * L, GameObject * ptr)
	//{
	//	float x = CHECK_FLOAT(L,1 );
	//	float y = CHECK_FLOAT(L, 2);
	//	float x2 = CHECK_FLOAT(L, 3);
	//	float y2 = CHECK_FLOAT(L, 4);
	//	if(!x || !y|| !x2 || !y2|| !ptr)
	//		return 0;
	//	lua_pushnumber(L,ptr->calcRadAngle(x,y,x2,y2));
	//	return 1;
	//}

	//int GetInstanceID(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	if(ptr->GetMapMgr()->GetMapInfo()->type == INSTANCE_NULL)
	//		lua_pushnil(L);
	//	else
	//		lua_pushinteger(L,ptr->GetInstanceID());
	//	return 1;
	//}

	//int GetInRangePlayers(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	uint32 count = 0;
	//	lua_newtable(L);
	//	for(std::set<Object*>::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd(); itr++)
	//	{
	//		if((*itr)->IsUnit())
	//		{
	//			count++,
	//			lua_pushinteger(L,count);
	//			PUSH_UNIT(L,*itr);
	//			lua_rawset(L,-3);
	//		}
	//	}
	//	return 1;
	//}

	//int GetInRangeGameObjects(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	uint32 count = 0;
	//	lua_newtable(L);
	//	for (std::set<Object*>::iterator itr = ptr->GetInRangeSetBegin();itr!= ptr->GetInRangeSetEnd();itr++)
	//	{
	//		if( (*itr) ->GetTypeId() == TYPEID_GAMEOBJECT)
	//		{
	//			count++,
	//			lua_pushinteger(L,count);
	//			PUSH_GO(L,*itr);
	//			lua_rawset(L,-3);
	//		}
	//	}
	//	return 1;
	//}

	//int IsInFront(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	Object * target = CHECK_OBJECT(L, 1);
	//	if (!target)
	//	{
	//		lua_pushnil(L);
	//		return 1;
	//	}
	//	if(ptr->isInFront(target))
	//		lua_pushboolean(L, 1);
	//	else
	//		lua_pushboolean(L, 0);
	//	return 1;
	//}

	//int IsInBack(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	Object * target = CHECK_OBJECT(L, 1);
	//	if (!target)
	//	{
	//		lua_pushnil(L);
	//		return 1;
	//	}
	//	if(ptr->isInBack(target))
	//		lua_pushboolean(L, 1);
	//	else
	//		lua_pushboolean(L, 0);
	//	return 1;
	//}

	//int GetUInt32Value(lua_State * L, GameObject * ptr)
	//{
	//	int field = luaL_checkint(L,1);
	//	if (ptr && field > 0)
	//		lua_pushinteger(L,ptr->GetUInt32Value(field));
	//	else
	//		lua_pushnil(L);
	//	return 1;
	//}

	//int GetUInt64Value(lua_State * L, GameObject * ptr)
	//{
	//	int field = luaL_checkint(L,1);
	//	if (ptr && field)
	//		PUSH_GUID(L,ptr->GetUInt64Value(field));
	//	else
	//		lua_pushnil(L);
	//	return 1;
	//}

	//int SetUInt32Value(lua_State * L, GameObject * ptr)
	//{
	//	int field = luaL_checkint(L,1);
	//	int value = luaL_checkint(L,2);
	//	if (ptr && field)
	//		ptr->SetUInt32Value(field,value);
	//	return 0;
	//}

	//int SetUInt64Value(lua_State * L, GameObject * ptr)
	//{
	//	int field = luaL_checkint(L,1);
	//	uint64 guid = CHECK_GUID(L,1);
	//	if (ptr && field)
	//		ptr->SetUInt64Value(field,guid);
	//	return 0;
	//}

	//int SetFloatValue(lua_State * L, GameObject * ptr)
	//{
	//	int field = luaL_checkint(L,1);
	//	float value = CHECK_FLOAT(L,2);
	//	if (ptr)
	//		ptr->SetFloatValue(field,value);
	//	return 0;
	//}

	//int Update(lua_State * L, GameObject* ptr)
 //   {	//just despawns/respawns to update GO visuals
	//	//credits: Sadikum
 //       CHECK_TYPEID(TYPEID_GAMEOBJECT);
	//	MapMgr * mapmgr = ptr->GetMapMgr();
 //       uint32 NewGuid = mapmgr->GenerateGameobjectGuid();
 //       ptr->RemoveFromWorld(true);
 //       ptr->SetNewGuid(NewGuid);
 //       ptr->SaveToDB();
 //       ptr->PushToWorld(mapmgr);
 //       return 0;
 //   }

	//int GetFloatValue(lua_State * L, GameObject * ptr)
	//{
	//	int field = luaL_checkint(L,1);
	//	if( ptr && field)
	//		lua_pushnumber(L,ptr->GetFloatValue(field));
	//	else
	//		lua_pushnil(L);
	//	return 1;
	//}

	//int ModUInt32Value(lua_State * L, GameObject * ptr)
	//{
	//	int field = luaL_checkint(L,1);
	//	int value = luaL_checkint(L,2);
	//	if (ptr && field)
	//		ptr->ModSignedInt32Value(field,value);
	//	return 0;
	//}

	//int CastSpell(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID(TYPEID_GAMEOBJECT);
	//	uint32 sp = CHECK_ULONG(L,1);
	//	if (!sp) return 0;
	//	Spell * spp = new Spell(ptr,dbcSpell.LookupEntry(sp),true,NULL);
	//	SpellCastTargets tar(ptr->GetGUID());
	//	spp->prepare(&tar);
	//	return 0;
	//}

	//int FullCastSpell(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID(TYPEID_GAMEOBJECT);
	//	uint32 sp = CHECK_ULONG(L,1);
	//	if (!sp) return 0;
	//	Spell * spp = new Spell(ptr,dbcSpell.LookupEntry(sp),false,NULL);
	//	SpellCastTargets tar(ptr->GetGUID());
	//	spp->prepare(&tar);
	//	return 0;
	//}

	//int CastSpellOnTarget(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID(TYPEID_GAMEOBJECT);
	//	uint32 sp = CHECK_ULONG(L,1);
	//	Unit * target = CHECK_UNIT(L,2);
	//	if (!sp || target==NULL) return 0;
	//	Spell * spp = new Spell(ptr,dbcSpell.LookupEntry(sp),true,NULL);
	//	spp->m_targets.m_unitTarget = target->GetGUID();
	//	//prepare digest
	//	SpellCastTargets tar(target->GetGUID());
	//	spp->m_targets = tar;
	//	spp->SendSpellStart();
	//	spp->cast(false);
	//	return 0;
	//}

	//int GetGameTime(lua_State * L, GameObject * ptr)
	//{
	//	lua_pushnumber(L, ((uint32)sWorld.GetGameTime()));
	//	Log.Notice("LuaEngine","Please use the global function GetGameTime instead. This GO-based one is deprecated.");
	//	return 1;
	//}

	//int GetLandHeight(lua_State * L, GameObject * ptr)
	//{
	//	float x = CHECK_FLOAT(L,1);
	//	float y = CHECK_FLOAT(L,2);
	//	if (!ptr || !x || !y) 
	//		lua_pushnil(L);
	//	else 
	//	{
	//		float lH = ptr->GetMapMgr()->GetLandHeight(x,y);
	//		lua_pushnumber(L, lH);
	//	}
	//	return 1;
	//}

	//int SetZoneWeather(lua_State * L, GameObject * ptr)
	//{
	//	/*
	//	WEATHER_TYPE_NORMAL            = 0, // NORMAL (SUNNY)
	//	WEATHER_TYPE_FOG               = 1, // FOG
	//	WEATHER_TYPE_RAIN              = 2, // RAIN
	//	WEATHER_TYPE_HEAVY_RAIN        = 4, // HEAVY_RAIN
	//	WEATHER_TYPE_SNOW              = 8, // SNOW
	//	WEATHER_TYPE_SANDSTORM         = 16 // SANDSTORM
	//	*/
	//	uint32 zone_id = CHECK_ULONG(L,1);
	//	uint32 type = CHECK_ULONG(L, 2);
	//	float Density = CHECK_FLOAT(L, 3); //min: 0.30 max: 2.00
	//	if (Density<0.30f || Density>2.0f || !zone_id || !type)
	//		return 0;

	//	uint32 sound;
	//	if(Density<=0.30f)
	//		sound = 0;

	//	switch(type)
	//	{
	//		case 2:                                             //rain
	//		case 4:                                             
	//			if(Density  <0.40f)
	//				 sound = 8533;
	//			else if(Density  <0.70f)
	//				sound = 8534;
	//			else
	//				sound = 8535;
	//			break;
	//		case 8:                                             //snow
	//			if(Density  <0.40f)
	//				sound = 8536;
	//			else if(Density  <0.70f)
	//				sound = 8537;
	//			else
	//				sound = 8538;
	//			break;
	//		case 16:                                             //storm
	//			if(Density  <0.40f)
	//				sound = 8556;
	//			else if(Density  <0.70f)
	//				sound = 8557;
	//			else
	//				sound = 8558;
	//			break;
	//		default:											//no sound
	//			sound = 0;
	//			break;
	//	}
	//	WorldPacket data(SMSG_WEATHER, 9);
	//	data.Initialize(SMSG_WEATHER);
	//	if(type == 0 ) // set all parameter to 0 for sunny.
	//		data << uint32(0) << float(0) << uint32(0) << uint8(0);		
	//	else if (type == 1) // No sound/density for fog
	//		data << type << float(0) << uint32(0) << uint8(0);		
	//	else
	//		data << type << Density << sound << uint8(0) ;

	//	sWorld.SendZoneMessage(&data, zone_id, 0);

	//	return 0;
	//}

	//int GetDistanceYards(lua_State * L, GameObject * ptr)
	//{
	//	Unit * target = CHECK_UNIT(L, 1);
	//	if(!ptr || !target)
	//		lua_pushnil(L);
	//	else 
	//	{
	//		LocationVector vec = ptr->GetPosition();
	//		lua_pushnumber(L,(float)vec.Distance(target->GetPosition()));
	//	}
	//	return 1;
	//}

	//int PhaseSet(lua_State * L, GameObject * ptr)
	//{
	//	uint32 newphase = CHECK_ULONG(L,1);
	//	bool Save = (luaL_optint(L,2,false)>0 ? true:false);
	//	if (!ptr)
	//		return 0;
	//	ptr->Phase(PHASE_SET, newphase);
	//	if (ptr->m_spawn) 
	//		ptr->m_spawn->phase = newphase; 
	//	if (Save)
	//	{
	//		ptr->SaveToDB();
	//		ptr->m_loadedFromDB = true;
	//	}
	//	return 0;
	//}

	//int PhaseAdd(lua_State * L, GameObject * ptr)
	//{
	//	uint32 newphase = CHECK_ULONG(L,1);
	//	bool Save = (luaL_optint(L,2,false)>0 ? true:false);
	//	if (!ptr)
	//		return 0;
	//	ptr->Phase(PHASE_ADD, newphase);
	//	if (ptr->m_spawn) 
	//		ptr->m_spawn->phase |= newphase; 
	//	if (Save)
	//	{
	//		ptr->SaveToDB();
	//		ptr->m_loadedFromDB = true;
	//	}
	//	return 0;
	//}

	//int PhaseDelete(lua_State * L, GameObject * ptr)
	//{
	//	uint32 newphase = CHECK_ULONG(L,1);
	//	bool Save = (luaL_optint(L,2,false)>0 ? true:false);
	//	if (!ptr)
	//		return 0;
	//	ptr->Phase(PHASE_DEL, newphase);
	//	if (ptr->m_spawn) 
	//		ptr->m_spawn->phase &= ~newphase; 
	//	if (Save)
	//	{
	//		ptr->SaveToDB();
	//		ptr->m_loadedFromDB = true;
	//	}
	//	return 0;
	//}

	//int GetPhase(lua_State * L, GameObject * ptr)
	//{
	//	if (ptr)
	//		lua_pushnumber(L,ptr->m_phase);
	//	else
	//		lua_pushnil(L);
	//	return 1;
	//}

	//int SendPacket(lua_State * L, GameObject * ptr)
	//{
	//	WorldPacket * data = CHECK_PACKET(L,1);
	//	bool self = CHECK_BOOL(L,2);
	//	if (ptr != NULL || data != NULL)
	//		ptr->SendMessageToSet(data, self);
	//	return 0;
	//}

	//int SendPacketToZone(lua_State * L, GameObject * ptr)
	//{
	//	WorldPacket * data = CHECK_PACKET(L,1);
	//	uint32 zone_id = CHECK_ULONG(L, 2);
	//	if (data != NULL)
	//		sWorld.SendZoneMessage(data,zone_id);
	//	return 0;
	//}

	//int SendPacketToInstance(lua_State * L, GameObject * ptr)
	//{
	//	WorldPacket * data = CHECK_PACKET(L,1);
	//	uint32 instance_id = CHECK_ULONG(L,2);
	//	if (data != NULL)
	//		sWorld.SendInstanceMessage(data,instance_id);
	//	return 0;
	//}

	//int SendPacketToWorld(lua_State * L, GameObject * ptr)
	//{
	//	WorldPacket * data = CHECK_PACKET(L,1);
	//	if (data != NULL)
	//		sWorld.SendGlobalMessage(data);
	//	return 0;
	//}

	//int FullCastSpellOnTarget(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID(TYPEID_GAMEOBJECT);
	//	uint32 sp = CHECK_ULONG(L,1);
	//	Unit * target = CHECK_UNIT(L,2);
	//	if (!sp) return 0;
	//	Spell * spp = new Spell(ptr,dbcSpell.LookupEntry(sp),false,NULL);
	//	SpellCastTargets tar(target->GetGUID());
	//	spp->prepare(&tar);
	//	return 0;
	//}

	//int GetGUID(lua_State * L, GameObject* ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	PUSH_GUID(L,ptr->GetGUID());
	//	return 1;
	//}

	//int PerformWorldDBQuery(lua_State * L, GameObject* ptr)
	//{
	//	Log.Notice("LuaEngine", "GO:PerformWorldDBQuery(...) is outdated! Please use the global function WorldDBQuery(...) instead! (This warning will be removed in some revisions then your Scripts will abort if you do not change that!)");
	//	return 0;
	//}

	//int PerformCharDBQuery(lua_State * L, GameObject* ptr)
	//{
	//	Log.Notice("LuaEngine", "GO:PerformCharDBQuery(...) is outdated! Please use the global function CharDBQuery(...) instead! (This warning will be removed in some revisions then your Scripts will abort if you do not change that!)");
	//	return 0;
	//}

	//int IsActive(lua_State * L, GameObject* ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	lua_pushboolean(L, (ptr->IsActive() ? 1 : 0));
	//	return 1;
	//}

	//int Activate(lua_State * L, GameObject* ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	if (ptr->GetUInt32Value(GAMEOBJECT_DYNAMIC) == 1)
	//	{
	//		ptr->SetUInt32Value(GAMEOBJECT_DYNAMIC, 0);
	//	} 
	//	else
	//	{
	//		ptr->SetUInt32Value(GAMEOBJECT_DYNAMIC, 1);
	//	}
	//	return 1;
	//}
	//
	//int DespawnObject(lua_State * L, GameObject* ptr)
	//{
	//	CHECK_TYPEID(TYPEID_GAMEOBJECT);
	//	int delay = luaL_checkint(L,1);
	//	int respawntime = luaL_checkint(L,2);
	//	if (!delay) 
	//		delay=1; //Delay 0 might cause bugs
	//	ptr->Despawn(delay,respawntime);
	//	return 0;
	//}

	//int AddLoot(lua_State * L, GameObject* ptr)
	//{
	//	CHECK_TYPEID(TYPEID_GAMEOBJECT);
	//	uint32 itemid = luaL_checkint(L,1);
	//	uint32 mincount = luaL_checkint(L,2);
	//	uint32 maxcount = luaL_checkint(L,3);
	//	uint32 ffa_loot = luaL_checkint(L,4);
	//	lootmgr.AddLoot(&ptr->loot,itemid,mincount,maxcount,ffa_loot);
	//	return 0;
	//}

	//int GetInstanceOwner(lua_State * L, GameObject * ptr)
	//{
	//	MapInfo *pMapinfo = WorldMapInfoStorage.LookupEntry(ptr->GetMapId());
	//	if (pMapinfo) //this block = IsInInstace()
	//	{
	//		if (pMapinfo->type != INSTANCE_NULL)
	//		{	
	//			lua_pushboolean(L,0);
	//			return 1;
	//		}
	//	}
	//	Instance * pInstance = sInstanceMgr.GetInstanceByIds(ptr->GetMapId(), ptr->GetInstanceID());
	//	if (pInstance->m_creatorGuid != 0) // creator guid is 0 if its owned by a group.
	//	{
	//		Player * owner = pInstance->m_mapMgr->GetPlayer(pInstance->m_creatorGuid);
	//		PUSH_UNIT(L,owner);
	//	}
	//	else
	//	{
	//		uint32 gId = pInstance->m_creatorGroup;
	//		PUSH_UNIT(L,objmgr.GetGroupById(gId)->GetLeader()->m_loggedInPlayer);
	//	}
	//	return 1;
	//}

	//int GetDungeonDifficulty(lua_State * L, GameObject * ptr)
	//{
	//	MapInfo *pMapinfo = WorldMapInfoStorage.LookupEntry(ptr->GetMapId());
	//	if (pMapinfo) //this block = IsInInstace()
	//	{
	//		if (pMapinfo->type != INSTANCE_NULL)
	//		{	
	//			lua_pushboolean(L,0);
	//			return 1;
	//		}
	//	}
	//	Instance * pInstance = sInstanceMgr.GetInstanceByIds(ptr->GetMapId(), ptr->GetInstanceID());
	//	lua_pushnumber(L, pInstance->m_difficulty);
	//	return 1;
	//}

	//int SetDungeonDifficulty(lua_State * L, GameObject * ptr)
	//{
	//	uint8 difficulty = luaL_checkint(L,1);
	//	MapInfo *pMapinfo = WorldMapInfoStorage.LookupEntry(ptr->GetMapId());
	//	if (pMapinfo) //this block = IsInInstace()
	//	{
	//		if (pMapinfo->type != INSTANCE_NULL)
	//		{	
	//			lua_pushboolean(L,0);
	//			return 1;
	//		}
	//	}
	//	Instance * pInstance = sInstanceMgr.GetInstanceByIds(ptr->GetMapId(), ptr->GetInstanceID());
	//	pInstance->m_difficulty = difficulty;
	//	lua_pushboolean(L,1);
	//	return 1;
	//}

	//int SetByteValue(lua_State * L, GameObject * ptr)
	//{
	//	if (!ptr) return 0;
	//	uint32 index = luaL_checkint(L,1);
	//	uint32 index1 = luaL_checkint(L,2);
	//	uint8 value = luaL_checkint(L,3);
	//	ptr->SetByte(index,index1,value);
	//	return 0;
	//}

	//int GetByteValue(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET_INT(TYPEID_GAMEOBJECT);
	//	uint32 index = luaL_checkint(L,1);
	//	uint32 index1 = luaL_checkint(L,2);
	//	lua_pushinteger(L,ptr->GetByte(index,index1));
	//	return 1;
	//}

	//int HasFlag(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	uint32 index = luaL_checkint(L,1);
	//	uint32 flag = luaL_checkint(L,2);
	//	lua_pushboolean(L, ptr->HasFlag(index,flag) ? 1 : 0);
	//	return 1;
	//}

	//int IsInPhase(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET(TYPEID_GAMEOBJECT);
	//	uint32 phase = luaL_checkint(L,1);
	//	lua_pushboolean(L, ((ptr->m_phase & phase) != 0) ? 1 : 0);
	//	return 1;
	//}

	//int GetSpawnId(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET_INT(TYPEID_GAMEOBJECT);
	//	lua_pushnumber(L, ptr->m_spawn != NULL ? ptr->m_spawn->id : 0);
	//	return 1;
	//}

	//int GetAreaId(lua_State * L, GameObject * ptr)
	//{
	//	CHECK_TYPEID_RET_INT(TYPEID_GAMEOBJECT);
	//	lua_pushnumber(L, ( ptr->GetMapMgr()->GetAreaID(ptr->GetPositionX(), ptr->GetPositionY()) ) );
	//	return 1;
	//}

	//int SetPosition(lua_State * L, GameObject * ptr)
	//{
	//	if (!ptr) return 0;
	//	uint32 NewGuid = ptr->GetMapMgr()->GenerateGameobjectGuid();
 //       ptr->RemoveFromWorld(true);
 //       ptr->SetNewGuid(NewGuid);
	//	float x = CHECK_FLOAT(L,1);
	//	float y = CHECK_FLOAT(L,2);
	//	float z = CHECK_FLOAT(L,3);
	//	float o = CHECK_FLOAT(L,4);
	//	ptr->SetPosition(x, y, z, o);
	//	ptr->AddToWorld();
	//	return 0;
	//}

	//int GetObjectType(lua_State * L, GameObject * ptr)
	//{
	//	if (!ptr) 
	//	{ 
	//		lua_pushnil(L); 
	//		return 1; 
	//	}
	//	lua_pushstring(L, "GameObject");
	//	return 1;
	//}
}
