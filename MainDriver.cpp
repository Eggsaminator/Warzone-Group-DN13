#include "GameEngineDriver.cpp"
#include "CardsDriver.cpp"
#include "MapDriver.cpp"
#include "OrdersDriver.cpp"
#include "PlayerDriver.cpp"


int main()
{
    //Part 1: Map
    testLoadMaps();

    //Part 2: Player
    testPlayers();

    //Part 3: Orders
    testOrdersList();

    //Part 4: Cards
    testCards();

    //Part 5: Game Engine
	testGameStates();
}