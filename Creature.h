class Creature
{
protected:
	int maxHP;
	int currentHP;
    int baseDamage;
    int dmgMult;
    int captureRate;

public:
	Creature();
	~Creature();
	void Attack();
	void Restore() {
		currentHP = maxHP;
	}
};