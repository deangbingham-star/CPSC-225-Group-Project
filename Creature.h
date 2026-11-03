using std::ostream;
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
	int getCurHP() {return currentHP;}
	void setHP(int x) {
	    maxHP = x; 
	    currentHP = x;
	}
	void takeDamage(int x) {currentHP -= x;}
	void setName(string s) {name = s;}
	
	friend ostream& operator<<(ostream& os, Creature* c);
};