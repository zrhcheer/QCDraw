#include "CdPoint.h"
#include <math.h>
#include "CdDataCalculateTool.h"
#include <sstream>

CdPoint::CdPoint()
    : m_dX(0)
    , m_dY(0)
{
}

CdPoint::CdPoint(double dX, double dY)
{
    m_dX = dX;
    m_dY = dY;
}

CdPoint::CdPoint(const CdPoint & cdPoint)
{
    m_dX = cdPoint.m_dX;
    m_dY = cdPoint.m_dY;
}

CdPoint & CdPoint::operator = (const CdPoint &cdPoint)
{
    m_dX = cdPoint.m_dX;
    m_dY = cdPoint.m_dY;
    return *this;
}

bool CdPoint::operator == (const CdPoint &cdPoint) const
{
    bool bRet = false;
    if(0 == CdDataCalculateTool::DoubleCompare(m_dX , cdPoint.m_dX)
            && 0 == CdDataCalculateTool::DoubleCompare(m_dY , cdPoint.m_dY))
        bRet = true;
    return bRet;
}

double CdPoint::GetDistanceTo(const CdPoint &cdPoint) const
{
    double dDistance = 0;
    dDistance = sqrt(pow(m_dX - cdPoint.m_dX, 2) + pow(m_dY - cdPoint.m_dY, 2));
    return dDistance;
}

std::string CdPoint::ToString()
{
    std::string strRet;
    std::stringstream streamTmp;
    streamTmp<<"m_dX:";
    streamTmp<<m_dX<<",";
    streamTmp<<"m_dY:";
    streamTmp<<m_dY;
    streamTmp>>strRet;
    return strRet;
}
