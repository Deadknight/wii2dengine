#ifndef WEAPON_H
#define WEAPON_H

class Weapon
{
public:
	Weapon(Unit *weaponOwner, uint32 id, std::string names);
	~Weapon();

	virtual void Init();
	virtual bool CanReload();
	virtual void Reload();
	virtual bool CanFire();
	virtual void Fire();
	virtual void Update(Real duration);

	uint32 GetId() { return m_id; }
	void SetId(uint32 val) { m_id = val; }
	uint32 GetProjectileEntry() { return m_projectileEntry; }
	void SetProjectileEntry(uint32 val) { m_projectileEntry = val; }
	std::string GetProjectileName() { return m_projectileName; }
	void SetProjectileName(std::string val) { m_projectileName = val; }
	int32 GetCurrentFireCooldown() { return m_currentFireCooldown; }
	int32 GetFireCooldown() { return m_fireCooldown; }
	void SetFireCooldown(Real val) { m_fireCooldown = val; }
	int32 GetCurrentReloadCooldown() { return m_currentReloadCooldown; }
	int32 GetReloadCooldown() { return m_reloadCooldown; }
	void SetReloadCooldown(Real val) { m_reloadCooldown = val; }
	uint32 GetDamage() { return m_damage; }
	void SetDamage(uint32 val) { m_damage = val; }
	int32 GetCurrentMagazine() { return m_currentMagazine; }
	void SetCurrentMagazine(int32 val) { m_currentMagazine = val; }
	int32 GetMaxMagazine() { return m_maxMagazine; }
	void SetMaxMagazine(int32 val) { m_maxMagazine = val; }

	Projectile *CreateProjectile(const char* name, uint32 entry, Real lifetime);

protected:
	uint32 m_id;
	uint32 m_projectileEntry;
	std::string m_projectileName;
	std::string m_name;
	Real m_currentFireCooldown;
	Real m_fireCooldown;
	Real m_currentReloadCooldown;
	Real m_reloadCooldown;
	uint32 m_damage;
	int32 m_currentMagazine;
	int32 m_maxMagazine;
	
	Unit *m_weaponOwner;
};

#endif
