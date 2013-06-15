#include <iostream>

#include "experiment.h"

using namespace std;
experiment::experiment(microManager* _manager, QObject *parent) :
    QObject(parent),manager(_manager),
    samplesToCollect(20),samplesCollected(0),
    bootBatchSize(480),sampleInterval(2),
    maxCpu(90.0),maxMem(90.0),
    sampler(new perfdata::perfsampler(_manager,true))
{
    QString desc="Scalability test. \n";
    desc+="Cpu Limit: "+QString::number(maxCpu)
            +" Mem Limit: "+QString::number(maxMem)
            +" Batch size: "+QString::number(bootBatchSize)
            +" Sample rate: "+QString::number(sampleInterval)
            +"\n";
    description=desc.toStdString();

}


void experiment::samplingDone(){
    if(sampler->lastRecordedCpuUsage()<maxCpu
            and sampler->lastRecordedMemUsage()<maxMem){
        cout << "Collected "
             << sampler->numberOfSamples() << " / "
             << samplesToCollect << " samples. Continuing."
             << endl;

        connect(manager,SIGNAL(n_confirmed_boot()),this,SLOT(bootingDone()));
        manager->boot_n(bootBatchSize);
    }else{
        cout << "Sampling complete" << endl;
        sampler->printSamples(&cout);
        sampler->dumpData_separateFiles(experimentInfo());
        emit experimentComplete();
    }
}

string experiment::experimentInfo(){
    QString s(this->description.c_str());
    s+="Started: " + this->startTime.toString()+"\n";
    s+="Ended: " + this->stopTime.toString()+"\n";
    return s.toStdString();
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
