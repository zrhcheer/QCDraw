#ifndef SIMICIRCLECHART_H
#define SIMICIRCLECHART_H

#include <QFrame>
#include <QPainter>
#include <QColor>

struct tagSectorConf
{
    tagSectorConf(){}
    tagSectorConf(const QColor& c,const int& v)
    {
        clr = c;
        val = v;
    }

    QColor clr;
    unsigned int  val;
};

class SimiCircleChart : public QFrame
{
    Q_OBJECT
public:
    explicit SimiCircleChart(QWidget *parent = 0);
    ~SimiCircleChart();
protected:
    virtual void paintEvent(QPaintEvent *);
signals:
    
public slots:
    //void setChartData(const QVector<tagSectorConf>& vecSectorConf);
    //void setAnglePointerPos(const int angle);
    //设置当前显示百分比
    void setPercent(const int& percent);
private:
    int draw(QPainter* painter);
    //设置当前图的m_cX,m_cY,m_cW,m_cH;
    int setCords(double x, double y, double w, double h);
    //更新饼型图
    void  updateCurrent();

    double m_curPercent;//当前显示的百分比

    QColor _startClr;//开始颜色
    QColor _endClr;//结束颜色

    QString m_strTitle;//饼型图表示的事物
    double m_cX,m_cY,m_cW,m_cH;
};

#endif // SIMICIRCLECHART_H
