#include "PlayerStrategies.h"
#include "set"
#include "Map.h"
#include "CommandProcessing.h"

using std::set;
using std::stoi;
using std::invalid_argument;
using std::cout;

PlayerStrategy::PlayerStrategy(Player* p, vector<Player*> allPls, Map* map) {
	player = p;
    allPlayers = allPls;
    gameMap = map;
}

Player* PlayerStrategy::getPlayer() {
    return player;
}

HumanPlayerStrategy::HumanPlayerStrategy(Player* p, vector<Player*> allPls, Map* map) : PlayerStrategy(p, allPls, map) {}

bool HumanPlayerStrategy::issueOrder() {

    cout << "----------------------\n";
    cout << "* " << getPlayer()->getName() << " *\n";
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
                return false;
            }
        }
        catch (invalid_argument e) {

        }
        if (!cmdIsValid) {
            cout << "Invalid command. Enter Y or N.\n\n";
        }
    }

    if (getPlayer()->getReinforcementPoolLeftToDeploy() > 0) {
        //MUST ISSUE DEPLOY ORDERS
        int remainingReinforcementPool = getPlayer()->getReinforcementPoolLeftToDeploy();
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

        getPlayer()->setReinforcementPoolLeftToDeploy(remainingReinforcementPool - numberArmyUnits);

        vector<Territory*> listToDefend = toDefend();

        if (listToDefend.size() > 0) {
            Orders* orderToAdd = new Deploy(getPlayer(), numberArmyUnits, listToDefend.at(0));
            getPlayer()->addOrder(orderToAdd);
        }
    }
    else {
        //ISSUE ANY ORDER EXCEPT DEPLOY

        //create dynamic choice of possible orders to issue
        set<string> setOfPossibleOrders = { "Advance" };

        vector<Card*> cardsInHand = getPlayer()->getHand()->hand_content;
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

            for (int i = 0; i < getPlayer()->getTerritories().size(); i++) {
                string partialString = to_string(i + 1) + ") " + getPlayer()->getTerritories().at(i)->getName() + "\n";
                instructions += partialString;
            }

            while (!cmdIsValid) {
                try {
                    mCommand = mainCommandProcessor->getSimpleCommandNoValidation(instructions);
                    string mCommand_name = mCommand->getName();

                    choiceInt = stoi(mCommand_name);

                    if (choiceInt > 0 && choiceInt <= getPlayer()->getTerritories().size()) {
                        break;
                    }
                }
                catch (invalid_argument e) {

                }
                cout << "Invalid territory number.\n";
            }

            Territory* sourceTerritory = getPlayer()->getTerritories().at(choiceInt - 1);

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
                    Orders* orderToAdd = new Advance(getPlayer(), numberArmyUnits, sourceTerritory, listToAttack.at(0));
                    getPlayer()->addOrder(orderToAdd);
                }
            }
            else
            {
                vector<Territory*> listToDefend = toDefend();
                if (listToDefend.size() > 0) {
                    Orders* orderToAdd = new Advance(getPlayer(), numberArmyUnits, sourceTerritory, listToDefend.at(0));
                    getPlayer()->addOrder(orderToAdd);
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
                return true;
            }

            if (orderType == "Bomb")
            {
                vector<Territory*> listToAttack = toAttack();
                if (listToAttack.size() > 0) {
                    cardPtr->play(nullptr, listToAttack.at(0), NULL, nullptr);
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

                    for (int i = 0; i < getPlayer()->getTerritories().size(); i++) {
                        string partialString = to_string(i + 1) + ") " + getPlayer()->getTerritories().at(i)->getName() + "\n";
                        instructions += partialString;
                    }

                    while (!cmdIsValid) {
                        try {
                            mCommand = mainCommandProcessor->getSimpleCommandNoValidation(instructions);
                            string mCommand_name = mCommand->getName();

                            choiceInt = stoi(mCommand_name);

                            if (choiceInt > 0 && choiceInt <= getPlayer()->getTerritories().size()) {
                                break;
                            }
                        }
                        catch (invalid_argument e) {

                        }
                        cout << "Invalid territory number.\n";
                    }

                    Territory* sourceTerritory = getPlayer()->getTerritories().at(choiceInt - 1);

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
                    cardPtr->play(sourceTerritory, listToDefend.at(0), numberArmyUnits, nullptr);
                }
            }
            else if (orderType == "Diplomacy")
            {
                //pick player to negotiate with
                int choiceInt = 0;
                cmdIsValid = false;
                instructions = "With which player do you want to negotiate? (enter number):\n";

                vector<Player*> newAllPlayers = getAllPlayers();

                for (int i = 0; i < newAllPlayers.size(); i++) {
                    if (newAllPlayers.at(i) == getPlayer()) {
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
                cardPtr->play(nullptr, nullptr, NULL, randomPlayer);
            }
            else if (orderType == "Blockade")
            {
                vector<Territory*> listToDefend = toDefend();
                if (listToDefend.size() > 0) {
                    cardPtr->play(nullptr, listToDefend.at(0), NULL, nullptr);
                }
            }
        }
    }

    return true;
}
vector<Territory*> HumanPlayerStrategy::toDefend() {
    string instructions = "Which territory do you want to defend? (enter number):\n";

    vector<Territory*> ownedTerritories = getPlayer()->getTerritories();

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

    for (int i = 0; i < getMap()->getTerritories().size(); i++) {
        if (getMap()->getTerritories().at(i)->getOwner() != getPlayer()) {
            territoriesToConquer.push_back(getMap()->getTerritories().at(i));
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


AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p, vector<Player*> allPls, Map* map) : PlayerStrategy(p, allPls, map) {}
bool AggressivePlayerStrategy::issueOrder() {
    return false;
}
vector<Territory*> AggressivePlayerStrategy::toDefend() {
    return vector<Territory*>{};
}
vector<Territory*> AggressivePlayerStrategy::toAttack() {
    return vector<Territory*>{};
}


BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p, vector<Player*> allPls, Map* map) : PlayerStrategy(p, allPls, map) {}
bool BenevolentPlayerStrategy::issueOrder() {
    return false;
}
vector<Territory*> BenevolentPlayerStrategy::toDefend() {
    return vector<Territory*>{};
}
vector<Territory*> BenevolentPlayerStrategy::toAttack() {
    return vector<Territory*>{};
}


NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p, vector<Player*> allPls, Map* map) : PlayerStrategy(p, allPls, map) {}
bool NeutralPlayerStrategy::issueOrder() {
    return false;
}
vector<Territory*> NeutralPlayerStrategy::toDefend() {
    return vector<Territory*>{};
}
vector<Territory*> NeutralPlayerStrategy::toAttack() {
    return vector<Territory*>{};
}


CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p, vector<Player*> allPls, Map* map) : PlayerStrategy(p, allPls, map) {}
bool CheaterPlayerStrategy::issueOrder() {
    return false;
}
vector<Territory*> CheaterPlayerStrategy::toDefend() {
    return vector<Territory*>{};
}
vector<Territory*> CheaterPlayerStrategy::toAttack() {
    return vector<Territory*>{};
}