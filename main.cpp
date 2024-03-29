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
//#include "qemuvm.h"
//#include "qprocessmanager_simple.h"

using namespace std;

//#include "main.moc"


int main(int argc, char *argv[])
{        

    srand(time(0));

    qDebug("\nServerside MicroManager\n");

    QCoreApplication a(argc, argv);
    a.setApplicationName("microManage server");
    a.setOrganizationDomain("cs.hioa.no");
    a.setOrganizationName("NSA group, Dept. of Coumputer Science, HiOA");

    // qprocessManager_simple* manager=new qprocessManager_simple(&a);
    microManager* manager=new microManager(&a);

    QObject::connect(manager,SIGNAL(exit()), &a,SLOT(quit()));

    //Put the manager into the event-loop
    QTimer::singleShot(0,manager,SLOT(userPrompt()));

    return a.exec();


}
