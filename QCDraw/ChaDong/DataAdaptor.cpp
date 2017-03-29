#include "DataAdaptor.h"

DataAdaptor::DataAdaptor() :
    m_stuData(600,500)
{
}
DataAdaptor::DataAdaptor(const QSize sz) :
    m_stuData(sz.width(),sz.height())
{

}

void DataAdaptor::DrawLens(float Za,float Zb,float Zc,float ZdAngle,float lensAngle, const list<CdPoint> & lstZfh)
{
    m_stuData.Clear();
    IniCdLens(Za, Zb, Zc, ZdAngle,lensAngle);
    IniPointList(lstZfh);
    m_stuData.calcArea();
}

void DataAdaptor::DrawCircleMargin(float Xs,
                                      float Xb,
                                      float magnegicMargin,int magnegicFlag ,const list<CdPoint>& listPoints)
{
    m_stuData.Clear();
    string fistName = "Xs";
    switch(magnegicFlag)
    {
    case 0:
        fistName = "Xs";
        break;
    case 1:
        fistName = "Xa";
        break;
    }
    IniCdCircleMargin(Xs, Xb,magnegicMargin, fistName);
    IniPointList(listPoints);
    m_stuData.calcArea();
}

void DataAdaptor::DrawCircle2(float Xs, float Xa, float Xb, float X1b,float tmpAngle, const list<CdPoint> & lstZfh)
{
    m_stuData.Clear();
    IniCdRound2(Xs, Xa, Xb, X1b,tmpAngle);
    IniPointList(lstZfh);
    m_stuData.calcArea();
}

void DataAdaptor::DrawCircle(float fZzd, float fAngle, float fZf, float fAngleF, float fRdz, const list<CdPoint> & lstZfh)
{

    m_stuData.Clear();

    IniCdRound(fZzd, fAngle, fZf, fRdz);
    IniPointList(lstZfh);


    m_stuData.calcArea();
}


void DataAdaptor::DrawQuadrangle(float fXdz, float fRdz, const list<CdPoint> & lstZfh)
{
    m_stuData.Clear();

    IniCdQuardrangle(fXdz, fRdz);
    IniPointList(lstZfh);

    m_stuData.calcArea();
}

void DataAdaptor::DrawQuadrangle2(float fZzd, float fRzd, float fFIzd, float fIn, const list<CdPoint> &lstZfh)
{
    m_stuData.Clear();

    double dR = 0.5 * (fRzd < fZzd ? fRzd : fZzd);
    double dX = (5 / fIn) > (0.25 * fZzd) ? (5 / fIn) : (0.25 * fZzd);
    CdPoint pointO(0, 0);
    CdPoint pointA(-dR, dR / tan(45 * 1.0 / 180 * M_PI));
    CdPoint pointB(-dR, fZzd * sin(fFIzd));
    CdPoint pointC(fZzd * cos(fFIzd), fZzd * sin(fFIzd));
    CdPoint pointD(0, 0);
    CdPoint pointE(fRzd, 0);
    CdPoint pointF(fRzd, -dX);
    CdPoint pointG(dX / tan(25 * 1.0 / 180 * M_PI), -dX);
    pointD.m_dX = (fZzd * sin(fFIzd) + tan(fFIzd) * fRzd + tan(12 * 1.0 / 180 * M_PI) * fZzd * cos(fFIzd)) / (tan(fFIzd) + tan(12 * 1.0 / 180 * M_PI));
    pointD.m_dY = tan(fFIzd) * (pointD.m_dX - fRzd);
    CdPolygon cdPolygon;
    cdPolygon.m_vecPoint.push_back(pointO);
    cdPolygon.m_vecPoint.push_back(pointA);
    cdPolygon.m_vecPoint.push_back(pointB);
    cdPolygon.m_vecPoint.push_back(pointC);
    cdPolygon.m_vecPoint.push_back(pointD);
    cdPolygon.m_vecPoint.push_back(pointE);
    cdPolygon.m_vecPoint.push_back(pointF);
    cdPolygon.m_vecPoint.push_back(pointG);

    m_stuData.m_stuPolygon = cdPolygon;
    m_stuData.m_vecPolygon.push_back(m_stuData.m_stuPolygon);
    IniPointList(lstZfh);

    m_stuData.calcArea();
}

void DataAdaptor::DrawQuadrangle3(float fZzd, float fRzd, float fFIzd, float fIn, const list<CdPoint> &lstZfh)
{
    m_stuData.Clear();

    double dR = 0.5 * (fRzd < fZzd ? fRzd : fZzd);
    double dX = (5 / fIn) > (0.25 * fZzd) ? (5 / fIn) : (0.25 * fZzd);
    CdPoint pointO(0, 0);
    CdPoint pointA(-dR, dR / tan(45 * 1.0 / 180 * M_PI));
    CdPoint pointB(-dR, fZzd * sin(fFIzd));
    CdPoint pointC(fZzd * cos(fFIzd), fZzd * sin(fFIzd));
    CdPoint pointD(0, 0);
    CdPoint pointE(0.5 * fRzd, 0);
    CdPoint pointF(0.5 * fRzd, -dX);
    CdPoint pointG(dX / tan(25 * 1.0 / 180 * M_PI), -dX);
    pointD.m_dX = (fZzd * sin(fFIzd) + 0.5 * tan(fFIzd) * fRzd + tan(24 * 1.0 / 180 * M_PI) * fZzd * cos(fFIzd)) / (tan(fFIzd) + tan(24 * 1.0 / 180 * M_PI));
    pointD.m_dY = tan(fFIzd) * (pointD.m_dX - 0.5 * fRzd);
    CdPolygon cdPolygon;
    cdPolygon.m_vecPoint.push_back(pointO);
    cdPolygon.m_vecPoint.push_back(pointA);
    cdPolygon.m_vecPoint.push_back(pointB);
    cdPolygon.m_vecPoint.push_back(pointC);
    cdPolygon.m_vecPoint.push_back(pointD);
    cdPolygon.m_vecPoint.push_back(pointE);
    cdPolygon.m_vecPoint.push_back(pointF);
    cdPolygon.m_vecPoint.push_back(pointG);

    m_stuData.m_stuPolygon = cdPolygon;
    m_stuData.m_vecPolygon.push_back(m_stuData.m_stuPolygon);
    IniPointList(lstZfh);

    m_stuData.calcArea();
}

void DataAdaptor::DrawQuadrangle4(float fZzd, float fRzd, float fFIzd, float fIn, const list<CdPoint> &lstZfh)
{
    m_stuData.Clear();

    double dR = 0.5 * (fRzd < fZzd ? fRzd : fZzd);
    double dX = (5 / fIn) > (0.25 * fZzd) ? (5 / fIn) : (0.25 * fZzd);
    CdPoint pointO(0, 0);
    CdPoint pointA(-dR, dR / tan(45 * 1.0 / 180 * M_PI));
    CdPoint pointB(-dR, fZzd * sin(fFIzd));
    CdPoint pointC(0, 0);
    CdPoint pointD(fRzd, 0);
    CdPoint pointE(fRzd, -dX);
    CdPoint pointF(dX / tan(25 * 1.0 / 180 * M_PI), -dX);
    CdPoint pointG(0.5 * fRzd, -0.5 * fRzd* tan(25 * 1.0 / 180 * M_PI));
    pointC.m_dX = (fZzd * sin(fFIzd) + tan(fFIzd) * fRzd) / tan(fFIzd);
    pointC.m_dY = fZzd * sin(fFIzd);
    CdPolygon cdPolygon;
    cdPolygon.m_vecPoint.push_back(pointO);
    cdPolygon.m_vecPoint.push_back(pointA);
    cdPolygon.m_vecPoint.push_back(pointB);
    cdPolygon.m_vecPoint.push_back(pointC);
    cdPolygon.m_vecPoint.push_back(pointD);
    if(0.5 * fRzd > dX / tan(25 * 1.0 / 180 * M_PI))
    {
        cdPolygon.m_vecPoint.push_back(pointE);
        cdPolygon.m_vecPoint.push_back(pointF);
    }
    else
    {
        cdPolygon.m_vecPoint.push_back(pointG);
    }
    CdPoint pointSB(fZzd * cos(fFIzd), fZzd * sin(fFIzd));


    m_stuData.m_stuPolygon = cdPolygon;
    m_stuData.m_vecPolygon.push_back(m_stuData.m_stuPolygon);
    IniPointList(lstZfh);

    m_stuData.m_vecAddedPoint.push_back(pointSB);
    m_stuData.m_vecAddedPoint.push_back(pointD);
    m_stuData.m_vecAddedLine.push_back(CdLine(pointO, pointSB, 0));

    m_stuData.calcArea();
}

void DataAdaptor::DrawQuadrangle5(float fZzd, float fRzd, float fFIzd, float fIn, const list<CdPoint> &lstZfh)
{
    m_stuData.Clear();

    double dR = 0.5 * (fRzd < fZzd ? fRzd : fZzd);
    double dX = (5 / fIn) > (0.25 * fZzd) ? (5 / fIn) : (0.25 * fZzd);
    CdPoint pointO(0, 0);
    CdPoint pointA(-dR, dR / tan(45 * 1.0 / 180 * M_PI));
    CdPoint pointB(-dR, fZzd * sin(fFIzd));
    CdPoint pointC(0, 0);
    CdPoint pointD(0.5 * fRzd, 0);
    CdPoint pointE(0.5 * fRzd, -dX);
    CdPoint pointF(dX / tan(25 * 1.0 / 180 * M_PI), -dX);
    CdPoint pointG(0.5 * fRzd, -0.5 * fRzd*tan(25 * 1.0 / 180 * M_PI));
    pointC.m_dX = (fZzd * sin(fFIzd) + 0.5 * tan(fFIzd) * fRzd) / tan(fFIzd);
    pointC.m_dY = fZzd * sin(fFIzd);

    CdPoint pointSB(fZzd * cos(fFIzd), fZzd * sin(fFIzd));

    CdPolygon cdPolygon;
    cdPolygon.m_vecPoint.push_back(pointO);
    cdPolygon.m_vecPoint.push_back(pointA);
    cdPolygon.m_vecPoint.push_back(pointB);
    cdPolygon.m_vecPoint.push_back(pointC);
    cdPolygon.m_vecPoint.push_back(pointD);
    if(0.5 * fRzd > dX / tan(25 * 1.0 / 180 * M_PI))
    {
        cdPolygon.m_vecPoint.push_back(pointE);
        cdPolygon.m_vecPoint.push_back(pointF);
    }
    else
    {
        cdPolygon.m_vecPoint.push_back(pointG);
    }

    m_stuData.m_stuPolygon = cdPolygon;
    m_stuData.m_vecPolygon.push_back(m_stuData.m_stuPolygon);
    IniPointList(lstZfh);

    m_stuData.m_vecAddedPoint.push_back(pointSB);
    m_stuData.m_vecAddedPoint.push_back(pointD);
    m_stuData.m_vecAddedLine.push_back(CdLine(pointO, pointSB, 0));



    m_stuData.calcArea();
}

void DataAdaptor::DrawQuadrangle6(float fZzd, float fRec, float fAngle, const list<CdPoint> &lstZfh) {
    m_stuData.Clear();

    float ang = M_PI / 180;
    //算出个点的坐标
    CdPoint pointO(0, 0);
    CdPoint pointCenter(0.5 * fZzd * cos(fAngle * ang), 0.5 * fZzd * sin(fAngle * ang));
    CdPoint pointA(((-0.5 * fZzd) / cos((90 + 15 - fAngle) * ang)) * sin(15 * ang), ((0.5 * fZzd) / cos((90 + 15 - fAngle) * ang)) * cos(15 * ang));
    CdPoint pointB(0.707 * fZzd * cos((fAngle - 45) * ang), 0.707 * fZzd * sin((fAngle - 45) * ang));
    CdPoint pointC(fRec * cos(fAngle * ang) + (fZzd / 2) * sin(fAngle * ang), fRec * sin(fAngle * ang) - (fZzd / 2) * cos(fAngle * ang));
    CdPoint pointD(((-1 * fRec) / cos((90 + 15 - fAngle) * ang)) * sin(15 * ang), (fRec / cos((90 + 15 - fAngle) * ang)) * cos(15 * ang));

    //将四边形的各个点添加到四边形结构中
    CdPolygon cdPolygon;
    cdPolygon.m_vecPoint.push_back(pointA);
    cdPolygon.m_vecPoint.push_back(pointB);
    cdPolygon.m_vecPoint.push_back(pointC);
    cdPolygon.m_vecPoint.push_back(pointD);

    m_stuData.m_stuPolygon = cdPolygon;
    m_stuData.m_vecPolygon.push_back(m_stuData.m_stuPolygon);
    IniPointList(lstZfh);

    //将圆的信息添加到员结构中
    m_stuData.m_stuRound.m_dRadius = sqrt(((0.5 * fZzd * cos(fAngle * ang)) * (0.5 * fZzd * cos(fAngle * ang))) + ((0.5 * fZzd * sin(fAngle * ang)) * (0.5 * fZzd * sin(fAngle * ang))));
    m_stuData.m_stuRound.m_pointCenter = pointCenter;
    m_stuData.m_vecRound.push_back(m_stuData.m_stuRound);

    //将两条带箭头的线添加到线结构中
    CdLine lineArrow;
    lineArrow.m_pointA = pointO;
    lineArrow.m_pointB.m_dX = fZzd * cos(fAngle * ang);
    lineArrow.m_pointB.m_dY = fZzd * sin(fAngle * ang);
    lineArrow.m_type = 1;//新添加字段，0代表线，1代表带箭头的线
    m_stuData.m_vecAssisLine.push_back(lineArrow);
    CdLine lineArrow_second;
    lineArrow_second.m_pointA = pointO;
    lineArrow_second.m_pointB.m_dY = (pointC.m_dX * pointD.m_dY - pointC.m_dY * pointD.m_dX) / ((1 / (tan(M_PI / 3)) * (pointD.m_dY - pointC.m_dY)) + (pointC.m_dX - pointD.m_dX));
    lineArrow_second.m_pointB.m_dX = lineArrow_second.m_pointB.m_dY * (1 / tan(M_PI / 3));
    lineArrow_second.m_type = 1;//新添加字段，0代表线，1代表带箭头的线
    m_stuData.m_vecAssisLine.push_back(lineArrow_second);

    //将辅助虚线添加到虚线结构中去
    CdLine addLineArrow;
    addLineArrow.m_pointA = pointO;
    addLineArrow.m_pointB = pointA;
    m_stuData.m_vecAddedLine.push_back(addLineArrow);

    //将各个点的描述添加到描述结构中
    m_stuData.m_mapAssisText.insert(make_pair("A", pointA));
    m_stuData.m_mapAssisText.insert(make_pair("B", pointB));
    m_stuData.m_mapAssisText.insert(make_pair("C", pointC));
    m_stuData.m_mapAssisText.insert(make_pair("D", pointD));
    m_stuData.m_mapAssisText.insert(make_pair("Zzd", lineArrow.m_pointB));
    m_stuData.m_mapAssisText.insert(make_pair("Zrec", lineArrow_second.m_pointB));

    m_stuData.calcArea();
}

void DataAdaptor::DrawBianYaQiChaDongQuXian(float fIcd, float fIsd, float fK, float fIres)
{
    m_stuData.Clear();

    CdPoint pointA(0, fIcd);
    CdPoint pointB(fIres, fIcd);
    CdPoint pointC((fIsd - fIcd) / fK + fIres, fIsd);
    CdPoint pointD((fIsd - fIcd) / fK + fIres * 2, fIsd);
    m_stuData.m_vecTranLine.push_back(CdLine(pointA, pointB, 0));
    m_stuData.m_vecTranLine.push_back(CdLine(pointB, pointC, 0));
    m_stuData.m_vecTranLine.push_back(CdLine(pointC, pointD, 0));



    m_stuData.calcArea(false,false);
}

void DataAdaptor::DrawMuXianChaDongQuXian(double fIdz, double fK, const list<CdPoint> &lstZfh, const list<CdPoint> &lstZfh1)
{
    m_stuData.Clear();

    CdPoint pointO(0, 0);
    CdPoint pointA(0, fIdz);
    CdPoint pointB(fIdz, fIdz);
    CdPoint pointC(fIdz / fK, fIdz);

    IniPointList(lstZfh);
    IniPointList1(lstZfh1);
    m_stuData.m_vecTranPoint.push_back(pointO);
    m_stuData.m_vecTranPoint.push_back(pointA);
    m_stuData.m_vecTranPoint.push_back(pointB);
    m_stuData.m_vecTranPoint.push_back(pointC);

    //¸¨Öúµã£¬ÓÃÓÚ¿ØÖÆ×ø±êÏµ£¬ÓëÊý¾ÝÎÞ¹Ø
    m_stuData.m_vecInvisiblePoint.push_back(CdPoint(fIdz * 5, fIdz * 5));
    m_stuData.m_vecInvisiblePoint.push_back(CdPoint(-fIdz, -fIdz));

    m_stuData.m_strXCoordText = "Izd(A)";
    m_stuData.m_strYCoordText = "Icd(A)";

    string strText = "Iqd=";
    strText += QString::number(fIdz).toStdString();
    m_stuData.m_mapAssisText.insert(make_pair(strText, CdPoint(0, fIdz)));
    strText = "K=";
    strText += QString::number(fK).toStdString();
    m_stuData.m_mapAssisText.insert(make_pair(strText, pointC));

//    if(m_stuData.m_vecPoint.size() > 0)
//    {
//        CdPoint pointTmp = m_stuData.m_vecPoint[0];
//        strText = "Klm(";
//        strText += QString::number(pointTmp.m_dY / fK /pointTmp.m_dX).left(QString::number(pointTmp.m_dY / fK /pointTmp.m_dX).indexOf('.') + 3).toStdString();
//        strText += ")";
//        m_stuData.m_mapAssisText.insert(make_pair("" + strText, pointTmp));
//        pointTmp = m_stuData.m_vecPoint[m_stuData.m_vecPoint.size() - 1];
//        strText = "Klm(";
//        strText += QString::number(pointTmp.m_dY / fK /pointTmp.m_dX).left(QString::number(pointTmp.m_dY / fK /pointTmp.m_dX).indexOf('.') + 3).toStdString();
//        strText += ")";
//        m_stuData.m_mapAssisText.insert(make_pair("" + strText, pointTmp));
//    }

    m_stuData.calcArea(true);
    m_stuData.m_enuShapeType = TypeMuXianChaDong;
}

void DataAdaptor::DrawXianLuChaDongQuXian(double fIdz, double fK, const list<CdPoint> &lstZfh, const list<CdPoint> &lstZfh1)
{
    m_stuData.Clear();

    CdPoint pointO(0, 0);
    CdPoint pointA(0, fIdz);
    CdPoint pointB(0, fIdz);
    CdPoint pointC(fIdz / fK, fIdz);
    IniPointList(lstZfh);
    IniPointList1(lstZfh1);
    m_stuData = m_stuData;
    m_stuData.m_vecTranPoint.push_back(pointO);
    m_stuData.m_vecTranPoint.push_back(pointA);
    m_stuData.m_vecTranPoint.push_back(pointB);
    m_stuData.m_vecTranPoint.push_back(pointC);

    //¸¨Öúµã£¬ÓÃÓÚ¿ØÖÆ×ø±êÏµ£¬ÓëÊý¾ÝÎÞ¹Ø
    m_stuData.m_vecInvisiblePoint.push_back(CdPoint(fIdz * 5, fIdz * 5));
    m_stuData.m_vecInvisiblePoint.push_back(CdPoint(-fIdz, -fIdz));

    m_stuData.m_strXCoordText = "Izd(A)";
    m_stuData.m_strYCoordText = "Icd(A)";

    string strText = "Iqd=";
    strText += QString::number(fIdz).toStdString();
    m_stuData.m_mapAssisText.insert(make_pair(strText, CdPoint(0, fIdz)));
    strText = "K=";
    strText += QString::number(fK).toStdString();
    m_stuData.m_mapAssisText.insert(make_pair(strText, pointC));

    m_stuData.calcArea(true,false);

    m_stuData.m_enuShapeType = TypeXianLuChaDong;
}


void DataAdaptor::IniCdLens(float Za,float Zb,float Zc,float ZdAngle,float lensAngle)
{
    float tmpZdFAngle = ZdAngle * M_PI / 180; //换算弧度
    float tempCossZdAngle = ( ZdAngle + 90)* M_PI / 180; //换算弧度
    CdPoint lensCenter;
    float interLensAngle = ( 180 - lensAngle) * M_PI / 180;
    float lensRadius = fabs(Za - Zb)  / (sin(interLensAngle) * 2);
    float barLens = lensRadius * cos(interLensAngle);

    lensCenter.m_dX = (Za + Zb)  * cos(tmpZdFAngle) / 2;
    lensCenter.m_dY = (Za + Zb) * sin(tmpZdFAngle) / 2 ;


    CdArc tmpArc;
    tmpArc.m_radius = lensRadius;
    tmpArc.m_ptCenter.m_dX = lensCenter.m_dX + barLens * cos(tempCossZdAngle);
    tmpArc.m_ptCenter.m_dY = lensCenter.m_dY + barLens * sin(tempCossZdAngle);
    tmpArc.m_startAngle = ZdAngle - 90 - ( 360 - lensAngle * 2) / 2;
    tmpArc.m_spanAngle = 360 - lensAngle * 2;
    m_stuData.m_vecArc.push_back(tmpArc);


    tmpArc.m_ptCenter.m_dX = lensCenter.m_dX - barLens * cos(tempCossZdAngle);
    tmpArc.m_ptCenter.m_dY = lensCenter.m_dY - barLens * sin(tempCossZdAngle);
    tmpArc.m_startAngle =  ZdAngle + 90  - ( 360 - lensAngle * 2) / 2;
    tmpArc.m_spanAngle = 360 - lensAngle * 2;
    m_stuData.m_vecArc.push_back(tmpArc);

    //圆形两根辅助线，第一个有箭头，第二根没箭头
    CdLine lineArrow;
    float maxRadius = std::max(std::max(Za,Zb),Zc);
    float minRadius = std::min(std::min(Za,Zb),Zc);
    float outRadus = (maxRadius - minRadius) / 10;
    float upRadius = maxRadius + outRadus;
    float lowRadius = minRadius - outRadus;
    lineArrow.m_pointA.m_dX = lowRadius * cos(tmpZdFAngle);
    lineArrow.m_pointA.m_dY = lowRadius * sin(tmpZdFAngle);
    lineArrow.m_pointB.m_dX = upRadius * cos(tmpZdFAngle);
    lineArrow.m_pointB.m_dY = upRadius * sin(tmpZdFAngle);
    m_stuData.m_vecAssisLine.push_back(lineArrow);

    CdPoint tmpZcPoint;
    tmpZcPoint.m_dX = Zc * cos(tmpZdFAngle);
    tmpZcPoint.m_dY = Zc * sin(tmpZdFAngle);
    float lensThick = (lensRadius - barLens) * 1.1;//maxRadius - minRadius;

    float xDis = lensThick * cos(tempCossZdAngle);
    float yDis = lensThick * sin(tempCossZdAngle);

    lineArrow.m_pointA.m_dX = tmpZcPoint.m_dX - xDis;//lensThick * cos(tempCossZdAngle);
    lineArrow.m_pointA.m_dY = tmpZcPoint.m_dY - yDis;//lensThick * sin(tempCossZdAngle);
    lineArrow.m_pointB.m_dX = tmpZcPoint.m_dX + xDis;//lensThick * cos(tempCossZdAngle);
    lineArrow.m_pointB.m_dY = tmpZcPoint.m_dY + yDis;//lensThick * sin(tempCossZdAngle);
    m_stuData.m_vecAssisLine.push_back(lineArrow);

    CdPoint tmpShowPt;
    tmpShowPt.m_dX = 0 + Za * cos(tmpZdFAngle);
    tmpShowPt.m_dY = 0 + Za * sin(tmpZdFAngle);
    string strTmp = "Za(";
    strTmp += QString::number(Za).toStdString();
    strTmp += ")";
    m_stuData.m_mapAssisText.insert(make_pair(strTmp, tmpShowPt));

    tmpShowPt.m_dX = 0 + Zb * cos(tmpZdFAngle);
    tmpShowPt.m_dY = 0 + Zb * sin(tmpZdFAngle);
    strTmp = "Zb(";
    strTmp += QString::number(fabs(Zb)).toStdString();
    strTmp += ")";
    m_stuData.m_mapAssisText.insert(make_pair(strTmp, tmpShowPt));

    tmpShowPt.m_dX = 0 + Zc * cos(tmpZdFAngle);
    tmpShowPt.m_dY = 0 + Zc * sin(tmpZdFAngle);
    strTmp = "Zc(";
    strTmp += QString::number(Zc).toStdString();
    strTmp += ")";
    m_stuData.m_mapAssisText.insert(make_pair(strTmp, tmpShowPt));
}
void DataAdaptor::IniCdCircleMargin(float Xs, float Xb,float magnegicMargin,const string& strXs)
{
    //圆心及半径
    CdPoint pointCenter;
    float dRadius = fabs(Xb - Xs) / 2;
    pointCenter.m_dX = 0;//圆心横坐标
    pointCenter.m_dY = (Xs + Xb) / 2;//圆心纵坐标

    m_stuData.m_stuRound.m_dRadius = dRadius;
    m_stuData.m_stuRound.m_pointCenter = pointCenter;
    m_stuData.m_stuRound._isDot = false;
    m_stuData.m_vecRound.push_back(m_stuData.m_stuRound);

    dRadius += dRadius * magnegicMargin;
//    pointCenter.m_dX = 0;//圆心横坐标
//    pointCenter.m_dY = (Xs + X1b) / 2;//圆心纵坐标

    m_stuData.m_stuRound.m_dRadius = dRadius;
    m_stuData.m_stuRound.m_pointCenter = pointCenter;
    m_stuData.m_stuRound._isDot = true;
    m_stuData.m_vecRound.push_back(m_stuData.m_stuRound);

    CdPoint tmpShowPt;
    tmpShowPt.m_dX = 0;
    tmpShowPt.m_dY = Xs;

    string strTmp = strXs + "(0,";
    strTmp += QString::number(Xs).toStdString();
    strTmp += ")";
    m_stuData.m_mapAssisText.insert(make_pair(strTmp, tmpShowPt));

    tmpShowPt.m_dY = Xb;
    strTmp = "Xb(0,";
    strTmp += QString::number(Xb).toStdString();
    strTmp += ")";
    m_stuData.m_mapAssisText.insert(make_pair(strTmp, tmpShowPt));
}

void DataAdaptor::IniCdRound2(float Xs,float Xa,float Xb,float X1b,float tmpAngle)//float fZzd, float fAngle, float fZf, float fRdz)
{
    //圆心及半径
    CdPoint pointCenter;
    float dRadius = fabs(Xa - Xb) / 2;
    pointCenter.m_dX = 0;//圆心横坐标
    pointCenter.m_dY = (Xb + Xa) / 2;//圆心纵坐标

    m_stuData.m_stuRound.m_dRadius = dRadius;
    m_stuData.m_stuRound.m_pointCenter = pointCenter;
    m_stuData.m_vecRound.push_back(m_stuData.m_stuRound);

    dRadius = fabs(Xs - X1b) / 2;
    pointCenter.m_dX = 0;//圆心横坐标
    pointCenter.m_dY = (Xs + X1b) / 2;//圆心纵坐标

    m_stuData.m_stuRound.m_dRadius = dRadius;
    m_stuData.m_stuRound.m_pointCenter = pointCenter;
    m_stuData.m_vecRound.push_back(m_stuData.m_stuRound);



    //圆形两根辅助线，第一个有箭头，第二根没箭头
    double tempfangle = -tmpAngle * M_PI / 180; //换算弧度
    dRadius = std::max(std::max(fabs(Xs),fabs(Xb)),std::max(fabs(Xa),fabs(X1b)));
    CdLine lineArrow;
    lineArrow.m_pointA.m_dX = 0;
    lineArrow.m_pointA.m_dY = 0;
    lineArrow.m_pointB.m_dX = 0 + dRadius * cos(tempfangle);
    lineArrow.m_pointB.m_dY =0 + dRadius * sin(tempfangle);
    m_stuData.m_vecAssisLine.push_back(lineArrow);

    tempfangle = -( 180 - tmpAngle)* M_PI / 180; //换算弧度
    lineArrow.m_pointA.m_dX = 0;
    lineArrow.m_pointA.m_dY = 0;
    lineArrow.m_pointB.m_dX = 0 + dRadius * cos(tempfangle);
    lineArrow.m_pointB.m_dY = 0 + dRadius * sin(tempfangle);
    m_stuData.m_vecAssisLine.push_back(lineArrow);

    CdPoint tmpShowPt;
    tmpShowPt.m_dX = 0;
    tmpShowPt.m_dY = Xs;

    string strTmp = "Xs(0,";
    strTmp += QString::number(Xs).toStdString();
    strTmp += ")";
    m_stuData.m_mapAssisText.insert(make_pair(strTmp, tmpShowPt));

    tmpShowPt.m_dY = X1b;
    strTmp = "X1b(0,";
    strTmp += QString::number(X1b).toStdString();
    strTmp += ")";
    m_stuData.m_mapAssisText.insert(make_pair(strTmp, tmpShowPt));


    tmpShowPt.m_dY = Xa;
    strTmp = "Xa(0,";
        strTmp += QString::number(Xa).toStdString();
        strTmp += ")";
    m_stuData.m_mapAssisText.insert(make_pair(strTmp, tmpShowPt));

    tmpShowPt.m_dY = Xb;
    strTmp = "Xb(0,";
        strTmp += QString::number(Xb).toStdString();
        strTmp += ")";
    m_stuData.m_mapAssisText.insert(make_pair(strTmp, tmpShowPt));
}

void DataAdaptor::IniCdRound(float fZzd, float fAngle, float fZf, float fRdz)
{
    //圆心及半径
    CdPoint pointCenter;
    double dRadius = (fZzd + fZf) / 2;

    double tempfangle = fAngle * M_PI / 180; //换算弧度
    pointCenter.m_dX = ((fZzd + fZf) / 2 - fZf) * cos(tempfangle);//圆心横坐标
    pointCenter.m_dY = ((fZzd + fZf) / 2 - fZf) * sin(tempfangle);//圆心纵坐标

    m_stuData.m_stuRound.m_dRadius = dRadius;
    m_stuData.m_stuRound.m_pointCenter = pointCenter;
    m_stuData.m_vecRound.push_back(m_stuData.m_stuRound);
    //圆形两根辅助线，第一个有箭头，第二根没箭头
    CdLine lineArrow;
    lineArrow.m_pointA.m_dX = pointCenter.m_dX - dRadius * cos(tempfangle);
    lineArrow.m_pointA.m_dY = pointCenter.m_dY - dRadius * sin(tempfangle);
    lineArrow.m_pointB.m_dX = pointCenter.m_dX + dRadius * cos(tempfangle);
    lineArrow.m_pointB.m_dY = pointCenter.m_dY + dRadius * sin(tempfangle);

    CdLine lineNormal;
    lineNormal.m_pointA.m_dX = fRdz - lineArrow.m_pointB.m_dY / tan(tempfangle);
    lineNormal.m_pointA.m_dY = 0 - lineArrow.m_pointB.m_dY;

    lineNormal.m_pointB.m_dX = fRdz + lineArrow.m_pointB.m_dY / tan(tempfangle);
    lineNormal.m_pointB.m_dY = lineArrow.m_pointB.m_dY;
    m_stuData.m_vecAssisLine.push_back(lineArrow);
    m_stuData.m_vecAssisLine.push_back(lineNormal);

    string strTmp = "Zdz(";
    strTmp += QString::number(fZzd).toStdString();
    strTmp += "∠";
    strTmp += QString::number(fAngle).toStdString();
    strTmp += "°)";
    m_stuData.m_mapAssisText.insert(make_pair(strTmp, lineArrow.m_pointB));
    strTmp = "Rdz(";
        strTmp += QString::number(fRdz).toStdString();
        strTmp += ",0)";
    m_stuData.m_mapAssisText.insert(make_pair(strTmp, CdPoint(fRdz, 0)));
}

void DataAdaptor::IniCdQuardrangle(float fXdz, float fRdz)
{
    CdPoint pointA(fRdz, 0);
    CdPoint pointB(0, fXdz);
    CdPoint pointC;
    pointC.m_dX = (fXdz + fRdz * tan(60 * M_PI / 180)) / ((tan(60 * M_PI / 180)) + tan(7 * M_PI / 180));
    pointC.m_dY = (pointC.m_dX - fRdz) * tan(60 * M_PI / 180);
    //m_stuData.m_stuQuardrangle.m_arrayPoint[0] = pointA;
    //m_stuData.m_stuQuardrangle.m_arrayPoint[1] = pointB;
    //m_stuData.m_stuQuardrangle.m_arrayPoint[2] = pointC;
    //m_stuData.m_stuQuardrangle.m_arrayPoint[3] = CdPoint(0, 0);
    //m_stuData.m_vecQuardangle.push_back(m_stuData.m_stuQuardrangle);
    //计算辅助线用点，D和E
    CdPoint pointD;
    pointD.m_dX = pointA.m_dX;
    pointD.m_dY = 0 - pointA.m_dX * tan(15 * M_PI / 180);
    CdPoint pointE;
    pointE.m_dX = 0 - pointB.m_dY * tan(15 * M_PI / 180);
    pointE.m_dY = pointB.m_dY;
    //m_stuData.m_vecAssisLine.push_back(CdLine(pointE, pointB));
    //m_stuData.m_vecAssisLine.push_back(CdLine(CdPoint(0, 0), pointE));
    //m_stuData.m_vecAssisLine.push_back(CdLine(CdPoint(0, 0), pointD));
    //m_stuData.m_vecAssisLine.push_back(CdLine(pointA, pointD));

    //在多边形里边存上辅助线用点，用于后期的扩缩计算
    m_stuData.m_stuPolygon.m_vecPoint.push_back(CdPoint(0, 0));
    m_stuData.m_stuPolygon.m_vecPoint.push_back(pointD);
    m_stuData.m_stuPolygon.m_vecPoint.push_back(pointA);
    m_stuData.m_stuPolygon.m_vecPoint.push_back(pointC);
    m_stuData.m_stuPolygon.m_vecPoint.push_back(pointB);
    m_stuData.m_stuPolygon.m_vecPoint.push_back(pointE);
    m_stuData.m_vecPolygon.push_back(m_stuData.m_stuPolygon);

    string strTmp = "Xdz(0,";
    strTmp += QString::number(fXdz).toStdString();
    strTmp += ")";
    m_stuData.m_mapAssisText.insert(make_pair(strTmp, CdPoint(0, fXdz)));
    strTmp = "Rdz(";
        strTmp += QString::number(fRdz).toStdString();
        strTmp += ",0)";
    m_stuData.m_mapAssisText.insert(make_pair(strTmp, CdPoint(fRdz, 0)));
}

void DataAdaptor::IniPointList(const list<CdPoint> & lstZfh)
{
    m_stuData.m_vecPoint.clear();
    for(list<CdPoint>::const_iterator it = lstZfh.begin(); it != lstZfh.end(); it++)
    {
        m_stuData.m_vecPoint.push_back(*it);
    }
}
void DataAdaptor::IniPointList1(const list<CdPoint> & lstZfh)
{
    m_stuData.m_vecPointChaDong.clear();
    for(list<CdPoint>::const_iterator it = lstZfh.begin(); it != lstZfh.end(); it++)
    {
        m_stuData.m_vecPointChaDong.push_back(*it);
    }
}

