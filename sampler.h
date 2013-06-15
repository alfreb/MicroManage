#ifndef SAMPLER_H
#define SAMPLER_H

#include <QObject>

/*
 *
 * Collect timed samples
 *
 *  - CPU performance data
 *  - Memory
 *  - Response times
 *
 * Calculate
 *  - mean while sampling
 *  - standard deviation after sampling
 *
 * Output
 *  - to various formats (?)
 *  - To file
 *
 */

//template <class TYPE>
class sampler : public QObject
{
    Q_OBJECT

  //  vector< TYPE > samples;


public:
    explicit sampler(QObject *parent = 0);
    void start();


signals:    
    void samplingComplete();

public slots:
    void collectSample();
    
};

#endif // SAMPLER_H
