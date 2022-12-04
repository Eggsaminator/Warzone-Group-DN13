#include "Player.h"
#include "PlayerStrategies.h"

#include <unordered_set>

PlayerStrategy::PlayerStrategy(Player* newPlayer) {
	player = newPlayer;
}
ostream& operator << (ostream& os, const PlayerStrategy& strategy) {
	return os << "\nDisplaying strategy: " << typeid(strategy).name() << endl;
}

// Helper Functions definitions start here

vector<Territory*> PlayerStrategy::getAdjacentEnemyTerritories(Territory* origin) {
	vector<Territory*> enemyAdjacencies = vector<Territory*>();
	for (Territory* adjacentTerritory : origin->getAdjacencyList()) {
		if (adjacentTerritory->getOwner() != player) {
			enemyAdjacencies.push_back(adjacentTerritory);
		}
	}

	return enemyAdjacencies;
}
Territory* PlayerStrategy::getStrongestTerritory() {
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
	OrderList* orderList = new OrderList(player->getName());

	// Reinforce
	Territory* strongestTerritory = getStrongestTerritory();
	if (player->getReinforcementPoolLeftToDeploy() > 0) {
		Deploy* deployOrder = new Deploy(player, player->getReinforcementPoolLeftToDeploy(), strongestTerritory);
		orderList->addOrder(deployOrder);
	}

	// Bomb
	for (Card* card : player->getHand()->hand_content) {
		vector<Territory*> territories = player->getTerritories();
		if (territories.size() <= 0) {
			break;
		}
		vector<Territory*> someEnemyTerritories = getAdjacentEnemyTerritories(territories[0]);
		if (someEnemyTerritories.size() <= 0) {
			break;
		}
		
		if (card->card_type.compare("Bomb") == 0) {
			Bomb* bombOrder = new Bomb(player, someEnemyTerritories[0]);
			orderList->addOrder(bombOrder);
		}
	}

	// Advance
	for (Territory* territory : player->getTerritories()) {
		vector<Territory*> enemyTerritories = getAdjacentEnemyTerritories(territory);
		// Split the army evenly
		int armiesPerTerritory = (int) (territory->getArmies() / enemyTerritories.size());
		for (Territory* enemyTerritory : enemyTerritories) {
			Advance* advanceOrder = new Advance(player, armiesPerTerritory, territory, enemyTerritory);
			orderList->addOrder(advanceOrder);
		}
	}

	// Does not defend

	return orderList;
}
vector<Territory*> AggressivePlayerStrategy::toAttack() {
	unordered_set<Territory*> uniqueTerritories;
	for (Territory* territory : player->getTerritories()) {
		vector<Territory*> enemyTerritories = getAdjacentEnemyTerritories(territory);
		for (Territory* enemyTerritory : enemyTerritories) {
			uniqueTerritories.insert(enemyTerritory);
		}
	}

	vector<Territory*> adjacentEnemyTerritories(uniqueTerritories.begin(), uniqueTerritories.end());
	return adjacentEnemyTerritories;
}
vector<Territory*> AggressivePlayerStrategy::toDefend() {
	return vector<Territory*>();
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) : PlayerStrategy(player) {

}
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {

}
BenevolentPlayerStrategy::BenevolentPlayerStrategy(BenevolentPlayerStrategy* strategy) : PlayerStrategy(strategy->player) {

}
OrderList* BenevolentPlayerStrategy::issueOrder() {
	OrderList* orderList = new OrderList(player->getName());

	Territory* strongestTerritory = getStrongestTerritory();
	Territory* weakestTerritory = getWeakestTerritory();
	// Reinforce
	if (player->getReinforcementPoolLeftToDeploy() > 0) {
		Deploy* deployOrder = new Deploy(player, player->getReinforcementPoolLeftToDeploy(), weakestTerritory);
		orderList->addOrder(deployOrder);
	}

	// Airlift - half from strongest territory to weakest
	// Blockade - strongest territory
	for (Card* card : player->getHand()->hand_content) {
		if (card->card_type.compare("Airlift") == 0) {
			Airlift* airliftOrder = new Airlift(player, (int) (strongestTerritory->getArmies() / 2), strongestTerritory, weakestTerritory);
			orderList->addOrder(airliftOrder);
		}

		if (card->card_type.compare("Blockade") == 0) {
			Blockade* blockadeOrder = new Blockade(player, strongestTerritory);
			orderList->addOrder(blockadeOrder);
		}
	}

	return orderList;
}
vector<Territory*> BenevolentPlayerStrategy::toAttack() {
	return vector<Territory*>();
}
vector<Territory*> BenevolentPlayerStrategy::toDefend() {
	return player->getTerritories();
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
	OrderList* orderList = new OrderList(player->getName());

	for (Territory* territory : toAttack()) {
		territory->setOwner(player);
		territory->setArmies(1);
	}

	return orderList;
}
vector<Territory*> CheaterPlayerStrategy::toAttack() {
	unordered_set<Territory*> uniqueTerritories;
	for (Territory* territory : player->getTerritories()) {
		vector<Territory*> enemyTerritories = getAdjacentEnemyTerritories(territory);
		for (Territory* enemyTerritory : enemyTerritories) {
			uniqueTerritories.insert(enemyTerritory);
		}
	}

	vector<Territory*> adjacentEnemyTerritories(uniqueTerritories.begin(), uniqueTerritories.end());
	return adjacentEnemyTerritories;
}
vector<Territory*> CheaterPlayerStrategy::toDefend() {
	return vector<Territory*>();
}