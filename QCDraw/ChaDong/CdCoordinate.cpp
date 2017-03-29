#include "CdCoordinate.h"
#include "CdDataCalculateTool.h"
#include <sstream>

CdCoordinate::CdCoordinate()
    : m_dTop(0)
    , m_dLeft(0)
    , m_dBottom(0)
    , m_dRight(0)
{
}

CdCoordinate::CdCoordinate(double dTop, double dLeft, double dBottom, double dRight)
{
    m_dTop = dTop;
    m_dLeft = dLeft;
    m_dBottom = dBottom;
    m_dRight = dRight;
}

CdCoordinate::CdCoordinate(const CdCoordinate &cdCoordinate)
{
    m_dTop = cdCoordinate.m_dTop;
    m_dLeft = cdCoordinate.m_dLeft;
    m_dBottom = cdCoordinate.m_dBottom;
    m_dRight = cdCoordinate.m_dRight;
}

CdCoordinate &CdCoordinate::operator = (const CdCoordinate &cdCoordinate)
{
    m_dTop = cdCoordinate.m_dTop;
    m_dLeft = cdCoordinate.m_dLeft;
    m_dBottom = cdCoordinate.m_dBottom;
    m_dRight = cdCoordinate.m_dRight;
    return *this;
}

bool CdCoordinate::operator == (const CdCoordinate &cdCoordinate)
{
    bool bRet = false;
    if(0 == CdDataCalculateTool::DoubleCompare(m_dTop , cdCoordinate.m_dTop)
            && 0 == CdDataCalculateTool::DoubleCompare(m_dLeft , cdCoordinate.m_dLeft)
            && 0 == CdDataCalculateTool::DoubleCompare(m_dBottom , cdCoordinate.m_dBottom)
            && 0 == CdDataCalculateTool::DoubleCompare(m_dRight , cdCoordinate.m_dRight))
        bRet = true;
    return bRet;
}

double CdCoordinate::Width() const
{
    double dRet = 0;
    dRet = CdDataCalculateTool::DoubleAbsolute(m_dRight - m_dLeft);
    return dRet;
}

double CdCoordinate::Height() const
{
    double dRet = 0;
    dRet = CdDataCalculateTool::DoubleAbsolute(m_dTop - m_dBottom);
    return dRet;
}

std::string CdCoordinate::ToString()
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
