#ifndef PLAYER_H
#define PLAYER_H

class Player : public Unit
{
public:
	Player(uint64 guid);
	virtual ~Player();

	virtual void Init(const char* name, uint32 entry);
	virtual void Update(Real duration);
	virtual void OnCollide(CollisionPrimitive *cpTarget);

	void UpdateControllers();
	void UpdateMovement(Real duration);
private:
	uint32 _fields[PLAYER_END];
	ML_Sprite *cursor;
};

#endif
