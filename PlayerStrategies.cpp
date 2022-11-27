#include "PlayerStrategies.h"
#include "set"
#include "Map.h"
using std::set;

PlayerStrategy::PlayerStrategy(Player* p) {
	player = p;
}


HumanPlayerStrategy::HumanPlayerStrategy(Player* p) : PlayerStrategy(p){}

bool HumanPlayerStrategy::issueOrder(vector<Player*> allPlayers) {
    if (getPlayer()->getReinforcementPoolLeftToDeploy() > 0) {
        //MUST ISSUE DEPLOY ORDERS
        int remainingReinforcementPool = getPlayer()->getReinforcementPoolLeftToDeploy();
        int numberArmyUnits = (rand() % remainingReinforcementPool) + 1;

        getPlayer()->setReinforcementPoolLeftToDeploy(remainingReinforcementPool - numberArmyUnits);

        if (toDefend().size() > 0) {
            Orders* orderToAdd = new Deploy(getPlayer(), numberArmyUnits, toDefend().at(0));
            getPlayer()->addOrder(orderToAdd);
        }
    }else {
        //ISSUE ANY ORDER EXCEPT DEPLOY



        //ADVANCE
        Territory* destinationTerritory = nullptr;
        int randomSourceIndex = rand() % getPlayer()->getTerritories().size();
        Territory* sourceTerritory = getPlayer()->getTerritories().at(randomSourceIndex);

        string advanceTypes[] = { "Attack", "Defend" };
        string advanceType = advanceTypes[rand() % 2];

        if (advanceType == "Attack") {
        	if (toAttack().size() > 0) {
        		int numberArmyUnits = rand() % (sourceTerritory->getArmies() + 1);

        		Orders* orderToAdd = new Advance(getPlayer(), numberArmyUnits, sourceTerritory, toAttack().at(0));
                getPlayer()->addOrder(orderToAdd);
        	}
        }
        else
        {
        	if (toDefend().size() > 0) {
        		int numberArmyUnits = rand() % (sourceTerritory->getArmies() + 1);

        		Orders* orderToAdd = new Advance(getPlayer(), numberArmyUnits, sourceTerritory, toDefend().at(0));
                getPlayer()->addOrder(orderToAdd);
        	}
        }




        //GET CARDS
        if (getPlayer()->getHand()->hand_content.size() > 0) {
            vector<Card*> cardsInHand = getPlayer()->getHand()->hand_content;
            int randomCardIndex = rand() % cardsInHand.size();
            Card* cardPtr = cardsInHand.at(randomCardIndex);


            if (cardPtr->card_type == "Bomb")
            {
                if (toAttack().size() > 0) {
                    cardPtr->play(nullptr, toAttack().at(0), NULL, nullptr);
                }
            }
            else if (cardPtr->card_type == "Reinforcement")
            {
                //WHAT DO WE DO WITH REINFORCEMENT CARDS??
            }
            else if (cardPtr->card_type == "Airlift")
            {
                if (toDefend().size() > 0) {
                    int randomSourceIndex = rand() % getPlayer()->getTerritories().size();
                    Territory* sourceTerritory = getPlayer()->getTerritories().at(randomSourceIndex);

                    int randomNbArmyUnits = rand() % (sourceTerritory->getArmies() + 1);
                    cardPtr->play(sourceTerritory, toDefend().at(0), randomNbArmyUnits, nullptr);
                }
            }
            else if (cardPtr->card_type == "Diplomacy")
            {
                bool randomPlayerPicked = false;
                Player* randomPlayer = nullptr;

                while (!randomPlayerPicked) {
                    int randomPlayerIndex = rand() % allPlayers.size();
                    if (allPlayers[randomPlayerIndex] != getPlayer()) {
                        randomPlayerPicked = true;
                        randomPlayer = allPlayers[randomPlayerIndex];
                    }
                }
                cardPtr->play(nullptr, nullptr, NULL, randomPlayer);
            }
            else if (cardPtr->card_type == "Blockade")
            {
                if (toDefend().size() > 0) {
                    cardPtr->play(nullptr, toDefend().at(0), NULL, nullptr);
                }
            }
        }
    }
}
vector<Territory*> HumanPlayerStrategy::toDefend() {
    vector<Territory*> ownedTerritories = getPlayer()->getTerritories();
    return ownedTerritories;
}
vector<Territory*> HumanPlayerStrategy::toAttack() {
    vector<Territory*> ownedTerritories = getPlayer()->getTerritories();
    set<Territory*> territoriesToAttackSet;
    auto territoryIterator = ownedTerritories.begin();
    while (territoryIterator != ownedTerritories.end()) {
        vector<Territory*> adjacentTerr = (*territoryIterator)->getAdjacencyList();
        for (int i = 0; i < adjacentTerr.size(); i++) {
            territoriesToAttackSet.insert(adjacentTerr[i]);
        }
        ++territoryIterator;
    }

    vector<Territory*> territoriesToAttack;
    auto territoryIteratorSet = territoriesToAttackSet.begin();
    while (territoryIteratorSet != territoriesToAttackSet.end()) {
        if ((*territoryIteratorSet)->getOwner() != getPlayer()) {
            territoriesToAttack.push_back(*territoryIteratorSet);
        }
        ++territoryIteratorSet;
    }
    return territoriesToAttack;
}


AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p) {}
bool AggressivePlayerStrategy::issueOrder(vector<Player*> allPlayers) {

}
vector<Territory*> AggressivePlayerStrategy::toDefend() {

}
vector<Territory*> AggressivePlayerStrategy::toAttack() {

}


BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) : PlayerStrategy(p) {}
bool BenevolentPlayerStrategy::issueOrder(vector<Player*> allPlayers) {

}
vector<Territory*> BenevolentPlayerStrategy::toDefend() {

}
vector<Territory*> BenevolentPlayerStrategy::toAttack() {

}


NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) : PlayerStrategy(p) {}
bool NeutralPlayerStrategy::issueOrder(vector<Player*> allPlayers) {
	return false;
}
vector<Territory*> NeutralPlayerStrategy::toDefend() {
	return vector<Territory*>{};
}
vector<Territory*> NeutralPlayerStrategy::toAttack() {
	return vector<Territory*>{};
}


CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p) : PlayerStrategy(p) {}
bool CheaterPlayerStrategy::issueOrder(vector<Player*> allPlayers) {

}
vector<Territory*> CheaterPlayerStrategy::toDefend() {

}
vector<Territory*> CheaterPlayerStrategy::toAttack() {

}