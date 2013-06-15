#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <QObject>
#include <QDateTime>

#include "micromanager.h"
#include "../perfdata/perfSampler.h"

/*
    Example 1:
    - Test the effect of X on hyperScale [CPU, memory and VMCount]
        - where X is [trueSleep, kvm, qemu-switches]

    Example 2:
    - Test the effect of running 0 - n VM's on hyperScale
        - 20 samples of CPU/memory every k vm where k*m=n
        - Calculate median and standard error
*/


class experiment : public QObject
{
    Q_OBJECT
    microManager* manager;

    int samplesToCollect;
    int samplesCollected;

    int bootBatchSize;
    int sampleInterval;

    QDateTime startTime;
    QDateTime stopTime;

    float maxCpu;
    float maxMem;

protected:
    std::string description;
    perfdata::perfsampler* sampler;

    //virtual endCondition;
public:
    explicit experiment(microManager* _manager,QObject *parent = 0);
    std::string experimentInfo();
    void start();

signals:
    void experimentComplete();

public slots:
    void samplingDone();
    void bootingDone();

};

#endif // EXPERIMENT_H
