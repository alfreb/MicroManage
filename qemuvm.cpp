#include "qemuvm.h"
#include "QDebug"
#include <iostream>
/*
  Statics

 */

QString qemuVm::command="./qemu_dummy";//"qemu-system-i386";//

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
    microMachine(),boot_char('!') {
    //connect(&proc,SIGNAL(readyRead()),this,SLOT(firstByteRecieved()));
}

/*
qemuVm::qemuVm(QString n) :
  microMachine(n){}
*/

qemuVm::~qemuVm(){
  halt();
}

/*
  Start / Stop
*/
void qemuVm::boot(){
  proc.start(command,args);

  //This is necessary if the command is not valid, i.e. on mac.
  if(!proc.waitForStarted()){
      throw std::string("Unable to run "+command.toStdString());
  }
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
      /*
    qDebug()<<"Waiting for vm to boot...";
    QString bootString=readAll();
    if(bootString.size()>1)
      qDebug()<<"Boot signal too big? : '" << bootString << "'. Only first char saved.";
    isBooted=bootString.at(0);*/
      qDebug()<<"VM has not yet confirmed boot. Try again later.";
      return;
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

void qemuVm::firstByteRecieved(){
    QByteArray data=proc.readAll();
    //proc.state()
    if(isBooted==0 and data[0]==boot_char){
        //std::cout <<"Boot confirmed: vm "<< this->numericId << std::endl;
        this->isBooted=true;
        //disconnect(&proc,SIGNAL(readyRead()),this,SLOT(firstByteRecieved()));
        //emit bootConfirmed(this);
    }else if(isBooted==0){
        std::cout <<"Unexpected process output: " << std::string(data).c_str() << std::endl;
    }else{
        //There was data from the process. Save?
    }
}
