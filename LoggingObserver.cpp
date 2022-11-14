#include "LoggingObesrver.h"


Observer::Observer(){
}; 
Observer::~Observer(){
};

LogObserver::LogObserver(){
}
LogObserver::LogObserver(Subject *s){
_subject = s;
s->attach(this);
logFile->open("gamelog.txt", std::ios_base::app);
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
  
}