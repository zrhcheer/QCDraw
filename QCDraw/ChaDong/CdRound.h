#ifndef CDROUND_H
#define CDROUND_H
#include "CdPoint.h"
#include "CdRect.h"

class CdRound
{
public:
    CdPoint m_pointCenter;
    double m_dRadius;
    bool _isDot;//是否是虚线
    CdRound();
    CdRound(CdPoint pointCenter, double dRadius,bool isDot = false);
    CdRound(const CdRound & cdRound);
    CdRound & operator = (const CdRound & cdRound);
    bool operator == (const CdRound & cdRound) const;
    //点是否在圆内，判定依据是点到圆心的距离是否小于半径，点在圆上也为true
    bool IsPointInRound(const CdPoint & cdPoint) const;
    CdRect GetBoundRect() const;//取得边界矩形
};

#endif // CDROUND_H
