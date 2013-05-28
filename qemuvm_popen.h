#ifndef QEMUVM_POPEN_H
#define QEMUVM_POPEN_H

#include "micromachine.h"
#include "stdio.h"

class qemuVm_popen : public microMachine
{
    Q_OBJECT

    FILE* proc;

    char* command;

    //The first character output by VM after boot
    const char boot_char;

public:
    explicit qemuVm_popen(QObject* parent=0);
    ~qemuVm_popen();

    virtual void boot();
    virtual void halt();
    virtual QString readAll();
    virtual void write(const char* s);
    virtual void processRequest(const char* req);
    virtual void processRequest_timed(const char* req,QTime& t);

signals:
    void bootConfirmed(qemuVm_popen*);

public slots:
  void firstByteRecieved();


};

#endif // QEMUVM_POPEN_H
