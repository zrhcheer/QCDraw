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
    CdRect GetBoundRect() const;//取得边界矩形
    double GetArea() const;//取得当前多边形面积
    //点是否在多边形内，采用面积法进行判定，本函数未经数学论证，可能仅适用于绝大多数凸多边形，点在多边形上也视为内
    bool IsPointInPolygon(const CdPoint & cdPoint) const;
private:
    //使用海伦公式求三角形面积
    double GetTriangleArea(const CdPoint & pointA, const CdPoint & pointB, const CdPoint & pointC) const;
};

#endif // CDPOLYGON_H
