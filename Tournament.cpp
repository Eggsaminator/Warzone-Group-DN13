#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "CommandProcessing.h"
#include "GameEngine.h"

using namespace std;




void testTournament()
{
    Engine* engine = new Engine();
    CommandProcessor* adapter = new CommandProcessor(engine);
    adapter->chooseInputMethod();
    delete adapter;

}
