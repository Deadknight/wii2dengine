#ifndef __LUA_UNITFUNCTIONS_H
#define __LUA_UNITFUNCTIONS_H

namespace luaUnit
{
	LUAFUNC int Unit_GetHealth(lua_State * L, T * ptr);
	LUAFUNC int Unit_SetHealth(lua_State * L, T * ptr);
	LUAFUNC int Unit_GetHealthPercent(lua_State * L, T * ptr);
	LUAFUNC int Unit_GetHealthMax(lua_State * L, T * ptr);
	LUAFUNC int Unit_SetHealthMax(lua_State * L, T * ptr);
	LUAFUNC int Unit_GetHealthBase(lua_State * L, T * ptr);
	LUAFUNC int Unit_SetHealthBase(lua_State * L, T * ptr);
	LUAFUNC int Unit_GetMana(lua_State * L, T * ptr);
	LUAFUNC int Unit_SetMana(lua_State * L, T * ptr);
	LUAFUNC int Unit_GetManaPercent(lua_State * L, T * ptr);
	LUAFUNC int Unit_GetManaMax(lua_State * L, T * ptr);
	LUAFUNC int Unit_SetManaMax(lua_State * L, T * ptr);
	LUAFUNC int Unit_GetManaBase(lua_State * L, T * ptr);
	LUAFUNC int Unit_SetManaBase(lua_State * L, T * ptr);
	LUAFUNC int Unit_AddWeapon(lua_State * L, T * ptr);
	LUAFUNC int Unit_SetSelectedWeapon(lua_State * L, T * ptr);
	LUAFUNC int Unit_ChangeSprite(lua_State * L, T * ptr);


	/*int GossipCreateMenu(lua_State * L, Unit * ptr);
	int GossipMenuAddItem(lua_State * L, Unit * ptr);
	int GossipSendMenu(lua_State * L, Unit * ptr);
	int GossipComplete(lua_State * L, Unit * ptr);
	int GossipSendPOI(lua_State * L, Unit * ptr);
	int GossipMiscAction(lua_State * L, Unit * ptr);

	//////////[GET]///////////
	int GetPlayerRace(lua_State * L, Unit * ptr);
	int GetCurrentSpellId(lua_State * L, Unit * ptr);
	int GetStanding(lua_State * L, Unit * ptr);
	int GetMainTank(lua_State * L, Unit * ptr);
	int GetAddTank(lua_State * L, Unit * ptr);
	int GetX(lua_State * L, Unit * ptr);
	int GetY(lua_State * L, Unit * ptr);
	int GetZ(lua_State * L, Unit * ptr);
	int GetO(lua_State * L, Unit * ptr);
	int GetTauntedBy(lua_State * L, Unit * ptr);
	int GetSoulLinkedWith(lua_State * L, Unit * ptr);
	int GetItemCount(lua_State * L, Unit * ptr);
	int GetName(lua_State * L, Unit * ptr);
	int GetHealthPct(lua_State * L, Unit * ptr);
	int GetManaPct(lua_State * L, Unit * ptr);
	int GetInstanceID(lua_State * L, Unit * ptr);
	int GetClosestPlayer(lua_State * L, Unit * ptr);
	int GetRandomPlayer(lua_State * L, Unit * ptr);
	int GetRandomFriend(lua_State * L, Unit * ptr);
	int GetUnitBySqlId(lua_State * L, Unit * ptr);
	int GetPlayerClass(lua_State * L, Unit * ptr);
	int GetHealth(lua_State * L, Unit * ptr);
	int GetMaxHealth(lua_State * L, Unit * ptr);
	int GetCreatureNearestCoords(lua_State * L, Unit * ptr);
	int GetGameObjectNearestCoords(lua_State *L, Unit * ptr);
	int GetDistance(lua_State * L, Unit * ptr);
	int GetGUID(lua_State * L, Unit * ptr);
	int GetZoneId(lua_State *L, Unit * ptr);
	int GetMaxMana(lua_State * L, Unit * ptr);
	int GetMana(lua_State * L, Unit * ptr);
	int GetCurrentSpell(lua_State * L, Unit * ptr);
	int GetSpawnO(lua_State * L, Unit * ptr);
	int GetSpawnZ(lua_State * L, Unit * ptr);
	int GetSpawnY(lua_State * L, Unit * ptr);
	int GetSpawnX(lua_State * L, Unit * ptr);
	int GetInRangePlayersCount(lua_State * L, Unit * ptr);
	int GetUInt32Value(lua_State * L, Unit * ptr);
	int GetUInt64Value(lua_State * L, Unit * ptr);
	int GetFloatValue(lua_State * L, Unit * ptr);
	int GetAIState(lua_State * L, Unit * ptr);
	int GetCurrentSpell(lua_State * L, Unit * ptr);
	int GetInRangeGameObjects(lua_State * L, Unit * ptr);
	int GetInRangePlayers(lua_State * L, Unit * ptr);
	int GetAITargets(lua_State * L, Unit * ptr);
	int GetUnitByGUID(lua_State * L, Unit * ptr);
	int GetInRangeObjectsCount(lua_State * L, Unit * ptr);
	int GetAITargetsCount(lua_State * L, Unit * ptr);
	int GetUnitToFollow(lua_State * L, Unit * ptr);
	int GetNextTarget(lua_State * L, Unit * ptr);
	int GetPetOwner(lua_State * L, Unit * ptr);
	int GetEntry(lua_State * L, Unit * ptr);
	int GetFaction(lua_State * L, Unit *ptr);
	int GetThreatByPtr(lua_State * L, Unit * ptr);
	int GetInRangeFriends(lua_State * L, Unit * ptr);
	int GetPowerType(lua_State * L, Unit * ptr);
	int GetMapId(lua_State * L, Unit * ptr);
	int GetFactionStanding(lua_State * L, Unit * ptr);
	int GetLevel(lua_State * L, Unit * ptr);
	int GetStealthLevel(lua_State * L, Unit * ptr);
	int GetRandomEnemy(lua_State * L, Unit * ptr);
	int GetTarget(lua_State * L, Unit * ptr);
	int GetSelection(lua_State * L, Unit * ptr);
	int GetMaxSkill(lua_State * L, Unit * ptr);
	int GetCurrentSkill(lua_State * L, Unit * ptr);
	int GetGuildName(lua_State * L, Unit * ptr);
	int GetAccountName(lua_State * L, Unit * ptr);
	int GetGamemasterLevel(lua_State * L, Unit * ptr);
	int GetTeam(lua_State * L, Unit * ptr);
	//Kian - Added Commands.
	int GetDisplay(lua_State * L, Unit * ptr);
	int GetNativeDisplay(lua_State * L, Unit * ptr);

	////////////////////////
	//Bools(Is? commands)///
	////////////////////////
	int IsPlayerAttacking(lua_State * L, Unit * ptr);
	int IsPlayerMoving(lua_State * L, Unit * ptr);
	//int IsPlayerAtWar(lua_State * L, Unit * ptr);
	int IsPlayer(lua_State * L, Unit * ptr);
	int IsCreature(lua_State * L, Unit * ptr);
	int IsInCombat(lua_State * L, Unit * ptr);
	int IsAlive(lua_State * L, Unit * ptr);
	int IsDead(lua_State * L, Unit * ptr);
	int IsInWorld(lua_State * L, Unit * ptr);
	int IsCreatureMoving(lua_State * L, Unit * ptr );
	int IsFlying(lua_State * L, Unit * ptr);
	int IsInFront(lua_State * L, Unit * ptr);
	int IsInBack(lua_State * L, Unit * ptr);
	int IsPacified(lua_State * L, Unit * ptr);
	int IsFeared(lua_State * L, Unit * ptr);
	int IsStunned(lua_State * L, Unit * ptr);
	int HasInRangeObjects(lua_State * L, Unit * ptr);
	int HasQuest(lua_State * L, Unit * ptr);
	int HasTitle(lua_State * L, Unit * ptr);
	int HasSkill(lua_State * L, Unit * ptr);
	int HasSpell(lua_State * L, Unit * ptr);
	int HasItem(lua_State * L, Unit * ptr);
	int IsInWater(lua_State * L, Unit * ptr);
	int IsInArc(lua_State * L, Unit * ptr);
	int IsPet(lua_State * L, Unit * ptr);
	int IsPoisoned(lua_State * L, Unit * ptr);
	int IsStealthed(lua_State * L, Unit * ptr);
	int CanUseCommand(lua_State * L, Unit * ptr);
        int IsMounted(lua_State * L, Unit * ptr);



	//////////////////////
	///////OTHERS/////////
	//////////////////////
	int RemoveFlag(lua_State * L, Unit * ptr);
	int AdvanceSkill(lua_State * L, Unit * ptr);
	int AddSkill(lua_State * L, Unit * ptr);
	int RemoveSkill(lua_State * L, Unit * ptr);
	int PlaySpellVisual(lua_State * L, Unit * ptr);
	int RemoveThreatByPtr(lua_State * L, Unit * ptr);
	int EventCastSpell(lua_State * L, Unit * ptr);
	int AttackReaction(lua_State * L, Unit * ptr);
	int DismissPet(lua_State * L, Unit * ptr);
	int HandleEvent(lua_State * L, Unit * ptr);
	int SetMoveRunFlag(lua_State * L, Unit * ptr);
	int SendChatMessage(lua_State * L, Unit * ptr);
	int MoveTo(lua_State * L, Unit * ptr);
	int SetMovementType(lua_State * L, Unit * ptr);
	int CastSpell(lua_State * L, Unit * ptr);
	int FullCastSpell(lua_State * L, Unit * ptr);
	int FullCastSpellOnTarget(lua_State * L, Unit * ptr);
	int SpawnGameObject(lua_State * L, Unit * ptr);
	int SpawnCreature(lua_State * L, Unit * ptr);
	int RegisterEvent(lua_State * L, Unit * ptr);
	int RemoveEvents(lua_State * L, Unit * ptr);
	int SendBroadcastMessage(lua_State * L, Unit * ptr);
	int SendAreaTriggerMessage(lua_State * L, Unit * ptr);
	int MarkQuestObjectiveAsComplete(lua_State * L, Unit * ptr);
	int LearnSpell(lua_State * L, Unit* ptr);
	int UnlearnSpell(lua_State * L, Unit * ptr);
	int HasFinishedQuest(lua_State * L, Unit * ptr);
	int ClearThreatList(lua_State * L, Unit * ptr);
	int ChangeTarget(lua_State * L, Unit * ptr);
	int Emote(lua_State * L, Unit * ptr);
	int Despawn(lua_State * L, Unit * ptr);
	int PlaySoundToSet(lua_State * L, Unit * ptr);
	int RemoveAura(lua_State * L, Unit * ptr);
	int StopMovement(lua_State * L, Unit * ptr);
	int AddItem(lua_State * L, Unit * ptr);
	int RemoveItem(lua_State * L, Unit * ptr);
	int CreateCustomWaypointMap(lua_State * L, Unit * ptr);
	int CreateWaypoint(lua_State * L, Unit * ptr);
	int DestroyCustomWaypointMap(lua_State * L, Unit * ptr);
	int MoveToWaypoint(lua_State * L, Unit * ptr);
	int TeleportUnit(lua_State * L, Unit * ptr);
	int ClearHateList(lua_State * L, Unit * ptr);
	int WipeHateList(lua_State * L, Unit * ptr);
	int WipeTargetList(lua_State * L, Unit * ptr);
	int WipeCurrentTarget(lua_State * L, Unit * ptr);
	int CastSpellAoF(lua_State * L, Unit * ptr);
	int RemoveAllAuras(lua_State *L, Unit * ptr);
	int ReturnToSpawnPoint(lua_State * L, Unit * ptr);
	int HasAura(lua_State * L, Unit * ptr);
	int Land(lua_State * L, Unit * ptr);
	int CancelSpell(lua_State * L, Unit * ptr);
	int Root(lua_State * L, Unit * ptr);
	int Unroot(lua_State * L, Unit * ptr);
	int CalcDistance(lua_State * L, Unit * ptr);
	int ModUInt32Value(lua_State * L, Unit * ptr);
	int ModFloatValue(lua_State * L, Unit * ptr);
	int SendPacket(lua_State * L, Unit * ptr);
	int AdvanceQuestObjective(lua_State * L, Unit * ptr);
	int Heal(lua_State * L, Unit * ptr);
	int Energize(lua_State * L, Unit * ptr);
	int SendChatMessageAlternateEntry(lua_State * L, Unit * ptr);
	int SendChatMessageToPlayer(lua_State * L, Unit * ptr);
	int Strike(lua_State * L, Unit * ptr);
	int Kill(lua_State * L, Unit * ptr);
	int DealDamage(lua_State * L, Unit * ptr);
	int CreateGuardian(lua_State * L, Unit * ptr);
	int CalcToDistance(lua_State * L, Unit * ptr);
	int CalcAngle(lua_State * L, Unit * ptr);
	int CalcRadAngle(lua_State * L, Unit * ptr);
	int IsInvisible(lua_State * L, Unit * ptr);
	int IsInvincible(lua_State * L, Unit * ptr);
	int ResurrectPlayer(lua_State * L, Unit * ptr);
	int KickPlayer(lua_State * L, Unit * ptr);
	int CanCallForHelp(lua_State * L, Unit * ptr);
	int CallForHelpHp(lua_State * L, Unit * ptr);
	int RemoveFromWorld(lua_State * L, Unit * ptr);
	int SpellNonMeleeDamageLog(lua_State * L, Unit * ptr);
	int ModThreat(lua_State * L, Unit * ptr);
	int AddAssistTargets(lua_State * L, Unit * ptr);
	int RemoveAurasByMechanic(lua_State * L, Unit * ptr);
	int RemoveAurasType(lua_State * L, Unit * ptr);
	int AddAura(lua_State * L, Unit * ptr);
	int InterruptSpell(lua_State * L, Unit * ptr);
	int RemoveStealth(lua_State * L, Unit * ptr);
	int RegisterAIUpdateEvent(lua_State * L, Unit * ptr);
	int ModifyAIUpdateEvent(lua_State * L, Unit * ptr);
	int RemoveAIUpdateEvent(lua_State * L, Unit * ptr);
	int deleteWaypoint(lua_State * L, Unit * ptr);
	int DealGoldCost(lua_State * L, Unit * ptr);
	int DealGoldMerit(lua_State * L, Unit * ptr);
	int DeMorph(lua_State * L, Unit * ptr);
	int Attack(lua_State * L, Unit * ptr);
	int MoveFly(lua_State * L, Unit * ptr);
	int NoRespawn(lua_State * L, Unit * ptr);
	int FlyCheat(lua_State * L, Unit * ptr);
	int StartQuest(lua_State * L, Unit * ptr);
	int FinishQuest(lua_State * L, Unit * ptr);
	int RepairAllPlayerItems(lua_State * L, Unit * ptr);
	int LifeTimeKills(lua_State * L, Unit * ptr);
	int ClearCooldownForSpell(lua_State * L, Unit * ptr);
	int ClearAllCooldowns(lua_State * L, Unit * ptr);
	int ResetAllTalents(lua_State * L, Unit * ptr);
	int RemovePvPFlag(lua_State * L, Unit * ptr);
	int RemoveNegativeAuras(lua_State * L, Unit * ptr);
	int EquipWeapons(lua_State * L, Unit * ptr);
	int Dismount(lua_State * L, Unit * ptr);
	int AdvanceAllSkills(lua_State * L, Unit * ptr);
	int Possess(lua_State * L, Unit * ptr);
	int Unpossess(lua_State * L, Unit * ptr);
	int SavePlayer(lua_State * L, Unit * ptr);
	int StartTaxi(lua_State * L, Unit * ptr);
	//Halestorm - Added Commands
	int StopChannel(lua_State * L, Unit * ptr);
	int ChannelSpell(lua_State * L, Unit * ptr);
	int EnableFlight(lua_State * L, Unit * ptr);
	int GetCoinage(lua_State * L, Unit * ptr);
	int FlagPvP(lua_State * L, Unit * ptr);
	//////////////////////////////////////////////////////////////////////////
	// WORLD PVP NOT SUPPORTED!
	//////////////////////////////////////////////////////////////////////////
	//int FlagWorldPvP(lua_State * L, Unit * ptr);
	//int DisableWorldPvP(lua_State * L, Unit * ptr);
	/////////////////////
	//////SetStuff///////
	/////////////////////
	int SetStealth(lua_State * L, Unit * ptr);
	int SetAIState(lua_State * L, Unit * ptr);
	int SetPlayerStanding(lua_State * L, Unit * ptr);
	int SetLevel(lua_State * L, Unit * ptr);
	int SetPlayerAtWar(lua_State * L, Unit * ptr);
	int SetCreatureName(lua_State * L, Unit * ptr);
	int SetDeathState(lua_State * L, Unit * ptr);
	int SetPowerType(lua_State * L, Unit * ptr);
	int SetAttackTimer(lua_State * L, Unit * ptr);
	int SetMana(lua_State * L, Unit * ptr);
	int SetMaxMana(lua_State * L, Unit * ptr);
	int SetHealth(lua_State * L, Unit * ptr);
	int SetMaxHealth(lua_State * L, Unit * ptr);
	int SetFlying(lua_State * L, Unit * ptr);
	int SetCombatCapable(lua_State * L, Unit * ptr);
	int SetCombatMeleeCapable(lua_State * L, Unit * ptr);
	int SetCombatRangedCapable(lua_State * L, Unit * ptr);
	int SetCombatSpellCapable(lua_State * L, Unit * ptr);
	int SetCombatTargetingCapable(lua_State * L, Unit * ptr);
	int SetNPCFlags(lua_State * L, Unit * ptr);
	int SetModel(lua_State * L, Unit * ptr);
	int SetScale(lua_State * L, Unit * ptr);
	int SetFaction(lua_State * L, Unit * ptr);
	int SetStandState(lua_State * L, Unit * ptr);
	int SetTauntedBy(lua_State * L, Unit * ptr);
	int SetSoulLinkedWith(lua_State * L, Unit * ptr);
	int SetInFront(lua_State * L, Unit * ptr);
	int SetHealthPct(lua_State * L, Unit * ptr);
	int SetOutOfCombatRange(lua_State * L, Unit * ptr);
	int ModifyRunSpeed(lua_State * L, Unit * ptr);
	int ModifyWalkSpeed(lua_State * L, Unit * ptr);
	int ModifyFlySpeed(lua_State * L, Unit * ptr);
	int SetRotation(lua_State * L, Unit * ptr);
	int SetOrientation(lua_State * L, Unit * ptr);
	int SetUInt32Value(lua_State * L, Unit * ptr);
	int SetUInt64Value(lua_State * L, Unit * ptr);
	int SetFloatValue(lua_State * L, Unit * ptr);
	int SetUnitToFollow(lua_State * L, Unit * ptr);
	int SetNextTarget(lua_State * L, Unit * ptr);
	int SetPetOwner(lua_State * L, Unit * ptr);
	int SetFacing(lua_State * L, Unit * ptr);
	int SetMount(lua_State * L, Unit * ptr);
	int SetKnownTitle(lua_State * L, Unit * ptr);
	//int SetWorldState(lua_State * L, Unit * ptr);
	//hypersniper's
	int GetGameTime(lua_State * L, Unit * ptr);
	int PlaySoundToPlayer(lua_State *L, Unit * ptr);
	int GetDuelState(lua_State * L, Unit * ptr);
	int SetPosition(lua_State * L, Unit * ptr);
	int CastSpellOnTarget(lua_State * L, Unit * ptr);
	int GetLandHeight(lua_State * L, Unit * ptr);
	int QuestAddStarter(lua_State * L, Unit * ptr);
	int QuestAddFinisher(lua_State * L, Unit * ptr);
	int SetPlayerSpeed(lua_State * L, Unit * ptr);
	int GiveHonor(lua_State * L, Unit * ptr);
	int SetBindPoint(lua_State * L, Unit * ptr);
	int SoftDisconnect(lua_State * L, Unit * ptr);
	int SetZoneWeather(lua_State * L, Unit * ptr);
	int SetPlayerWeather(lua_State * L, Unit * ptr);
	int SendPacketToPlayer(lua_State * L, Unit * ptr);
	int SendPacketToZone(lua_State * L, Unit * ptr);
	int SendPacketToWorld(lua_State * L, Unit * ptr);
	int SendPacketToInstance(lua_State * L, Unit * ptr);
	int PlayerSendChatMessage(lua_State * L, Unit * ptr);
	int GetDistanceYards(lua_State * L, Unit * ptr);
	int VendorAddItem(lua_State * L, Unit * ptr);
	int VendorRemoveItem(lua_State * L, Unit * ptr);
	int VendorRemoveAllItems(lua_State * L, Unit * ptr);
	int CreatureHasQuest(lua_State * L, Unit * ptr);
	int SendVendorWindow(lua_State * L, Unit * ptr);
	int SendTrainerWindow(lua_State * L, Unit * ptr);
	int SendInnkeeperWindow(lua_State * L, Unit * ptr);
	int SendBankWindow(lua_State * L, Unit * ptr);
	int SendAuctionWindow(lua_State * L, Unit * ptr);
	int SendBattlegroundWindow(lua_State * L, Unit * ptr);
	int GetInventoryItem(lua_State * L, Unit * ptr);
	int GetInventoryItemById(lua_State * L, Unit * ptr);
	int PhaseSet(lua_State * L, Unit * ptr);
	int PhaseAdd(lua_State * L, Unit * ptr);
	int PhaseDelete(lua_State * L, Unit * ptr);
	int GetPhase(lua_State * L, Unit * ptr);
	int AggroWithInRangeFriends(lua_State * L, Unit * ptr); //halestorm
	int GetPrimaryCombatTarget(lua_State * L, Unit * ptr);
	int MoveRandomArea(lua_State * L, Unit * ptr);
	int SendLootWindow(lua_State * L, Unit * ptr);
	int AddLoot(lua_State * L, Unit * ptr);
	int SetPacified(lua_State * L, Unit * ptr);
	//hypersniper: vehicle stuff
	int SpawnVehicle(lua_State * L, Unit * ptr);
	int SetVehicle(lua_State * L, Unit * ptr);
	int GetVehicle(lua_State * L, Unit * ptr);
	int RemoveFromVehicle(lua_State * L, Unit * ptr);
	int GetVehicleSeat(lua_State * L, Unit * ptr);
	int IsVehicle(lua_State * L, Unit * ptr);
	int GetPassengerCount(lua_State * L, Unit * ptr);
	int MoveVehicle(lua_State * L, Unit * ptr);
	//end vehicle stuff
	int SetPlayerLock(lua_State * L, Unit * ptr);
	int GetGroupPlayers(lua_State * L, Unit * ptr);
	int IsGm(lua_State * L, Unit * ptr);
	int GetDungeonDifficulty(lua_State * L, Unit * ptr);
	int GetGroupLeader(lua_State * L, Unit * ptr);
	int SetGroupLeader(lua_State * L, Unit * ptr);
	int AddGroupMember(lua_State * L, Unit * ptr);
	int SetDungeonDifficulty(lua_State * L, Unit * ptr);
	int ExpandToRaid(lua_State * L, Unit * ptr);
	int SendPacketToGroup(lua_State * L, Unit * ptr);
	int IsGroupFull(lua_State * L, Unit * ptr);
	//credits for next 9 funcs: alvanaar
	int IsGroupedWith(lua_State * L, Unit * ptr); 
	int GetTotalHonor(lua_State * L, Unit * ptr);
	int GetHonorToday(lua_State * L, Unit * ptr);
	int GetHonorYesterday(lua_State * L, Unit * ptr);
	int GetArenaPoints(lua_State * L, Unit * ptr);
	int AddArenaPoints(lua_State * L, Unit * ptr);
	int AddLifetimeKills(lua_State * L, Unit * ptr);
	int GetGender(lua_State * L, Unit * ptr); //9
	int SetGender(lua_State * L, Unit * ptr);
	int GetGroupType(lua_State * L, Unit * ptr);
	//next 5: thanks Alvanaar
	int SendPacketToGuild(lua_State * L, Unit * ptr);
	int GetGuildId(lua_State * L, Unit * ptr);
	int GetGuildRank(lua_State * L, Unit * ptr);
	int SetGuildRank(lua_State * L, Unit * ptr);
	int IsInGuild(lua_State * L, Unit * ptr); //5
	int SendGuildInvite(lua_State * L, Unit * ptr);
	int DemoteGuildMember(lua_State * L, Unit * ptr);
	int PromoteGuildMember(lua_State * L, Unit * ptr);
	int SetGuildMotd(lua_State * L, Unit * ptr);
	int GetGuildMotd(lua_State * L, Unit * ptr);
	int SetGuildInformation(lua_State * L, Unit * ptr);
	int AddGuildMember(lua_State * L, Unit * ptr);
	int RemoveGuildMember(lua_State * L, Unit * ptr);
	int SetPublicNote(lua_State * L, Unit * ptr);
	int SetOfficerNote(lua_State * L, Unit * ptr);
	int DisbandGuild(lua_State * L, Unit * ptr);
	int ChangeGuildMaster(lua_State * L, Unit * ptr);
	int SendGuildChatMessage(lua_State * L, Unit * ptr);
	int SendGuildLog(lua_State * L, Unit * ptr);
	int GuildBankDepositMoney(lua_State * L, Unit * ptr);
	int GuildBankWithdrawMoney(lua_State * L, Unit * ptr);
	int GetInstanceOwner(lua_State * L, Unit * ptr);
	int GetGmRank(lua_State * L, Unit * ptr);
	int SetByteValue(lua_State * L, Unit * ptr);
	int GetByteValue(lua_State * L, Unit * ptr);
	int IsPvPFlagged(lua_State * L, Unit * ptr);
	int IsFFAPvPFlagged(lua_State * L, Unit * ptr);
	int GetGuildLeader(lua_State * L, Unit * ptr);
	int GetGuildMemberCount(lua_State * L, Unit * ptr);
	int CanAttack(lua_State * L, Unit * ptr);
	int GetInRangeUnits(lua_State * L, Unit * ptr);
	int GetInRangeEnemies(lua_State * L, Unit * ptr);
	int IsFriendly(lua_State * L, Unit * ptr);
	int MovePlayerTo(lua_State * L, Unit * ptr);
	// Alvy: next 15
	//int IsInChannel(lua_State * L, Unit * ptr); "unresolved externals"
	//int JoinChannel(lua_State * L, Unit * ptr); "unresolved externals"
	//int LeaveChannel(lua_State * L, Unit * ptr); "unresolved externals"
	//int SetChannelOwner(lua_State * L, Unit * ptr); super broken
	//int GetChannelOwner(lua_State * L, Unit * ptr); super broken
	//int SendPacketToChannel(lua_State * L, Unit * ptr); "unresolved externals"
	//int SetChannelName(lua_State * L, Unit * ptr); "unresolved externals"
	//int SetChannelPassword(lua_State * L, Unit * ptr); "unresolved externals"
	//int GetChannelPassword(lua_State * L, Unit * ptr); "unresolved externals"
	//int GetChannelOwner(lua_State * L, Unit * ptr); super broken again
	//int KickFromChannel(lua_State * L, Unit * ptr); "unresolved externals"
	//int BanFromChannel(lua_State * L, Unit * ptr); "unresolved externals"
	//int UnbanFromChannel(lua_State * L, Unit * ptr); "unresolved externals"
	//int GetChannelMemberCount(lua_State * L, Unit * ptr); "unresolved externals"
	//int GetChannelMembers(lua_State * L, Unit * ptr); super broken
	int GetPlayerMovementVector(lua_State * L, Unit * ptr);
	int UnsetKnownTitle(lua_State * L, Unit * ptr);
	int IsInPhase(lua_State * L, Unit * ptr);
	int HasFlag(lua_State * L, Unit * ptr);
	int Repop(lua_State * L, Unit * ptr);
	int SetMovementFlags(lua_State * L, Unit * ptr);
	int GetSpawnId(lua_State * L, Unit * ptr);
	int ResetTalents(lua_State * L, Unit * ptr);
	int SetTalentPoints(lua_State * L, Unit * ptr);
	int GetTalentPoints(lua_State * L, Unit * ptr);
	int EventChat(lua_State * L, Unit * ptr);
	int GetEquippedItemBySlot(lua_State * L, Unit * ptr);
	int GetGuildMembers(lua_State * L, Unit * ptr);
	//int AddAchievement(lua_State * L, Unit * ptr);
	//int RemoveAchievement(lua_State * L, Unit * ptr);
	//int HasAchievement(lua_State * L, Unit * ptr);
	int RemoveArenaPoints(lua_State * L, Unit * ptr);
	int TakeHonor(lua_State * L, Unit * ptr);
	int GetAreaId(lua_State * L, Unit * ptr);
	int ResetPetTalents(lua_State * L, Unit * ptr);
	int IsDazed(lua_State * L, Unit * ptr);
	int GetAura(lua_State * L, Unit * ptr);
	int IsRooted(lua_State * L, Unit * ptr);
	int HasAuraWithMechanic(lua_State * L, Unit * ptr);
	int HasNegativeAura(lua_State * L, Unit * ptr);
	int HasPositiveAura(lua_State * L, Unit * ptr);
	int SetActionBar(lua_State * L, Unit * ptr);
	int GetClosestFriend(lua_State * L, Unit * ptr);
	int GetClosestEnemy(lua_State * L, Unit * ptr);
	int IsOnTaxi(lua_State * L, Unit * ptr);
	int GetTaxi(lua_State * L, Unit * ptr);
	int GetObjectType(lua_State * L, Unit * ptr);*/
}
#endif
