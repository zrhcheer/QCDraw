#ifndef ROUND_AND_QUARDRANGLE_H
#define ROUND_AND_QUARDRANGLE_H

#include <QWidget>
#include <QTimer>
#include "CdData.h"

using namespace std;

class RoundAndQuardrangle : public QWidget
{
    Q_OBJECT
public:
    explicit RoundAndQuardrangle(QWidget *parent = 0);


    void SetTimeInterval(int iInterval);

    //void Clear();

    void setCdData(const CdData& stuData);
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
public slots:
    void timerEvent();

private:
    CdData m_stuData;

    int m_iCurrentPointIndex;
    CdPoint m_pointMouse;
public:
    QTimer m_timer;
};

#endif // ROUND_AND_QUARDRANGLE_H
