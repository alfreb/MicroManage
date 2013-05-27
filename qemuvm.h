#ifndef QEMUVM_H
#define QEMUVM_H

#include "micromachine.h"
#include "QProcess"

class qemuVm : public microMachine
{
    Q_OBJECT

    QProcess proc;
    static QString command;
    static QStringList args;

    //The first character output by VM after boot
    const char boot_char;

public:
    qemuVm();
    ~qemuVm();

    virtual void boot();
    virtual void halt();
    virtual QString readAll();
    virtual void write(const char* s);
    virtual response processRequest(const char* req);
    virtual response processRequest_timed(const char* req,QTime& t);

signals:
    void bootConfirmed(qemuVm*);

public slots:
  void firstByteRecieved();

};

#endif // QEMUVM_H
