#ifndef MICROMACHINE_H
#define MICROMACHINE_H

#include <QObject>
#include <QTime>

//Would typically become a more complex type later, including it's own assessment of QoS
typedef QString response;

/*
    Abstract class
*/

class microMachine : public QObject
{
    Q_OBJECT

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
  explicit microMachine(QObject *parent = 0);
    
signals:
  void bootConfirmed();
    
public slots:

    
};

#endif // MICROMACHINE_H
