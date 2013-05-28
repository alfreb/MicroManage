#ifndef QEMUVM_H
#define QEMUVM_H

#include "micromachine.h"
#include "QProcess"

class qemuVm_qprocess : public microMachine
{
    Q_OBJECT

    QProcess proc;
    static QString command;
    static QStringList args;

    /*A Timer to time requests.
        - Should only be created when needed
        - Should be destroyed when not in use
     */
    QTime* timer;

    //The first character output by VM after boot
    const char boot_char;

public:
    qemuVm_qprocess(QObject *parent = 0);
    ~qemuVm_qprocess();

    virtual void boot();
    virtual void halt();    
    virtual void assignToCores(std::vector<int> &cores);
    virtual QString readAll();
    virtual void write(std::string s);
    virtual void processRequest(std::string req);
    virtual void processRequest_timed(std::string req);

    //Halt, and delete self when process is stopped
    void halt_controlled();

signals:
    void bootConfirmed(qemuVm_qprocess*);
    void timedRequestHandled(qemuVm_qprocess*, int);

public slots:
  void firstByteRecieved();
  void timedRequestDone();

};

#endif // QEMUVM_H
