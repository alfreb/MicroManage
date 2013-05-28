#ifndef QPROCESSMANAGER_SIMPLE_H
#define QPROCESSMANAGER_SIMPLE_H

#include "QVector"
#include "QProcess"

class qprocessManager_simple //: public QObject
{
  //  Q_OBJECT

    QVector<QProcess*> vms;

public:
    explicit qprocessManager_simple(QObject *parent=0);
    ~qprocessManager_simple();
};

#endif // QPROCESSMANAGER_SIMPLE_H
