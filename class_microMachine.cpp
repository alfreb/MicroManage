#include "class_microMachine.h"

/*
  Base class initialization
*/
int microMachine::instanceCount=0;

microMachine::microMachine(QString n) : 
  numericId(++instanceCount),isBooted(0),instanceName(n),
  bestResponseTime_ms(-1),lastResponseTime_ms(0),currentQoS(-1){}

microMachine::microMachine() : 
  numericId(++instanceCount),isBooted(0),instanceName("N/A"),
  bestResponseTime_ms(-1),lastResponseTime_ms(0),currentQoS(-1){}


microMachine::~microMachine(){
  /* 
     Nothing allocated, nothing freed.
     
     OBS: unexpected behavior will result from when deleting a VM object before the process is stopped.     
  */  
}


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

/*
  Statics

 */

QString qemuVm::command="qemu-system-i386";

QStringList cmd_args(){
  QStringList args;
  args << "-hda" << "../microMachines_experimental_clean/microMachine.hda";
  args << "--nographic";
  return args;
}

QStringList qemuVm::args=cmd_args();



/*
  Construct / Destruct
*/
qemuVm::qemuVm() :
  microMachine() {}

qemuVm::qemuVm(QString n) :
  microMachine(n){}

qemuVm::~qemuVm(){
  halt();
}


/*
  Start / Stop
*/
void qemuVm::boot(){  
  proc.start(command,args);
}

void qemuVm::halt(){
  proc.kill();
}


/*
  VM Communication
*/

QString qemuVm::readAll(){
  proc.waitForReadyRead();
  return QString(proc.readAll().constData());
}

void qemuVm::write(const char* s){
  if(isBooted==0){
    qDebug()<<"Waiting for vm to boot...";
    QString bootString=readAll();
    if(bootString.size()>1)
      qDebug()<<"Boot signal too big? : '" << bootString << "'. Only first char saved.";
    isBooted=bootString.at(0);
  }
    
  proc.write(s);
}

response qemuVm::processRequest(const char* req){  
  write(req);
  return readAll();  
}

response qemuVm::processRequest_timed(const char* req,QTime& t){
  t.start();
  write(req);
  QString resp=readAll();
  lastResponseTime_ms=t.elapsed();
  if(lastResponseTime_ms<bestResponseTime_ms){
    bestResponseTime_ms=lastResponseTime_ms;
    currentQoS=10;
  }else{
    currentQoS=(float(bestResponseTime_ms)/float(lastResponseTime_ms))*10;
  }
  return resp;
}


