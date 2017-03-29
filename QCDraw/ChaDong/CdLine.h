#ifndef CDLINE_H
#define CDLINE_H

#include "CdPoint.h"
#include "math.h"

class CdLine
{
public:
    CdPoint m_pointA;
    CdPoint m_pointB;
    int m_type;
    CdLine();
    CdLine(const CdPoint & pointA, const CdPoint & pointB, const int & type);
    CdLine(double dXA, double dYA, double dXB, double dYB, int type);
    CdLine(const CdLine & cdLine);
    CdLine & operator = (const CdLine & cdLine);
    bool operator == (const CdLine & cdLine) const;
    //判定两条线段是否交叉，当一条线段的端点在另一条线段上时，本函数认为不交叉
    bool IsCrossedWith(const CdLine & cdLine) const;
    CdPoint GetPercentPoint(int iPercent, bool bBeginFromA = true) const;
private:
    //计算线OA与OB的叉积，参数分别是点O、A、B
    double GetCrossProduct(const CdPoint & pointO, const CdPoint & pointA, const CdPoint & pointB) const;
};

#endif // CDLINE_H
