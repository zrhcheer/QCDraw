#include "CdLine.h"

CdLine::CdLine()
    : m_pointA(0, 0)
    , m_pointB(0, 0)
    , m_type(0)
{
}

CdLine::CdLine(const CdPoint &pointA, const CdPoint &pointB, const int &type)
{
    m_pointA = pointA;
    m_pointB = pointB;
    m_type = type;
}

CdLine::CdLine(double dXA, double dYA, double dXB, double dYB, int type)
{
    m_pointA.m_dX = dXA;
    m_pointA.m_dY = dYA;
    m_pointB.m_dX = dXB;
    m_pointB.m_dY = dYB;
    m_type = type;
}

CdLine::CdLine(const CdLine &cdLine)
{
    m_pointA = cdLine.m_pointA;
    m_pointB = cdLine.m_pointB;
    m_type = cdLine.m_type;
}

CdLine &CdLine::operator =(const CdLine &cdLine)
{
    m_pointA = cdLine.m_pointA;
    m_pointB = cdLine.m_pointB;
    m_type = cdLine.m_type;
    return *this;
}

bool CdLine::operator ==(const CdLine &cdLine) const
{
    bool bRet = false;
    if(m_pointA == cdLine.m_pointA && m_pointB == cdLine.m_pointB)
        bRet = true;
    return bRet;
}

bool CdLine::IsCrossedWith(const CdLine &cdLine) const
{
    bool bRet = false;
    //叉积判定线段相交的算法原理参见"http://www.cnblogs.com/zhangchaoyang/articles/2668562.html"
    //本函数仅采纳了交叉部分，三点共线部分在本算法中不采纳，三点共线视为不相交
    double dCrsPdct1 = GetCrossProduct(cdLine.m_pointA, cdLine.m_pointB, m_pointA);
    double dCrsPdct2 = GetCrossProduct(cdLine.m_pointA, cdLine.m_pointB, m_pointB);
    double dCrsPdct3 = GetCrossProduct(m_pointA, m_pointB, cdLine.m_pointA);
    double dCrsPdct4 = GetCrossProduct(m_pointA, m_pointB, cdLine.m_pointB);
    if(dCrsPdct1 * dCrsPdct2 < 0 && dCrsPdct3 * dCrsPdct4 < 0)
        bRet = true;
    return bRet;
}

CdPoint CdLine::GetPercentPoint(int iPercent, bool bBeginFromA) const
{
    CdPoint pointRet;
    if(iPercent > 100)
        iPercent = 100;
    if(iPercent < 0)
        iPercent = 0;
    if(!bBeginFromA)
        iPercent = 100 - iPercent;
    //求出线的角度(弧度单位)
    double dAngle = atan2((m_pointB.m_dY - m_pointA.m_dY), (m_pointB.m_dX - m_pointA.m_dX));
    double dPercentLength = m_pointA.GetDistanceTo(m_pointB) * iPercent / 100;
    //XY方向的差值
    double dXOffset = dPercentLength * cos(dAngle);
    double dYOffset = dPercentLength * sin(dAngle);
    pointRet.m_dX = m_pointA.m_dX + dXOffset;
    pointRet.m_dY = m_pointA.m_dY + dYOffset;
    return pointRet;
}

double CdLine::GetCrossProduct(const CdPoint &pointO, const CdPoint &pointA, const CdPoint &pointB) const
{
    double dCrossProduct = 0;
    //计算出相对于点O的两个向量
    CdPoint pointTempOA(pointA.m_dX - pointO.m_dX, pointA.m_dY - pointO.m_dY);
    CdPoint pointTempOB(pointB.m_dX - pointO.m_dX, pointB.m_dY - pointO.m_dY);
    dCrossProduct = pointTempOA.m_dX * pointTempOB.m_dY - pointTempOA.m_dY * pointTempOB.m_dX;
    return dCrossProduct;
}
