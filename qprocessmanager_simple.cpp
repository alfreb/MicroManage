#include "qprocessmanager_simple.h"
#include "QProcess"
#include "iostream"

using namespace std;


qprocessManager_simple::qprocessManager_simple(QObject* parent)
{
    QString command="./qemu_dummy";//"qemu-system-i386";//
    QStringList args;
    args << "-hda" << "../microMachines_experimental_clean/microMachine.hda";
    args << "--nographic";

#define VM_COUNT 202
    cout << "Creating process objects" << endl;
    for(int i=0;i<VM_COUNT; i++)
        vms.push_back(new QProcess(parent));

    cout << "Processes created. Type 'asdf' or someting to start them...";
    string s;
    cin >> s;

    cout << "Starting processes" << endl;

    QProcess* p;
    QVector<QProcess*>::Iterator it;
    for(it=vms.begin(); it!=vms.end(); ++it){
        p=*it;
        p->start(command,args);
    }
    cout << "All started" << endl;
}

qprocessManager_simple::~qprocessManager_simple(){
    QProcess* p;
    QVector<QProcess*>::Iterator it;
    for(it=vms.begin(); it!=vms.end(); ++it){
        p=*it;
        p->kill();
    }
}
