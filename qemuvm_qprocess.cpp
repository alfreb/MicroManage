#include "qemuvm_qprocess.h"
#include "QDebug"
#include <iostream>

#ifndef __MACH__
//LINUX-specific, for CPU core control
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#endif

//#define _GNU_SOURCE
/*
  Statics

 */


//QString qemuVm_qprocess::command="./qemu_dummy";
QString qemuVm_qprocess::command="qemu-system-i386";

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
    microMachine(),boot_char('!'),proc(this),timer(0)
{
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
  //BUT IT WILL BREAK EVERYTHING!!

  /*
  if(!proc.waitForStarted()){
      throw std::string("Unable to run "+command.toStdString());
  }*/

}

void qemuVm_qprocess::halt(){
  proc.kill();
}

void qemuVm_qprocess::halt_controlled(){
  proc.kill();
  connect(&proc,SIGNAL(finished(int)),this,SLOT(deleteLater()));
}

/*
    CPU Control - Linux only
*/
void qemuVm_qprocess::assignToCores(std::vector<int> cores)
{
    proc.

#ifndef __MACH__
  pid_t pid=getpid();
  cpu_set_t my_set;        /* Define your cpu_set bit mask. */
  CPU_ZERO(&my_set);       /* Initialize it all to 0, i.e. no CPUs selected. */

  vector<int>::iterator it;
  for(it=cores.begin(); it!=cores.end(); ++it)
    CPU_SET(*it, &my_set);     /* set the bit that represents core 7. */
  sched_setaffinity(pid, sizeof(cpu_set_t), &my_set); /* Set affinity of tihs process to */

#endif


  /* the defined mask, i.e. only 7. */
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
