#ifndef _HH_CDDATA_H
#define _HH_CDDATA_H
#include "CdCoordinate.h"
#include "CdPoint.h"
#include "CdQuardrangle.h"
#include "CdRound.h"
#include "CdLine.h"
#include "cdpolygon.h"
#include "cdarc.h"
#include <vector>
#include "CdRect.h"
#include <map>
#include <string>
#include "Qt_Painter.h"

using std::string;
using std::vector;
using std::map;

enum ShapeType
{
    TypeXianLuChaDong,
    TypeMuXianChaDong,
    TypeUnknown
};

class CdData
{
public:

    CdData();
    CdData(int width,int height);
    CdData(const CdData & cdData);
    CdData & operator = (const CdData & cdData);

    //
    //DataAdaptor m_stuDataAdaptor;
    Qt_CoordinateConvert m_stuQtConvert;
    int m_iBlank;
    void Clear(const QSize& sz);
    void Clear();

    void calcArea(const QSize& sz, bool bflag=false,bool bSetBig = true);
    void calcArea(bool bflag=false,bool bSetBig=true);

    void drawSmallEntity(Qt_Painter& painter,const QSize& sz);
    void drawEntity(Qt_Painter& painter,const QSize& sz,int iCurrentPointIndex,const CdPoint& pointMouse,bool bDrawText = true);
    Qt_CoordinateConvert& getStuConvert()
    {
        return m_stuQtConvert;
    }

    //
    CdCoordinate m_stuCoordinate;
    CdRound m_stuRound;
    CdQuardrangle m_stuQuardrangle;
    CdPolygon m_stuPolygon;

    vector<CdArc> m_vecArc;//弧特性图形列表
    vector<CdRound> m_vecRound;//圆特性图形列表
    vector<CdQuardrangle> m_vecQuardangle;//四边形特性图形列表
    vector<CdPolygon> m_vecPolygon;//多边形图形列表
    CdRect m_stuRectAreaBound;//用于内部扩缩坐标系的计算
    CdRect m_stuRectPointBound;//用于内部扩缩坐标系的计算
    vector<CdLine> m_vecAssisLine;//圆及四边形可能用到的辅助线
    vector<CdLine> m_vecTranLine;//变压器差动线集合
    vector<CdPoint> m_vecPoint;//潮流数据点折线用到的点
    vector<CdPoint> m_vecPointChaDong;//差动潮流数据点折线用到的点
    vector<CdPoint> m_vecTranPoint;//差动点集合
    map<string, CdPoint> m_mapAssisText;//辅助文字
    string m_strXCoordText;//横坐标轴显示文字
    string m_strYCoordText;//纵坐标轴显示文字
    vector<CdPoint> m_vecInvisiblePoint;//这个点其实是起到扩充坐标系的作用，参与坐标系比例计算但不会参与绘制
    ShapeType m_enuShapeType;
    vector<CdPoint> m_vecAddedPoint;//不知到干嘛用的点
    vector<CdLine> m_vecAddedLine;//辅助虚线

private:
    QSize _size;

};

#endif // _HH_CDDATA_H
