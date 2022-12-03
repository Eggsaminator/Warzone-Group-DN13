#include "Player.h"
#include "PlayerStrategies.h"

PlayerStrategy::PlayerStrategy(Player* newPlayer) {
	player = newPlayer;
}
ostream& operator << (ostream& os, const PlayerStrategy& strategy) {
	return os << "\nDisplaying strategy: " << typeid(strategy).name() << endl;
}

// Helper Functions definitions start here

vector<Territory*>* PlayerStrategy::getAdjacentEnemyTerritories(Territory* origin) {
	vector<Territory*>* enemyAdjacencies = new vector<Territory*>();
	for (Territory* adjacentTerritory : origin->getAdjacencyList()) {
		if (adjacentTerritory->getOwner() != player) {
			enemyAdjacencies->push_back(adjacentTerritory);
		}
	}

	return enemyAdjacencies;
}
Territory* AggressivePlayerStrategy::getStrongestTerritory() {
	Territory* strongestTerritory = nullptr;
	for (Territory* territory : player->getTerritories()) {
		int territoryArmies = territory->getArmies();
		if (strongestTerritory == nullptr || territoryArmies > strongestTerritory->getArmies()) {
			strongestTerritory = territory;
		}
	}

	return strongestTerritory;
}
vector<Card*>* AggressivePlayerStrategy::getAggressiveCards() {
	vector<Card*>* aggressiveCards = new vector<Card*>();
	for (Card* card : player->getHand()->hand_content) {
		if (card->card_type.compare("Bomb") == 0 ||
			card->card_type.compare("Reinforcement") == 0 ||
			card->card_type.compare("Airlift") == 0) {
			aggressiveCards->push_back(card);
		}
	}

	return aggressiveCards;
}
Territory* BenevolentPlayerStrategy::getWeakestTerritory() {
	Territory* weakestTerritory = nullptr;
	for (Territory* territory : player->getTerritories()) {
		int territoryArmies = territory->getArmies();
		if (weakestTerritory == nullptr || territoryArmies < weakestTerritory->getArmies()) {
			weakestTerritory = territory;
		}
	}

	return weakestTerritory;
}

// Helper Function definitions end here

HumanPlayerStrategy::HumanPlayerStrategy(Player* player) : PlayerStrategy(player) {

}
HumanPlayerStrategy::~HumanPlayerStrategy() {

}
HumanPlayerStrategy::HumanPlayerStrategy(HumanPlayerStrategy* strategy) : PlayerStrategy(strategy->player) {

}
OrderList* HumanPlayerStrategy::issueOrder() {
	return nullptr;
}
vector<Territory*> HumanPlayerStrategy::toAttack() {
	return vector<Territory*>();
}
vector<Territory*> HumanPlayerStrategy::toDefend() {
	return vector<Territory*>();
}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) : PlayerStrategy(player) {

}
AggressivePlayerStrategy::~AggressivePlayerStrategy() {

}
AggressivePlayerStrategy::AggressivePlayerStrategy(AggressivePlayerStrategy* strategy) : PlayerStrategy(strategy->player) {

}
OrderList* AggressivePlayerStrategy::issueOrder() {

}
vector<Territory*> AggressivePlayerStrategy::toAttack() {

}
vector<Territory*> AggressivePlayerStrategy::toDefend() {

}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) : PlayerStrategy(player) {

}
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {

}
BenevolentPlayerStrategy::BenevolentPlayerStrategy(BenevolentPlayerStrategy* strategy) : PlayerStrategy(strategy->player) {

}
OrderList* BenevolentPlayerStrategy::issueOrder() {

}
vector<Territory*> BenevolentPlayerStrategy::toAttack() {

}
vector<Territory*> BenevolentPlayerStrategy::toDefend() {

}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) : PlayerStrategy(player) {

}
NeutralPlayerStrategy::~NeutralPlayerStrategy() {

}
NeutralPlayerStrategy::NeutralPlayerStrategy(NeutralPlayerStrategy* strategy) : PlayerStrategy(strategy->player) {

}
OrderList* NeutralPlayerStrategy::issueOrder() {
	return nullptr;
}
vector<Territory*> NeutralPlayerStrategy::toAttack() {
	return vector<Territory*>();
}
vector<Territory*> NeutralPlayerStrategy::toDefend() {
	return vector<Territory*>();
}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player) : PlayerStrategy(player) {

}
CheaterPlayerStrategy::~CheaterPlayerStrategy() {

}
CheaterPlayerStrategy::CheaterPlayerStrategy(CheaterPlayerStrategy* strategy) : PlayerStrategy(strategy->player) {

}
OrderList* CheaterPlayerStrategy::issueOrder() {

}
vector<Territory*> CheaterPlayerStrategy::toAttack() {
	player->getTerritories();
	
}
vector<Territory*> CheaterPlayerStrategy::toDefend() {

}