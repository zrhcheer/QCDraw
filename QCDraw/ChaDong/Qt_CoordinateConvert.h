#ifndef QT_COORDINATECONVERT_H
#define QT_COORDINATECONVERT_H
#include "CdCoordinate.h"
#include "CdRect.h"
#include "G_EnvironmentalVaraible.h"

class Qt_CoordinateConvert
{
public:
    //�����������Ϣ���ɿؼ���������ȥ�߿��������õ�����ͬʱҲ���߼�����ϵ��ϵͳ����ϵ�еĴ�С
    CdRect m_stuRectPaintArea;
    //�߼�����ϵ����Ϣ�������ݵķֲ����޾���
    CdCoordinate m_stuCoordinate;
    //ʵ�ʻ��ƴ�С��������������ת���������ϵʵ�ʴ�С����������ϵ�ľ��м���
    CdRect m_stuRectCoordArea;
private:
    //�����ߣ��߼�����λ�������������λ���ȵı�ֵ
    double m_dUnit;
    //��ֱ�����ϵ�Ϊ�˱�֤���ж����õ�ƫ����
    double m_dVerOffset;
    //ˮƽ�����ϵ�Ϊ�˱�֤���ж����õ�ƫ����
    double m_dHorOffset;
    //�±��ĸ��ǹ�Բ���ı��ε�����ʹ�õ�
    //ͼ�α߽����
    CdRect m_stuRectAreaBound;
    //ͼ���ⲿ�ĳ�����߽����
    CdRect m_stuRectPointBound;
    //ͼ�����ź�ı߽���Σ���ͼ�α���ı߽���μ�������ı߽����ȷ�������ź�ı߽���Σ�ȷ������Ϊ�߶Ⱦ�����ռ������ϵ����߶ȵ�radio��
    CdRect m_stuRectBigSizeAreaBound;
    //����ϵ������ʼ��Ϊ0.25����������Ĭ��ֵ�����Ĭ��ֵ�볱�����г�ͻ�������һ������С
    double m_dRadio;
public:
    Qt_CoordinateConvert();
    //������������ϵ
    void SetBigSizeData(const CdRect & stuRectAreaBound, const CdRect & stuRectPointBound, CdCoordinate &stuCoordinate);
    //��������Ӧ����ϵ
    void SetData(const CdCoordinate & stuCoordinate, const CdRect & stuRectPaintArea);
    //���߼������ӳ��Ϊ�豸�����
    CdPoint MapPointFromLogicToSys(const CdPoint & pointTarget,bool bSeeStu = false) const;
    //���豸�����ӳ��Ϊ�߼������
    CdPoint MapPointFromSysToLogic(const CdPoint & pointTarget) const;
    //���ձ����߻��㳤�ȵ�λ���������������������ţ�
    double MapLenthFromSysToLogic(double dLength);
    //����ϵ���ȹ�λ
    void ResetBigSizeParam();
};

#endif // QT_COORDINATECONVERT_H
