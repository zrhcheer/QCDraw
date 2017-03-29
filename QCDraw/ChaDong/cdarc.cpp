#include "cdarc.h"

CdArc::CdArc()
{
}
CdRect CdArc::GetBoundRect() const
{
    //取得外接矩形
    double maxX = -99999;
    double minX = 99999;
    double maxY = -99999;
    double minY = 99999;

    //算起始点
    float tmpAngle = m_startAngle * M_PI / 180; //换算弧度
    CdPoint tmpPt;
    tmpPt.m_dX = m_ptCenter.m_dX + m_radius * cos(tmpAngle);
    tmpPt.m_dY = m_ptCenter.m_dY + m_radius * sin(tmpAngle);
    if(tmpPt.m_dX >  maxX)
    {
        maxX = tmpPt.m_dX;
    }
    if(tmpPt.m_dX < minX)
    {
        minX = tmpPt.m_dX;
    }
    if(tmpPt.m_dY >  maxY)
    {
        maxY = tmpPt.m_dY;
    }
    if(tmpPt.m_dY < minY)
    {
        minY = tmpPt.m_dY;
    }

    //结束点
    tmpAngle = (m_startAngle + m_spanAngle) * M_PI / 180; //换算弧度
    tmpPt.m_dX = m_ptCenter.m_dX + m_radius * cos(tmpAngle);
    tmpPt.m_dY = m_ptCenter.m_dY + m_radius * sin(tmpAngle);
    if(tmpPt.m_dX >  maxX)
    {
        maxX = tmpPt.m_dX;
    }
    if(tmpPt.m_dX < minX)
    {
        minX = tmpPt.m_dX;
    }
    if(tmpPt.m_dY >  maxY)
    {
        maxY = tmpPt.m_dY;
    }
    if(tmpPt.m_dY < minY)
    {
        minY = tmpPt.m_dY;
    }

    //算中间点
    int start = m_startAngle;
    int end = m_startAngle + m_spanAngle;

    int remStart = 0;
    if(start < 0)
    {
        remStart = -((-start) / 90 * 90);
    }
    else
    {
        remStart = (start / 90) * 90 + 90;
    }
    for(;remStart < end;remStart += 90)
    {
        tmpAngle = remStart * M_PI / 180; //换算弧度
        tmpPt.m_dX = m_ptCenter.m_dX + m_radius * cos(tmpAngle);
        tmpPt.m_dY = m_ptCenter.m_dY + m_radius * sin(tmpAngle);
        if(tmpPt.m_dX >  maxX)
        {
            maxX = tmpPt.m_dX;
        }
        if(tmpPt.m_dX < minX)
        {
            minX = tmpPt.m_dX;
        }
        if(tmpPt.m_dY >  maxY)
        {
            maxY = tmpPt.m_dY;
        }
        if(tmpPt.m_dY < minY)
        {
            minY = tmpPt.m_dY;
        }
    }
     return CdRect(maxY, minX, minY, maxX);
}
