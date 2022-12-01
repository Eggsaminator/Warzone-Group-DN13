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
    FileCommandProcessorAdapter* adapter = new FileCommandProcessorAdapter(engine);
    adapter->chooseInputMethod();

}

int main()
{
    testTournament();
}