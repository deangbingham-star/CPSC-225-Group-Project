using std::ostream;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::string;

class Creature
{
protected:
	string name;
	string creatureType;
	int maxHP;
	int currentHP;
	int baseDamage;
	int attackBuff;
	int defenseBuff;
	int captureRate;

	int level;
	int xpToLevel;
	int curXP;

public:
	Creature();
	Creature(ifstream& fin);
	~Creature();
	virtual void Attack(Creature* c, bool isOwned);
	void Restore() {
		currentHP = maxHP;
		attackBuff = 0;
		defenseBuff = 0;
	}
	int getCurHP() {
		return currentHP;
	}
	int getMaxHP() {
		return maxHP;
	}
	void setHP(int x) {
		maxHP = x;
		currentHP = x;
	}
	void takeDamage(int x);
	void applyAttackBuff(int x) {
		attackBuff += x;
	}
	void applyDefenseBuff(int x) {
		defenseBuff += x;
	}

	void grantXP(int x);
	virtual void levelUp();

	void setName(string s) {
		name = s;
	}
	string getName() {
		return name;
	}

	void saveCreatureData(ofstream& fout);

	friend ostream& operator<<(ostream& os, Creature* c);
};

class Tank : public Creature
{
public:
	Tank();
	Tank(ifstream& fin);
	~Tank();
	void Attack(Creature* c, bool isOwned);
	void levelUp();
};

class Fighter : public Creature
{
public:
	Fighter();
	Fighter(ifstream& fin);
	~Fighter();
	void Attack(Creature* c, bool isOwned);
	void levelUp();
};

class Mage : public Creature
{
public:
	Mage();
	Mage(ifstream& fin);
	~Mage();
	void Attack(Creature* c, bool isOwned);
	void levelUp();
};

class Boss : public Creature
{
public:
	Boss();
	Boss(ifstream& fin);
	~Boss();
	void Attack(Creature* c, bool isOwned);
	void levelUp();
};