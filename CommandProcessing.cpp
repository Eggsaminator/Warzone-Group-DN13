#include <iostream>
#include <fstream>
#include "CommandProcessing.h"

// -----CommandProcessor-----
CommandProcessor::CommandProcessor(Engine* engine) {
    m_engine = engine;
    new LogObserver(this);
}

CommandProcessor::~CommandProcessor() {

}

map<string, vector<string>> CommandProcessor::s_commandValidStates = {
    {"startup",{"start"}}, //new command
    {"loadmap", {"start", "maploaded"}},
    {"validatemap", {"maploaded"}},
    {"addplayer", {"mapvalidated", "playersadded"}},
    {"gamestart", {"playersadded"}},
    {"play", {"win"}},
    {"quit", {"win"}}
};

Command* CommandProcessor::readCommand() {
    string userInput;
    string cmd;
    string argument;

    do {
        cout << "Please enter a valid command:" << endl;
        getline(cin, userInput);
        int delimiterIndex = userInput.find(' ');

        cmd = userInput.substr(0, delimiterIndex);
        argument = (delimiterIndex != string::npos) ? userInput.substr(delimiterIndex + 1, userInput.length()) : "";

        cout << "Command: " << cmd << endl;
        cout << "Argument: " << ((argument.compare("") != 0) ? argument : "None") << endl;
    } while (!inputIsValid(cmd, argument));

    Command* command = new Command(cmd, argument);
    saveCommand(command);
    return command;
}

void CommandProcessor::saveCommand(Command* command) {
    m_commandList.push_back(command);
    notify(this);
}

string CommandProcessor::stringToLog(){
	return "Command :" + m_commandList.back()->getName() + "\n";
}
Command* CommandProcessor::getCommand() {
    Command* command = readCommand();
    if (validate(m_engine->getCurrentState(), command)) {
        command->execute(m_engine);
        if(command->getName()=="startup")
        {
            cout<<"i need to start a game! "<<endl;
            m_engine->startupPhase(this);
        }
    }
    return command;
}

Command* CommandProcessor::getCommand(string promptMessage) {
    cout << promptMessage << endl;
    return getCommand();
}

Command* CommandProcessor::getSimpleCommandNoValidation(string promptMessage) {
    cout << promptMessage << endl;
    Command* command;

    string userInput;
    string cmd;

    getline(cin, userInput);
    int delimiterIndex = userInput.find(' ');

    cmd = userInput.substr(0, delimiterIndex);

    command = new Command(cmd, "");

    return command;
}

// Checks if the entered strings correspond to a valid command
bool CommandProcessor::inputIsValid(string command, string argument) {
    // Ensure command exists
    if (!s_commandValidStates.count(command)) {
        return false;
    }


    if ((command.compare("loadmap") == 0)
        || (command.compare("addplayer") == 0)) {
            
        return (argument.compare("") != 0);
    } else {
        return (argument.compare("") == 0);
    }
}

// Ensures the command is valid in the current state
bool CommandProcessor::validate(State* state, Command* command) {
    if (!isValid(state, command))
    {
        string invalidCommandError = "Error! This command " + command->getName() + " is invalid in the current GameState " + state->getStateName() + "!";
        cout << invalidCommandError << endl;
        command->saveEffect(invalidCommandError);
        return false;
    }
    return true;
}

// Checks the validity of a command in the passed state
bool CommandProcessor::isValid(State* state, Command* command) {
    if (state == nullptr || command == nullptr)
    {
        return false;
    }
    // Ensure command name exists
    bool commandExists = false;
    map<string, vector<string>>::iterator commandIterator;
    for (commandIterator = s_commandValidStates.begin(); commandIterator != s_commandValidStates.end(); commandIterator++) {
        if (commandIterator->first.compare(command->getName()) == 0) {
            commandExists = true;
            break;
        }
    }
    if (!commandExists) {
        return false;
    }

    vector<string> validPair = (*commandIterator).second;
    // Check if command matches any of the valid states
    for (vector<string>::iterator it = validPair.begin(); it != validPair.end(); it++) {
        if (it->compare(state->getStateName()) == 0) {
            return true;
        }
    }

    return false;
}

void CommandProcessor::chooseInputMethod() {
    string userInput;
    string cmd = "";
    string argument = "";
    while (!isValidInputMethod(cmd, argument)) {
        cout << "Please enter a valid input method (-console or -file <filename> or tournament):" << endl;
        getline(cin, userInput);
        int delimiterIndex = userInput.find(' ');

        cmd = userInput.substr(0, delimiterIndex);
        argument = (delimiterIndex != string::npos) ? userInput.substr(delimiterIndex + 1, userInput.length()) : "";

        cout << "Command: " << cmd << endl;
        cout << "Argument: " << ((argument.compare("") != 0) ? argument : "None") << endl;
    }

    if (cmd.compare("-console") == 0) {
        getCommand();
    }
    if (cmd.compare("-file") == 0) {
        FileCommandProcessorAdapter* fileProcessor = new FileCommandProcessorAdapter(m_engine);
        fileProcessor->setFile(argument);
        fileProcessor->processFile();
    }

    if(cmd.compare("tournament")==0)
    {
        cout<<"hello it is a tournament"<<endl;
        generate_tournament(userInput);
        cout<<"generate file is done"<<endl;
        FileCommandProcessorAdapter* fileProcessor = new FileCommandProcessorAdapter(m_engine);
        fileProcessor->setTournament(true); // Added the tournament status !!!!
        fileProcessor->setFile("tournament.txt");
        cout<<"processfile begins"<<endl;
        fileProcessor->processFile();
        //fileProcessor->m_engine->startupPhase(fileProcessor);
        //fileProcessor->m_engine->mainTournamentLoop(fileProcessor);
        //cout<<"start up finished";
    }
}

bool CommandProcessor::isValidInputMethod(string command, string argument) {
    if ((command.compare("-console") == 0 && argument.compare("") == 0)
        || (command.compare("-file") == 0 && argument.compare("") != 0) ||(command.compare("tournament") == 0 && argument.compare("") != 0)) {
        return true;
    }
    return false;
}

void CommandProcessor::setTournament(bool b)
{
    is_tournament=b;
}

bool CommandProcessor::getTournament()
{
    return is_tournament;
}

// -----Command-----
Command::Command(string command) {
    m_command = command;
    m_argument = "";
    m_effect = "";
    new LogObserver(this);
}

Command::Command(string command, string argument) {
    m_command = command;
    m_argument = argument;
    m_effect = "";
    new LogObserver(this);
}

Command::~Command() {

}

void Command::execute(Engine* engine) {
    if (engine == nullptr) {
        cout << "Error! Engine invalid" << endl;
        return;
    }

    saveEffect(m_command);
    engine->launchTransitionCommand(m_command);
    
}

string Command::getName() {
    return m_command;
}

string Command::getArgument() {
    return m_argument;
}

string Command::getEffect() {
    return m_effect;
}

void Command::saveEffect(string effect) {
    m_effect = effect;
    notify(this);
}

string Command::stringToLog(){
	return "Command's effect:" + this->getEffect() + "\n";
}
// -----FileCommandProcessorAdapter-----
FileCommandProcessorAdapter::FileCommandProcessorAdapter(Engine* engine) : CommandProcessor(engine) {
    m_fileContents = nullptr;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {

}

void FileCommandProcessorAdapter::setFile(string path) {
    m_filePath = path;
    m_fileContents = readFile(m_filePath);
}

void FileCommandProcessorAdapter::processFile() {
    // readCommand() pops m_fileContents, thus this will never be infinite
    while (m_fileContents->size() > 0) {
        Command* command = readCommand();
        //cout<<"i got a new command"<<endl;
        if (validate(m_engine->getCurrentState(), command)) {
            command->execute(m_engine);
            //cout<<"command done";
            if(command->getName()=="startup")
        {
            //cout<<"i need to start a game! "<<endl;
            m_engine->startupPhase(this);

            //cout <<"finish complete game loop"<<endl;
        }
        if(command->getName()=="play")
        {
            //cout<<"i want to replay"<<endl;
            m_engine->replay_game(this);
        }
        }
    }
    cout<<"exiting process file"<<endl;
}

queue<string>* FileCommandProcessorAdapter::readFile(string path) {
    queue<string>* fileText = new queue<string>();
    string nextLine;
    ifstream file(path);

    while (getline(file, nextLine)) {
        fileText->push(nextLine);
    }

    file.close();
    return fileText;
}

Command* FileCommandProcessorAdapter::readCommand() {
    string userInput;
    string cmd;
    string argument;

    do {
        userInput = m_fileContents->front();
        m_fileContents->pop();
        int delimiterIndex = userInput.find(' ');

        cmd = userInput.substr(0, delimiterIndex);
        argument = (delimiterIndex != string::npos) ? userInput.substr(delimiterIndex + 1, userInput.length()) : "";

        cout << "Command: " << cmd << endl;
        cout << "Argument: " << ((argument.compare("") != 0) ? argument : "None") << endl;
    } while (!inputIsValid(cmd, argument) && !m_fileContents->empty());

    if (m_fileContents->empty() && !inputIsValid(cmd, argument))
    {
        cout << "File " << m_filePath << " is out of valid commands! Error!" << endl;
        return nullptr;
    }

    Command* command = new Command(cmd, argument);
    saveCommand(command);
    return command;
}

void generate_tournament(string userInput)
{
    string cmd=userInput.substr(0,userInput.find(' '));
    

    string arg_m;
    string arg_p;
    string arg_d;
    string arg_g;
    vector<string> arguments;

        arg_m=userInput.substr(userInput.find("-M")+2,userInput.find("-P")-5-userInput.find("-M")+2);
        cout<<arg_m<<endl;
        arguments.push_back(arg_m);
        arg_p=userInput.substr(userInput.find("-P")+2,userInput.find("-G")-5-userInput.find("-P")+2);
        cout<<arg_p<<endl;
        arguments.push_back(arg_p);
        arg_g=userInput.substr(userInput.find("-G")+2,userInput.find("-D")-5-userInput.find("-G")+2);
        cout<<arg_g<<endl;
        arguments.push_back(arg_g);
        arg_d=userInput.substr(userInput.find("-D")+2,userInput.length());
        cout<<arg_d<<endl;
        arguments.push_back(arg_d);




    if(cmd.compare("tournament")!=0 ||arguments.size()!=4)
    {
        cout<<"This command is not valid a tournament command";
    }
    else
    {
        // The command is valid we can start to write the file
        ofstream strm;
        strm.open("tournament.txt");
        ofstream stream;
        stream.open("tournament_report.txt");
        stream<<"Tournament mode:"<<endl;
        stream<<"M: ";
        
        vector<string> maps;
        string list_map=arguments[0];
        int delim_index=list_map.find(',');
        int previous=0;
        maps.push_back(list_map.substr(1,delim_index-1));
        stream<<list_map.substr(1,delim_index-1)<<", ";
        while(delim_index!=string::npos){
        previous=delim_index;
        delim_index=list_map.find(',',delim_index+1);
        maps.push_back(list_map.substr(previous+1,delim_index-previous));
        stream<<list_map.substr(previous+1,delim_index-previous)<<", ";
        }
        stream<<endl;

        stream<<"P: ";

        

        // TODO Separate list of players
        vector<string> players;
        string list_player=arguments[1];
        delim_index=list_player.find(',');
        previous=0;
        players.push_back(list_player.substr(1,delim_index-1));
        stream<<list_player.substr(1,delim_index-1)<<", ";
        while(delim_index!=string::npos){
        previous=delim_index;
        delim_index=list_player.find(',',delim_index+1);
        players.push_back(list_player.substr(previous+1,delim_index-previous));
        stream<<list_player.substr(previous+1,delim_index-previous)<<", ";
        }
        stream<<endl;


        int number_game;
        number_game=stoi(arguments[2]);
        stream<<"G: "<<number_game<<endl;
        int max_loop;
        max_loop=stoi(arguments[3]);
        stream<<"D: "<<max_loop<<endl;

        for(int i=0;i<number_game;i++)
        {
            for(int j=0;j<maps.size();j++)
            {   strm<<"startup"<<endl;
                strm<<"loadmap "<<maps[j]<<endl;
                strm<<"validatemap"<<endl;
                for(int k=0;k<players.size();k++)
                {
                    strm<<"addplayer "<<players[k]<<endl;

                }
                strm<<"gamestart"<<endl;
                if(i==number_game-1 && j==maps.size()-1)
                {
                    strm<<"quit"<<endl;
                }
                else{
                strm<<"play"<<endl;
                
                }
            }
        }
        //strm<<"quit"<<endl;

        strm.close();
        stream.close();

        
        



    }
}