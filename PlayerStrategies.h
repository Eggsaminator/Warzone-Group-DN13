#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;
class Territory;
class Player;

class PlayerStrategy {
public:
	PlayerStrategy(Player* p);
	virtual bool issueOrder(vector<Player*> allPlayers) = 0;
	virtual vector<Territory*> toDefend() = 0;
	virtual vector<Territory*> toAttack() = 0;
	Player* getPlayer();
private:
	Player* player;
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	HumanPlayerStrategy(Player* p);
	bool issueOrder(vector<Player*> allPlayers);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	AggressivePlayerStrategy(Player* p);
	bool issueOrder(vector<Player*> allPlayers);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	BenevolentPlayerStrategy(Player* p);
	bool issueOrder(vector<Player*> allPlayers);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	NeutralPlayerStrategy(Player* p);
	bool issueOrder(vector<Player*> allPlayers);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class CheaterPlayerStrategy : public PlayerStrategy {
public:
	CheaterPlayerStrategy(Player* p);
	bool issueOrder(vector<Player*> allPlayers);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};