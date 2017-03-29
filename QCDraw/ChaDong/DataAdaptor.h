#ifndef DATAADAPTOR_H
#define DATAADAPTOR_H

#include "CdData.h"
#include <QString>
#include <list>

using namespace std;

class DataAdaptor
{
public:

    DataAdaptor();
    DataAdaptor(const QSize sz);

    void DrawLens(float Za,float Zb,float Zc,float ZdAngle,float lensAngle, const list<CdPoint> & lstZfh);
    void DrawCircleMargin(float Xs,
                                          float Xb,
                                          float magnegicMargin,int magnegicFlag , const list<CdPoint>& listPoints);
    void DrawCircle2(float Xs, float Xa, float Xb, float X1b,float tmpAngle, const list<CdPoint> & lstZfh);
    void DrawCircle(float fZzd, float fAngle, float fZf, float fAngleF, float fRdz, const list<CdPoint> &lstZfh);//Բ�����迹�̵����������ھ��뱣��I���򡢢�Σ�
    void DrawQuadrangle(float fXdz, float fRdz, const list<CdPoint> &lstZfh);//�ı����迹�̵���1�������ھ��뱣��I���򡢢�Σ�
    void DrawQuadrangle2(float fZzd, float fRzd, float fFIzd, float fIn, const list<CdPoint> &lstZfh);//�ı����迹�̵���2�������ڽӵؾ���I��II�Σ�
    void DrawQuadrangle3(float fZzd, float fRzd, float fFIzd, float fIn, const list<CdPoint> &lstZfh);//�ı����迹�̵���3��������������I��II�Σ�
    void DrawQuadrangle4(float fZzd, float fRzd, float fFIzd, float fIn, const list<CdPoint> &lstZfh);//�ı����迹�̵���4�������ڽӵؾ����Σ�
    void DrawQuadrangle5(float fZzd, float fRzd, float fFIzd, float fIn, const list<CdPoint> &lstZfh);//�ı����迹�̵���5����Ӧ���������Σ�
    void DrawQuadrangle6(float fZzd, float fRec, float fAngle, const list<CdPoint> &lstZfh);//����III���ı�������

    void DrawBianYaQiChaDongQuXian(float fIcd, float fIsd, float fK, float fIres);//�ı����迹�̵���5����Ӧ���������Σ�

    void DrawMuXianChaDongQuXian(double fIdz, double fK, const list<CdPoint> &lstZfh, const list<CdPoint> &lstZfh1);//2013�0�2��10�0�8�0�029�0�6�0�9�0�0���0�4�0�7�0�2�0�0�0�5�0�6�0�1�0�4�0�3�0�9
    void DrawXianLuChaDongQuXian(double fIdz, double fK, const list<CdPoint> &lstZfh, const list<CdPoint> &lstZfh1);//2013�0�2��11�0�8�0�015�0�6�0�9�0�0���0�4�0�7�0�3�0�8�0�0���0�5�0�6�0�9�0�4�0�5���0�3�0�8


    const CdData& getCdData() const
    {
        return m_stuData;
    }
private:

    void IniCdLens(float Za,float Zb,float Zc,float ZdAngle,float lensAngle);
    void IniCdCircleMargin(float Xs, float Xb,float magnegicMargin,const string& strXs);
    void IniCdRound2(float Xs,float Xa,float Xb,float X1b,float tmpAngle);
    void IniCdRound(float fZzd, float fAngle, float fZf, float fRdz);
    void IniCdQuardrangle(float fXdz, float fRdz);
    void IniPointList(const list<CdPoint> &lstZfh);
    void IniPointList1(const list<CdPoint> & lstZfh);

    CdData m_stuData;
};

#endif // DATAADAPTOR_H
