#ifndef QT_PAINTER_H
#define QT_PAINTER_H
#include <QPainter>
#include <map>

#include "CdLine.h"
#include "Qt_CoordinateConvert.h"
#include "cdpolygon.h"
#include "CdDataCalculateTool.h"
#include "cdarc.h"
#include "CdRound.h"
#include "CdQuardrangle.h"


class Qt_Painter : private QPainter
{
private:
    Qt_CoordinateConvert * m_pConvert;
public:
    Qt_Painter(QPaintDevice * device, Qt_CoordinateConvert * pConvert);
    //绘制网格线
    void DrawSubLine(int iInterval);
    //绘制坐标系
    void DrawCoordinate(const CdCoordinate & coordinate,bool bDrawTxt=true,const string & strXCoordText = "", const string & strYCoordText = "");

    //绘制弧
    void DrawCdArc(const CdArc &arc);
    //绘制圆
    void DrawCdRound(const CdRound & round);
    //绘制四边形,注意，四边形将发生变化，被标准化
    void DrawQuardrangle(CdQuardrangle & quardrangle);
    //绘制点折线
    void DrawPointLine(const vector<CdPoint> & vecPoint, unsigned int iIndex, const CdData * pData=NULL);
    //绘制系统坐标文字
    void DrawCoordTextBySysPoint(const CdPoint & point, const QString &strPointName = "", bool bNeedPoint = false, QColor color = Qt::black);
    //绘制逻辑坐标文字
    void DrawCoordTextByLogicPoint(const CdPoint & point, const QString &strPointName, bool bNeedPoint = false, QColor color = Qt::black);
    //绘制边框及背景
    void DrawBackGround();
    //绘制辅助线，如果是两条线，则认为是圆，第一条需要带箭头，否则认为是四边形，全部不带箭头
    void DrawAssisLine(const vector<CdLine> & vecAssisLine);
    //绘制多边形（按照多边形点的原有顺序进行绘制）
    void DrawCdPolygon(const CdPolygon &cdPolygon);
    //绘制变压器差动保护的线
    void DrawVecLines(const vector<CdLine> & vecLines);
    //绘制辅助文字，参数为一个已string为key，坐标点CdPoint为value的map
    void DrawAssisText(const map<string, CdPoint> & vecAssisText);
    //绘制SB点
    void DrawAddedPoint(const vector<CdPoint> & vecSBPoint,bool bDrawText);
    //绘制SB线
    void DrawAddedLine(const vector<CdLine> & vecSBLine);
    //母线差动绘制
    void DrawMuXianChaDongQuXian(const vector<CdPoint> & vecChaDongPoint);
    //线路差动绘制
    void DrawXianLuChaDongQuXian(const vector<CdPoint> & vecChaDongPoint);
private:
    //画带箭头的坐标轴线，有横向和纵向两种
    void DrawCoordLine(const CdPoint & pointStart, const CdPoint & pointEnd,
                       bool bIsHor = true, int iArrowLength = 6, const string &strMark = "");
    //绘制一个三角形，顶点为三角形的顶点，size为三角形的高，X角度为高与X轴正向的角度(0~360)，tri角度为三角形的高与边的夹角(0~360)，pen颜色为边颜色，brush颜色为填充色
    void DrawTriangle(CdPoint pointVertex, double dSize, double dAngleX, double dAngleTri = 45, QColor penColor = Qt::black, QColor brushColor = Qt::black);
    //保留小数点后n位
    QString PrecNumber(QString strNum, int i = 2);
    QLineF GetPercentLine(const QLineF & qline, int iPercent, bool bBeginFromA = true) const;
    QPointF GetQPoint(const CdPoint &point);
public:
    //做成属性更合适，此处直接做成public
    QColor m_colorSubLine;//网格线颜色
    QColor m_colorCoordnate;//坐标系颜色
    QColor m_colorRound;//圆颜色
    QColor m_colorArc;//弧颜色
    QColor m_colorQuardrangle;//四边形颜色
    QColor m_colorPoint;//遥信遥测点颜色
    QColor m_colorPointLine;//点折线颜色
    QColor m_colorTranFillVecLine;//变压器折线填充颜色
    QColor m_colorTranVecLine;//变压器折线颜色
    QColor m_colorBackGround;//背景色
    QColor m_colorPointLineText;//点折线点坐标文字颜色

    unsigned char bCurrentColorStyle;
};

#endif // QT_PAINTER_H
