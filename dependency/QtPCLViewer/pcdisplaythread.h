#ifndef PCDISPLAYTHREAD_H
#define PCDISPLAYTHREAD_H

#include <QObject>
#include <QThread>
#include <Any.h>

class PCDisplayThread : public QThread
{
public:
    PCDisplayThread();
    void setCloud(Any data);

    // QThread interface
protected:
    void run();
private:
    Any data;
};

#endif // PCDISPLAYTHREAD_H
