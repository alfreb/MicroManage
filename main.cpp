#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QStringList>
#include <vector>
#include <iostream>
#include <QTime>
#include <QTimer>

//Locals
//#include "class_microMachine.h"
//#include "class_microMachine.cpp"
//#include "simulation_menu.h"

#include "micromanager.h"
#include "qemuvm.h"

using namespace std;

//#include "main.moc"


int main(int argc, char *argv[])
{        
  
  srand(time(0));
  
  qDebug("\nServerside MicroManager\n");
  
  QCoreApplication a(argc, argv);

  int vmCount(0);

  if(argc>1)
    vmCount=atoi(argv[1]);

  microManager* manager=new microManager(&a);

  QObject::connect(manager,SIGNAL(exit()), &a,SLOT(quit()));
  //QObject::connect(manager,SIGNAL(allBooted()),manager,SLOT(afterBoot()));
  //Put the manager into the event-loop
  QTimer::singleShot(0,manager,SLOT(userPrompt()));

  return a.exec();
  

}
