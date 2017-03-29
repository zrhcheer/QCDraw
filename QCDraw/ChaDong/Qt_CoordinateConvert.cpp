#include "Qt_CoordinateConvert.h"
#include "CdDataCalculateTool.h"

Qt_CoordinateConvert::Qt_CoordinateConvert()
{
    m_dRadio = 0.25;
}

void Qt_CoordinateConvert::SetBigSizeData(const CdRect &stuRectAreaBound, const CdRect &stuRectPointBound, CdCoordinate &stuCoordinate)
{
    m_stuRectAreaBound = stuRectAreaBound;
    m_stuRectPointBound = stuRectPointBound;
    double dRadio = m_dRadio;
    double dMaxWidth = stuCoordinate.Width() * m_dRadio;
    dRadio = dMaxWidth / m_stuRectAreaBound.Width();
    CdRect rectBigAreaTemp;
    CdRect rectBigArea;
    rectBigAreaTemp.m_dBottom = stuRectAreaBound.m_dBottom * dRadio;
    rectBigAreaTemp.m_dLeft = stuRectAreaBound.m_dLeft * dRadio;
    rectBigAreaTemp.m_dRight = stuRectAreaBound.m_dRight * dRadio;
    rectBigAreaTemp.m_dTop = stuRectAreaBound.m_dTop * dRadio;
    //如果扩大后的矩形与点集相交，则按照最低的与点集不相交的大小进行并求出新的横纵比例，取较小的
    if(rectBigAreaTemp.HasIntersectionWith(m_stuRectPointBound))
    {
        //新的纵横比例
        double dXRadio = 0;
        double dYRadio = 0;
        //X方向
        if(m_stuRectPointBound.m_dLeft > rectBigAreaTemp.m_dLeft && m_stuRectPointBound.m_dLeft < rectBigAreaTemp.m_dRight)
        {
            rectBigAreaTemp.m_dRight = m_stuRectPointBound.m_dLeft;
            dXRadio = rectBigAreaTemp.m_dRight / stuRectAreaBound.m_dRight;
        }
        else if(m_stuRectPointBound.m_dRight > rectBigAreaTemp.m_dLeft && m_stuRectPointBound.m_dRight < rectBigAreaTemp.m_dRight)
        {
            rectBigAreaTemp.m_dLeft = m_stuRectPointBound.m_dRight;
            dXRadio = rectBigAreaTemp.m_dLeft / stuRectAreaBound.m_dLeft;
        }
        //Y方向
        if(m_stuRectPointBound.m_dTop > rectBigAreaTemp.m_dBottom && m_stuRectPointBound.m_dTop < rectBigAreaTemp.m_dTop)
        {
            rectBigAreaTemp.m_dBottom = m_stuRectPointBound.m_dTop;
            dYRadio = rectBigAreaTemp.m_dBottom / stuRectAreaBound.m_dBottom;
        }
        else if(m_stuRectPointBound.m_dBottom > rectBigAreaTemp.m_dBottom && m_stuRectPointBound.m_dBottom < rectBigAreaTemp.m_dTop)
        {
            rectBigAreaTemp.m_dTop = m_stuRectPointBound.m_dBottom;
            dYRadio = rectBigAreaTemp.m_dTop / stuRectAreaBound.m_dTop;
        }
        dRadio = dXRadio < dYRadio ? dXRadio : dYRadio;
        rectBigAreaTemp.m_dBottom = stuRectAreaBound.m_dBottom * dRadio;
        rectBigAreaTemp.m_dLeft = stuRectAreaBound.m_dLeft * dRadio;
        rectBigAreaTemp.m_dRight = stuRectAreaBound.m_dRight * dRadio;
        rectBigAreaTemp.m_dTop = stuRectAreaBound.m_dTop * dRadio;
    }
    rectBigArea = rectBigAreaTemp;
    //针对扩缩后的矩形再次进行坐标系的扩张并针对新坐标系进行自适应
    if(m_stuCoordinate.m_dBottom > rectBigAreaTemp.m_dBottom * G_EnvironmentalVaraible::m_dCoordDataRatio)
        m_stuCoordinate.m_dBottom = rectBigAreaTemp.m_dBottom * G_EnvironmentalVaraible::m_dCoordDataRatio;
    if(m_stuCoordinate.m_dLeft > rectBigAreaTemp.m_dLeft * G_EnvironmentalVaraible::m_dCoordDataRatio)
        m_stuCoordinate.m_dLeft = rectBigAreaTemp.m_dLeft * G_EnvironmentalVaraible::m_dCoordDataRatio;
    if(m_stuCoordinate.m_dTop < rectBigAreaTemp.m_dTop * G_EnvironmentalVaraible::m_dCoordDataRatio)
        m_stuCoordinate.m_dTop = rectBigAreaTemp.m_dTop * G_EnvironmentalVaraible::m_dCoordDataRatio;
    if(m_stuCoordinate.m_dRight < rectBigAreaTemp.m_dRight * G_EnvironmentalVaraible::m_dCoordDataRatio)
        m_stuCoordinate.m_dRight = rectBigAreaTemp.m_dRight * G_EnvironmentalVaraible::m_dCoordDataRatio;
    stuCoordinate = m_stuCoordinate;
    SetData(m_stuCoordinate, m_stuRectPaintArea);
    //保存下新的圆及四边形区域，及扩缩比率
    m_stuRectBigSizeAreaBound = rectBigArea;
    m_dRadio = dRadio;
}

void Qt_CoordinateConvert::SetData(const CdCoordinate &stuCoordinate, const CdRect &stuRectPaintArea)
{
    m_stuCoordinate = stuCoordinate;
    m_stuRectPaintArea = stuRectPaintArea;
    //在构造函数中来计算合适的比例尺
    //比例尺大小应该取宽度比例与高度比例中较小的一个，以保证不管从高度还是宽度上，坐标系都能被容纳在绘制区内
    double dWidUnit = stuRectPaintArea.Width() / stuCoordinate.Width();
    double dHeiUnit = stuRectPaintArea.Height() / stuCoordinate.Height();
    m_dUnit = CdDataCalculateTool::DoubleCompare(dWidUnit , dHeiUnit) > 0 ? dHeiUnit : dWidUnit;
    m_stuRectCoordArea.m_dBottom = m_stuCoordinate.m_dBottom * m_dUnit;
    m_stuRectCoordArea.m_dLeft = m_stuCoordinate.m_dLeft * m_dUnit;
    m_stuRectCoordArea.m_dRight = m_stuCoordinate.m_dRight * m_dUnit;
    m_stuRectCoordArea.m_dTop = m_stuCoordinate.m_dTop * m_dUnit;
    m_dVerOffset = (m_stuRectPaintArea.Height() - m_stuRectCoordArea.Height()) / 2;
    m_dHorOffset = (m_stuRectPaintArea.Width() - m_stuRectCoordArea.Width()) / 2;
}

CdPoint Qt_CoordinateConvert::MapPointFromLogicToSys(const CdPoint &pointTarget,bool bSeeStu) const
{
    CdPoint pointResult;
    CdPoint pointTargetTmp = pointTarget;
    if((m_stuRectAreaBound.IsPointInRect(pointTargetTmp) || bSeeStu) && m_dRadio > 1)
    {
        pointTargetTmp.m_dX = pointTarget.m_dX * m_dRadio;
        pointTargetTmp.m_dY = pointTarget.m_dY * m_dRadio;
    }
    pointResult.m_dX = (pointTargetTmp.m_dX - m_stuCoordinate.m_dLeft) * m_dUnit
            + m_dHorOffset + m_stuRectPaintArea.m_dLeft;
    pointResult.m_dY = (m_stuCoordinate.m_dTop - pointTargetTmp.m_dY) * m_dUnit
            + m_dVerOffset + m_stuRectPaintArea.m_dTop;
    return pointResult;
}

CdPoint Qt_CoordinateConvert::MapPointFromSysToLogic(const CdPoint &pointTarget) const
{
    CdPoint pointResult;
    if(m_stuCoordinate.Width() != 0 || m_stuCoordinate.Height() != 0)
    {
        pointResult.m_dX = (pointTarget.m_dX - m_dHorOffset - m_stuRectPaintArea.m_dLeft) / m_dUnit + m_stuCoordinate.m_dLeft;
        pointResult.m_dY = m_stuCoordinate.m_dTop - (pointTarget.m_dY - m_dVerOffset - m_stuRectPaintArea.m_dTop) / m_dUnit;
        if(m_stuRectBigSizeAreaBound.IsPointInRect(pointResult) && m_dRadio > 1)
        {
            pointResult.m_dX /= m_dRadio;
            pointResult.m_dY /= m_dRadio;
        }
    }
    return pointResult;
}

double Qt_CoordinateConvert::MapLenthFromSysToLogic(double dLength)
{
    return dLength / (m_dUnit == 0 ? 1 : m_dUnit);
}

void Qt_CoordinateConvert::ResetBigSizeParam()
{
    //图形边界矩形
    m_stuRectAreaBound = CdRect();
    //图形外部的潮流点边界矩形
    m_stuRectPointBound = CdRect();
    //图形扩张后的边界矩形，由图形本身的边界矩形及潮流点的边界矩形确定出扩张后的边界矩形，确定规则为高度尽可能占据坐标系整体高度的radio倍
    m_stuRectBigSizeAreaBound = CdRect();
    //扩缩系数，初始化为0.25，尽量贴近默认值，如果默认值与潮流点有冲突，则进行一定的缩小
    m_dRadio = 0.25;
}
