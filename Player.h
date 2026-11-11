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
	int healingItems;
    int attackBuffItems;
    int defenseBuffItems;

public:
	Player(string n);
	Player(ifstream& fin);
	void savePlayerData();
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