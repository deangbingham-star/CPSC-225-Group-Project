using std::string;
using std::ifstream;
class Player
{
private:
    const string NAME;
	int numCreatures;
	Creature* creatures[3];
	Creature* activeCreature;
	
	int currency;
    int attackBuffItems;
    int defenseBuffItems;
    int healingItems;
    
public:
	Player(string n);
	Player(ifstream& fin);
	~Player();
	
	void addCreature();
	void addCreature(Creature* c);
	void removeCreature();
	void setActiveCreature();
	void setActiveCreature(int n);
	void catchCreature(Creature* c);
	
	int buyItem(int x);
	int sellItem();
    void useItem();
	
	void viewStatus();
	void battle();
	void shop();
	bool challengeBoss();
};