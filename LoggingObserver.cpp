#include <vector>
#include "LoggingObesrver.h"
#include "player.h"
#include "GameEngine.h"
#include "CommandProcessing.h"

Observer::Observer(){
}; 
Observer::~Observer(){
};

LogObserver::LogObserver(){
}
LogObserver::LogObserver(Subject *s){
_subject = s;
s->attach(this);
logFile = new ofstream("gamelog.txt", std::ios_base::app);
//logFile->open("gamelog.txt", std::ios_base::app);
}
LogObserver::~LogObserver(){
_subject->detach(this);
logFile->close();
}
void LogObserver::update(ILoggable *toLog){
    *logFile << toLog->stringToLog();
}



Subject::Subject(){
  _observers = new list<Observer*>;
}
Subject::~Subject(){ 
  delete _observers;
}
void Subject::attach(Observer* o){
  _observers->push_back(o);
};
void Subject::detach(Observer* o){
  _observers->remove(o);
};
void Subject::notify(ILoggable *toLog){
  list<Observer *>::iterator i = _observers->begin();
  for (; i != _observers->end(); ++i)
    (*i)->update(toLog);
};


void testLoggingObesrver(){
	ofstream *file = new ofstream("gamelog.txt", std::ios_base::app);
	*file << "\n\n\n\n\n------------------------------------------------------------------LOGGING TEST STARTS HERE------------------------------------------------------------------\n";

  vector<string> mapList;
	// initializing useful variables
	mapList.push_back("Canada.map");
	Player* sampleP = new Player("player");
	Player* sampleP2 = new Player("not player");
	Continent* continent = new Continent("test",0);
	Territory* sampleTarget = new Territory("territory #1", continent);
	Territory* sampleTarget1 = new Territory("territory #3", continent);
	Territory* sampleSource = new Territory("territory #2", continent);


	Orders* n1 = new Negotiate(sampleP, sampleP2);
  //create order logger
	//LogObserver *n1Log = new LogObserver(n1);
  //create orderlist logger
	//LogObserver *POlsLog = new LogObserver(sampleP->getOrdersList());
  //test addOrder logging
  sampleP->getOrdersList()->addOrder(n1);
	//test execute logging   1st LOGGING
	n1->execute();

  Engine *eng = new Engine();
  //create engine logger
	//LogObserver *engLog = new LogObserver(eng);
  //test transition logging
  eng->launchTransitionCommand("loadmap");

  CommandProcessor *cmdP = new CommandProcessor(eng);
	//LogObserver *cmdPLog = new LogObserver(cmdP);
  
  Command *cmd = new Command("logTesting Command");
	//LogObserver *cmdLog = new LogObserver(cmd);

  cmd->saveEffect("test the logging");

  cmdP->saveCommand(cmd);

}
