#include "CdRound.h"
#include "CdDataCalculateTool.h"

CdRound::CdRound()
    : m_pointCenter(0, 0)
    , m_dRadius(0)
{
    _isDot = false;
}

CdRound::CdRound(CdPoint pointCenter, double dRadius,bool isDot)
{
    m_pointCenter = pointCenter;
    m_dRadius = dRadius;
    _isDot = isDot;
}

CdRound::CdRound(const CdRound &cdRound)
{
    m_pointCenter = cdRound.m_pointCenter;
    m_dRadius = cdRound.m_dRadius;
    _isDot = cdRound._isDot;
}

CdRound &CdRound::operator = (const CdRound &cdRound)
{
    m_pointCenter = cdRound.m_pointCenter;
    m_dRadius = cdRound.m_dRadius;
    _isDot = cdRound._isDot;
    return *this;
}

bool CdRound::operator ==(const CdRound &cdRound) const
{
    bool bRet = false;
    if(m_pointCenter == cdRound.m_pointCenter
            && 0 == CdDataCalculateTool::DoubleCompare(m_dRadius , cdRound.m_dRadius))
        bRet = true;
    return bRet;
}

bool CdRound::IsPointInRound(const CdPoint &cdPoint) const
{
    bool bRet = false;
    if(0 > CdDataCalculateTool::DoubleCompare(m_pointCenter.GetDistanceTo(cdPoint) , m_dRadius))
        bRet = true;
    return bRet;
}

CdRect CdRound::GetBoundRect() const
{
    //取得外接矩形
    double maxX = m_pointCenter.m_dX + m_dRadius;
    double minX = m_pointCenter.m_dX - m_dRadius;
    double maxY = m_pointCenter.m_dY + m_dRadius;
    double minY = m_pointCenter.m_dY - m_dRadius;
    return CdRect(maxY, minX, minY, maxX);
}
