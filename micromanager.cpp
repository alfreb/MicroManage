#include "micromanager.h"
#include <iostream>
#include <QDebug>

using namespace std;

microManager::microManager(QObject *parent) :
    QObject(parent)
{
}

microManager::~microManager(){
    vector<qemuVm*>::iterator it;
    cout << "Killing all processes" << endl;
    for(it=vms.begin(); it!=vms.end(); it++){
        (*it)->halt();
        //No need to delete the objects - it will take forever and we're exiting anyway.
        //delete(*it);
    }
}

void microManager::menu_main(int vmCount){
    cout << endl << endl
         << " S I M U L A T I O N   M A N A G E R " << endl
         << " ===================================" << endl
         << endl
         << vmCount << " VM's currently booted" << endl
         << endl
         << "1 : Interact with a VM "<< endl
         << "2 : Boot more VM's "<< endl
         << "3 : Sample random response times"<< endl
         << "q : Quit "<< endl
         << endl;
}

void microManager::userPrompt(){
    std::string input="";

    while(true){

        menu_main(vms.size());

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


void microManager::menu_vmInteraction(){
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

void microManager::menu_time_n_random_requests(){
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

void microManager::bootN(int n){
    qemuVm* vm;
    for(int i=0;i<n; i++){
        vm=new qemuVm;
        vm->boot();
        vms.push_back(vm);
    }
    //vmCount=vms.size();
}


void microManager::menu_bootMore(){
    int count(0);
    cout << endl << "How many more? ";
    cin>>count;

    cout << "Booting " << count << " more machines" << endl;
    try{
        bootN(count);
    }catch(string s){
        cout << "Error during boot: " << s.c_str() << endl;
    }
}




