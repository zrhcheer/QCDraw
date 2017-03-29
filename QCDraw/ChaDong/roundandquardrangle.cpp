#include "roundandquardrangle.h"
#include <QMouseEvent>

#include "Qt_Painter.h"
#include "DataAdaptor.h"

RoundAndQuardrangle::RoundAndQuardrangle(QWidget *parent) :
    QWidget(parent),m_stuData(this->width(),this->height())
{

    m_iCurrentPointIndex = -1;
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
    m_timer.start(10 * 10 * 5);//刷新时间间隔，以毫秒为单位
    m_pointMouse.m_dX = -40;
    m_pointMouse.m_dY = -40;
    setMouseTracking(true);
}

void RoundAndQuardrangle::setCdData(const CdData& stuData)
{
    m_stuData = stuData;
    //m_stuData.calcArea(this->size());
    m_iCurrentPointIndex = -1;
    update();
}


void RoundAndQuardrangle::paintEvent(QPaintEvent *)
{
//    LOG_INFO("paintEvent begin:");
//    LOG_INFO("m_stuData.m_stuCoordinate:%s,Height:%d,Width:%d",
//             m_stuData.m_stuCoordinate.ToString().c_str(),
//             height(),width());

    Qt_Painter painter(this, &m_stuData.getStuConvert());
    m_stuData.drawEntity(painter,this->size(),m_iCurrentPointIndex,m_pointMouse);
}

void RoundAndQuardrangle::mouseMoveEvent(QMouseEvent *event)
{
    m_pointMouse.m_dX = event->x();
    m_pointMouse.m_dY = event->y();
    //鼠标滑动时触发刷新
    //repaint();
}

void RoundAndQuardrangle::enterEvent(QEvent *)
{
    setCursor(Qt::CrossCursor);
}

void RoundAndQuardrangle::leaveEvent(QEvent *)
{
    m_pointMouse.m_dX = -40;
    m_pointMouse.m_dY = -40;
}

void RoundAndQuardrangle::SetTimeInterval(int iInterval)
{
    m_timer.setInterval(iInterval);
}


void RoundAndQuardrangle::timerEvent()
{
    m_iCurrentPointIndex += m_timer.interval() / 10;
    if(m_iCurrentPointIndex > INT_MAX - 100)
        m_iCurrentPointIndex = 0;
    repaint();
}
