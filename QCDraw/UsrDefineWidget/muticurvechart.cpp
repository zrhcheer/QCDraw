#include "muticurvechart.h"
//#include <qgraphicsscene>


#include <QPainter>
#include <QPainterPath>
using namespace std;
#define THRESHOLD 0.6

MutiCurveChart::MutiCurveChart(QWidget *parent )//QPainter *painter)
    :QFrame(parent)

{
    font.setFamily("verdana");
    font.setPixelSize(15);
    //painter = painter;
    //painter->setFont(font);
    cX = 0;
    cY = 0;
    cW = 100;
    cH = 100;

    m_strXTitle = "";
    m_strYTitle = "";
    m_strTitle = "历史合格率统计曲线";
    m_xMin = 0;
    m_xMax = 50;
    m_yMin = 0;
    m_yMax = 100;
}
MutiCurveChart::~MutiCurveChart()
{
}

int MutiCurveChart::setCords(double x, double y, double w, double h)
{
    this->cX = x;
    this->cY = y;
    this->cW = w;
    this->cH = h;
    return 0;
}
void MutiCurveChart::SetCurveData(const QString& name,
                                  const QVector<QPointF>& curveData)
{
    if(polyData.end() == polyData.find(name))
    {
        return;
    }
    polyData[name].pointList = curveData;
}

void MutiCurveChart::setXAxis(double min,double max)
{
    m_xMin = min;
    m_xMax = max;
}

void MutiCurveChart::setYAxis(double min,double max)
{
    m_yMin = min;
    m_yMax = max;
}

int MutiCurveChart::addCurve(const QString& strName,const QColor clr,
                             const QVector<QPointF>& curveData )
{
    MutiCurveDataInfo& resultDataInfo = polyData[strName];
    //int size = polyData.size();
    //polyData.append(resultDataInfo);
    resultDataInfo.name = strName;
    resultDataInfo.chartColor = clr;

    resultDataInfo.pointList = curveData;
    return 1;
}

int MutiCurveChart::draw(QPainter *painter)
{
    painter->save();
    //绘制边框及背景
    //    QBrush brush(QColor::fromRgb(0, 0, 0));
    QColor clrText = palette().text().color();
    QBrush brush(palette().background());


    painter->setBrush(brush);
    //QPen bkPen(brush.color());
    painter->setPen(brush.color());

    painter->drawRect(this->contentsRect().adjusted(1,1,-1,-1));
    //painter->drawRect(2, 2, this->width() - 4 , this->height()  -4);

    //画边框
    //绘边框
    /*painter->setPen(clrText);
    //painter->drawLine(0,0, this->width(),0);
    painter->drawLine(0,0, 0 ,this->height());
    painter->drawLine(0,this->height(), this->width(),this->height());*/

    //QPen dotPen(Qt::DashLine);
    //dotPen.setColor(clrText);
    //painter->setPen(dotPen);
    //painter->drawLine(this->width(),0 + 5,this->width(),this->height() - 5);

    //this->styleChange();
    painter->restore();

    //绘制内容
    painter->save();


    //绘制标题
    QColor clrBright = this->palette().brightText().color();
    //    painter->setPen(clrBright);
    //    painter->drawText(wBorder  + 3 ,wBorder +  painter->fontMetrics().height() ,m_strTitle);
    painter->restore();


    painter->save();
    painter->setPen(clrText);

    /* painter->drawRect(20,20,100,100);
    painter->setViewport(20,20,100,100);
    painter->drawRect(0,0,80,80);
    painter->setWindow(0,0,100,100);
    painter->drawRect(2,2,96,96);*/

    QMap<QString,MutiCurveDataInfo>::Iterator iterPoly = polyData.begin();
    for (;iterPoly != polyData.end(); iterPoly++)
    {
        MutiCurveDataInfo& tmpPoly = iterPoly.value();
        QPen polyPen;
        polyPen.setWidth(2);
        polyPen.setColor(tmpPoly.chartColor);
        painter->setPen(polyPen);
        if(tmpPoly.pointList.size() > 0)
        {
            //画线
            double myX,myY;
            double hold = (m_yMax - m_yMin)  * THRESHOLD;
            QPointF& tmpPoint = tmpPoly.pointList[0];
            if(tmpPoint.y() < m_xMin + hold)
            {
                myX  = (tmpPoint.x() - m_xMin) / (m_xMax - m_xMin) * cW + cX;
                myY = cY + cH - (tmpPoint.y() - m_yMin) / hold  * cH / 5;
            }
            else
            {
                myX  = (tmpPoint.x() - m_xMin) / (m_xMax - m_xMin) * cW + cX;
                myY = cY + cH - cH / 5 -
                        (tmpPoint.y() - m_yMin -  hold) / (m_yMax - hold) *  cH * 4 / 5;
            }
            QPainterPath path;
            path.moveTo(myX,myY);
            for(int j = 1; j < tmpPoly.pointList.size();j++)
            {

                QPointF& tmpPoint = tmpPoly.pointList[j];
                if(tmpPoint.y() < m_xMin + hold)
                {
                    myX  = (tmpPoint.x() - m_xMin) / (m_xMax - m_xMin) * cW + cX;
                    myY = cY + cH - (tmpPoint.y() - m_yMin) / hold  * cH / 5;
                }
                else
                {
                    myX  = (tmpPoint.x() - m_xMin) / (m_xMax - m_xMin) * cW + cX;
                    myY = cY + cH - cH / 5 -
                            (tmpPoint.y() - m_yMin -  hold) / (m_yMax - hold) *  cH * 4 / 5;
                }
                //myX  = (tmpPoly.pointList[j].x() - m_xMin) / (m_xMax - m_xMin) * cW + cX;
                //myY = cY + cH - (tmpPoly.pointList[j].y() - m_yMin) / (m_yMax - m_yMin) * cH;
                path.lineTo(myX ,myY);
            }
            painter->strokePath(path,polyPen);
        }
    }
    painter->restore();

    painter->save();
    QString strYLabel = QString::number(100);

    int realFontSize = (cX -6)  / strYLabel.size();
    QFont fontMark("宋体",realFontSize,QFont::Bold);
    painter->setFont(fontMark);
    painter->setPen(clrText);

    //画槓向
//    painter->drawText(cX-7 - painter->fontMetrics().width(strYLabel),
//                      cY + painter->fontMetrics().height() / 3,strYLabel);
    //painter->drawLine(cX,cY,cX-6,cY);

    //    for(int i = 1; i <= 10; i ++)
    //    {
    //        painter->drawLine(cX,cY + cH * i / 10,cX-3,cY+ cH * i / 10);

    //        if(0 == i % 2)
    //        {
    //            QString strYLabel = QString::number(m_yMax - (m_yMax - m_yMin) * i / 10);
    //            painter->drawText(cX-7 - painter->fontMetrics().width(strYLabel),
    //                              cY + cH * i / 10 + painter->fontMetrics().height() / 3,strYLabel);
    //        }
    //    }

    QFontMetrics fontMetrics(fontMark);
    int hFont = fontMetrics.height();

    int Count =100;
    for (int i=0;i<5;i++)
    {
        QString label = QString::number(Count);
        painter->drawLine(cX-3,cY+cH/10*i*2,cX,cY+cH/10*i*2);
        painter->drawText(cX-fontMetrics.width(label) - 5,cY + cH * i *2/ 10+ hFont / 3, label);
        Count = Count - 10;
    }

    //draw x_axix
    for(int i = 0; i < 24; i ++)
    {
        painter->drawLine(cX + cW * i / 24,cY + cH,
                          cX+ cW * i / 24,cY+ cH + 3);
        if(0 == i % 2)
        {
            QString strLab = QString::number(i);
            painter->drawText(cX + cW * i / 24 - painter->fontMetrics().width(strLab) / 2,
                              cY + cH + painter->fontMetrics().height() + 1,strLab);
        }
    }
    painter->drawLine(cX + cW ,cY + cH,
                      cX+ cW ,cY+ cH + 3);
    painter->drawText(cX + cW - painter->fontMetrics().width("24H") / 2,
                      cY + cH + painter->fontMetrics().height() + 1,"24H");


    painter->drawLine(cX,cY+cH,cX,cY - 5);
    painter->drawLine(cX,cY+cH,cX+cW + 5,cY+cH);

    painter->restore();
    return 0;
}

int MutiCurveChart::drawLegend(QPainter *painter)
{
    QColor clrText = palette().text().color();
    QPen pen(clrText);
    painter->save();
    painter->setPen(pen);
    int dist = 5;
    int x,y;
    y = cY + cH + dist + 5;
    x = cX;
    QMap<QString,MutiCurveDataInfo>::Iterator iterPoly = polyData.begin();
    for (;iterPoly != polyData.end(); iterPoly++)
    {
        MutiCurveDataInfo& tmpPoly = iterPoly.value();
        painter->setBrush(tmpPoly.chartColor);

        painter->setPen(tmpPoly.chartColor);
        painter->drawRect(x ,y + painter->fontMetrics().height() / 4 ,
                          painter->fontMetrics().height() / 2,painter->fontMetrics().height() /2 );
        painter->setPen(clrText);
        painter->drawText(x + dist + painter->fontMetrics().height()/ 2 ,
                          y+painter->fontMetrics().height()/2+dist,
                          tmpPoly.name );

        x += painter->fontMetrics().width(tmpPoly.name) + dist + painter->fontMetrics().height() / 2 + dist * 2;
    }
    painter->restore();
    return 0;
}
void MutiCurveChart::clearCurve()
{
    polyData.clear();
}

void MutiCurveChart::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    setCords(25, 10, width() - 45, height() - 45);
    draw(&painter);
    drawLegend(&painter);
}
