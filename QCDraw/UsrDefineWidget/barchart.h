#ifndef BARCHART_H
#define BARCHART_H

#define PerConst = 3.6;
#include <QPainter>
#include <QMap>
#include <QDebug>
#include <math.h>
#include <QFrame>

class PieceNC
{
public:
    explicit PieceNC();
    //设置名字
    void setName(QString name);
    //设置颜色
    void setColor(Qt::GlobalColor, Qt::GlobalColor colorJ);
    void setColor(QColor color, QColor colorJ);
    //设置百分比
    void setPerc(float Percentage);

    QString pname;//名字
    QColor rgbColor;//颜色
    QColor rgbColorJ;//颜色
    float pPerc;//百分比

private:

};
class BarChart : public QFrame
{
public:

    explicit BarChart(QWidget *parent = 0);
    ~BarChart();
    //在柱状图中添加圆柱
    int addPiece(const QString& name,  Qt::GlobalColor, Qt::GlobalColor colorJ, float Percentage);
    int addPiece(const QString& name,  QColor, QColor colorJ, float Percentage);
    //设置圆柱的值
    bool setPieceValue(const QString& name,  float Percentage);
    //设置cX,cY,cW,cH
    int setCords(double x, double y, double w, double h);
    //清空柱状图的内容
    void AllClear();
    //设置柱状图表示的事物
    void setMyTitle(const QString& strTitle);
    //设置Y轴的长度
    void setYAxis(double dbY);
protected:
    //画图事件
    virtual void paintEvent(QPaintEvent *);

private:
    double cX,cY,cW,cH;//cW,cH分别为柱状图内条纹的宽度和高度
                                  //cX,cY分别是Y轴的顶端距离原点的距离
    //bool shadows;
    QMap<QString,PieceNC> pieces;

    //QPainter *cpainter;
    int draw(QPainter *painter);
    int drawLegend(QPainter *painter);

    QString m_strTitle;//柱状图表示的事物
    double m_yAxis;//Y轴的长度

signals:

public slots:

};
#endif // BARCHART_H
