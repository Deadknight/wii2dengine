#ifndef PET_H
#define PET_H

enum PET_STATE
{
    PET_STATE_PASSIVE,
    PET_STATE_DEFENSIVE,
    PET_STATE_AGGRESSIVE
};

class Pet : public Creature
{
public:
	Pet(uint64 guid);
	virtual ~Pet();

	virtual void Update(Real duration);
	
	uint8 GetPetState() { return PET_STATE_PASSIVE; }
};

#endif
