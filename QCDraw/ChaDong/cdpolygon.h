#ifndef CDPOLYGON_H
#define CDPOLYGON_H
#include "CdPoint.h"
#include "CdRect.h"
#include <vector>
#include <stdlib.h>

using namespace std;

class CdPolygon
{
public:
    CdPolygon();
    vector<CdPoint> m_vecPoint;
    CdRect GetBoundRect() const;//ȡ�ñ߽����
    double GetArea() const;//ȡ�õ�ǰ��������
    //���Ƿ��ڶ�����ڣ���������������ж���������δ����ѧ��֤�����ܽ������ھ������͹����Σ����ڶ������Ҳ��Ϊ��
    bool IsPointInPolygon(const CdPoint & cdPoint) const;
private:
    //ʹ�ú��׹�ʽ�����������
    double GetTriangleArea(const CdPoint & pointA, const CdPoint & pointB, const CdPoint & pointC) const;
};

#endif // CDPOLYGON_H
