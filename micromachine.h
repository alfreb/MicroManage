#ifndef MICROMACHINE_H
#define MICROMACHINE_H

#include <QObject>
#include <QTime>
#include <QVector>

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

  //CPU control
  virtual void assignToCores(std::vector<int> &cores)=0;

  //Communication
  virtual QString readAll()=0;
  virtual void write(std::string s)=0;
  virtual void processRequest(std::string req)=0;
  virtual void processRequest_timed(std::string req)=0;
  virtual void processRequest_timed_withCoreReassign(std::string req,
						     std::vector<int>& cores)=0;

  //Getters
  QString name();
  int id();
  float qos();
  unsigned int lastResponseTime();
  unsigned int bestResponseTime();


  //Construct / Destruct
  explicit microMachine(QObject *parent = 0);
    
signals:
  //void bootConfirmed(microMachine* p);

    
public slots:

    
};

#endif // MICROMACHINE_H
