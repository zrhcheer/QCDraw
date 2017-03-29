#ifndef CDRECT_H
#define CDRECT_H
#include "CdPoint.h"
#include <string>

class CdRect
{
public:
    double m_dTop;
    double m_dLeft;
    double m_dBottom;
    double m_dRight;
    CdRect();
    CdRect(double dTop, double dLeft, double dBottom, double dRight);
    CdRect(CdPoint pointLeftTop, CdPoint pointRightBottom);
    CdRect(const CdRect & cdRect);
    CdRect & operator = (const CdRect & cdRect);
    bool HasIntersectionWith(const CdRect & cdRect) const;//�ж����������Ƿ��н��������ຬ���ཻ
    bool IsPointInRect(const CdPoint & point) const;
    bool operator == (const CdRect & cdRect);
    double Width() const;
    double Height() const;
    std::string ToString();
    CdPoint GetCenter();
    CdRect &UnionRect(const CdRect & cdRect);//����ǰ����ʹ���ܹ�������������
    void Scale(double dScale);
    void adjustScale(double dScale);
};

#endif // CDRECT_H
