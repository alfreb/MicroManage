#ifndef QEMUVM_H
#define QEMUVM_H

#include "micromachine.h"
#include "QProcess"

class qemuVm : public microMachine
{
    QProcess proc;
    static QString command;
    static QStringList args;

public:
    qemuVm();
    ~qemuVm();

    virtual void boot();
    virtual void halt();
    virtual QString readAll();
    virtual void write(const char* s);
    virtual response processRequest(const char* req);
    virtual response processRequest_timed(const char* req,QTime& t);

};

#endif // QEMUVM_H
