#ifndef TIMEVAL_H
#define TIMEVAL_H
#include <sys/time.h>

class TimeVal
{
public:
    TimeVal();
    bool operator<(const TimeVal& other) const;

    void getCurrentTime();
    long  msecsTo(const TimeVal& other) const;
    TimeVal addMSecs(const long& msec) const;
private:
    struct timeval _timer;
};

#endif // TIMEVAL_H
