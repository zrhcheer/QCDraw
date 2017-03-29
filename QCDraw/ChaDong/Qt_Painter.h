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
    //����������
    void DrawSubLine(int iInterval);
    //��������ϵ
    void DrawCoordinate(const CdCoordinate & coordinate,bool bDrawTxt=true,const string & strXCoordText = "", const string & strYCoordText = "");

    //���ƻ�
    void DrawCdArc(const CdArc &arc);
    //����Բ
    void DrawCdRound(const CdRound & round);
    //�����ı���,ע�⣬�ı��ν������仯������׼��
    void DrawQuardrangle(CdQuardrangle & quardrangle);
    //���Ƶ�����
    void DrawPointLine(const vector<CdPoint> & vecPoint, unsigned int iIndex, const CdData * pData=NULL);
    //����ϵͳ��������
    void DrawCoordTextBySysPoint(const CdPoint & point, const QString &strPointName = "", bool bNeedPoint = false, QColor color = Qt::black);
    //�����߼���������
    void DrawCoordTextByLogicPoint(const CdPoint & point, const QString &strPointName, bool bNeedPoint = false, QColor color = Qt::black);
    //���Ʊ߿򼰱���
    void DrawBackGround();
    //���Ƹ����ߣ�����������ߣ�����Ϊ��Բ����һ����Ҫ����ͷ��������Ϊ���ı��Σ�ȫ��������ͷ
    void DrawAssisLine(const vector<CdLine> & vecAssisLine);
    //���ƶ���Σ����ն���ε��ԭ��˳����л��ƣ�
    void DrawCdPolygon(const CdPolygon &cdPolygon);
    //���Ʊ�ѹ�����������
    void DrawVecLines(const vector<CdLine> & vecLines);
    //���Ƹ������֣�����Ϊһ����stringΪkey�������CdPointΪvalue��map
    void DrawAssisText(const map<string, CdPoint> & vecAssisText);
    //����SB��
    void DrawAddedPoint(const vector<CdPoint> & vecSBPoint,bool bDrawText);
    //����SB��
    void DrawAddedLine(const vector<CdLine> & vecSBLine);
    //ĸ�߲����
    void DrawMuXianChaDongQuXian(const vector<CdPoint> & vecChaDongPoint);
    //��·�����
    void DrawXianLuChaDongQuXian(const vector<CdPoint> & vecChaDongPoint);
private:
    //������ͷ���������ߣ��к������������
    void DrawCoordLine(const CdPoint & pointStart, const CdPoint & pointEnd,
                       bool bIsHor = true, int iArrowLength = 6, const string &strMark = "");
    //����һ�������Σ�����Ϊ�����εĶ��㣬sizeΪ�����εĸߣ�X�Ƕ�Ϊ����X������ĽǶ�(0~360)��tri�Ƕ�Ϊ�����εĸ���ߵļн�(0~360)��pen��ɫΪ����ɫ��brush��ɫΪ���ɫ
    void DrawTriangle(CdPoint pointVertex, double dSize, double dAngleX, double dAngleTri = 45, QColor penColor = Qt::black, QColor brushColor = Qt::black);
    //����С�����nλ
    QString PrecNumber(QString strNum, int i = 2);
    QLineF GetPercentLine(const QLineF & qline, int iPercent, bool bBeginFromA = true) const;
    QPointF GetQPoint(const CdPoint &point);
public:
    //�������Ը����ʣ��˴�ֱ������public
    QColor m_colorSubLine;//��������ɫ
    QColor m_colorCoordnate;//����ϵ��ɫ
    QColor m_colorRound;//Բ��ɫ
    QColor m_colorArc;//����ɫ
    QColor m_colorQuardrangle;//�ı�����ɫ
    QColor m_colorPoint;//ң��ң�����ɫ
    QColor m_colorPointLine;//��������ɫ
    QColor m_colorTranFillVecLine;//��ѹ�����������ɫ
    QColor m_colorTranVecLine;//��ѹ��������ɫ
    QColor m_colorBackGround;//����ɫ
    QColor m_colorPointLineText;//�����ߵ�����������ɫ

    unsigned char bCurrentColorStyle;
};

#endif // QT_PAINTER_H
