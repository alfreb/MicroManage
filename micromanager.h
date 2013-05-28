#ifndef MICROMANAGER_H
#define MICROMANAGER_H

#include <QObject>
#include <vector>
#include <qemuvm_qprocess.h>

class microManager : public QObject
{
    Q_OBJECT

    QTime t;
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

    void boot_n(int n);
    void shutdown_n(int n);
    void timedRequest(qemuVm_qprocess* vm, std::string req);

    /*
        Terminal UI menu items (Move to View class)
    */
    void menu_boot_n();
    void menu_shutdown_n();
    void menu_main(int vmCount);
    void menu_vmInteraction();
    void menu_time_n_random_requests();
    void menu_restrict_to_cores();

signals:
    void allStarted();
    void bootConfirmedAll(); //Connect to user prompt
    void menuItemComplete();
    void exit();

public slots:
     void userPrompt();
     void bootConfirmed(qemuVm_qprocess*); //One VM confirmed boot
     void timedRequestHandled(qemuVm_qprocess*, int);
     //void bootConfirmedAll();
     //void init();

};

#endif // MICROMANAGER_H
