using std::ostream;
using std::cout;
using std::endl;
using std::string;

class Creature
{
protected:
	string name;
	int maxHP;
	int currentHP;
	int baseDamage;
	int attackBuff;
	int defenseBuff;
	int captureRate;

public:
	Creature();
	~Creature();
	void Attack(Creature* c);
	void Restore() {
		currentHP = maxHP;
	}
	int getCurHP() { return currentHP; }
	void setHP(int x) {
		maxHP = x;
		currentHP = x;
	}
	void takeDamage(int x);
	void setName(string s) { name = s; }
	string getName()
	{
		return name;
	}

	friend ostream& operator<<(ostream& os, Creature* c);
};