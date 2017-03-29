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

    vector<CdArc> m_vecArc;//������ͼ���б�
    vector<CdRound> m_vecRound;//Բ����ͼ���б�
    vector<CdQuardrangle> m_vecQuardangle;//�ı�������ͼ���б�
    vector<CdPolygon> m_vecPolygon;//�����ͼ���б�
    CdRect m_stuRectAreaBound;//�����ڲ���������ϵ�ļ���
    CdRect m_stuRectPointBound;//�����ڲ���������ϵ�ļ���
    vector<CdLine> m_vecAssisLine;//Բ���ı��ο����õ��ĸ�����
    vector<CdLine> m_vecTranLine;//��ѹ����߼���
    vector<CdPoint> m_vecPoint;//�������ݵ������õ��ĵ�
    vector<CdPoint> m_vecPointChaDong;//��������ݵ������õ��ĵ�
    vector<CdPoint> m_vecTranPoint;//��㼯��
    map<string, CdPoint> m_mapAssisText;//��������
    string m_strXCoordText;//����������ʾ����
    string m_strYCoordText;//����������ʾ����
    vector<CdPoint> m_vecInvisiblePoint;//�������ʵ������������ϵ�����ã���������ϵ�������㵫����������
    ShapeType m_enuShapeType;
    vector<CdPoint> m_vecAddedPoint;//��֪�������õĵ�
    vector<CdLine> m_vecAddedLine;//��������

private:
    QSize _size;

};

#endif // _HH_CDDATA_H
