#include "CdDataCalculateTool.h"
#include "G_EnvironmentalVaraible.h"
#include <math.h>
#include "CdLine.h"
#include "CdData.h"

double CdDataCalculateTool::m_dCoordDataRatio = 1.1;

CdDataCalculateTool::CdDataCalculateTool()
{
}

int CdDataCalculateTool::DoubleCompare(double dValue1, double dValue2)
{
    int iRet = 0;
    if(DoubleAbsolute(dValue1 - dValue2) < G_EnvironmentalVaraible::g_dPrecision)
        iRet = 0;
    else if(dValue1 > dValue2)
        iRet = 1;
    else
        iRet = -1;
    return iRet;
}

double CdDataCalculateTool::DoubleAbsolute(double dValue)
{
    double dRet = 0;
    if(dValue > 0)
        dRet = dValue;
    else
        dRet = -dValue;
    return dRet;
}

void CdDataCalculateTool::CalculateCoordinate(CdData &stuData, bool bflag)
{
    //距离三段 与 line差动tran差动的区别
    //bflag =true line差动tran差动的
    //bflag =false 距离三段的
    if (bflag)
    {
        /*
     *2013年10月12日追加，除了计算坐标系边界之外，还需要计算四边形及四边形外的点边界
    */
        CdRect stuRectAreaBound;
        CdRect stuRectPointBound;
        //判定当前是什么类型，圆，多边形，还是四边形，并取得图形外的点集
        vector<CdPoint> vecOutPoint;
        //如果多边形集合不为空，则是多边形
        if(stuData.m_vecPolygon.size() > 0)
        {
            for(uint j = 0; j < stuData.m_vecPolygon.size(); j++)
            {
                stuRectAreaBound.UnionRect(stuData.m_vecPolygon[j].GetBoundRect());
                for(uint i = 0; i < stuData.m_vecPoint.size(); i++)
                {
                    if(!(stuData.m_vecPolygon[j].IsPointInPolygon(stuData.m_vecPoint[i])))
                    {
                        vecOutPoint.push_back(stuData.m_vecPoint[i]);
                    }
                }
            }
        }
        //如果圆不为空，则是圆形
        else if(stuData.m_vecRound.size() > 0)
        {
            for(uint j = 0; j < stuData.m_vecRound.size(); j++)
            {
                stuRectAreaBound.UnionRect(stuData.m_vecRound[j].GetBoundRect());
                for(uint i = 0; i < stuData.m_vecPoint.size(); i++)
                {
                    if(!(stuData.m_vecRound[j].IsPointInRound(stuData.m_vecPoint[i])))
                    {
                        vecOutPoint.push_back(stuData.m_vecPoint[i]);
                    }
                }
            }
        }
        //如果四边形不为空则是四边形
        else if(stuData.m_vecQuardangle.size() > 0)
        {
            for(uint j = 0; j < stuData.m_vecQuardangle.size(); j++)
            {
                stuRectAreaBound.UnionRect(stuData.m_stuPolygon.GetBoundRect());
                for(uint i = 0; i < stuData.m_vecPoint.size(); i++)
                {
                    if(!(stuData.m_vecQuardangle[j].IsPointInQuardrangle(stuData.m_vecPoint[i])))
                    {
                        vecOutPoint.push_back(stuData.m_vecPoint[i]);
                    }
                }
            }
        }
        else if(stuData.m_vecTranPoint.size() > 0)
        {
            CdRect rectAreaBound;
            for(uint i = 0; i < stuData.m_vecTranPoint.size(); i++)
            {
                if(rectAreaBound.m_dLeft > stuData.m_vecTranPoint[i].m_dX)
                    rectAreaBound.m_dLeft = stuData.m_vecTranPoint[i].m_dX;
                if(rectAreaBound.m_dRight < stuData.m_vecTranPoint[i].m_dX)
                    rectAreaBound.m_dRight = stuData.m_vecTranPoint[i].m_dX;
                if(rectAreaBound.m_dBottom > stuData.m_vecTranPoint[i].m_dY)
                    rectAreaBound.m_dBottom = stuData.m_vecTranPoint[i].m_dY;
                if(rectAreaBound.m_dTop < stuData.m_vecTranPoint[i].m_dY)
                    rectAreaBound.m_dTop = stuData.m_vecTranPoint[i].m_dY;
            }
            stuRectAreaBound.UnionRect(rectAreaBound);
            for(uint i = 0; i < stuData.m_vecPoint.size(); i++)
            {
                if(!(stuRectAreaBound.IsPointInRect(stuData.m_vecPoint[i])))
                {
                    vecOutPoint.push_back(stuData.m_vecPoint[i]);
                }
            }
        }
        //循环取得外部点集边界
        if(vecOutPoint.size() > 0)
        {
            double dLeft = 999999;
            double dRight = 999999;
            double dTop = 999999;
            double dBottom = 999999;
            //循环点集
            unsigned int iPointSize = vecOutPoint.size();
            for(unsigned int i = 0; i < iPointSize; i++)
            {
                if(dLeft > vecOutPoint[i].m_dX)
                    dLeft = vecOutPoint[i].m_dX;
                if(dRight < vecOutPoint[i].m_dX)
                    dRight = vecOutPoint[i].m_dX;
                if(dBottom > vecOutPoint[i].m_dY)
                    dBottom = vecOutPoint[i].m_dY;
                if(dTop < vecOutPoint[i].m_dY)
                    dTop = vecOutPoint[i].m_dY;
            }
            stuRectPointBound.m_dBottom = dBottom;
            stuRectPointBound.m_dLeft = dLeft;
            stuRectPointBound.m_dRight = dRight;
            stuRectPointBound.m_dTop = dTop;
        }
        stuData.m_stuRectAreaBound = stuRectAreaBound;
        stuData.m_stuRectPointBound = stuRectPointBound;
        /*
     *计算坐标系边界的思路
     *1.循环点集，确定点集的四条边界
     *2.循环四边形的四个点
     *3.确定圆
     */
        double dLeft = 0;
        double dRight = 0;
        double dTop = 0;
        double dBottom = 0;
        //循环点集
        unsigned int iPointSize = stuData.m_vecPoint.size();
        for(unsigned int i = 0; i < iPointSize; i++)
        {
            if(dLeft > stuData.m_vecPoint[i].m_dX)
                dLeft = stuData.m_vecPoint[i].m_dX;
            if(dRight < stuData.m_vecPoint[i].m_dX)
                dRight = stuData.m_vecPoint[i].m_dX;
            if(dBottom > stuData.m_vecPoint[i].m_dY)
                dBottom = stuData.m_vecPoint[i].m_dY;
            if(dTop < stuData.m_vecPoint[i].m_dY)
                dTop = stuData.m_vecPoint[i].m_dY;
        }
        //循环不可见点集
        iPointSize = stuData.m_vecInvisiblePoint.size();
        for(unsigned int i = 0; i < iPointSize; i++)
        {
            if(dLeft > stuData.m_vecInvisiblePoint[i].m_dX)
                dLeft = stuData.m_vecInvisiblePoint[i].m_dX;
            if(dRight < stuData.m_vecInvisiblePoint[i].m_dX)
                dRight = stuData.m_vecInvisiblePoint[i].m_dX;
            if(dBottom > stuData.m_vecInvisiblePoint[i].m_dY)
                dBottom = stuData.m_vecInvisiblePoint[i].m_dY;
            if(dTop < stuData.m_vecInvisiblePoint[i].m_dY)
                dTop = stuData.m_vecInvisiblePoint[i].m_dY;
        }
        //辅助线的循环
        for(uint i = 0; i < stuData.m_vecAssisLine.size(); i++)
        {
            if(dLeft > stuData.m_vecAssisLine[i].m_pointA.m_dX)
                dLeft = stuData.m_vecAssisLine[i].m_pointA.m_dX;
            if(dLeft > stuData.m_vecAssisLine[i].m_pointB.m_dX)
                dLeft = stuData.m_vecAssisLine[i].m_pointB.m_dX;
            if(dRight < stuData.m_vecAssisLine[i].m_pointA.m_dX)
                dRight = stuData.m_vecAssisLine[i].m_pointA.m_dX;
            if(dRight < stuData.m_vecAssisLine[i].m_pointB.m_dX)
                dRight = stuData.m_vecAssisLine[i].m_pointB.m_dX;

            if(dTop < stuData.m_vecAssisLine[i].m_pointA.m_dY)
                dTop = stuData.m_vecAssisLine[i].m_pointA.m_dY;
            if(dTop < stuData.m_vecAssisLine[i].m_pointB.m_dY)
                dTop = stuData.m_vecAssisLine[i].m_pointB.m_dY;
            if(dBottom > stuData.m_vecAssisLine[i].m_pointA.m_dY)
                dBottom = stuData.m_vecAssisLine[i].m_pointA.m_dY;
            if(dBottom > stuData.m_vecAssisLine[i].m_pointB.m_dY)
                dBottom = stuData.m_vecAssisLine[i].m_pointB.m_dY;
        }
        //变压器差动线的循环
        for(uint i = 0; i < stuData.m_vecTranLine.size(); i++)
        {
            if(dLeft > stuData.m_vecTranLine[i].m_pointA.m_dX)
                dLeft = stuData.m_vecTranLine[i].m_pointA.m_dX;
            if(dLeft > stuData.m_vecTranLine[i].m_pointB.m_dX)
                dLeft = stuData.m_vecTranLine[i].m_pointB.m_dX;
            if(dRight < stuData.m_vecTranLine[i].m_pointA.m_dX)
                dRight = stuData.m_vecTranLine[i].m_pointA.m_dX;
            if(dRight < stuData.m_vecTranLine[i].m_pointB.m_dX)
                dRight = stuData.m_vecTranLine[i].m_pointB.m_dX;

            if(dTop < stuData.m_vecTranLine[i].m_pointA.m_dY)
                dTop = stuData.m_vecTranLine[i].m_pointA.m_dY;
            if(dTop < stuData.m_vecTranLine[i].m_pointB.m_dY)
                dTop = stuData.m_vecTranLine[i].m_pointB.m_dY;
            if(dBottom > stuData.m_vecTranLine[i].m_pointA.m_dY)
                dBottom = stuData.m_vecTranLine[i].m_pointA.m_dY;
            if(dBottom > stuData.m_vecTranLine[i].m_pointB.m_dY)
                dBottom = stuData.m_vecTranLine[i].m_pointB.m_dY;
        }
        //取得图形边界
        CdRect recBound = stuRectAreaBound;
        if(dLeft > recBound.m_dLeft)
            dLeft = recBound.m_dLeft;
        if(dRight < recBound.m_dRight)
            dRight = recBound.m_dRight;
        if(dTop < recBound.m_dTop)
            dTop = recBound.m_dTop;
        if(dBottom > recBound.m_dBottom)
            dBottom = recBound.m_dBottom;
        //坐标系比内部元素大出1/20
        stuData.m_stuCoordinate.m_dBottom = dBottom * CdDataCalculateTool::m_dCoordDataRatio;
        stuData.m_stuCoordinate.m_dTop = dTop * CdDataCalculateTool::m_dCoordDataRatio;
        stuData.m_stuCoordinate.m_dLeft = dLeft * CdDataCalculateTool::m_dCoordDataRatio;
        stuData.m_stuCoordinate.m_dRight = dRight * CdDataCalculateTool::m_dCoordDataRatio;
    }
    else
    {
        /*
         *2013年10月12日追加，除了计算坐标系边界之外，还需要计算四边形及四边形外的点边界
        */
        CdRect stuRectAreaBound(-9990,9999,9999,-9999);
        CdRect stuRectPointBound;
        //判定当前是什么类型，圆，多边形，还是四边形，并取得图形外的点集
        vector<CdPoint> vecOutPoint;
        //如果多边形集合不为空，则是多边形
        if(stuData.m_vecPolygon.size() > 0)
        {
            for(uint j = 0; j < stuData.m_vecPolygon.size(); j++)
            {
                stuRectAreaBound.UnionRect(stuData.m_vecPolygon[j].GetBoundRect());
                for(uint i = 0; i < stuData.m_vecPoint.size(); i++)
                {
                    if(!(stuData.m_vecPolygon[j].IsPointInPolygon(stuData.m_vecPoint[i])))
                    {
                        vecOutPoint.push_back(stuData.m_vecPoint[i]);
                    }
                }
            }
        }
        //如果圆不为空，则是圆形
        if(stuData.m_vecRound.size() > 0)
        {
            for(uint j = 0; j < stuData.m_vecRound.size(); j++)
            {
                stuRectAreaBound.UnionRect(stuData.m_vecRound[j].GetBoundRect());
                //圆特性需要将辅助线也考虑进去
                CdRect rectTemp;
                for(uint i = 0; i < stuData.m_vecAssisLine.size(); i++)
                {
                    if(rectTemp.m_dLeft > stuData.m_vecAssisLine[i].m_pointA.m_dX)
                        rectTemp.m_dLeft = stuData.m_vecAssisLine[i].m_pointA.m_dX;
                    if(rectTemp.m_dLeft > stuData.m_vecAssisLine[i].m_pointB.m_dX)
                        rectTemp.m_dLeft = stuData.m_vecAssisLine[i].m_pointB.m_dX;
                    if(rectTemp.m_dRight < stuData.m_vecAssisLine[i].m_pointA.m_dX)
                        rectTemp.m_dRight = stuData.m_vecAssisLine[i].m_pointA.m_dX;
                    if(rectTemp.m_dRight < stuData.m_vecAssisLine[i].m_pointB.m_dX)
                        rectTemp.m_dRight = stuData.m_vecAssisLine[i].m_pointB.m_dX;

                    if(rectTemp.m_dTop < stuData.m_vecAssisLine[i].m_pointA.m_dY)
                        rectTemp.m_dTop = stuData.m_vecAssisLine[i].m_pointA.m_dY;
                    if(rectTemp.m_dTop < stuData.m_vecAssisLine[i].m_pointB.m_dY)
                        rectTemp.m_dTop = stuData.m_vecAssisLine[i].m_pointB.m_dY;
                    if(rectTemp.m_dBottom > stuData.m_vecAssisLine[i].m_pointA.m_dY)
                        rectTemp.m_dBottom = stuData.m_vecAssisLine[i].m_pointA.m_dY;
                    if(rectTemp.m_dBottom > stuData.m_vecAssisLine[i].m_pointB.m_dY)
                        rectTemp.m_dBottom = stuData.m_vecAssisLine[i].m_pointB.m_dY;
                }
                stuRectAreaBound.UnionRect(rectTemp);
                for(uint i = 0; i < stuData.m_vecPoint.size(); i++)
                {
                    if(!(stuData.m_vecRound[j].IsPointInRound(stuData.m_vecPoint[i])))
                    {
                        vecOutPoint.push_back(stuData.m_vecPoint[i]);
                    }
                }
            }
        }
        //判断弧的边界
        if(stuData.m_vecArc.size() > 0)
        {
            for(uint j = 0; j < stuData.m_vecArc.size(); j++)
            {
                stuRectAreaBound.UnionRect(stuData.m_vecArc[j].GetBoundRect());
            }
        }
        //如果四边形不为空则是四边形
        if(stuData.m_vecQuardangle.size() > 0)
        {
            for(uint j = 0; j < stuData.m_vecQuardangle.size(); j++)
            {
                stuRectAreaBound.UnionRect(stuData.m_stuPolygon.GetBoundRect());
                for(uint i = 0; i < stuData.m_vecPoint.size(); i++)
                {
                    if(!(stuData.m_vecQuardangle[j].IsPointInQuardrangle(stuData.m_vecPoint[i])))
                    {
                        vecOutPoint.push_back(stuData.m_vecPoint[i]);
                    }
                }
            }
        }
        //    CdRound zeroRound;
        //    //如果多边形中有数据则是多边形
        //    if(stuData.m_stuPolygon.m_vecPoint.size() > 0)
        //    {
        //        stuRectAreaBound = stuData.m_stuPolygon.GetBoundRect();
        //        for(int i = 0; i < stuData.m_vecPoint.size(); i++)
        //        {
        //            if(!(stuData.m_stuPolygon.IsPointInPolygon(stuData.m_vecPoint[i])))
        //            {
        //                vecOutPoint.push_back(stuData.m_vecPoint[i]);
        //            }
        //        }
        //    }
        //    //如果圆不为空，则是圆
        //    else if(!(stuData.m_stuRound == zeroRound))
        //    {
        //        stuRectAreaBound = stuData.m_stuRound.GetBoundRect();
        //        for(int i = 0; i < stuData.m_vecPoint.size(); i++)
        //        {
        //            if(!(stuData.m_stuRound.IsPointInRound(stuData.m_vecPoint[i])))
        //            {
        //                vecOutPoint.push_back(stuData.m_vecPoint[i]);
        //            }
        //        }
        //    }
        //    //否则认为是四边形
        //    else
        //    {
        //        stuRectAreaBound = stuData.m_stuQuardrangle.GetBoundRect();
        //        for(int i = 0; i < stuData.m_vecPoint.size(); i++)
        //        {
        //            if(!(stuData.m_stuQuardrangle.IsPointInQuardrangle(stuData.m_vecPoint[i])))
        //            {
        //                vecOutPoint.push_back(stuData.m_vecPoint[i]);
        //            }
        //        }
        //    }
        //循环取得外部点集边界
        if(vecOutPoint.size() > 0)
        {
            double dLeft = 999999;
            double dRight = 999999;
            double dTop = 999999;
            double dBottom = 999999;
            //循环点集
            unsigned int iPointSize = vecOutPoint.size();
            for(unsigned int i = 0; i < iPointSize; i++)
            {
                if(dLeft > vecOutPoint[i].m_dX)
                    dLeft = vecOutPoint[i].m_dX;
                if(dRight < vecOutPoint[i].m_dX)
                    dRight = vecOutPoint[i].m_dX;
                if(dBottom > vecOutPoint[i].m_dY)
                    dBottom = vecOutPoint[i].m_dY;
                if(dTop < vecOutPoint[i].m_dY)
                    dTop = vecOutPoint[i].m_dY;
            }
            stuRectPointBound.m_dBottom = dBottom;
            stuRectPointBound.m_dLeft = dLeft;
            stuRectPointBound.m_dRight = dRight;
            stuRectPointBound.m_dTop = dTop;
        }
        //杜江涛，扩大区比实际再扩大10%
        stuRectAreaBound.adjustScale(1.1);
        stuData.m_stuRectAreaBound = stuRectAreaBound;
        stuData.m_stuRectPointBound = stuRectPointBound;
        /*
         *计算坐标系边界的思路
         *1.循环点集，确定点集的四条边界
         *2.循环四边形的四个点
         *3.确定圆
         */
        double dLeft = 0;
        double dRight = 0;
        double dTop = 0;
        double dBottom = 0;
        //循环点集
        unsigned int iPointSize = stuData.m_vecPoint.size();
        for(unsigned int i = 0; i < iPointSize; i++)
        {
            if(dLeft > stuData.m_vecPoint[i].m_dX)
                dLeft = stuData.m_vecPoint[i].m_dX;
            if(dRight < stuData.m_vecPoint[i].m_dX)
                dRight = stuData.m_vecPoint[i].m_dX;
            if(dBottom > stuData.m_vecPoint[i].m_dY)
                dBottom = stuData.m_vecPoint[i].m_dY;
            if(dTop < stuData.m_vecPoint[i].m_dY)
                dTop = stuData.m_vecPoint[i].m_dY;
        }
        //    //循环四边形的四个点
        //    for(int i = 0; i < 4; i++)
        //    {
        //        if(dLeft > stuData.m_stuQuardrangle.m_arrayPoint[i].m_dX)
        //            dLeft = stuData.m_stuQuardrangle.m_arrayPoint[i].m_dX;
        //        if(dRight < stuData.m_stuQuardrangle.m_arrayPoint[i].m_dX)
        //            dRight = stuData.m_stuQuardrangle.m_arrayPoint[i].m_dX;
        //        if(dBottom > stuData.m_stuQuardrangle.m_arrayPoint[i].m_dY)
        //            dBottom = stuData.m_stuQuardrangle.m_arrayPoint[i].m_dY;
        //        if(dTop < stuData.m_stuQuardrangle.m_arrayPoint[i].m_dY)
        //            dTop = stuData.m_stuQuardrangle.m_arrayPoint[i].m_dY;
        //    }
        //    //圆的范围的确定
        //    if(dLeft > stuData.m_stuRound.m_pointCenter.m_dX - stuData.m_stuRound.m_dRadius)
        //        dLeft = stuData.m_stuRound.m_pointCenter.m_dX - stuData.m_stuRound.m_dRadius;
        //    if(dRight < stuData.m_stuRound.m_pointCenter.m_dX + stuData.m_stuRound.m_dRadius)
        //        dRight = stuData.m_stuRound.m_pointCenter.m_dX + stuData.m_stuRound.m_dRadius;
        //    if(dTop < stuData.m_stuRound.m_pointCenter.m_dY + stuData.m_stuRound.m_dRadius)
        //        dTop = stuData.m_stuRound.m_pointCenter.m_dY + stuData.m_stuRound.m_dRadius;
        //    if(dBottom > stuData.m_stuRound.m_pointCenter.m_dY - stuData.m_stuRound.m_dRadius)
        //        dBottom = stuData.m_stuRound.m_pointCenter.m_dY - stuData.m_stuRound.m_dRadius;
        //    //多边形范围的确定
        //    CdRect recBound = stuData.m_stuPolygon.GetBoundRect();
        //    if(dLeft > recBound.m_dLeft)
        //        dLeft = recBound.m_dLeft;
        //    if(dRight < recBound.m_dRight)
        //        dRight = recBound.m_dRight;
        //    if(dTop < recBound.m_dTop)
        //        dTop = recBound.m_dTop;
        //    if(dBottom > recBound.m_dBottom)
        //        dBottom = recBound.m_dBottom;
        //辅助线的循环
        for(uint i = 0; i < stuData.m_vecAssisLine.size(); i++)
        {
            if(dLeft > stuData.m_vecAssisLine[i].m_pointA.m_dX)
                dLeft = stuData.m_vecAssisLine[i].m_pointA.m_dX;
            if(dLeft > stuData.m_vecAssisLine[i].m_pointB.m_dX)
                dLeft = stuData.m_vecAssisLine[i].m_pointB.m_dX;
            if(dRight < stuData.m_vecAssisLine[i].m_pointA.m_dX)
                dRight = stuData.m_vecAssisLine[i].m_pointA.m_dX;
            if(dRight < stuData.m_vecAssisLine[i].m_pointB.m_dX)
                dRight = stuData.m_vecAssisLine[i].m_pointB.m_dX;

            if(dTop < stuData.m_vecAssisLine[i].m_pointA.m_dY)
                dTop = stuData.m_vecAssisLine[i].m_pointA.m_dY;
            if(dTop < stuData.m_vecAssisLine[i].m_pointB.m_dY)
                dTop = stuData.m_vecAssisLine[i].m_pointB.m_dY;
            if(dBottom > stuData.m_vecAssisLine[i].m_pointA.m_dY)
                dBottom = stuData.m_vecAssisLine[i].m_pointA.m_dY;
            if(dBottom > stuData.m_vecAssisLine[i].m_pointB.m_dY)
                dBottom = stuData.m_vecAssisLine[i].m_pointB.m_dY;
        }
        //变压器差动线的循环
        for(uint i = 0; i < stuData.m_vecTranLine.size(); i++)
        {
            if(dLeft > stuData.m_vecTranLine[i].m_pointA.m_dX)
                dLeft = stuData.m_vecTranLine[i].m_pointA.m_dX;
            if(dLeft > stuData.m_vecTranLine[i].m_pointB.m_dX)
                dLeft = stuData.m_vecTranLine[i].m_pointB.m_dX;
            if(dRight < stuData.m_vecTranLine[i].m_pointA.m_dX)
                dRight = stuData.m_vecTranLine[i].m_pointA.m_dX;
            if(dRight < stuData.m_vecTranLine[i].m_pointB.m_dX)
                dRight = stuData.m_vecTranLine[i].m_pointB.m_dX;

            if(dTop < stuData.m_vecTranLine[i].m_pointA.m_dY)
                dTop = stuData.m_vecTranLine[i].m_pointA.m_dY;
            if(dTop < stuData.m_vecTranLine[i].m_pointB.m_dY)
                dTop = stuData.m_vecTranLine[i].m_pointB.m_dY;
            if(dBottom > stuData.m_vecTranLine[i].m_pointA.m_dY)
                dBottom = stuData.m_vecTranLine[i].m_pointA.m_dY;
            if(dBottom > stuData.m_vecTranLine[i].m_pointB.m_dY)
                dBottom = stuData.m_vecTranLine[i].m_pointB.m_dY;
        }
        //取得图形边界
        CdRect recBound = stuRectAreaBound;
        if(dLeft > recBound.m_dLeft)
            dLeft = recBound.m_dLeft;
        if(dRight < recBound.m_dRight)
            dRight = recBound.m_dRight;
        if(dTop < recBound.m_dTop)
            dTop = recBound.m_dTop;
        if(dBottom > recBound.m_dBottom)
            dBottom = recBound.m_dBottom;
        //坐标系比内部元素大出1/20
        stuData.m_stuCoordinate.m_dBottom = dBottom * G_EnvironmentalVaraible::m_dCoordDataRatio;
        stuData.m_stuCoordinate.m_dTop = dTop * G_EnvironmentalVaraible::m_dCoordDataRatio;
        stuData.m_stuCoordinate.m_dLeft = dLeft * G_EnvironmentalVaraible::m_dCoordDataRatio;
        stuData.m_stuCoordinate.m_dRight = dRight * G_EnvironmentalVaraible::m_dCoordDataRatio;

    }
}
