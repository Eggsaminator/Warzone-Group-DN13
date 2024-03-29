#include "CommandProcessing.h"
#include "GameEngine.h"

Engine* mainEngine = new Engine();
CommandProcessor* mainCommandProcessor = new CommandProcessor(mainEngine);

int main()
{
    //Part 1: Command processor
    //testCommandProcessor();
    
    //Part 2: Startup phase
    //testStartupPhase();

    //Part 3: Main Game Loop
    /*testMainGameLoop();*/

    //Part 4: Order Execution
    //testOrderExecution();

    //Part 5: logging
    //testLoggingObesrver();
	Map gameMap;
	vector<Player*> players;
	Player* player1 = new Player("player1");
	HumanPlayerStrategy* strat = new HumanPlayerStrategy(player1, players, &gameMap);
	player1->strategy = strat;

	Player* player2 = new Player("player2");
	Player* player3 = new Player("player3");

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);

	Continent* continent1 = new Continent("continent1", 10);
	Continent* continent2 = new Continent("continent2", 3);
	Continent* continent3 = new Continent("continent3", 1);

	Territory* terr1 = new Territory("terr1", continent1);
	Territory* terr2 = new Territory("terr2", continent1);
	Territory* terr2_1 = new Territory("terr2_1", continent1);
	Territory* terr3 = new Territory("terr3", continent2);
	Territory* terr4 = new Territory("terr4", continent2);
	Territory* terr4_1 = new Territory("terr4_1", continent2);
	Territory* terr4_2 = new Territory("terr4_2", continent2);
	Territory* terr4_3 = new Territory("terr4_3", continent2);
	Territory* terr4_4 = new Territory("terr4_4", continent2);
	Territory* terr4_5 = new Territory("terr4_5", continent2);
	Territory* terr4_6 = new Territory("terr4_6", continent2);
	Territory* terr4_7 = new Territory("terr4_7", continent2);
	Territory* terr4_8 = new Territory("terr4_8", continent2);
	Territory* terr4_9 = new Territory("terr4_9", continent2);
	Territory* terr4_10 = new Territory("terr4_10", continent2);
	Territory* terr4_11 = new Territory("terr4_11", continent2);
	Territory* terr5 = new Territory("terr5", continent3);
	Territory* terr6 = new Territory("terr6", continent3);

	terr1->addAdjacency(terr4_4);
	terr4_4->addAdjacency(terr1);
	terr2->addAdjacency(terr4_7);
	terr4_7->addAdjacency(terr2);

	player1->addTerritory(terr1);
	player1->addTerritory(terr2);
	player1->addTerritory(terr2_1);
	player1->addTerritory(terr3);
	player2->addTerritory(terr4);
	player2->addTerritory(terr4_1);
	player2->addTerritory(terr4_2);
	player2->addTerritory(terr4_3);
	player2->addTerritory(terr4_4);
	player2->addTerritory(terr4_5);
	player2->addTerritory(terr4_6);
	player2->addTerritory(terr4_7);
	player2->addTerritory(terr4_8);
	player2->addTerritory(terr4_9);
	player2->addTerritory(terr4_10);
	player2->addTerritory(terr4_11);
	player2->addTerritory(terr5);
	player3->addTerritory(terr6);

	gameMap.addContinent(continent1);
	gameMap.addContinent(continent2);
	gameMap.addContinent(continent3);

	mainEngine->setMyMap(&gameMap);
	mainEngine->setMyPlayers(players);

	player1->setReinforcementPoolLeftToDeploy(0);

	Deck* newDeck = new Deck();
	Hand* newHand = new Hand();
	Card* newCard1 = new Card("Bomb", newDeck, newHand);
	Card* newCard2 = new Card("Airlift", newDeck, newHand);
	Card* newCard3 = new Card("Diplomacy", newDeck, newHand);
	Card* newCard4 = new Card("Blockade", newDeck, newHand);
	
	newHand->setPlayer(player1);
	player1->setHand(newHand);
	player1->getHand()->add_card(newCard1);
	player1->getHand()->add_card(newCard2);
	player1->getHand()->add_card(newCard3);
	player1->getHand()->add_card(newCard4);

	player1->issueOrder();
}
