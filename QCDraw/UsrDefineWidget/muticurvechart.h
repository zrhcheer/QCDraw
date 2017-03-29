#ifndef MUTICURVECHART_H
#define MUTICURVECHART_H

#include <QFrame>
#include <QMap>
struct  MutiCurveDataInfo
{
    QString name;//����
    QVector<QPointF> pointList;//���ڴ洢��
    QColor chartColor; //�����ɫ
    bool bYOutRanger;//Y�����Ƿ���
};

class MutiCurveChart : public QFrame
{
public:

     explicit MutiCurveChart(QWidget *parent = 0);
    ~MutiCurveChart();
    //����cX,cY,cW,cH
    int setCords(double x, double y, double w, double h);

    //�ú����ǽ�map�еĵ�һ��Ԫ����ɫ�����ϣ�����ʱҲ�Ƕ�ȡ��һ���ߵ���ɫ�����Ե�mapΪ��ʱ���ú�����Ч
    void SetLineColor(QString strLineName, QColor color);

    virtual void paintEvent(QPaintEvent *);
    //��������
    int addCurve(const QString& strName,const QColor clr,
                 const QVector<QPointF>& curveData);
    //�������ߵ�ֵ
    void SetCurveData(const QString& name,const QVector<QPointF>& curveData);
    //���������������
    void clearCurve();
    //����m_xMin,m_xMax;
    void setXAxis(double min,double max);
    //����m_yMin,m_yMax;
    void setYAxis(double min,double max);
private:
    double cX,cY,cW,cH,pW;
    //cW,cH�ֱ�Ϊ��״ͼ�����ƵĿ�Ⱥ͸߶�
    //cX,cY�ֱ���Y��Ķ��˾���ԭ��ľ���

    QString m_strXTitle;//X����������
    QString m_strYTitle;//Y����������
    QString m_strTitle;//����ͼ��ʾ������
    double m_xMin,m_xMax;
    double m_yMin,m_yMax;


    QFont font;//����

    int draw(QPainter *painter);
    int drawLegend(QPainter *painter);

    //-------------------------------add by Mengqb------------------------------------------
    QMap<QString,MutiCurveDataInfo> polyData; //���ڻ���������
    //------------------------------------------------------------------------

signals:

public slots:

};
#endif // MUTICURVECHART_H
