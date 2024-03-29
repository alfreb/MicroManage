#ifndef MICROMANAGER_H
#define MICROMANAGER_H

#include <QObject>
#include <vector>
#include <qemuvm_qprocess.h>


namespace perfdata{
  class perfsampler;
}

//Might be circular
#include "../perfdata/perfSampler.h"


class microManager : public QObject
{
    Q_OBJECT

    QTime t;
    
    //System, CPU related
    int totalCPUCores;
    //Cores available for VM's to freely move to
    std::vector<int> freeCores;
    //Cores restricting VM's by default
    std::vector<int> lockedCores;
    
    //PerfSampler, for out-of-experiment resource sampling
    perfdata::perfsampler* sampler;
    
    //VM containter
    std::vector<qemuVm_qprocess*> vms;
    int vmsBooted;
    int pctBooted;
    int progStep;

    //For QoS sampling
    int samplesOrdered;
    int sum_sampleTimes;

    //int vmsResponded;
    std::vector<qemuVm_qprocess*> vmsRequested;


public:
    explicit microManager(QObject *parent = 0);
    ~microManager();

    //VM Control
    void boot_n(int n);
    void shutdown_n(int n);
    void timedRequest(qemuVm_qprocess* vm, std::string req,std::vector<int>* onCores=0);

    //Getters
    int getVmsBooted();


    /*
        Terminal UI menu items (Move to View class)
    */
    void menu_boot_n();
    void menu_shutdown_n();
    void menu_main(int vmCount);
    void menu_vmInteraction();
    void menu_time_n_random_requests(bool withCpuReassign=0);
    void menu_restrict_to_cores();
    void menu_run_scaling_profile_experiment();        
    void menu_perfsampler();

signals:
    //void allStarted();
    //void bootConfirmedAll(); //Connect to user prompt
    void n_confirmed_boot();
    void menuItemComplete();
    void exit();

public slots:
    //Custom slots for menuItems completing
    void complete_menu_boot_n();
    void complete_menu_perfsampler();
     void userPrompt();
     void bootConfirmed(qemuVm_qprocess*); //One VM confirmed boot
     void timedRequestHandled(qemuVm_qprocess*, int);
     //void bootConfirmedAll();
     //void init();

};

#endif // MICROMANAGER_H
