#include <iostream>
#include <string>
#include <vector>
#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "CommandProcessing.h"
#include <set>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


void testStartupPhase()
{
	cout<<"Demonstration of the start up phase"<<endl;

	Engine* mEngine = new Engine();
	CommandProcessor* mCommandProcessor = new CommandProcessor(mEngine);
	mEngine->startupPhase(mCommandProcessor);
	vector<Player*> myListPlayer=mEngine->getPlayers();
	Hand * myHand;
	vector<Territory*> myTerr;
	for (int i = 0; i < size(myListPlayer); i++)
	{
		cout << "Player " << i << " :" << myListPlayer[i]->getName() << endl;
		myHand = myListPlayer[i]->getHand();
		myHand->display();
		myTerr = myListPlayer[i]->getTerritories();
		cout << "number of owned territories :" << myTerr.size() << endl;
		cout << "The reinforcement pool of the player contains : " << myListPlayer[i]->getReinforcementPool() << " army." << endl;
	}
}

int main()
{
testStartupPhase();	
}