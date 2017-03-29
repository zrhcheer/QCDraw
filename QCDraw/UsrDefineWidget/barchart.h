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
    //��������
    void setName(QString name);
    //������ɫ
    void setColor(Qt::GlobalColor, Qt::GlobalColor colorJ);
    void setColor(QColor color, QColor colorJ);
    //���ðٷֱ�
    void setPerc(float Percentage);

    QString pname;//����
    QColor rgbColor;//��ɫ
    QColor rgbColorJ;//��ɫ
    float pPerc;//�ٷֱ�

private:

};
class BarChart : public QFrame
{
public:

    explicit BarChart(QWidget *parent = 0);
    ~BarChart();
    //����״ͼ�����Բ��
    int addPiece(const QString& name,  Qt::GlobalColor, Qt::GlobalColor colorJ, float Percentage);
    int addPiece(const QString& name,  QColor, QColor colorJ, float Percentage);
    //����Բ����ֵ
    bool setPieceValue(const QString& name,  float Percentage);
    //����cX,cY,cW,cH
    int setCords(double x, double y, double w, double h);
    //�����״ͼ������
    void AllClear();
    //������״ͼ��ʾ������
    void setMyTitle(const QString& strTitle);
    //����Y��ĳ���
    void setYAxis(double dbY);
protected:
    //��ͼ�¼�
    virtual void paintEvent(QPaintEvent *);

private:
    double cX,cY,cW,cH;//cW,cH�ֱ�Ϊ��״ͼ�����ƵĿ�Ⱥ͸߶�
                                  //cX,cY�ֱ���Y��Ķ��˾���ԭ��ľ���
    //bool shadows;
    QMap<QString,PieceNC> pieces;

    //QPainter *cpainter;
    int draw(QPainter *painter);
    int drawLegend(QPainter *painter);

    QString m_strTitle;//��״ͼ��ʾ������
    double m_yAxis;//Y��ĳ���

signals:

public slots:

};
#endif // BARCHART_H
