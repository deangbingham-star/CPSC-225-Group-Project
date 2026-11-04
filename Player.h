using std::string;
class Player
{
private:
	static int numCreatures;
	Creature* creatures[3];
	Creature* activeCreature;
	int currency;
	const string NAME;

public:
	Player(string n);
	~Player();
	void addCreature();
	void addCreature(Creature* c);
	void removeCreature();
	void setActiveCreature();
	void battle();
	void catchCreature(Creature* c);
};