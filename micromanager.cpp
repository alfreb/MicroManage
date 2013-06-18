#include <iostream>
#include <fstream>
#include <QDebug>
#include <QThread>
#include <unistd.h>

#include "micromanager.h"
#include "experiment.h"
//#include "../perfdata/perfSampler.h"
using namespace std;

microManager::microManager(QObject *parent) :
    QObject(parent),vmsBooted(0),pctBooted(0),progStep(0),samplesOrdered(0),sum_sampleTimes(0),totalCPUCores(sysconf( _SC_NPROCESSORS_ONLN ))
{
    connect(this,SIGNAL(menuItemComplete()),this,SLOT(userPrompt()));
    
    for(int i=0;i<totalCPUCores;i++){
        freeCores.push_back(i);
    }

    //QThread* thread1=new QThread;
    //perf->moveToThread(thread1);
    //connect(thread1,SIGNAL(started()),perf,SLOT(startSampling()));
    //connect(thread1,SIGNAL())
}

microManager::~microManager(){
    vector<qemuVm_qprocess*>::iterator it;
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
         << "2 : Boot n VM's "<< endl
         << "3 : Shutdown n VM's"<< endl
         << "4 : Sample random response times"<< endl
         << "5 : Restrict VM's to certain cores " << endl
         << "6 : Sample random response, with automatic CPU-reassign"<< endl
         << "7 : Run Scaling Profile Experiment"<< endl
         << "8 : Sample CPU (multisample) and memory (single sample)"<< endl
         << "q : Quit "<< endl
         << endl;

}

void microManager::userPrompt(){
    std::string input="";

    // while(true){

    menu_main(vms.size());

    int reqs(0);
    while(input.size()<1){
        cout << endl << ++reqs << " microManage$ ";
        std::getline(cin,input);
    }

    switch(QString(input.c_str()).at(0).toLower().toLatin1()){
    case '1':
        menu_vmInteraction();
        break;
    case '2':
        menu_boot_n();
        break;
    case '3':
        menu_shutdown_n();
        break;
    case '4':
        menu_time_n_random_requests();
        break;
    case '5':
        menu_restrict_to_cores();
        break;
    case '6':
        menu_time_n_random_requests(true);
        break;
    case '7':
        menu_run_scaling_profile_experiment();
        break;
    case '8':
        menu_perfsampler();
	break;
    case 'q':
        cout <<"Exiting" << endl;
        emit exit();
        return;
    }
    //}
}

void microManager::menu_perfsampler(){

    int sampleRate(1),sampleCount(6),iterations(10);
    bool log(true);
    
    cout << "Sampling memory and CPU. "
         << "Default setup is:" << endl
         << iterations << " multisamples, "
         << "each an average (with errors) of " << sampleCount
         << " individual samples collected with " << sampleRate
         << " second(s) interval. Simple logging to file is on. "<< endl
	 << " logging to separate files (for mac plot) is off." << endl
         << " 'c' to change, 'y' (or anything) to go on: ";

    char in;
      //    cin>>in;
    string line;
    getline(cin, line);
    in=line[0];
    
    if(in=='c' or in=='C'){
      cout << "Total number of multisamples: "; 
      cin >> iterations;
      cout << "Samples pr. multisample: "; 
      cin >> sampleCount;
      cout << "Sample rate: "; 
      cin >> sampleRate;
      cout << "Log to separate files? (bool,1 or 0)"; 
      cin >> log;
      
    }
    
    sampler=new perfdata::perfsampler(this,sampleRate,sampleCount,true,sampleRate,iterations,log);
    connect(sampler,SIGNAL(samplingDone()),this,SLOT(complete_menu_perfsampler()));
    
    sampler->start();

    cout << "Sampler started" << endl;
}


void microManager::complete_menu_perfsampler(){

  emit menuItemComplete();
}
void microManager::menu_restrict_to_cores(){
    cout << "Enter a list of cpu-cores, between 1 and core count,  separated with enter. End with n <= 0 " << endl;
    std::vector<int> cores;
    int core;
    do{
        cin>>core;
        if(core>0)
            cores.push_back(core-1);
    }while(core>0);

    cout << "Registered cores: " << endl;
    for(vector<int>::iterator it=cores.begin(); it!=cores.end();++it)
        cout << *it << " ";
    cout << endl;
    cout << "Assigning..." << endl;

    vector<qemuVm_qprocess*>::iterator it;
    for(it=vms.begin();it!=vms.end();++it)
        (*it)->assignToCores(cores);

    cout << "All processes reassigned" << endl;
    emit this->menuItemComplete();
}

void microManager::menu_vmInteraction(){
    response data;
    int vmNr(0);
    qemuVm_qprocess* vm(0);
    string req="a";

    cout << endl << "Enter vm id: ";
    cin >> vmNr;
    if(vmNr>=0 and vmNr<vms.size()){
        vm=vms[vmNr];
        cout << "Enter a single character request" << endl;
        cin >> req;
        timedRequest(vm,req);
    }else{
        cout << "Invalid ID. Type a number between 0 and " << vms.size() << endl;
        emit this->menuItemComplete();
    }
    //
}

void microManager::timedRequest(qemuVm_qprocess *vm,std::string req,vector<int>* onCores){

    vmsRequested.push_back(vm);

    qDebug()<<"Requesting VM " << vm->id();
    connect(vm,SIGNAL(timedRequestHandled(qemuVm_qprocess*,int)),this,SLOT(timedRequestHandled(qemuVm_qprocess*,int)));
    if(!onCores)
        vm->processRequest_timed(req);
    else{
        vm->processRequest_timed_withCoreReassign(req,*onCores);
    }

}

void microManager::menu_run_scaling_profile_experiment(){
    experiment* e=new experiment(this);
    connect(e,SIGNAL(experimentComplete()),this,SLOT(userPrompt()));
    e->start();
}

void microManager::menu_time_n_random_requests(bool withCoreReassign){
    int sampleCount(0);
    int vmNr(0);

    Q_ASSERT(vmsRequested.size()==0);

    qemuVm_qprocess* vm(0);
    QString data;

    cout << endl << "How many samples? " << endl;
    cin >> sampleCount;

    while(sampleCount>vms.size()){
        cout << "Please enter a sample size smaller than "<< vms.size()<< "(the number of VM's) ";
        cin >> sampleCount;
    }

    cout << "------------------------------------------------------------------" << endl;
    cout << "Sampling QoS from " << sampleCount << " randomly selected vm's" << endl;
    cout << "------------------------------------------------------------------" << endl;
    this->samplesOrdered=sampleCount;
    this->sum_sampleTimes=0;
    
    vector<int>* cores=0;
    if(withCoreReassign){
        cores=&freeCores;
    }

    for(int i=0;i<samplesOrdered; i++){

        //Randomly draw vms that are not allready being requested
        do{
            vmNr=rand() % vms.size();
        }while(find(vmsRequested.begin(),vmsRequested.end(),vms[vmNr])!=vmsRequested.end());

        timedRequest(vms[vmNr],"a",cores);

    }
    /*
    cout << endl << "Average response time over "
         << sampleCount << " samples: " << float(timeTotal)/float(sampleCount) << " ms."
         << endl;*/
}





void microManager::shutdown_n(int n){
    qDebug()<<"Shutting down "<< n << " vm's";
    if(n>=vms.size()){
        n=vms.size()-1;
    }

    qemuVm_qprocess* vm;
    for(int i=0;i<n; i++){
        vm=vms.back();
        qDebug()<<"shutting down Vm " << vm->id();

        vms.pop_back();
        vm->halt();
        //vm->deleteLater();
        //disconnect(vm,SIGNAL(bootConfirmed(qemuVm_qprocess*)),this,SLOT(bootConfirmed(qemuVm_qprocess*)));
        //connect(vm,SIGNAL(requestHandled(qemuVm_qprocess*, QByteArray)),this,SLOT(requestHandled(qemuVm_qprocess*,QByteArray)));
    }

    emit this->menuItemComplete();
}

void microManager::menu_shutdown_n(){
    cout << "Sorry, not yet implemented" << endl;
    emit this->menuItemComplete();
    return;

    int count(0);
    cout << endl << "How many do you want to shut down? ";
    cin>>count;

    if(count>vms.size()){
        cout << "Can't do that, "<<vms.size()<< " vms are booted.";

    }else{
        cout << "Terminating (stopping and then deleting remains) " << count << " vm's" << endl;
        shutdown_n(count);
    }


}

void microManager::boot_n(int n){
    qemuVm_qprocess* vm;
    //pctBooted=0;
    for(int i=0;i<n; i++){
        vm=new qemuVm_qprocess(this);
        vm->boot();
        vms.push_back(vm);
        connect(vm,SIGNAL(bootConfirmed(qemuVm_qprocess*)),this,SLOT(bootConfirmed(qemuVm_qprocess*)));
        //connect(vm,SIGNAL(requestHandled(qemuVm_qprocess*, QByteArray)),this,SLOT(requestHandled(qemuVm_qprocess*,QByteArray)));
    }
    //vmCount=vms.size();
}

void microManager::menu_boot_n(){
    int count(0);
    cout << endl << "How many do you want to boot? ";
    cin>>count;

    cout << "Booting " << count << "  machines" << endl;
    connect(this,SIGNAL(n_confirmed_boot()),this,SLOT(complete_menu_boot_n()));
    try{
        boot_n(count);
    }catch(string s){
        cout << "Error during boot: " << s.c_str() << endl;
    }
}

void microManager::complete_menu_boot_n(){
    disconnect(this,SIGNAL(n_confirmed_boot()),this,SLOT(complete_menu_boot_n()));
    emit menuItemComplete();
}

void microManager::bootConfirmed(qemuVm_qprocess* p){
    disconnect(p,SIGNAL(bootConfirmed(qemuVm_qprocess*)),this,SLOT(bootConfirmed(qemuVm_qprocess*)));
    //cout << "vmsBooted: " << vmsBooted << endl;
    int progWidth=50;
    if(++vmsBooted >= vms.size()){

        qDebug()<< " All booted! " << endl;
        emit n_confirmed_boot();


    }else{

        float pct=(float(vmsBooted)/float(vms.size()))*progWidth;
        float increase=pct - pctBooted;

        if(increase >= 5){
            cout << "\r 0% |";
            for(int i=0;i<progWidth;i++){
                if(i<=pct)
                    cout << "=";
                else
                    cout << " ";
            }

            cout << "| 100%";
            cout.flush();
            //cout << progString.c_str();
            pctBooted=pct;
        }

    }
}

void microManager::timedRequestHandled(qemuVm_qprocess * p, int t){
    //qDebug()<< " Response from vm " << p->id() << ", que size: " << vmsRequested.size();

    vector<qemuVm_qprocess*>::iterator it=find(vmsRequested.begin(),vmsRequested.end(),p);

    //FAILS: Q_ASSERT(it!=vmsRequested.end()); WHY?
    //IF we are expecting a response from this one:
    if(it!=vmsRequested.end()){
        if(samplesOrdered>0)
            sum_sampleTimes+=t;
        vmsRequested.erase(it);
    }

    if(vmsRequested.size()==0){
        if(samplesOrdered>0){
            cout << "------------------------------------------------------------------" << endl;
            float result=float(sum_sampleTimes)/float(samplesOrdered);
            cout << result << " average response time over " << samplesOrdered << " samples" << endl;
            cout << "With " << vms.size() << " vm's running " << endl;
            cout << "------------------------------------------------------------------" << endl;
        }
        emit menuItemComplete();
    }

}

int microManager::getVmsBooted(){return vms.size();}

