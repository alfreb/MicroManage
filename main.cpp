#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QStringList>
#include <vector>
#include <iostream>
#include <QTime>
#include <QTimer>

//Locals
#include "class_microMachine.h"
#include "class_microMachine.cpp"
#include "simulation_menu.h"


using namespace std;

class microManager : public QObject {

  Q_OBJECT
  
  int vmCount;
  QTime t;
  vector<qemuVm*> vms;

public:
  
  microManager(int _vmCount,QObject *parent=0) : QObject(parent),vmCount(_vmCount) 
  {};
  ~microManager(){
    vector<qemuVm*>::iterator it;
    cout << "Killing all processes" << endl;
    for(it=vms.begin(); it!=vms.end(); it++){
      (*it)->halt();      
      //No need to delete the objects - it will take forever and we're exiting anyway.
      //delete(*it);
    } 
};

public slots:
  
  void afterBoot(){
    std::string input="";
    
    while(true){
      

      print_menu(vms.size());
      
      cin >> input;
      
      switch(QString(input.c_str()).at(0).toLower().toLatin1()){
      case '1':
	menu_vmInteraction();
	break;
      case '2':
	menu_bootMore();
	break;
      case '3':
	menu_time_n_random_requests();
	break;
      case 'q':	
	cout <<"Exiting" << endl;
	emit exit();
	return;
      }                  
    }    
  }

  void menu_vmInteraction(){
    response data;    
    int vmNr(0);
    qemuVm* vm(0);
    char req='a';

    cout << endl << "Enter vm id: ";
    cin >> vmNr;      
    if(vmNr>=0 and vmNr<vms.size()){
      vm=vms[vmNr];
      cout << "Enter a single character request" << endl;
      cin >> req;
      data=vm->processRequest_timed(string(&req).c_str(),t); 
      qDebug() << "Response: " << data 
	       << " response time: " << vm->lastResponseTime()
	       << " QoS: " << vm->qos();
      }else{
	cout << "Invalid ID. Type a number between 0 and " << vms.size() << endl;
      }
  }

  void menu_time_n_random_requests(){
    int sampleCount(0);
    int vmNr(0);
    qemuVm* vm(0);
    QString data;

    cout << endl << "How many samples? " << endl;
    cin >> sampleCount;

    int timeTotal(0);
    
    for(int i=0;i<sampleCount; i++){
      vmNr=rand() % vms.size();
      vm=vms[vmNr];
      data=vm->processRequest_timed("a",t);
      qDebug()<< "VM nr. " << vmNr<< "Response: " << data
	       << " response time: " << vm->lastResponseTime()
	       << " QoS: " << vm->qos();
      timeTotal+=vm->lastResponseTime();
    }
    cout << endl << "Average response time over " 
	 << sampleCount << " samples: " << float(timeTotal)/float(sampleCount) << " ms."
	 << endl;
  }

  void bootN(int n){    
    qemuVm* vm;
    for(int i=0;i<n; i++){
      vm=new qemuVm;
      vm->boot();
      vms.push_back(vm);
    }
    vmCount=vms.size();
  }

  void menu_bootMore(){
    int count(0);
    cout << endl << "How many more? ";
    cin>>count;
    
    cout << "Booting " << count << " more machines" << endl;
    
    bootN(count);
    
  }

  
  void bootAll(){
    bootN(vmCount);
    emit allBooted();
  }

signals:
  void allBooted();
  void exit();

};

#include "main.moc"


int main(int argc, char *argv[])
{        
  
  srand(time(0));
  
  qDebug("\nServerside MicroManager\n");
  
  QCoreApplication a(argc, argv);

  int vmCount(0);

  if(argc>1)
    vmCount=atoi(argv[1]);

  microManager* manager=new microManager(vmCount,&a);

  QObject::connect(manager,SIGNAL(exit()), &a,SLOT(quit()));
  QObject::connect(manager,SIGNAL(allBooted()),manager,SLOT(afterBoot()));
  
  //Put the manager into the event-loop
  QTimer::singleShot(0,manager,SLOT(bootAll()));

  return a.exec();
  





}
