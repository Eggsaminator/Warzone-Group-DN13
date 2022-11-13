#include <iostream>
#include "CommandProcessing.h"
#include "GameEngine.h"

using namespace std;

void testCommandProcessor() {
    Engine* engine = &Engine();
    CommandProcessor* processor = CommandProcessor::instance(engine);

    cout << "---------------------------------------------" << endl;
    cout << "Part 1: Commands can be read from the console" << endl;
    cout << "---------------------------------------------" << endl;
    // Use the following input strings to the console:
    /*
    asdf
    -console
    loadmap asdf
    gamestart
    replay
    replay
    */
    processor->chooseInputMethod();
    for (int i = 0; i < 3; i++) {
        processor->getCommand();
    }

    cout << "---------------------------------------------" << endl;
    cout << "Part 2: Commands can be read from a text file" << endl;
    cout << "---------------------------------------------" << endl;
    
    // Note that the following commented code also works:
    // processor->chooseInputMethod();
    // Input into the console: "-file commandFile.txt"

    FileCommandProcessorAdapter* adapter = FileCommandProcessorAdapter::instance(engine);
    adapter->setFile("commandFile.txt");
    adapter->processFile();

    cout << "--------------------------------------------------------------" << endl;
    cout << "Part 3: Commands result in the correct effect and state change" << endl;
    cout << "--------------------------------------------------------------" << endl;
    // Use the following input strings to the console:
    /*
    quit
    loadmap asdf
    loadmap asdf
    validatemap
    addplayer asdf
    gamestart
    replay
    quit
    */
    
    Command* command;

    for (int i = 0; i < 8; i++) {
        command = processor->getCommand();
        cout << "Engine state: " << engine->getCurrentState()->getStateName() << endl;
    }

    string input;
    cin >> input;
}