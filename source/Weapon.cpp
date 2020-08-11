#include "Stdafx.h"

Weapon::Weapon(Unit *weaponOwner, uint32 id, std::string name)
{
	m_weaponOwner = weaponOwner;
	m_id = id;
	m_projectileEntry = 0;
	m_projectileName = "";
	m_name = "";
	m_currentFireCooldown = 0;
	m_fireCooldown = 0;
	m_currentReloadCooldown = 0;
	m_reloadCooldown = 0;
	m_damage = 0;
	m_currentMagazine = 0;
	m_maxMagazine = 0;
}

Weapon::~Weapon()
{
	
}

void Weapon::Init()
{
	ScriptSystem->OnWeaponEvent(this, WEAPON_EVENT_INIT, 0);
	sLuaMgr.OnWeaponEvent(this, WEAPON_EVENT_INIT, 0);
}

bool Weapon::CanReload()
{
	if(m_currentMagazine == -1) //Infinite ammo :D
		return false;

	if(m_currentMagazine >= m_maxMagazine)
	{
		//well it can't be possible but we can check
		m_currentMagazine = m_maxMagazine;
		return false;
	}

	if(m_currentReloadCooldown > 0) //Omg we are reloading dont reload second time
		return false;

	return true;
}

void Weapon::Reload()
{
	if(!CanReload())
		return;

	ScriptSystem->OnWeaponEvent(this, WEAPON_EVENT_RELOAD, 0);
	sLuaMgr.OnWeaponEvent(this, WEAPON_EVENT_RELOAD, 0);

	m_currentReloadCooldown = m_reloadCooldown;
}

bool Weapon::CanFire()
{
	if(m_currentMagazine == -1) //Infinite ammo :D
		return true;

	if(m_currentMagazine > 0) //If we have magazine
		if(m_currentFireCooldown <= 0) //Fire cooldown
			if(m_currentReloadCooldown <= 0) //If we are not reloading
				return true;
	return false;
}

void Weapon::Fire()
{
	if(!CanFire())
		return;
	
	ScriptSystem->OnWeaponEvent(this, WEAPON_EVENT_FIRE, 0);
	sLuaMgr.OnWeaponEvent(this, WEAPON_EVENT_FIRE, 0);

	Projectile *p = new Projectile();
	p->SetLifeTime(2);
	p->SetDirection(m_weaponOwner->GetDirection().normalise());
	Vector3 pos = m_weaponOwner->GetPosition();
	p->SetPosition(pos.x, pos.y, pos.z);
	p->Init(m_projectileName.c_str(), m_projectileEntry);
	if(m_weaponOwner->GetType() == TYPE_PLAYER)
		p->GetCollisionPrimitive()->SetCollisionFlag(COLLISION_FLAG_CREATURE | COLLISION_FLAG_GAMEOBJECT | COLLISION_FLAG_WORLD);
	else
		p->GetCollisionPrimitive()->SetCollisionFlag(COLLISION_FLAG_PLAYER | COLLISION_FLAG_GAMEOBJECT | COLLISION_FLAG_WORLD);
	//p->Init("bullet", 1);
	sMap.AddTimedObject(p);

	if(m_currentMagazine != -1)
		m_currentMagazine--;

	m_currentFireCooldown = m_fireCooldown;

	//Well script can generate projectiles here, update will be based on scripts too :D
}

void Weapon::Update(Real duration)
{
	GType val(MYTYPE_FLOAT, &duration);
	ScriptSystem->OnWeaponEvent(this, WEAPON_EVENT_UPDATE, 1, &val);
	sLuaMgr.OnWeaponEvent(this, WEAPON_EVENT_UPDATE, 1, &val);

	if(m_currentFireCooldown > 0)
		m_currentFireCooldown -= duration;
	else
		m_currentFireCooldown = 0;

	if(m_currentReloadCooldown > 0)
		m_currentReloadCooldown -= duration;
	else
		m_currentReloadCooldown = 0;
}

Projectile *Weapon::CreateProjectile(const char* name, uint32 entry, Real lifetime)
{
	Projectile *p = new Projectile();
	p->SetLifeTime(lifetime);
	p->SetDirection(m_weaponOwner->GetDirection().normalise());
	p->SetPosition(m_weaponOwner->GetPosition());
	p->Init(name, entry);
	sMap.AddTimedObject(p);
	return p;
}
