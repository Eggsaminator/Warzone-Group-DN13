#include "Player.h"
#include "PlayerStrategies.h"
#include "Map.h"
#include "CommandProcessing.h"
#include <set>
#include <unordered_set>

using std::set;
using std::unordered_set;
using std::stoi;
using std::invalid_argument;
using std::cout;

PlayerStrategy::PlayerStrategy(Player* p) {
	player = p;
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

HumanPlayerStrategy::HumanPlayerStrategy(Player* p, vector<Player*> allPls, Map* map, CommandProcessor* cmdPro) : PlayerStrategy(p) {
    allPlayers = allPls;
    gameMap = map;
    mainCommandProcessor = cmdPro;
}

OrderList* HumanPlayerStrategy::issueOrder() {
    OrderList* orderList = new OrderList(player->getName());

    cout << "----------------------\n";
    cout << "* " << player->getName() << " *\n";
    cout << "----------------------\n\n";

    //ask if want to issue order
    Command* mCommand;
    bool cmdIsValid = false;
    while (!cmdIsValid) {
        try {
            mCommand = mainCommandProcessor->getSimpleCommandNoValidation("Do you want to issue an order? [Y/N]");
            string mCommand_name = mCommand->getName();

            if (mCommand_name == "Y" || mCommand_name == "y") {
                break;
            }
            else if (mCommand_name == "N" || mCommand_name == "n") {
                return orderList;
            }
        }
        catch (invalid_argument e) {

        }
        if (!cmdIsValid) {
            cout << "Invalid command. Enter Y or N.\n\n";
        }
    }

    if (player->getReinforcementPoolLeftToDeploy() > 0) {
        //MUST ISSUE DEPLOY ORDERS
        int remainingReinforcementPool = player->getReinforcementPoolLeftToDeploy();
        cout << "You still have " << remainingReinforcementPool << " army units to deploy so you must issue a deploy order.\n";

        //pick nb army units to deploy
        int numberArmyUnits = 0;
        cmdIsValid = false;
        while (!cmdIsValid) {

            try {
                mCommand = mainCommandProcessor->getSimpleCommandNoValidation("How many units do you want to deploy? (minimum 1)");
                string mCommand_name = mCommand->getName();

                numberArmyUnits = stoi(mCommand_name);
                if (numberArmyUnits > 0 && numberArmyUnits <= remainingReinforcementPool) {
                    break;
                }
            }
            catch (invalid_argument e) {

            }
            cout << "Invalid number of army units.\n\n";
        }
        cout << "\n";

        player->setReinforcementPoolLeftToDeploy(remainingReinforcementPool - numberArmyUnits);

        vector<Territory*> listToDefend = toDefend();

        if (listToDefend.size() > 0) {
            Orders* orderToAdd = new Deploy(player, numberArmyUnits, listToDefend.at(0));
            player->addOrder(orderToAdd);
        }
    }
    else {
        //ISSUE ANY ORDER EXCEPT DEPLOY

        //create dynamic choice of possible orders to issue
        set<string> setOfPossibleOrders = { "Advance" };

        vector<Card*> cardsInHand = player->getHand()->hand_content;
        for (int i = 0; i < cardsInHand.size(); i++) {
            setOfPossibleOrders.insert(cardsInHand.at(i)->card_type);
        }

        vector<string> possibleOrders(setOfPossibleOrders.begin(), setOfPossibleOrders.end());

        //pick what type of order to issue
        string instructions = "What type of order do you want to issue? (enter number):\n";

        for (int i = 0; i < possibleOrders.size(); i++) {
            string partialString = to_string(i + 1) + ") " + possibleOrders.at(i) + "\n";
            instructions += partialString;
        }

        int orderIndex = 0;
        bool cmdIsValid = false;

        while (!cmdIsValid) {

            try {
                mCommand = mainCommandProcessor->getSimpleCommandNoValidation(instructions);
                string mCommand_name = mCommand->getName();

                orderIndex = stoi(mCommand_name);

                if (orderIndex > 0 && orderIndex <= possibleOrders.size()) {
                    break;
                }
            }
            catch (invalid_argument e) {

            }
            cout << "Invalid order number.\n";
        }

        string orderType = possibleOrders.at(orderIndex - 1);

        if (orderType == "Advance") {

            //pick source territory
            int choiceInt = 0;
            cmdIsValid = false;
            instructions = "From which territory do you want to advance your army units? (enter number):\n";

            for (int i = 0; i < player->getTerritories().size(); i++) {
                string partialString = to_string(i + 1) + ") " + player->getTerritories().at(i)->getName() + "\n";
                instructions += partialString;
            }

            while (!cmdIsValid) {
                try {
                    mCommand = mainCommandProcessor->getSimpleCommandNoValidation(instructions);
                    string mCommand_name = mCommand->getName();

                    choiceInt = stoi(mCommand_name);

                    if (choiceInt > 0 && choiceInt <= player->getTerritories().size()) {
                        break;
                    }
                }
                catch (invalid_argument e) {

                }
                cout << "Invalid territory number.\n";
            }

            Territory* sourceTerritory = player->getTerritories().at(choiceInt - 1);

            //pick if attack/defend
            choiceInt = 0;
            cmdIsValid = false;
            instructions = "Do you want to attack or defend? (enter number):\n1) Attack\n2) Defend";

            while (!cmdIsValid) {
                try {
                    mCommand = mainCommandProcessor->getSimpleCommandNoValidation(instructions);
                    string mCommand_name = mCommand->getName();

                    choiceInt = stoi(mCommand_name);

                    if (choiceInt > 0 && choiceInt <= 2) {
                        break;
                    }
                }
                catch (invalid_argument e) {

                }
                cout << "Invalid choice number.\n";
            }

            string advanceTypes[] = { "Attack", "Defend" };
            string advanceType = advanceTypes[choiceInt - 1];

            //pick nb army units
            int numberArmyUnits = 0;
            cmdIsValid = false;
            instructions = "How many army units do you want to advance? (minimum 0 and maximum " + to_string(sourceTerritory->getArmies()) + "):";

            while (!cmdIsValid) {
                try {
                    mCommand = mainCommandProcessor->getSimpleCommandNoValidation(instructions);
                    string mCommand_name = mCommand->getName();

                    numberArmyUnits = stoi(mCommand_name);

                    if (numberArmyUnits >= 0 && numberArmyUnits <= sourceTerritory->getArmies()) {
                        break;
                    }
                }
                catch (invalid_argument e) {

                }
                cout << "Invalid amount of army units.\n";
            }

            //issue order
            if (advanceType == "Attack") {
                vector<Territory*> listToAttack = toAttack();
                if (listToAttack.size() > 0) {
                    Orders* orderToAdd = new Advance(player, numberArmyUnits, sourceTerritory, listToAttack.at(0));
                    orderList->addOrder(orderToAdd);
                }
            }
            else
            {
                vector<Territory*> listToDefend = toDefend();
                if (listToDefend.size() > 0) {
                    Orders* orderToAdd = new Advance(player, numberArmyUnits, sourceTerritory, listToDefend.at(0));
                    orderList->addOrder(orderToAdd);
                }
            }
        }
        else
        {
            //retrieve picked card from hand
            Card* cardPtr = nullptr;
            for (int i = 0; i < cardsInHand.size(); i++) {

                if (cardsInHand.at(i)->card_type == orderType) {
                    cardPtr = cardsInHand.at(i);
                    break;
                }
            }

            if (cardPtr == nullptr) {
                return orderList;
            }

            if (orderType == "Bomb")
            {
                vector<Territory*> listToAttack = toAttack();
                if (listToAttack.size() > 0) {
                    Bomb* bomb = new Bomb(player, listToAttack.at(0));
                    orderList->addOrder(bomb);
                }
            }
            else if (orderType == "Reinforcement")
            {
                //WHAT DO WE DO WITH REINFORCEMENT CARDS??
            }
            else if (orderType == "Airlift")
            {
                vector<Territory*> listToDefend = toDefend();
                if (listToDefend.size() > 0) {
                    //pick source territory
                    int choiceInt = 0;
                    cmdIsValid = false;
                    instructions = "From which territory do you want to airlift your army units? (enter number):\n";

                    for (int i = 0; i < player->getTerritories().size(); i++) {
                        string partialString = to_string(i + 1) + ") " + player->getTerritories().at(i)->getName() + "\n";
                        instructions += partialString;
                    }

                    while (!cmdIsValid) {
                        try {
                            mCommand = mainCommandProcessor->getSimpleCommandNoValidation(instructions);
                            string mCommand_name = mCommand->getName();

                            choiceInt = stoi(mCommand_name);

                            if (choiceInt > 0 && choiceInt <= player->getTerritories().size()) {
                                break;
                            }
                        }
                        catch (invalid_argument e) {

                        }
                        cout << "Invalid territory number.\n";
                    }

                    Territory* sourceTerritory = player->getTerritories().at(choiceInt - 1);

                    //pick nb army units
                    int numberArmyUnits = 0;
                    cmdIsValid = false;
                    instructions = "How many army units do you want to airlift? (minimum 0 and maximum " + to_string(sourceTerritory->getArmies()) + "):";

                    while (!cmdIsValid) {
                        try {
                            mCommand = mainCommandProcessor->getSimpleCommandNoValidation(instructions);
                            string mCommand_name = mCommand->getName();

                            numberArmyUnits = stoi(mCommand_name);

                            if (numberArmyUnits >= 0 && numberArmyUnits <= sourceTerritory->getArmies()) {
                                break;
                            }
                        }
                        catch (invalid_argument e) {

                        }
                        cout << "Invalid amount of army units.\n";
                    }
                    Airlift* airlift = new Airlift(player, numberArmyUnits, sourceTerritory, listToDefend.at(0));
                    orderList->addOrder(airlift);
                }
            }
            else if (orderType == "Diplomacy")
            {
                //pick player to negotiate with
                int choiceInt = 0;
                cmdIsValid = false;
                instructions = "With which player do you want to negotiate? (enter number):\n";

                vector<Player*> newAllPlayers = allPlayers;

                for (int i = 0; i < newAllPlayers.size(); i++) {
                    if (newAllPlayers.at(i) == player) {
                        newAllPlayers.erase(newAllPlayers.begin() + i);
                        i--;
                        continue;
                    }
                    string partialString = to_string(i + 1) + ") " + newAllPlayers.at(i)->getName() + "\n";
                    instructions += partialString;
                }

                while (!cmdIsValid) {
                    try {
                        mCommand = mainCommandProcessor->getSimpleCommandNoValidation(instructions);
                        string mCommand_name = mCommand->getName();

                        choiceInt = stoi(mCommand_name);

                        if (choiceInt > 0 && choiceInt <= newAllPlayers.size()) {
                            break;
                        }
                    }
                    catch (invalid_argument e) {

                    }
                    cout << "Invalid player number.\n";
                }

                Player* randomPlayer = newAllPlayers[choiceInt - 1];
                Negotiate* negotiate = new Negotiate(player, randomPlayer);
                orderList->addOrder(negotiate);
            }
            else if (orderType == "Blockade")
            {
                vector<Territory*> listToDefend = toDefend();
                if (listToDefend.size() > 0) {
                    Blockade* blockade = new Blockade(player, listToDefend.at(0));
                    orderList->addOrder(blockade);
                }
            }
        }
    }

    return orderList;
}
vector<Territory*> HumanPlayerStrategy::toDefend() {
    string instructions = "Which territory do you want to defend? (enter number):\n";

    vector<Territory*> ownedTerritories = player->getTerritories();

    if (ownedTerritories.size() < 1) {
        return vector<Territory*>{};
    }

    for (int i = 0; i < ownedTerritories.size(); i++) {
        string partialString = to_string(i + 1) + ") " + ownedTerritories.at(i)->getName() + "\n";
        instructions += partialString;
    }

    Command* mCommand;
    int cmdInt = 0;
    bool cmdIsValid = false;

    while (!cmdIsValid) {

        try {
            mCommand = mainCommandProcessor->getSimpleCommandNoValidation(instructions);
            string mCommand_name = mCommand->getName();

            cmdInt = stoi(mCommand_name);

            if (cmdInt > 0 && cmdInt <= ownedTerritories.size()) {
                break;
            }
        }
        catch (invalid_argument e) {

        }
        cout << "Invalid territory number.\n";
    }

    vector<Territory*> toDefend;
    toDefend.push_back(ownedTerritories.at(cmdInt - 1));

    return toDefend;
}
vector<Territory*> HumanPlayerStrategy::toAttack() {
    string instructions = "Which territory do you want to attack? (enter number):\n";

    vector<Territory*> territoriesToConquer;

    for (int i = 0; i < gameMap->getTerritories().size(); i++) {
        if (gameMap->getTerritories().at(i)->getOwner() != player) {
            territoriesToConquer.push_back(gameMap->getTerritories().at(i));
        }
    }

    if (territoriesToConquer.size() < 1) {
        return vector<Territory*>{};
    }

    for (int i = 0; i < territoriesToConquer.size(); i++) {
        string partialString = to_string(i + 1) + ") " + territoriesToConquer.at(i)->getName() + "\n";
        instructions += partialString;
    }

    Command* mCommand;
    int cmdInt = 0;
    bool cmdIsValid = false;

    while (!cmdIsValid) {

        try {
            mCommand = mainCommandProcessor->getSimpleCommandNoValidation(instructions);
            string mCommand_name = mCommand->getName();

            cmdInt = stoi(mCommand_name);

            if (cmdInt > 0 && cmdInt <= territoriesToConquer.size()) {
                break;
            }
        }
        catch (invalid_argument e) {

        }
        cout << "Invalid territory number.\n";
    }

    vector<Territory*> toAttack;
    toAttack.push_back(territoriesToConquer.at(cmdInt - 1));

    return toAttack;
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
        int armiesPerTerritory = (int)(territory->getArmies() / enemyTerritories.size());
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
            Airlift* airliftOrder = new Airlift(player, (int)(strongestTerritory->getArmies() / 2), strongestTerritory, weakestTerritory);
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
    player->setPlayerStrategy(new AggressivePlayerStrategy(player));
    return player->toDefend();
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