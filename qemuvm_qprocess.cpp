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
    microMachine(),boot_char('!'),proc(this) {
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



/*
  VM Communication
*/

QString qemuVm_qprocess::readAll(){
  //proc.waitForReadyRead();
  return QString(proc.readAll().constData());
}

void qemuVm_qprocess::write(const char* s){
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

response qemuVm_qprocess::processRequest(const char* req){
  write(req);
  return readAll();
}

void qemuVm_qprocess::processRequest_timed(const char* req,QTime& t){
  t.start();
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

void qemuVm_qprocess::timedRequestReady(){
    QString resp=readAll();

}
