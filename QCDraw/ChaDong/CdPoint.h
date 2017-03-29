#ifndef CDPOINT_H
#define CDPOINT_H
#include <string>

class CdPoint
{
public:
    double m_dX;
    double m_dY;
    CdPoint();
    CdPoint(double dX, double dY);
    CdPoint(const CdPoint & cdPoint);
    CdPoint & operator = (const CdPoint &cdPoint);
    bool operator == (const CdPoint & cdPoint) const;
    //ȡ�õ�ǰ�㵽������ľ���
    double GetDistanceTo(const CdPoint & cdPoint) const;
    std::string ToString();
};

#endif // CDPOINT_H
