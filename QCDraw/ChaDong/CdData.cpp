#include "CdData.h"
#include "DataAdaptor.h"

CdData::CdData(int width,int height) :
    _size(width,height)
{
    m_strYCoordText = "jX";
    m_strXCoordText = "R";
    m_enuShapeType = TypeUnknown;

    m_iBlank = 5;

    m_stuQtConvert.SetData(m_stuCoordinate,
                                          CdRect(0 + m_iBlank, 0 + m_iBlank,
                                                 height - m_iBlank, width - m_iBlank));
}
CdData::CdData()
{
    m_strYCoordText = "jX";
    m_strXCoordText = "R";
    m_enuShapeType = TypeUnknown;

    m_iBlank = 5;
}

CdData::CdData(const CdData &cdData)
{
    m_vecAssisLine = cdData.m_vecAssisLine;
    m_stuCoordinate = cdData.m_stuCoordinate;
    m_stuQuardrangle = cdData.m_stuQuardrangle;
    m_stuRound = cdData.m_stuRound;
    m_vecPoint = cdData.m_vecPoint;
    m_stuPolygon = cdData.m_stuPolygon;
    m_stuRectAreaBound = cdData.m_stuRectAreaBound;
    m_stuRectPointBound = cdData.m_stuRectPointBound;
    m_vecRound = cdData.m_vecRound;//圆特性图形列表
    m_vecQuardangle = cdData.m_vecQuardangle;//四边形特性图形列表
    m_vecPolygon = cdData.m_vecPolygon;//多边形图形列表
    m_vecTranLine = cdData.m_vecTranLine;
    m_mapAssisText = cdData.m_mapAssisText;
    m_strXCoordText = cdData.m_strXCoordText;
    m_strYCoordText = cdData.m_strYCoordText;
    m_vecTranPoint = cdData.m_vecTranPoint;
    m_vecInvisiblePoint = cdData.m_vecInvisiblePoint;
    m_vecPointChaDong = cdData.m_vecPointChaDong;
    m_enuShapeType = cdData.m_enuShapeType;
    m_vecAddedLine = cdData.m_vecAddedLine;
    m_vecAddedPoint = cdData.m_vecAddedPoint;
}

CdData &CdData::operator =(const CdData &cdData)
{
    m_vecAssisLine = cdData.m_vecAssisLine;
    m_stuCoordinate = cdData.m_stuCoordinate;
    m_stuQuardrangle = cdData.m_stuQuardrangle;
    m_stuRound = cdData.m_stuRound;
    m_vecArc = cdData.m_vecArc;
    m_vecPoint = cdData.m_vecPoint;
    m_stuPolygon = cdData.m_stuPolygon;
    m_stuRectAreaBound = cdData.m_stuRectAreaBound;
    m_stuRectPointBound = cdData.m_stuRectPointBound;
    m_vecRound = cdData.m_vecRound;//圆特性图形列表
    m_vecQuardangle = cdData.m_vecQuardangle;//四边形特性图形列表
    m_vecPolygon = cdData.m_vecPolygon;//多边形图形列表
    m_vecTranLine = cdData.m_vecTranLine;
    m_mapAssisText = cdData.m_mapAssisText;
    m_strXCoordText = cdData.m_strXCoordText;
    m_strYCoordText = cdData.m_strYCoordText;
    m_vecTranPoint = cdData.m_vecTranPoint;
    m_vecInvisiblePoint = cdData.m_vecInvisiblePoint;
    m_vecPointChaDong = cdData.m_vecPointChaDong;
    m_enuShapeType = cdData.m_enuShapeType;
    m_vecAddedLine = cdData.m_vecAddedLine;
    m_vecAddedPoint = cdData.m_vecAddedPoint;
    _size = cdData._size;
    return *this;
}

void CdData::Clear()
{
    Clear(_size);
}

void CdData::Clear(const QSize& sz)
{
    _size = sz;
    DataAdaptor m_stuDataAdaptor;
    *this = m_stuDataAdaptor.getCdData();
    CdDataCalculateTool::CalculateCoordinate(*this, false);
    m_stuQtConvert.SetData(m_stuCoordinate,
                                          CdRect(0 + m_iBlank, 0 + m_iBlank,
                                                 sz.height() - m_iBlank, sz.width() - m_iBlank));
    m_stuQtConvert.ResetBigSizeParam();
}

void CdData::calcArea(bool bflag,bool bSetBig)
{
    calcArea(_size,bflag,bSetBig);
}

void CdData::calcArea(const QSize& sz, bool bflag,bool bSetBig)
{
    CdDataCalculateTool::CalculateCoordinate(*this, bflag);
    m_stuQtConvert.SetData(m_stuCoordinate,
                                          CdRect(0 + m_iBlank, 0 + m_iBlank,
                                                 sz.height() - m_iBlank, sz.width() - m_iBlank));
    if(bSetBig)
    {
        m_stuQtConvert.SetBigSizeData(m_stuRectAreaBound, m_stuRectPointBound, m_stuCoordinate);
    }
}

void CdData::drawSmallEntity(Qt_Painter& painter,const QSize& sz)
{
    CdPoint pt;
    int  iBlank = m_iBlank;
    m_iBlank = 0;
    drawEntity(painter,sz,0,pt,false);
    m_iBlank = iBlank;
    //QPainter smallPainter(&pix);
   // smallPainter.drawPixmap(pix.rect(),tmpPix,tmpPix.rect());
}

void CdData::drawEntity(Qt_Painter& painter,const QSize& sz,int iCurrentPointIndex,const CdPoint& pointMouse,bool bDrawText)
{

    m_stuQtConvert.SetData(m_stuCoordinate,
                           CdRect(0 + m_iBlank, 0 + m_iBlank,
                                  sz.height() - m_iBlank, sz.width() - m_iBlank));

    painter.DrawBackGround();
    painter.DrawSubLine(30);


    //painter.DrawCoordinate(m_stuCoordinate);
    CdCoordinate coord;
    coord.m_dBottom = m_stuQtConvert.MapPointFromSysToLogic(CdPoint(sz.width() - m_iBlank,sz.height() - m_iBlank)).m_dY;
    coord.m_dLeft = m_stuQtConvert.MapPointFromSysToLogic(CdPoint(0 + m_iBlank, 0 + m_iBlank)).m_dX;
    coord.m_dRight = m_stuQtConvert.MapPointFromSysToLogic(CdPoint(sz.width() - m_iBlank, sz.height() - m_iBlank)).m_dX;
    coord.m_dTop = m_stuQtConvert.MapPointFromSysToLogic(CdPoint(0 + m_iBlank, 0 + m_iBlank)).m_dY;
    painter.DrawCoordinate(coord,bDrawText, m_strXCoordText, m_strYCoordText);

    switch (m_enuShapeType)
    {
    case TypeXianLuChaDong:
        painter.DrawXianLuChaDongQuXian(m_vecTranPoint);
        painter.DrawVecLines(m_vecTranLine);
        painter.DrawAssisLine(m_vecAssisLine);
        painter.DrawPointLine(m_vecPoint, iCurrentPointIndex, this);
        painter.DrawPointLine(m_vecPointChaDong, iCurrentPointIndex, this);
        if(bDrawText)
        {
            painter.DrawCoordTextBySysPoint(pointMouse, "", true, painter.m_colorCoordnate);
        }
        break;
    case TypeMuXianChaDong:
        painter.DrawMuXianChaDongQuXian(m_vecTranPoint);
        painter.DrawVecLines(m_vecTranLine);
        painter.DrawAssisLine(m_vecAssisLine);
        painter.DrawPointLine(m_vecPoint, iCurrentPointIndex, this);
        painter.DrawPointLine(m_vecPointChaDong, iCurrentPointIndex, this);
        if(bDrawText)
        {
            painter.DrawCoordTextBySysPoint(pointMouse, "", true, painter.m_colorCoordnate);
        }
        break;
    default:
        for(uint i = 0;  i< m_vecRound.size(); i++)
        {
            painter.DrawCdRound(m_vecRound[i]);
        }
        //painter.DrawCdRound(m_stuRound);
        for(uint i = 0;  i< m_vecPolygon.size(); i++)
        {
            painter.DrawCdPolygon(m_vecPolygon[i]);
        }
        //painter.DrawCdPolygon(m_stuPolygon);
        for(uint i = 0;  i< m_vecQuardangle.size(); i++)
        {
            painter.DrawQuardrangle(m_vecQuardangle[i]);
        }
        for(uint i = 0;  i< m_vecArc.size(); i++)
        {
            painter.DrawCdArc(m_vecArc[i]);
        }
        painter.DrawVecLines(m_vecTranLine);
        painter.DrawAssisLine(m_vecAssisLine);
        painter.DrawPointLine(m_vecPoint, iCurrentPointIndex);
        if(bDrawText)
        {
            painter.DrawCoordTextBySysPoint(pointMouse, "", true, painter.m_colorCoordnate);
            painter.DrawAssisText(m_mapAssisText);
        }

        painter.DrawAddedLine(m_vecAddedLine);
        painter.DrawAddedPoint(m_vecAddedPoint,bDrawText);
        break;
    }
}
