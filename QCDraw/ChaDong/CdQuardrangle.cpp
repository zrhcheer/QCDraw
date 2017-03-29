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
     //�������˼���ǵ�ǰ��ֱ����ı��ε��ĸ��㹹�ɵ��ĸ������ε�������Ƿ�����ı������
     //�����㷨ǰ���뱣֤�ı�����organized
     if(Organize())
     {
         //�ٶ����ж���ΪO���ı���ΪABCD
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
    //organize���㷨˼���ǣ��ж�0��2��1��3����ɵ������߶��Ƿ��ཻ������ཻ˵���Ѿ���organized��������ȡ�������
    //���ʼ���޷��õ������ཻ���߶Σ�����ı��ε��ĸ��㱾���޷�����͹�ı���
    //a.�ж����״̬
    CdLine lineTempA(m_arrayPoint[0], m_arrayPoint[2], 0);
    CdLine lineTempB(m_arrayPoint[1], m_arrayPoint[3], 0);
    if(lineTempA.IsCrossedWith(lineTempB))
    {
        bRet = true;
    }
    //�����̬���У�������ж���������λ��
    if(!bRet)
    {
        CdLine lineTempA(m_arrayPoint[0], m_arrayPoint[1], 0);
        CdLine lineTempB(m_arrayPoint[2], m_arrayPoint[3], 0);
        if(lineTempA.IsCrossedWith(lineTempB))
        {
            bRet = true;
            //������1��2���ɵõ���׼�ı���
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
            //������1��2���ɵõ���׼�ı���
            CdPoint pointTemp = m_arrayPoint[2];
            m_arrayPoint[2] = m_arrayPoint[3];
            m_arrayPoint[3] = pointTemp;
        }
    }
    return bRet;
}

CdRect CdQuardrangle::GetBoundRect() const
{
    //ȡ����Ӿ���
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
