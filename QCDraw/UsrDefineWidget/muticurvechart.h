#ifndef MUTICURVECHART_H
#define MUTICURVECHART_H

#include <QFrame>
#include <QMap>
struct  MutiCurveDataInfo
{
    QString name;//名字
    QVector<QPointF> pointList;//用于存储点
    QColor chartColor; //曲线顔色
    bool bYOutRanger;//Y超出是否打出
};

class MutiCurveChart : public QFrame
{
public:

     explicit MutiCurveChart(QWidget *parent = 0);
    ~MutiCurveChart();
    //设置cX,cY,cW,cH
    int setCords(double x, double y, double w, double h);

    //该函数是将map中的第一个元素颜色设置上，画线时也是读取第一条线的颜色，所以当map为空时，该函数无效
    void SetLineColor(QString strLineName, QColor color);

    virtual void paintEvent(QPaintEvent *);
    //增加折线
    int addCurve(const QString& strName,const QColor clr,
                 const QVector<QPointF>& curveData);
    //设置折线的值
    void SetCurveData(const QString& name,const QVector<QPointF>& curveData);
    //清空所画所有折线
    void clearCurve();
    //设置m_xMin,m_xMax;
    void setXAxis(double min,double max);
    //设置m_yMin,m_yMax;
    void setYAxis(double min,double max);
private:
    double cX,cY,cW,cH,pW;
    //cW,cH分别为柱状图内条纹的宽度和高度
    //cX,cY分别是Y轴的顶端距离原点的距离

    QString m_strXTitle;//X轴代表的事物
    QString m_strYTitle;//Y轴代表的事物
    QString m_strTitle;//折线图表示的事物
    double m_xMin,m_xMax;
    double m_yMin,m_yMax;


    QFont font;//字体

    int draw(QPainter *painter);
    int drawLegend(QPainter *painter);

    //-------------------------------add by Mengqb------------------------------------------
    QMap<QString,MutiCurveDataInfo> polyData; //用于画多条曲线
    //------------------------------------------------------------------------

signals:

public slots:

};
#endif // MUTICURVECHART_H
