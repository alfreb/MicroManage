#ifndef CLASS_MICROMACHINE_H
#define CLASS_MICROMACHINE_H

#include <QProcess>
#include <QDebug>
#include <QStringList>
#include <QString>

//Would typically become a more complex type later, including it's own assessment of QoS
typedef QString response;


/*
  Abstract class
 */
class microMachine {

protected:
  static int instanceCount;
  int numericId;
  
  //Contains the boot-character - usually "!"
  QChar isBooted;
  QString instanceName;
  
  unsigned int bestResponseTime_ms; 
  unsigned int lastResponseTime_ms;

  float currentQoS;
  

 public:
  //Start / Stop
  virtual void boot()=0;
  virtual void halt()=0;
  
  //Communication
  virtual QString readAll()=0;
  virtual void write(const char* s)=0;
  virtual response processRequest(const char* req)=0;
  virtual response processRequest_timed(const char* req,QTime& t)=0;
  
  //Getters
  QString name();
  int id();  
  float qos();
  unsigned int lastResponseTime();
  unsigned int bestResponseTime();
  
  
  //Construct / Destruct
  microMachine();
  microMachine(QString n);
  ~microMachine();
  
};


/*
  Qemu-mm
*/
class qemuVm : public microMachine{
  QProcess proc;
  static QString command;
  static QStringList args;
public:
  qemuVm();
  qemuVm(QString n);
  ~qemuVm();

  virtual void boot();
  virtual void halt();
  virtual QString readAll();
  virtual void write(const char* s);
  virtual response processRequest(const char* req);
  virtual response processRequest_timed(const char* req,QTime& t);
};


#endif
