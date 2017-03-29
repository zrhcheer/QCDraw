#ifndef CDQUARDRANGLE_H
#define CDQUARDRANGLE_H

#include "CdPoint.h"
#include "CdRect.h"

class CdQuardrangle
{
public:
    CdPoint m_arrayPoint[4];
    CdQuardrangle();
    CdQuardrangle(const CdPoint & point1, const CdPoint & point2,
                  const CdPoint & point3, const CdPoint & point4);
    CdQuardrangle(const CdQuardrangle & cdQuardrangle);
    CdQuardrangle & operator = (const CdQuardrangle & cdQuardrangle);
    bool operator == (const CdQuardrangle & cdQuardrangle)const;
    //点是否在四边形内，采用面积法进行判定，本函数调用后四边形会被organized，点在四边形边上也视为内
    bool IsPointInQuardrangle(const CdPoint & cdPoint);
    //四边形的四个点中是否有这个点
    bool HasPoint(const CdPoint & cdPoint)const;
    //整理四边形，使得按点顺序绘制即可绘制出四边形,返回是否成功，如果失败则表示四个点不能构成四边形
    bool Organize();
    CdRect GetBoundRect() const;//取得边界矩形
private:
    //使用海伦公式求三角形面积
    double GetTriangleArea(const CdPoint & pointA, const CdPoint & pointB, const CdPoint & pointC) const;
};

#endif // CDQUARDRANGLE_H
