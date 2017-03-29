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
    //ȡ����Ӿ���
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
 *�㷨������
 *���㷨��������͹�����
 *�㷨�ǽ����ڡ�͹����ε���Ӿ������ĵ�һ��λ��͹������ڲ����ļ�������ϣ���δ������ѧ֤����
 *�㷨�Զ���ε���Ӿ������ĵ�Ϊ��������ĵ㣬�������θ�����ֱ�������ĵ㹹�ɵ������ε��������Ϊ�ı��ε����
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
 *�㷨������
 *���㷨δ����ѧ��֤�����ܻ᲻�ʺ�һЩ���
 *�㷨���������������õ������θ����㹹�ɵ�����������Ͳ����ڶ�������������ڶ������,������ڶ������
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
