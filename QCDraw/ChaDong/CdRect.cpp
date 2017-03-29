#include "CdRect.h"
#include "CdDataCalculateTool.h"
#include <sstream>

CdRect::CdRect()
{
    m_dTop = 0;
    m_dLeft = 0;
    m_dBottom = 0;
    m_dRight = 0;
}
CdRect::CdRect(double dTop, double dLeft, double dBottom, double dRight)
{
    m_dTop = dTop;
    m_dLeft = dLeft;
    m_dBottom = dBottom;
    m_dRight = dRight;
}
CdRect::CdRect(CdPoint pointLeftTop, CdPoint pointRightBottom)
{
    m_dTop = pointLeftTop.m_dY;
    m_dLeft = pointLeftTop.m_dX;
    m_dBottom = pointRightBottom.m_dY;
    m_dRight = pointRightBottom.m_dX;
}
CdRect::CdRect(const CdRect & cdRect)
{
    m_dTop = cdRect.m_dTop;
    m_dLeft = cdRect.m_dLeft;
    m_dBottom = cdRect.m_dBottom;
    m_dRight = cdRect.m_dRight;
}
CdRect & CdRect::operator = (const CdRect & cdRect)
{
    m_dTop = cdRect.m_dTop;
    m_dLeft = cdRect.m_dLeft;
    m_dBottom = cdRect.m_dBottom;
    m_dRight = cdRect.m_dRight;
    return *this;
}

bool CdRect::HasIntersectionWith(const CdRect &cdRect) const
{
    bool bRet = false;
    //先判定X方向
    if((m_dLeft > cdRect.m_dLeft && m_dLeft < cdRect.m_dRight)
            || (m_dRight > cdRect.m_dLeft && m_dRight < cdRect.m_dRight))
    {
        //再判定Y方向
        if((m_dTop > cdRect.m_dBottom && m_dTop < cdRect.m_dTop)
                || (m_dBottom > cdRect.m_dBottom && m_dBottom < cdRect.m_dTop))
        {
            bRet = true;
        }
    }
    return bRet;
}

bool CdRect::IsPointInRect(const CdPoint &point) const
{
    bool bRet = false;
    if(point.m_dX >= m_dLeft
            && point.m_dX <= m_dRight
            && point.m_dY >= m_dBottom
            && point.m_dY <= m_dTop)
        bRet = true;
    return bRet;
}

bool CdRect::operator == (const CdRect & cdRect)
{
    bool bRet = false;
    if(0 == CdDataCalculateTool::DoubleCompare(m_dTop, cdRect.m_dTop)
            && 0 == CdDataCalculateTool::DoubleCompare(m_dTop, cdRect.m_dTop)
            && 0 == CdDataCalculateTool::DoubleCompare(m_dTop, cdRect.m_dTop)
            && 0 == CdDataCalculateTool::DoubleCompare(m_dTop, cdRect.m_dTop))
        bRet = true;
    return bRet;
}

double CdRect::Width() const
{
    double dRet = 0;
    dRet = CdDataCalculateTool::DoubleAbsolute(m_dRight - m_dLeft);
    return dRet;
}

double CdRect::Height() const
{
    double dRet = 0;
    dRet = CdDataCalculateTool::DoubleAbsolute(m_dTop - m_dBottom);
    return dRet;
}


std::string CdRect::ToString()
{
    std::string strRet;
    std::stringstream streamTmp;
    streamTmp<<"Top:";
    streamTmp<<m_dTop<<",";
    streamTmp<<"Left:";
    streamTmp<<m_dLeft<<",";
    streamTmp<<"Bottom:";
    streamTmp<<m_dBottom<<",";
    streamTmp<<"Right:";
    streamTmp<<m_dRight;
    streamTmp>>strRet;
    return strRet;
}


CdPoint CdRect::GetCenter()
{
    return CdPoint(m_dLeft + Width() / 2, m_dBottom + Height() / 2);
}

CdRect & CdRect::UnionRect(const CdRect &cdRect)
{
    m_dLeft = m_dLeft < cdRect.m_dLeft ? m_dLeft : cdRect.m_dLeft;
    m_dRight = m_dRight > cdRect.m_dRight ? m_dRight : cdRect.m_dRight;
    m_dBottom = m_dBottom < cdRect.m_dBottom ? m_dBottom : cdRect.m_dBottom;
    m_dTop = m_dTop > cdRect.m_dTop ? m_dTop : cdRect.m_dTop;
    return *this;
}

void CdRect::adjustScale(double dScale)
{
    if(m_dLeft > 0)
    {
        m_dLeft = m_dLeft - m_dLeft * (dScale - 1);
    }
    else
    {
        m_dLeft *= dScale;
    }
    if(m_dRight > 0)
    {
        m_dRight *= dScale;
    }
    else
    {
        m_dRight = m_dRight - m_dRight * (dScale - 1);
    }
    if(m_dBottom > 0)
    {
        m_dBottom = m_dBottom - m_dBottom * (dScale - 1);
    }
    else
    {
        m_dBottom *= dScale;
    }
    if(m_dTop > 0)
    {
        m_dTop *= dScale;
    }
    else
    {
        m_dTop = m_dTop - m_dTop*(dScale - 1);
    }
}

void CdRect::Scale(double dScale)
{
    m_dLeft *= dScale;
    m_dRight *= dScale;
    m_dBottom *= dScale;
    m_dTop *= dScale;
}
