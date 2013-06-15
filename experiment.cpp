#include <iostream>

#include "experiment.h"

using namespace std;
experiment::experiment(microManager* _manager, QObject *parent) :
    QObject(parent),manager(_manager),
    samplesToCollect(10),samplesCollected(0),bootBatchSize(48),
    sampler(new perfdata::perfsampler(_manager,true))
{}


void experiment::samplingDone(){
    if(sampler->numberOfSamples()<samplesToCollect){
        cout << "Collected "
             << sampler->numberOfSamples() << " / "
             << samplesToCollect << " samples. Continuing."
             << endl;

            connect(manager,SIGNAL(n_confirmed_boot()),this,SLOT(bootingDone()));
            manager->boot_n(bootBatchSize);
    }else{
        cout << "Sampling complete" << endl;
        sampler->printSamples(&cout);
        emit experimentComplete();
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
