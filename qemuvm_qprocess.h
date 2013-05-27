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
    QTime* t;

    //The first character output by VM after boot
    const char boot_char;

public:
    qemuVm_qprocess(QObject *parent = 0);
    ~qemuVm_qprocess();

    virtual void boot();
    virtual void halt();
    virtual QString readAll();
    virtual void write(const char* s);
    virtual void processRequest(const char* req);
    virtual void processRequest_timed(const char* req,QTime& t);

signals:
    void bootConfirmed(qemuVm_qprocess*);
    void requestHandled(QByteArray*);

public slots:
  void firstByteRecieved();
  void timedRequestReady();

};

#endif // QEMUVM_H
