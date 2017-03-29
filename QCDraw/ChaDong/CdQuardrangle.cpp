#include "CdQuardrangle.h"
#include "CdLine.h"
#include <math.h>
#include "CdDataCalculateTool.h"

CdQuardrangle::CdQuardrangle()
{
    CdPoint pointTemp(0, 0);
    for(int i = 0; i < 4; i++)
        m_arrayPoint[i] = pointTemp;
}

CdQuardrangle::CdQuardrangle(const CdPoint & point1, const CdPoint & point2,
                             const CdPoint & point3, const CdPoint & point4)
{
    m_arrayPoint[0] = point1;
    m_arrayPoint[1] = point2;
    m_arrayPoint[2] = point3;
    m_arrayPoint[3] = point4;
}

CdQuardrangle::CdQuardrangle(const CdQuardrangle &cdQuardrangle)
{
    for(int i = 0; i < 4; i++)
    {
        m_arrayPoint[i] = cdQuardrangle.m_arrayPoint[i];
    }
}

CdQuardrangle &CdQuardrangle::operator =(const CdQuardrangle &cdQuardrangle)
{
    for(int i = 0; i < 4; i++)
    {
        m_arrayPoint[i] = cdQuardrangle.m_arrayPoint[i];
    }
    return *this;
}

bool CdQuardrangle::operator ==(const CdQuardrangle & cdQuardrangle) const
{
    bool bRet = true;
    for(int i = 0; i < 4; i++)
    {
        if(!HasPoint(cdQuardrangle.m_arrayPoint[i]))
        {
            bRet = false;
            break;
        }
    }
    return bRet;
}

bool CdQuardrangle::IsPointInQuardrangle(const CdPoint & cdPoint)
{
     bool bRet = false;
     //面积法的思想是当前点分别与四边形的四个点构成的四个三角形的面积和是否等于四边形面积
     //进行算法前必须保证四边形是organized
     if(Organize())
     {
         //假定待判定点为O，四边形为ABCD
         double dAreaOAB = GetTriangleArea(cdPoint, m_arrayPoint[0], m_arrayPoint[1]);
         double dAreaOBC = GetTriangleArea(cdPoint, m_arrayPoint[1], m_arrayPoint[2]);
         double dAreaOCD = GetTriangleArea(cdPoint, m_arrayPoint[2], m_arrayPoint[3]);
         double dAreaODA = GetTriangleArea(cdPoint, m_arrayPoint[3], m_arrayPoint[0]);
         double dAreaACB = GetTriangleArea(m_arrayPoint[0], m_arrayPoint[2], m_arrayPoint[1]);
         double dAreaACD = GetTriangleArea(m_arrayPoint[0], m_arrayPoint[2], m_arrayPoint[3]);

         if(0 == CdDataCalculateTool::DoubleCompare((dAreaOAB + dAreaOBC + dAreaOCD + dAreaODA) ,
                                               (dAreaACB + dAreaACD)))
             bRet = true;
     }

     return bRet;
}

bool CdQuardrangle::HasPoint(const CdPoint &cdPoint) const
{
    bool bRet = false;
    for(int i = 0; i < 4; i++)
    {
        if(cdPoint == m_arrayPoint[i])
        {
            bRet = true;
            break;
        }
    }
    return bRet;
}

bool CdQuardrangle::Organize()
{
    bool bRet = false;
    //organize的算法思想是，判定0，2及1，3点组成的两条线段是否相交，如果相交说明已经是organized，否则另取两点继续
    //如果始终无法得到两条相交的线段，则此四边形的四个点本身无法构成凸四边形
    //a.判定最初状态
    CdLine lineTempA(m_arrayPoint[0], m_arrayPoint[2], 0);
    CdLine lineTempB(m_arrayPoint[1], m_arrayPoint[3], 0);
    if(lineTempA.IsCrossedWith(lineTempB))
    {
        bRet = true;
    }
    //如果初态不行，则继续判定并调整点位置
    if(!bRet)
    {
        CdLine lineTempA(m_arrayPoint[0], m_arrayPoint[1], 0);
        CdLine lineTempB(m_arrayPoint[2], m_arrayPoint[3], 0);
        if(lineTempA.IsCrossedWith(lineTempB))
        {
            bRet = true;
            //交换点1和2即可得到标准四边形
            CdPoint pointTemp = m_arrayPoint[1];
            m_arrayPoint[1] = m_arrayPoint[2];
            m_arrayPoint[2] = pointTemp;
        }
    }
    if(!bRet)
    {
        CdLine lineTempA(m_arrayPoint[0], m_arrayPoint[3], 0);
        CdLine lineTempB(m_arrayPoint[1], m_arrayPoint[2], 0);
        if(lineTempA.IsCrossedWith(lineTempB))
        {
            bRet = true;
            //交换点1和2即可得到标准四边形
            CdPoint pointTemp = m_arrayPoint[2];
            m_arrayPoint[2] = m_arrayPoint[3];
            m_arrayPoint[3] = pointTemp;
        }
    }
    return bRet;
}

CdRect CdQuardrangle::GetBoundRect() const
{
    //取得外接矩形
    double maxX = -99999;
    double minX = 99999;
    double maxY = -99999;
    double minY = 99999;
    for(int i = 0; i < 4; i++)
    {
        if(maxX < m_arrayPoint[i].m_dX)
            maxX = m_arrayPoint[i].m_dX;
        if(minX > m_arrayPoint[i].m_dX)
            minX = m_arrayPoint[i].m_dX;
        if(maxY < m_arrayPoint[i].m_dY)
            maxY = m_arrayPoint[i].m_dY;
        if(minY > m_arrayPoint[i].m_dY)
            minY = m_arrayPoint[i].m_dY;
    }
    return CdRect(maxY, minX, minY, maxX);
}

double CdQuardrangle::GetTriangleArea(const CdPoint &pointA, const CdPoint &pointB, const CdPoint &pointC) const
{
    double dRet = 0;
    double dLenthAB = pointA.GetDistanceTo(pointB);
    double dLenthAC = pointA.GetDistanceTo(pointC);
    double dLenthBC = pointB.GetDistanceTo(pointC);
    double dP = (dLenthAB + dLenthAC + dLenthBC) / 2;
    dRet = sqrt(dP * (dP - dLenthAB) * (dP - dLenthAC) * (dP - dLenthBC));
    return dRet;
}
