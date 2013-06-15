#include <iostream>

#include "experiment.h"

using namespace std;
experiment::experiment(microManager* _manager, QObject *parent) :
    QObject(parent),manager(_manager),
    samplesToCollect(3),samplesCollected(0),bootBatchSize(48),
    sampler(new perfdata::perfsampler(true))
{}


void experiment::samplingDone(){
    if(sampler->numberOfSamples()<samplesToCollect){
        cout << "Collected "
             << sampler->numberOfSamples() << " / "
             << samplesToCollect << " samples. Continuing."
             << endl;
        sampler->start();
    }else{
        cout << "Sampling complete" << endl;
        sampler->printSamples(&cout);
        if(manager->getVmsBooted()>=samplesToCollect*bootBatchSize){
            emit experimentComplete();
            return;
        }else{
            connect(manager,SIGNAL(n_confirmed_boot()),this,SLOT(bootingDone()));
            manager->boot_n(bootBatchSize);
        }
    }        
}

void experiment::bootingDone(){
    cout << manager->getVmsBooted() << " vm's booted. Sampling." << endl;
    disconnect(manager,SIGNAL(n_confirmed_boot()),this,SLOT(bootingDone()));
    sampler->start();
}

void experiment::start(){
    startTime=QDateTime::currentDateTime();
    connect(sampler,SIGNAL(samplingDone()),this,SLOT(samplingDone()));
    sampler->start();
}
