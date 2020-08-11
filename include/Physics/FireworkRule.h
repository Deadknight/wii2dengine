#ifndef _FIREWORK_RULE_H
#define _FIREWORK_RULE_H

class Firework;

class FireworkRule
{
public:
	FireworkRule();
	~FireworkRule();
    
    /** 
     * Creates a new firework of this type and writes it into the given 
     * instance. The optional parent firework is used to base position 
     * and velocity on.
     */
	void Create(Firework *firework, const Firework *parent = NULL);
	
    unsigned type;

    /** The minimum length of the fuse. */
	Real minAge;

    /** The maximum legnth of the fuse. */
    Real maxAge;

    /** The minimum relative velocity of this firework. */
    Vector3 minVelocity;

    /** The maximum relative velocity of this firework. */
    Vector3 maxVelocity;

    /** The damping of this firework type. */
    Real damping;

	Random *random;	
};

#endif
