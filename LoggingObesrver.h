#pragma once
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class ILoggable {
public:
    virtual string stringToLog() = 0;
};

class Observer{
    public:
        ~Observer();
        Observer();
        virtual void update(ILoggable *toLog) = 0;

};

class Subject {
public:
    virtual void attach(Observer* o);
    virtual void detach(Observer* o);
    virtual void notify(ILoggable* toLog);
    Subject();
    ~Subject();
private:
    list<Observer*>* _observers;

};

class LogObserver : public Observer{
    public:
        LogObserver();
        LogObserver(Subject *s);
        ~LogObserver();
        void update(ILoggable *toLog);
    private:
        ofstream *logFile;
        Subject *_subject;
};




void testLoggingObesrver();