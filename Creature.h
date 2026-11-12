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

public:
	Creature();
	Creature(ifstream& fin);
	~Creature();
	virtual void Attack(Creature* c);
	void Restore() {
		currentHP = maxHP;
		attackBuff = 0;
		defenseBuff = 0;
	}
	int getCurHP() { return currentHP; }
	int getMaxHP() { return maxHP; }
	void setHP(int x) {
		maxHP = x;
		currentHP = x;
	}
	void takeDamage(int x);
	void applyAttackBuff(int x);
	void applyDefenseBuff(int x);
	
	void setName(string s) { name = s; }
	string getName() {return name; }
	
	void saveCreatureData(ofstream& fout);

	friend ostream& operator<<(ostream& os, Creature* c);
};