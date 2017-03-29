#ifndef QT_COORDINATECONVERT_H
#define QT_COORDINATECONVERT_H
#include "CdCoordinate.h"
#include "CdRect.h"
#include "G_EnvironmentalVaraible.h"

class Qt_CoordinateConvert
{
public:
    //绘制区域的信息，由控件绘制区减去边框留白区得到，它同时也是逻辑坐标系在系统坐标系中的大小
    CdRect m_stuRectPaintArea;
    //逻辑坐标系的信息，由数据的分布上限决定
    CdCoordinate m_stuCoordinate;
    //实际绘制大小，即经过比例尺转换后的坐标系实际大小，用于坐标系的居中计算
    CdRect m_stuRectCoordArea;
private:
    //比例尺，逻辑区单位长度与绘制区单位长度的比值
    double m_dUnit;
    //竖直方向上的为了保证居中而采用的偏移量
    double m_dVerOffset;
    //水平方向上的为了保证居中而采用的偏移量
    double m_dHorOffset;
    //下边四个是供圆及四边形的扩大使用的
    //图形边界矩形
    CdRect m_stuRectAreaBound;
    //图形外部的潮流点边界矩形
    CdRect m_stuRectPointBound;
    //图形扩张后的边界矩形，由图形本身的边界矩形及潮流点的边界矩形确定出扩张后的边界矩形，确定规则为高度尽可能占据坐标系整体高度的radio倍
    CdRect m_stuRectBigSizeAreaBound;
    //扩缩系数，初始化为0.25，尽量贴近默认值，如果默认值与潮流点有冲突，则进行一定的缩小
    double m_dRadio;
public:
    Qt_CoordinateConvert();
    //计算扩大坐标系
    void SetBigSizeData(const CdRect & stuRectAreaBound, const CdRect & stuRectPointBound, CdCoordinate &stuCoordinate);
    //计算自适应坐标系
    void SetData(const CdCoordinate & stuCoordinate, const CdRect & stuRectPaintArea);
    //将逻辑坐标点映射为设备坐标点
    CdPoint MapPointFromLogicToSys(const CdPoint & pointTarget,bool bSeeStu = false) const;
    //将设备坐标点映射为逻辑坐标点
    CdPoint MapPointFromSysToLogic(const CdPoint & pointTarget) const;
    //按照比例尺换算长度单位（本函数不考虑区域缩放）
    double MapLenthFromSysToLogic(double dLength);
    //扩缩系数等归位
    void ResetBigSizeParam();
};

#endif // QT_COORDINATECONVERT_H
