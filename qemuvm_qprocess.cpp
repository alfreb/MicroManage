#include "qemuvm_qprocess.h"
#include "QDebug"
#include <iostream>
/*
  Statics

 */


QString qemuVm_qprocess::command="./qemu_dummy";
//QString qemuVm::command="qemu-system-i386";

QStringList cmd_args(){
  QStringList args;
  args << "-hda" << "../microMachines_experimental_clean/microMachine.hda";
  args << "--nographic";
  return args;
}

QStringList qemuVm_qprocess::args=cmd_args();

/*
  Construct / Destruct
*/
qemuVm_qprocess::qemuVm_qprocess(QObject *parent) :
    microMachine(),boot_char('!'),proc(this),timer(0) {
    connect(&proc,SIGNAL(readyRead()),this,SLOT(firstByteRecieved()));
}

/*
qemuVm::qemuVm(QString n) :
  microMachine(n){}
*/

qemuVm_qprocess::~qemuVm_qprocess(){
  halt();
}

/*
  Start / Stop
*/
void qemuVm_qprocess::boot(){
  proc.start(command,args);

  //This is necessary if the command is not valid, i.e. on mac.
  if(!proc.waitForStarted()){
      throw std::string("Unable to run "+command.toStdString());
  }
}

void qemuVm_qprocess::halt(){
  proc.kill();
}

void qemuVm_qprocess::halt_controlled(){
  proc.kill();
  connect(&proc,SIGNAL(finished(int)),this,SLOT(deleteLater()));
}


/*
  VM Communication
*/

QString qemuVm_qprocess::readAll(){
  //proc.waitForReadyRead();
  return QString(proc.readAll().constData());
}

void qemuVm_qprocess::write(std::string s){
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
  proc.write(s.c_str());
}

void qemuVm_qprocess::processRequest(std::string req){
  connect(&proc,SIGNAL(readyRead()),this,SLOT(timedRequestDone()));
  write(req);
  //return readAll();
}

void qemuVm_qprocess::processRequest_timed(std::string req){
  connect(&proc,SIGNAL(readyRead()),this,SLOT(timedRequestDone()));
  timer=new QTime;
  timer->start();
  write(req);
}

void qemuVm_qprocess::firstByteRecieved(){
    QByteArray data=proc.readAll();
    //proc.state()
    if(isBooted==0 and data[0]==boot_char){
        //std::cout <<"Boot confirmed: vm "<< this->numericId << std::endl;
        isBooted=boot_char;
        disconnect(&proc,SIGNAL(readyRead()),this,SLOT(firstByteRecieved()));
        emit bootConfirmed(this);
    }else if(isBooted==0){
        std::cout <<"Unexpected process output: " << std::string(data).c_str() << std::endl;
    }else{
        qDebug()<<"This should not happen - this signal is disconnected";
        //There was data from the process. Save?
    }
}

void qemuVm_qprocess::timedRequestDone(){
    QByteArray data=proc.readAll();
    int t=-1;
    if(timer){
        t=timer->elapsed();
        this->lastResponseTime_ms=t;
        qDebug()<< "Response from VM " << this->id() << " : " << data << " Timed to " << t << " ms.";
        delete timer;
        timer=0;
    }
    disconnect(&proc,SIGNAL(readyRead()),this,SLOT(timedRequestDone()));
    emit this->timedRequestHandled(this,t);
}
