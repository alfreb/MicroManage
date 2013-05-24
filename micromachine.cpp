#include "micromachine.h"

int microMachine::instanceCount=0;

microMachine::microMachine(QObject *parent) :
    QObject(parent),
    numericId(++instanceCount),isBooted(0),instanceName("N/A"),
    bestResponseTime_ms(-1),lastResponseTime_ms(0),currentQoS(-1)
{}


/*
  Getters
*/
int microMachine::id(){
  return numericId;
}

unsigned int microMachine::lastResponseTime(){
  return lastResponseTime_ms;
}


float microMachine::qos(){
  return currentQoS;
}
