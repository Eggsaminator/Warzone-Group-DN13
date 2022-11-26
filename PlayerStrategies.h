#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;
class Territory;
class Player;

class PlayerStrategy {
public:
	PlayerStrategy();
	virtual void issueOrder(Player* nameP, vector<Player*> allPlayers, string name) = 0;
	virtual vector<Territory*> toDefend() = 0;
	virtual vector<Territory*> toAttack() = 0;
private:
};

class HumanPlayerStrategy : public PlayerStrategy {
	void issueOrder(Player* nameP, vector<Player*> allPlayers, string name);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class AggressivePlayerStrategy : public PlayerStrategy {
	void issueOrder(Player* nameP, vector<Player*> allPlayers, string name);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
	void issueOrder(Player* nameP, vector<Player*> allPlayers, string name);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class NeutralPlayerStrategy : public PlayerStrategy {
	void issueOrder(Player* nameP, vector<Player*> allPlayers, string name);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class CheaterPlayerStrategy : public PlayerStrategy {
	void issueOrder(Player* nameP, vector<Player*> allPlayers, string name);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};