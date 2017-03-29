#include "cdpolygon.h"
#include <map>
#include <math.h>
#include "CdDataCalculateTool.h"
#include <iostream>
using namespace std;

CdPolygon::CdPolygon()
{
}

CdRect CdPolygon::GetBoundRect() const
{
    //取得外接矩形
    double maxX = -99999;
    double minX = 99999;
    double maxY = -99999;
    double minY = 99999;
    for(vector<CdPoint>::const_iterator it = m_vecPoint.begin(); it != m_vecPoint.end(); it++)
    {
        if(maxX < it->m_dX)
            maxX = it->m_dX;
        if(minX > it->m_dX)
            minX = it->m_dX;
        if(maxY < it->m_dY)
            maxY = it->m_dY;
        if(minY > it->m_dY)
            minY = it->m_dY;
    }
    return CdRect(maxY, minX, minY, maxX);
}

/*
 *算法描述：
 *本算法仅适用于凸多边形
 *算法是建立在“凸多边形的外接矩形中心点一定位于凸多边形内部”的假设基础上（暂未经过数学证明）
 *算法以多边形的外接矩形中心点为多边形中心点，求出多边形各顶点分别与此中心点构成的三角形的面积和作为四边形的面积
*/
double CdPolygon::GetArea() const
{
    double dRetArea = 0;
    CdPoint pointCenter = GetBoundRect().GetCenter();
    for(uint i = 0; i < m_vecPoint.size(); i++)
    {
        dRetArea += GetTriangleArea(pointCenter, m_vecPoint[i], m_vecPoint[(i + 1) % m_vecPoint.size()]);
    }
    return dRetArea;
}

/*
 *算法描述：
 *本算法未经数学验证，可能会不适和一些情况
 *算法采用面积法，如果该点与多边形各顶点构成的三角形面积和不等于多边形面积，则点在多边形外,相等则在多边形内
*/
bool CdPolygon::IsPointInPolygon(const CdPoint &cdPoint) const
{
    bool bRet = false;
    double dCalArea = 0;
    int iCount = m_vecPoint.size();
    for(int i = 0; i < iCount; i++)
    {
        dCalArea += GetTriangleArea(cdPoint, m_vecPoint[i], m_vecPoint[(i + 1) % iCount]);
    }
    if(CdDataCalculateTool::DoubleCompare(dCalArea, GetArea()) == 0)
        bRet = true;
    return bRet;
}

double CdPolygon::GetTriangleArea(const CdPoint &pointA, const CdPoint &pointB, const CdPoint &pointC) const
{
    double dRet = 0;
    double dLenthAB = pointA.GetDistanceTo(pointB);
    double dLenthAC = pointA.GetDistanceTo(pointC);
    double dLenthBC = pointB.GetDistanceTo(pointC);
    double dP = (dLenthAB + dLenthAC + dLenthBC) / 2;
    dRet = sqrt(dP * (dP - dLenthAB) * (dP - dLenthAC) * (dP - dLenthBC));
    return dRet;
}
