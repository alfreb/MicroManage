#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QStringList>
#include <vector>
#include <iostream>
#include <QTime>
#include <QTimer>

using namespace std;

class microManager : public QObject {

  Q_OBJECT
  
  int vmCount;
  QTime t;
  vector<QProcess*> vms;

public:
  
  microManager(int _vmCount,QObject *parent=0) : QObject(parent),vmCount(_vmCount) 
  {};
  ~microManager(){
    vector<QProcess*>::iterator it;
    cout << "Killing all processes" << endl;
    for(it=vms.begin(); it!=vms.end(); it++){
      (*it)->kill();
      
      //No need to delete the objects - it will just take forever, and we're exiting anyway.
      //delete(*it);
    }
    

  };
										     
										     
										     
public slots:
  
  void doneBooting(){
    QByteArray data;    
    int vmToPoke(0);
    cout << "Done booting. " << endl;
    do{
      data.clear();
      cout << "Enter id of a vm to poke: " << endl;
      cin >> vmToPoke;
      if(vmToPoke>=0 and vmToPoke<vms.size()){
	t.start();
	vms[vmToPoke]->write("a"); //If this happens before vm is booted, it will mess up the seiral port
	vms[vmToPoke]->waitForReadyRead();
	data.append(vms[vmToPoke]->readAll());	
	qDebug() << "Response: " << data << " response time: " << t.elapsed() << endl;
      }else{
	cout << "Invalid ID. Type a number between 0 and " << vms.size() << endl;
      }
      
    }while(vmToPoke>0);
    
    cout <<"Exiting" << endl;
    emit exit();
  }
  
  void bootAll(){        

    QStringList args;
    args << "-hda" << "../microMachines_experimental_clean/microMachine.hda";
    args << "--nographic";
 
  
    QProcess* proc;
    for(int i=0; i<vmCount; i++){
      proc=new QProcess;
      //    proc->setProcessChannelMode(QProcess::MergedChannels);
      proc->start("qemu-system-i386",args);
      //      proc->waitForStarted(); //Creates buffer overflow after 2-300 vm's
      vms.push_back(proc);  
      //      qDebug()<< i << " vm's launched";
      /*
      if(i>0 and i%100==0){
	cout << "Booted " << i << " vm's - taking a break" << endl;
	sleep(3);
	cout << "Continuing" << endl;
	}*/
      
    
    };

    cout << "Booted " << vmCount << " vm's "<< endl;
    
    /*

      for(int i=0;i<vmCount; i++){
      //    data.clear();
      //vms[i]->waitForStarted();
      vms[i]->waitForReadyRead();
      //    
      //cout << " vm " << i << " confirmed boot " << endl;
      }*/
    
    //int keepGoing;
    
    //cout << "All VM's booted. Enter the number of a VM to poke: " << endl;
    /*cin >> keepGoing;
    
    /*
    srand(time(NULL));

    //  p1->write("ls\n");
  
    int sleepTime(0);
    QTime t;
    int timeout(60000);//MS to wait for response
    
    
    while(true){
      //sleepTime=rand()%10;
      //qDebug()<< "Sleeping " << sleepTime << "secs.";
      //sleep(sleepTime);
      //    qDebug()<<"Awake. Timing a request ";
      //    data.clear(); //Do we need to read it? No.
      t.start();
      proc->write("a");    

      if(proc->waitForReadyRead())
	qDebug()<< "Request took " << t.elapsed() << " ms. \n";
      else
	qDebug()<<"Timed out! Waited for " <<  timeout << " ms. and nothing.";
    }

    qDebug("Done");
    qDebug()<<data;
    */
    emit allBooted();
  }

signals:
  void allBooted();
  void exit();

};

#include "main.moc"


int main(int argc, char *argv[])
{        
  
  qDebug("\nServerside MicroManager\n");
  
  QCoreApplication a(argc, argv);
  int vmCount(48);

  if(argc>0)
    vmCount=atoi(argv[1]);

  microManager* manager=new microManager(vmCount,&a);

  QObject::connect(manager,SIGNAL(exit()), &a,SLOT(quit()));
  QObject::connect(manager,SIGNAL(allBooted()),manager,SLOT(doneBooting()));
  
  //Put the manager into the event-loop
  QTimer::singleShot(0,manager,SLOT(bootAll()));

  return a.exec();
  





}
