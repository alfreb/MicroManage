#ifndef QPROCESSMANAGER_SIMPLE_H
#define QPROCESSMANAGER_SIMPLE_H

#include "QVector"
#include "QProcess"

class qprocessManager_simple
{
    QVector<QProcess*> vms;

public:
    qprocessManager_simple(QObject *parent);
    ~qprocessManager_simple();
};

#endif // QPROCESSMANAGER_SIMPLE_H
