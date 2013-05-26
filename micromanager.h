#ifndef MICROMANAGER_H
#define MICROMANAGER_H

#include <QObject>
#include <vector>
#include <qemuvm.h>

class microManager : public QObject
{
    Q_OBJECT

    QTime t;
    std::vector<qemuVm*> vms;
    int vmsBooted;
    int pctBooted;
    int progStep;


public:
    explicit microManager(QObject *parent = 0);
    ~microManager();

    void bootN(int n);
    void menu_bootMore();
    //void bootAll();

    /*
        Terminal UI menu items (Move to View class)
    */
    void menu_main(int vmCount);
    void menu_vmInteraction();
    void menu_time_n_random_requests();


signals:
    void allStarted();
    void bootConfirmedAll(); //Connect to user prompt
    void exit();

public slots:
     void userPrompt();
     void bootConfirmed(qemuVm *p); //One VM confirmed boot
     //void bootConfirmedAll();
     //void init();

};

#endif // MICROMANAGER_H
