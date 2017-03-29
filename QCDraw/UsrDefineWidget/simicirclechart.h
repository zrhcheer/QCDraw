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
    //���õ�ǰ��ʾ�ٷֱ�
    void setPercent(const int& percent);
private:
    int draw(QPainter* painter);
    //���õ�ǰͼ��m_cX,m_cY,m_cW,m_cH;
    int setCords(double x, double y, double w, double h);
    //���±���ͼ
    void  updateCurrent();

    double m_curPercent;//��ǰ��ʾ�İٷֱ�

    QColor _startClr;//��ʼ��ɫ
    QColor _endClr;//������ɫ

    QString m_strTitle;//����ͼ��ʾ������
    double m_cX,m_cY,m_cW,m_cH;
};

#endif // SIMICIRCLECHART_H
