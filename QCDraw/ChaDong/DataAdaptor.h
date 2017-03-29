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
    void DrawCircle(float fZzd, float fAngle, float fZf, float fAngleF, float fRdz, const list<CdPoint> &lstZfh);//圆特性阻抗继电器（适用于距离保护I、Ⅱ、Ⅲ段）
    void DrawQuadrangle(float fXdz, float fRdz, const list<CdPoint> &lstZfh);//四边形阻抗继电器1（适用于距离保护I、Ⅱ、Ⅲ段）
    void DrawQuadrangle2(float fZzd, float fRzd, float fFIzd, float fIn, const list<CdPoint> &lstZfh);//四边形阻抗继电器2（适用于接地距离I、II段）
    void DrawQuadrangle3(float fZzd, float fRzd, float fFIzd, float fIn, const list<CdPoint> &lstZfh);//四边形阻抗继电器3（适用于相间距离I、II段）
    void DrawQuadrangle4(float fZzd, float fRzd, float fFIzd, float fIn, const list<CdPoint> &lstZfh);//四边形阻抗继电器4（适用于接地距离Ⅲ段）
    void DrawQuadrangle5(float fZzd, float fRzd, float fFIzd, float fIn, const list<CdPoint> &lstZfh);//四边形阻抗继电器5（适应于相间距离Ⅲ段）
    void DrawQuadrangle6(float fZzd, float fRec, float fAngle, const list<CdPoint> &lstZfh);//距离III段四边形特性

    void DrawBianYaQiChaDongQuXian(float fIcd, float fIsd, float fK, float fIres);//四边形阻抗继电器5（适应于相间距离Ⅲ段）

    void DrawMuXianChaDongQuXian(double fIdz, double fK, const list<CdPoint> &lstZfh, const list<CdPoint> &lstZfh1);//2013Äê10ÔÂ29ÈÕÌí¼ÓÄ¸²îÍ¼Ïñ
    void DrawXianLuChaDongQuXian(double fIdz, double fK, const list<CdPoint> &lstZfh, const list<CdPoint> &lstZfh1);//2013Äê11ÔÂ15ÈÕÌí¼ÓÏßÂ·²î¶¯ÇúÏß


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
