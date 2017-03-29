#include "Qt_Painter.h"
#include "CdData.h"

Qt_Painter::Qt_Painter(QPaintDevice *device, Qt_CoordinateConvert *pConvert)
    : QPainter(device)
    , m_pConvert(pConvert)
{
    bCurrentColorStyle = 0;
    if(bCurrentColorStyle == 0)
    {
        m_colorSubLine = QColor::fromRgb(100, 100, 100);
        m_colorCoordnate = QColor::fromRgb(10, 240, 250);
        m_colorRound = QColor::fromRgb(255, 47, 23);
        m_colorArc = QColor::fromRgb(255, 47, 23);
        m_colorQuardrangle = QColor::fromRgb(255, 47, 23);
        m_colorPoint = QColor::fromRgb(255, 90, 255);
        m_colorPointLine = QColor::fromRgb(79, 226, 52);
        m_colorTranFillVecLine = QColor::fromRgb(255, 47, 23, 150);
        m_colorTranVecLine = QColor::fromRgb(255, 47, 23);
        m_colorBackGround = QColor::fromRgb(30, 30, 30);
        m_colorPointLineText = m_colorPointLine;
    }
    else
    {
        m_colorSubLine = QColor::fromRgb(100, 100, 100);
        m_colorCoordnate = QColor::fromRgb(10, 240, 250);
        m_colorRound = QColor::fromRgb(255, 47, 23);
        m_colorArc = QColor::fromRgb(255, 47, 23);
        m_colorQuardrangle = QColor::fromRgb(255, 47, 23);
        m_colorTranFillVecLine = QColor::fromRgb(255, 47, 23, 150);
        m_colorPoint = QColor::fromRgb(255, 90, 255);
        m_colorPointLine = QColor::fromRgb(79, 226, 52);
        m_colorTranVecLine = QColor::fromRgb(255, 47, 23);
        m_colorBackGround = QColor::fromRgb(255, 255, 255);
        m_colorPointLineText = m_colorPointLine;
    }
    //绘制锯齿处理开关
    setRenderHint(QPainter::Antialiasing);
}

void Qt_Painter::DrawSubLine(int iInterval)
{
    save();
    //绘制锯齿处理开关
    setRenderHint(QPainter::Antialiasing, false);
    QPen penSubLine;
    penSubLine.setColor(m_colorSubLine);
    penSubLine.setStyle(Qt::DashLine);
    setPen(penSubLine);
    int iXOffset = (int)(m_pConvert->MapPointFromLogicToSys(CdPoint(0, 0))).m_dX % iInterval;
    int iYOffset = (int)(m_pConvert->MapPointFromLogicToSys(CdPoint(0, 0))).m_dY % iInterval;
    //LOG_INFO(m_pConvert->MapPointFromLogicToSys(CdPoint(0, 0)).ToString());
    //LOG_INFO(iXOffset).Log(",").Log(iYOffset).Log("\n");
    //辅助线数量为坐标系宽度（高度）/间隔
    int iXCount = device()->width() / iInterval;
    int iYCount = device()->height() / iInterval;
    //绘制辅助线，间隔为interval，采用实际坐标计算
    for(int i = 0; i < iXCount + 2 || i < iYCount + 2; i++)
    {
        drawLine(0, i * iInterval + iYOffset, device()->width(), i * iInterval + iYOffset);
        //If_Log::GetInstance()->Log(CdPoint(0, i * iInterval + iXOffset).ToString()).Log("\n");
        drawLine(i * iInterval + iXOffset, 0, i * iInterval + iXOffset, device()->height());
        //If_Log::GetInstance()->Log(CdPoint(i * iInterval, 0).ToString()).Log("\n");
    }
    restore();
}

void Qt_Painter::DrawCoordinate(const CdCoordinate &coordinate,bool bDrawTxt, const string & strXCoordText, const string & strYCoordText)
{
    save();
    if(bDrawTxt)
    {
        DrawCoordLine(CdPoint(coordinate.m_dLeft, 0), CdPoint(coordinate.m_dRight, 0), true, 6, strXCoordText);
        DrawCoordLine(CdPoint(0, coordinate.m_dBottom), CdPoint(0, coordinate.m_dTop), false, 6, strYCoordText);
    }
    else
    {
        DrawCoordLine(CdPoint(coordinate.m_dLeft, 0), CdPoint(coordinate.m_dRight, 0), true, 6, "");
        DrawCoordLine(CdPoint(0, coordinate.m_dBottom), CdPoint(0, coordinate.m_dTop), false, 6, "");
    }
    //计算原点坐标，显示坐标轴原点
    if(bDrawTxt)
    {
        CdPoint pointOri = m_pConvert->MapPointFromLogicToSys(CdPoint(0, 0));
        pointOri.m_dX += 0;
        pointOri.m_dY += 14;
        DrawCoordTextBySysPoint(pointOri, "0", false, m_colorCoordnate);
    }
    restore();
}

void Qt_Painter::DrawCdArc(const CdArc &arc)
{
    //设置画笔
    save();
    QPen penArc;
    penArc.setColor(m_colorArc);
    penArc.setWidth(2);
    setPen(penArc);
    //根据圆心及半径构建圆的左上及右下点
    const float& tmpRadius = arc.m_radius;
    CdPoint pointLeftTopTmp = CdPoint(arc.m_ptCenter.m_dX - tmpRadius,
                                      arc.m_ptCenter.m_dY + tmpRadius);
    CdPoint pointRightBottomTmp = CdPoint(arc.m_ptCenter.m_dX + tmpRadius,
                                          arc.m_ptCenter.m_dY - tmpRadius);
    //映射点到系统坐标系
    pointLeftTopTmp = m_pConvert->MapPointFromLogicToSys(pointLeftTopTmp,true);
    pointRightBottomTmp = m_pConvert->MapPointFromLogicToSys(pointRightBottomTmp,true);
    QRectF tmpRect(QPointF(pointLeftTopTmp.m_dX, pointLeftTopTmp.m_dY),
                   QPointF(pointRightBottomTmp.m_dX, pointRightBottomTmp.m_dY));
    //tmpRect = tmpRect.normalized();
    //绘制
    drawArc(tmpRect,arc.m_startAngle * 16,arc.m_spanAngle * 16);
    restore();
}

void Qt_Painter::DrawCdRound(const CdRound &round)
{
    //设置画笔
    save();
    QPen penRound;
    penRound.setColor(m_colorRound);
    penRound.setWidth(2);
    setPen(penRound);
    //根据圆心及半径构建圆的左上及右下点
    CdPoint pointLeftTopTmp = CdPoint(round.m_pointCenter.m_dX - round.m_dRadius,
                                      round.m_pointCenter.m_dY + round.m_dRadius);
    CdPoint pointRightBottomTmp = CdPoint(round.m_pointCenter.m_dX + round.m_dRadius,
                                          round.m_pointCenter.m_dY - round.m_dRadius);
    //映射点到系统坐标系
    pointLeftTopTmp = m_pConvert->MapPointFromLogicToSys(pointLeftTopTmp);
    pointRightBottomTmp = m_pConvert->MapPointFromLogicToSys(pointRightBottomTmp);
    //确定画笔
    if(round._isDot)
    {
        QPen tmpPen = this->pen();
        tmpPen.setStyle(Qt::DashLine);
        this->setPen(tmpPen);
    }
    //绘制
    drawEllipse(QRect(QPoint(pointLeftTopTmp.m_dX, pointLeftTopTmp.m_dY),
                      QPoint(pointRightBottomTmp.m_dX, pointRightBottomTmp.m_dY)));
    restore();
}

void Qt_Painter::DrawCoordLine(const CdPoint &pointStart, const CdPoint &pointEnd,
                               bool bIsHor, int iArrowLength, const string &strMark)
{
    /*
     *画箭头线其实是三根线，
     *一条主线，两条箭头辅线，
     *辅线以主线的结束点为起点，向主线两侧45方向画两条长度为iArrowLength的线段
     *所以会有两个辅助点，点A和点B，点A与点B的坐标是与系统坐标系相关的点
     *所以在计算后需要进一步进行坐标系的映射操作
     */
    save();
    QPen penCoordLine;
    penCoordLine.setColor(m_colorCoordnate);
    penCoordLine.setStyle(Qt::SolidLine);
    penCoordLine.setWidth(3);
    setPen(penCoordLine);

    CdPoint pointStartTmp;
    CdPoint pointEndTmp;
    pointStartTmp = m_pConvert->MapPointFromLogicToSys(pointStart);
    pointEndTmp = m_pConvert->MapPointFromLogicToSys(pointEnd);
    drawLine((int)pointStartTmp.m_dX, (int)pointStartTmp.m_dY,
             (int)pointEndTmp.m_dX, (int)pointEndTmp.m_dY);
    if(bIsHor)
    {
        DrawTriangle(pointEndTmp, iArrowLength, 0, 30, m_colorCoordnate, m_colorCoordnate);
        if(strMark.size() > 0)
            DrawCoordTextBySysPoint(CdPoint(pointEndTmp.m_dX, pointEndTmp.m_dY + 17), QString::fromStdString(strMark), false, m_colorCoordnate);
    }
    else
    {
        DrawTriangle(pointEndTmp, iArrowLength, 90, 30, m_colorCoordnate, m_colorCoordnate);
        if(strMark.size() > 0)
            DrawCoordTextBySysPoint(CdPoint(pointEndTmp.m_dX + 10, pointEndTmp.m_dY), QString::fromStdString(strMark), false, m_colorCoordnate);
    }
    restore();
}

void Qt_Painter:: DrawTriangle(CdPoint pointVertex, double dSize, double dAngleX, double dAngleTri, QColor penColor, QColor brushColor)
{
    //求出上顶点到底边垂线与底边的交点
    double dXDiff = dSize * cos(dAngleX * M_PI / 180);
    double dYDiff = dSize * sin(dAngleX * M_PI / 180);
    CdPoint pointHeight(pointVertex.m_dX - dXDiff, pointVertex.m_dY + dYDiff);
    //求出底边两个顶点
    dXDiff = dSize * tan(dAngleTri * M_PI / 180) * cos((90 - dAngleX) * M_PI / 180);
    dYDiff = dSize * tan(dAngleTri * M_PI / 180) * sin((90 - dAngleX) * M_PI / 180);
    CdPoint pointLeft(pointHeight.m_dX - dXDiff, pointHeight.m_dY - dYDiff);
    CdPoint pointRight(pointHeight.m_dX + dXDiff, pointHeight.m_dY + dYDiff);
    save();

    QPen pen;
    pen.setColor(penColor);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(brushColor);
    setPen(pen);
    setBrush(brush);

    if (isnan(pointVertex.m_dX)) {
         pointVertex.m_dX = 0;
    }
    if (isnan(pointVertex.m_dY)) {
        pointVertex.m_dY = 0;
    }
    if (isnan(pointLeft.m_dX)) {
        pointLeft.m_dX = 0;
    }
    if (isnan(pointLeft.m_dY)) {
        pointLeft.m_dY = 0;
    }
    if (isnan(pointRight.m_dX)) {
        pointRight.m_dX = 0;
    }
    if (isnan(pointRight.m_dY)) {
        pointRight.m_dY = 0;
    }

    QPainterPath path;
    path.moveTo(pointVertex.m_dX, pointVertex.m_dY);
    path.lineTo(pointLeft.m_dX, pointLeft.m_dY);
    path.lineTo(pointRight.m_dX, pointRight.m_dY);
    path.lineTo(pointVertex.m_dX, pointVertex.m_dY);
    drawPath(path);
    restore();
}

QString Qt_Painter::PrecNumber(QString strNum, int i)
{
    int iPos = strNum.indexOf('.');
    if(iPos != -1)
    {
        return strNum.left(iPos + i + 1);
    }
    else
    {
        return strNum + ".00";
    }
}

QLineF Qt_Painter::GetPercentLine(const QLineF &qline, int iPercent, bool bBeginFromA) const
{
    QLineF qlineRet;
    if(iPercent > 100)
        iPercent = 100;
    if(iPercent < 0)
        iPercent = 0;
    if(!bBeginFromA)
        iPercent = 100 - iPercent;
    //求出线的角度(弧度单位)
    double dAngle = atan2((qline.p2().ry() - qline.p1().ry()), (qline.p1().rx() - qline.p2().rx()));
    double dPercentLength = qline.length() * iPercent / 100;
    //XY方向的差值
    double dXOffset = dPercentLength * cos(dAngle);
    double dYOffset = dPercentLength * sin(dAngle);
    qlineRet.setP1(qline.p1());
    qlineRet.setP2(QPointF(qline.p1().rx() - dXOffset, qline.p1().ry() + dYOffset));
    return qlineRet;
}

QPointF Qt_Painter::GetQPoint(const CdPoint &point)
{
    return QPointF(point.m_dX, point.m_dY);
}



void Qt_Painter::DrawQuardrangle(CdQuardrangle &quardrangle)
{
    //设置画笔
    save();
    QPen penQuardrangle;
    penQuardrangle.setWidth(2);
    penQuardrangle.setColor(m_colorQuardrangle);
    setPen(penQuardrangle);
    //重新组织四边形
    if(quardrangle.Organize())
    {
        //将数据点映射到系统坐标系中
        CdPoint arrayPoint[4];
        for(int i = 0; i < 4; i++)
        {
            arrayPoint[i] = m_pConvert->MapPointFromLogicToSys(quardrangle.m_arrayPoint[i]);
        }
        //绘制
        for(int i = 0; i < 4; i++)
        {
            drawLine(arrayPoint[i].m_dX, arrayPoint[i].m_dY,
                     arrayPoint[(i + 1) % 4].m_dX, arrayPoint[(i + 1) % 4].m_dY);
        }
    }
    restore();
}

void Qt_Painter::DrawPointLine(const vector<CdPoint> &vecPoint, unsigned int iIndex, const CdData * pData)
{
    //如果参数为-1理解为不画
    if((unsigned int)-1 == iIndex)
    {
        return;
    }
    if(vecPoint.size() < 1)
    {
        return;
    }
    //变量定义
    int iRoundWidth = 2;
    //越界判定
    if(iIndex / 100 >= vecPoint.size())
    {
        iIndex = vecPoint.size() * 100;
    }
    //映射点到系统坐标系
    vector<CdPoint> vecPointTmp;
    for(unsigned int i = 0; i <= iIndex; i++)
    {
        CdPoint pointTmp = m_pConvert->MapPointFromLogicToSys(vecPoint[i]);
        vecPointTmp.push_back(pointTmp);
    }
    //绘制点的过程其实是将点绘制为一个圆，并绘制点与点之间的折线
    //设置画圆的画笔及画刷
    QPen penPoint;
    penPoint.setColor(m_colorPoint);
    penPoint.setWidth(3);
    QBrush brushPoint;
    brushPoint.setColor(m_colorPoint);
    brushPoint.setStyle(Qt::SolidPattern);
    setPen(penPoint);
    setBrush(brushPoint);
    //绘制当前最后一个点的动作是动画效果
    int iCurrrntPointNum = iIndex / 100;
    if(iCurrrntPointNum > 0)
    {
        QPen penPointLine;
        penPointLine.setColor(m_colorPointLine);
        penPointLine.setWidth(2);
        setPen(penPointLine);
        QLineF qlineTemp(vecPointTmp[iCurrrntPointNum - 1].m_dX, vecPointTmp[iCurrrntPointNum - 1].m_dY,
                vecPointTmp[iCurrrntPointNum].m_dX, vecPointTmp[iCurrrntPointNum].m_dY);
        drawLine(GetPercentLine(qlineTemp, iIndex % 100));
    }
    //线绘制折线，然后绘制点，这样可以保证点不被折线压住
    for(unsigned int i = 0; i /*<=2013年10月14日改为小于号最后一个点特殊处理*/< iIndex / 100; i++)
    {
        //当点数量大于2时，绘制折线
        if(i > 0)
        {
            QPen penPointLine;
            penPointLine.setColor(m_colorPointLine);
            penPointLine.setWidth(2);
            setPen(penPointLine);
            QLineF qlineTemp(vecPointTmp[i - 1].m_dX, vecPointTmp[i - 1].m_dY,
                    vecPointTmp[i].m_dX, vecPointTmp[i].m_dY);
            drawLine(qlineTemp);
        }

        //绘制点
        setPen(penPoint);
        setBrush(brushPoint);
        drawEllipse(QPoint(vecPointTmp[i].m_dX, vecPointTmp[i].m_dY), iRoundWidth, iRoundWidth);
    }
    if(pData != NULL)
    {
        map<string, CdPoint> mapAssisText = pData->m_mapAssisText;
        for(map<string, CdPoint>::const_iterator it = pData->m_mapAssisText.begin(); it != pData->m_mapAssisText.end(); it++)
        {
            QString strKey = QString::fromStdString(it->first);
            if(strKey.indexOf('l') > 0)
            {
                mapAssisText.erase(strKey.toStdString());
            }
        }
        if(iCurrrntPointNum > 0)
        {
            mapAssisText = pData->m_mapAssisText;
            for(map<string, CdPoint>::const_iterator it = pData->m_mapAssisText.begin(); it != pData->m_mapAssisText.end(); it++)
            {
                QString strKey = QString::fromStdString(it->first);
                if(strKey.indexOf('l') > 0)
                {
                    mapAssisText.erase(strKey.toStdString());
                    break;
                }
            }
            if(pData->m_vecPointChaDong.size() > 0)
                DrawCoordTextByLogicPoint(pData->m_vecPointChaDong[0], "", true, m_colorPointLineText);
        }
        if(iCurrrntPointNum > (int)vecPoint.size() - 1)
        {
            mapAssisText = pData->m_mapAssisText;
            if(pData->m_vecPointChaDong.size() > 0)
                DrawCoordTextByLogicPoint(pData->m_vecPointChaDong[pData->m_vecPointChaDong.size() - 1], "", true, m_colorPointLineText);
        }
        DrawAssisText(mapAssisText);
        //当差动点首点和末点距离较近时，只显示第一个点的坐标  --郭晓刚
        if(pData->m_vecPoint.size() > 0)
        {
            map<string, CdPoint> mapAssisPointText;
            string strText = "";
            if(iCurrrntPointNum > 0)
            {
                CdPoint pointTmp =pData->m_vecPoint[0];
                strText = "("+ QString::number(pointTmp.m_dX).toStdString() + "," +  QString::number(pointTmp.m_dY).toStdString() + ")";
                mapAssisPointText.insert(make_pair("" + strText, pointTmp));
            }
            if(iCurrrntPointNum > (int)pData->m_vecPoint.size() - 1)
            {
                int iFontWidth = fontMetrics().width(QString::fromStdString(strText));
                int iFontHeight = fontMetrics().height();
                CdPoint pointa = m_pConvert->MapPointFromLogicToSys(pData->m_vecPoint[0]);
                CdPoint pointb = m_pConvert->MapPointFromLogicToSys(pData->m_vecPoint[pData->m_vecPoint.size() - 1]);
                double ax = pointa.m_dX;
                double ay = pointa.m_dY;
                double bx = pointb.m_dX;
                double by = pointb.m_dY;
                if(fabs(ax-bx/*pointa.m_dX - pointb.m_dX*/)>iFontWidth||fabs(/*pointb.m_dX - pointb.m_dY*/ay-by)>iFontHeight){
                    CdPoint pointTmp = pData->m_vecPoint[pData->m_vecPoint.size() - 1];
                    strText = "(" + QString::number(pointTmp.m_dX).toStdString() + "," +  QString::number(pointTmp.m_dY).toStdString() + ")";
                    mapAssisPointText.insert(make_pair("" + strText, pointTmp));
                }
            }
            DrawAssisText(mapAssisPointText);
        }
    }
    else
    {
        CdPoint pointTempa = m_pConvert->MapPointFromLogicToSys(vecPoint[0]);
        CdPoint pointTempb = m_pConvert->MapPointFromLogicToSys(vecPoint[vecPoint.size() - 1]);
        if(iCurrrntPointNum > 0)
        {
            //pointTemp.m_dY -= 5;
            DrawCoordTextBySysPoint(pointTempa, "", true, m_colorPointLineText);
        }
        if(iCurrrntPointNum > (int)vecPoint.size() - 1)
        {
            //pointTemp.m_dY -= 5;
            QString strText = "";
            strText +="(" + PrecNumber(QString::number(vecPoint[vecPoint.size() - 1].m_dX)) + "," + PrecNumber(QString::number(vecPoint[vecPoint.size() - 1].m_dY)) + ")";
            int iFontWidth = fontMetrics().width(strText);
            int iFontHeight = fontMetrics().height();
            double ax = pointTempa.m_dX;
            double ay = pointTempa.m_dY;
            double bx = pointTempb.m_dX;
            double by = pointTempb.m_dY;
            if(fabs(ax-bx/*pointa.m_dX - pointb.m_dX*/)>iFontWidth||fabs(/*pointb.m_dX - pointb.m_dY*/ay-by)>iFontHeight)
                DrawCoordTextBySysPoint(pointTempb, strText, false, m_colorPointLineText);
        }
    }
}

void Qt_Painter::DrawCoordTextBySysPoint(const CdPoint &point, const QString & strPointName, bool bNeedPoint, QColor color)
{
    save();
    QFont font;
    font.setPointSize(12);
    setFont(font);
    QPen pen;
    pen.setColor(color);
    setPen(pen);
    QString strText;
    strText = strPointName;
    if(bNeedPoint)
    {
        CdPoint pointTmp = m_pConvert->MapPointFromSysToLogic(point);
        if(pointTmp.m_dY < 0.0000000001) {
            pointTmp.m_dY = 0.00000000;
        }
        strText += "(" + PrecNumber(QString::number(pointTmp.m_dX)) + "," + PrecNumber(QString::number(pointTmp.m_dY)) + ")";
    }
    //取得字符串的宽高，当坐标贴近绘图区域右上角时，将字符串显示在坐标点的左下
    int iFontWidth = fontMetrics().width(strText);
    int iFontHeight = fontMetrics().height();
    CdPoint pointTmp = point;
    // 将字符串显示在坐标右下 若显示字符串长度不够则显示在左上 ---郭晓刚
    if(point.m_dX+iFontWidth> device()->width())
        pointTmp.m_dX -= iFontWidth;
    else
        pointTmp.m_dY += iFontHeight;

    if(pointTmp.m_dX > 0)
    {
        iFontWidth = 0;
    }
    if(pointTmp.m_dY - iFontHeight > 0)
    {
        iFontHeight = 0;
    }
    drawText(pointTmp.m_dX + iFontWidth, pointTmp.m_dY + iFontHeight, strText);

    restore();
}

void Qt_Painter::DrawCoordTextByLogicPoint(const CdPoint &point, const QString &strPointName, bool bNeedPoint,  QColor color)
{
    save();
    QFont font;
    font.setPointSize(12);
    setFont(font);
    QPen pen;
    pen.setColor(color);
    setPen(pen);
    CdPoint pointTmp = m_pConvert->MapPointFromLogicToSys(point);
    QString strText;
    strText = strPointName;
    if(bNeedPoint)
    {
        strText += "(" + PrecNumber(QString::number(point.m_dX)) + "," + PrecNumber(QString::number(point.m_dY)) + ")";
    }
    //取得字符串的宽高，当坐标贴近绘图区域右上角时，将字符串显示在坐标点的左下
    int iFontWidth = fontMetrics().width(strText);
    int iFontHeight = fontMetrics().height();
    pointTmp.m_dX -= iFontWidth;
    //2013年10月29日改为默认显示在左上，贴边则显示到右下
    if(pointTmp.m_dX > 0)
    {
        iFontWidth = 0;
    }
    if(pointTmp.m_dY - iFontHeight > 0)
    {
        iFontHeight = 0;
    }

    drawText(pointTmp.m_dX + iFontWidth, pointTmp.m_dY + iFontHeight, strText);
    restore();
}

void Qt_Painter::DrawBackGround()
{
    //绘制边框及背景
    save();
    QBrush brush(m_colorBackGround);
    QPen pen(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(QColor::fromRgb(90, 90, 90));
    setBrush(brush);
    setPen(pen);
    drawRect(1, 1, device()->width() - 2, device()->height() - 2);
    restore();
}

void Qt_Painter::DrawAssisLine(const vector<CdLine> &vecAssisLine)
{
    //如果线的数量大于2，认为是四边形的辅助线
    if(vecAssisLine.size() > 2)
    {
        for(uint i = 0; i< vecAssisLine.size(); i++)
        {
            DrawCoordLine(vecAssisLine[i].m_pointA, vecAssisLine[i].m_pointB, false, 0);
            if(0 == i)
            {
                DrawCoordTextByLogicPoint(vecAssisLine[i].m_pointB, "", true, m_colorQuardrangle);
            }
            if(3 == i)
            {
                DrawCoordTextByLogicPoint(vecAssisLine[i].m_pointA, "", true, m_colorQuardrangle);
            }
        }
    }
    //否则，认为是圆的辅助线
    else
    {
        for(uint i = 0; i< vecAssisLine.size(); i++)
        {
            DrawCoordLine(vecAssisLine[i].m_pointA, vecAssisLine[i].m_pointB, false, 0);
            if(0 == i)
            {
                CdPoint pointVertex = vecAssisLine[i].m_pointB;
                pointVertex = m_pConvert->MapPointFromLogicToSys(pointVertex);
                DrawTriangle(pointVertex, 5, 180 * atan2((vecAssisLine[i].m_pointB.m_dY - vecAssisLine[i].m_pointA.m_dY),
                                                         (vecAssisLine[i].m_pointB.m_dX - vecAssisLine[i].m_pointA.m_dX)) / M_PI, 45, m_colorCoordnate, m_colorCoordnate);
                //DrawCoordTextBySysPoint(pointVertex, QString::number(vecAssisLine[i].m_pointA.GetDistanceTo(vecAssisLine[i].m_pointB)), false,
                //                        m_colorRound);
//                DrawCoordTextBySysPoint(pointVertex, QString::number(vecAssisLine[i].m_pointA.GetDistanceTo(vecAssisLine[i].m_pointB)), false,
//                                        m_colorRound);

            }
            if(1 == i)
            {
//                double dAngle = atan2((vecAssisLine[i].m_pointB.m_dY - vecAssisLine[i].m_pointA.m_dY),
//                                      (vecAssisLine[i].m_pointB.m_dX - vecAssisLine[i].m_pointA.m_dX));
//                double dXDiff = vecAssisLine[i].m_pointB.GetDistanceTo(vecAssisLine[i].m_pointA) * cos(dAngle) / 2;

//                DrawCoordTextByLogicPoint(CdPoint(vecAssisLine[i].m_pointA.m_dX + dXDiff, 0 - m_pConvert->MapLenthFromSysToLogic(font().pointSizeF() + 3)),
//                                          QString::number(vecAssisLine[i].m_pointA.m_dX + dXDiff), false, m_colorRound);

                if (1 == vecAssisLine[i].m_type) {
                    CdPoint pointVertex = vecAssisLine[i].m_pointB;
                    pointVertex = m_pConvert->MapPointFromLogicToSys(pointVertex);
                    DrawTriangle(pointVertex, 5, 180 * atan2((vecAssisLine[i].m_pointB.m_dY - vecAssisLine[i].m_pointA.m_dY),
                                                             (vecAssisLine[i].m_pointB.m_dX - vecAssisLine[i].m_pointA.m_dX)) / M_PI, 45, m_colorCoordnate, m_colorCoordnate);
                }
//                double dAngle = atan2((vecAssisLine[i].m_pointB.m_dY - vecAssisLine[i].m_pointA.m_dY),
//                                      (vecAssisLine[i].m_pointB.m_dX - vecAssisLine[i].m_pointA.m_dX));
                //double dXDiff = vecAssisLine[i].m_pointB.GetDistanceTo(vecAssisLine[i].m_pointA) * cos(dAngle) / 2;

                //DrawCoordTextByLogicPoint(CdPoint(vecAssisLine[i].m_pointA.m_dX + dXDiff,0 - m_pConvert->MapLenthFromSysToLogic(font().pointSizeF() + 3)),
               //         QString::number(vecAssisLine[i].m_pointA.m_dX + dXDiff), false, m_colorRound);
            }
        }
    }
}

void Qt_Painter::DrawCdPolygon(const CdPolygon & cdPolygon)
{
    CdPolygon cdPolyTemp;
    for(uint i = 0; i < cdPolygon.m_vecPoint.size(); i++)
    {
        cdPolyTemp.m_vecPoint.push_back(m_pConvert->MapPointFromLogicToSys(cdPolygon.m_vecPoint[i]));
    }
    QPen penQuardrangle;
    penQuardrangle.setWidth(2);
    penQuardrangle.setColor(m_colorQuardrangle);
    setPen(penQuardrangle);
    int iCount = cdPolyTemp.m_vecPoint.size();
    for(int i = 0; i < iCount; i++)
    {
        drawLine(cdPolyTemp.m_vecPoint[i].m_dX, cdPolyTemp.m_vecPoint[i].m_dY, cdPolyTemp.m_vecPoint[(i + 1) % iCount].m_dX, cdPolyTemp.m_vecPoint[(i + 1) % iCount].m_dY);
    }
}

void Qt_Painter::DrawVecLines(const vector<CdLine> &vecLines)
{
    QPen penVecLine;
    penVecLine.setWidth(2);
    penVecLine.setColor(m_colorTranVecLine);
    setPen(penVecLine);
    for(uint i = 0; i < vecLines.size(); i++)
    {
        //针对每一根线首先进行坐标转换
        CdPoint pointTempA = m_pConvert->MapPointFromLogicToSys(vecLines[i].m_pointA);
        CdPoint pointTempB = m_pConvert->MapPointFromLogicToSys(vecLines[i].m_pointB);
        drawLine(pointTempA.m_dX, pointTempA.m_dY, pointTempB.m_dX, pointTempB.m_dY);
    }
}

void Qt_Painter::DrawAssisText(const map<string, CdPoint> &vecAssisText)
{
    for(map<string, CdPoint>::const_iterator it = vecAssisText.begin(); it != vecAssisText.end(); it++)
    {
        CdPoint pointSys = m_pConvert->MapPointFromLogicToSys(it->second);
        pointSys.m_dX += 3;
        pointSys.m_dY -= 3;
        DrawCoordTextBySysPoint(pointSys, QString::fromStdString(it->first), false, m_colorPointLineText);
    }
}

void Qt_Painter::DrawAddedPoint(const vector<CdPoint> &vecSBPoint,bool bDrawText)
{
    QPen penPoint;
    penPoint.setColor(m_colorPoint);
    penPoint.setWidth(3);
    QBrush brushPoint;
    brushPoint.setColor(m_colorPoint);
    brushPoint.setStyle(Qt::SolidPattern);
    setPen(penPoint);
    setBrush(brushPoint);
    int iRoundWidth = 2;
    //映射点到系统坐标系
    vector<CdPoint> vecPointTmp;
    for(uint i = 0; i < vecSBPoint.size(); i++)
    {
        CdPoint pointTmp = m_pConvert->MapPointFromLogicToSys(vecSBPoint[i]);
        vecPointTmp.push_back(pointTmp);
    }
    for(uint i = 0; i < vecPointTmp.size(); i++)
    {
        drawEllipse(QPoint(vecPointTmp[i].m_dX, vecPointTmp[i].m_dY), iRoundWidth, iRoundWidth);
        if(bDrawText)
        {
            DrawCoordTextBySysPoint(vecPointTmp[i], "", true, m_colorPointLineText);
        }
    }
}

void Qt_Painter::DrawAddedLine(const vector<CdLine> &vecSBLine)
{
    QPen penLine;
    penLine.setColor(m_colorCoordnate);
    penLine.setStyle(Qt::DotLine);
    penLine.setWidth(2);
    setPen(penLine);
    for(uint i = 0; i < vecSBLine.size(); i++)
    {
        CdPoint pointA = m_pConvert->MapPointFromLogicToSys(vecSBLine[i].m_pointA);
        CdPoint pointB = m_pConvert->MapPointFromLogicToSys(vecSBLine[i].m_pointB);
        drawLine(pointA.m_dX, pointA.m_dY, pointB.m_dX, pointB.m_dY);
    }
}


void Qt_Painter::DrawMuXianChaDongQuXian(const vector<CdPoint> &vecChaDongPoint)
{
    if(vecChaDongPoint.size() == 4)
    {
        vector<CdPoint> vecTmpChaDongPoint = vecChaDongPoint;
        //转换为系统坐标
        vector<CdPoint> vecSysPoint;
        for(uint i = 0; i < vecTmpChaDongPoint.size(); i++)
        {
            vecSysPoint.push_back(m_pConvert->MapPointFromLogicToSys(vecTmpChaDongPoint[i]));
        }

        //数据点边界矩形的右上点
        CdPoint pointDataPointRectRightTop = m_pConvert->MapPointFromLogicToSys(CdPoint(m_pConvert->m_stuCoordinate.m_dRight / G_EnvironmentalVaraible::m_dCoordDataRatio, m_pConvert->m_stuCoordinate.m_dTop /G_EnvironmentalVaraible::m_dCoordDataRatio));
        //计算出射线与边界的交点
        CdPoint pointD;
        CdPoint pointE;
        //先计算出各射线与坐标系左边界的交点
        double dParaLengthX = pointDataPointRectRightTop.m_dX + 30;
        double dDY = vecSysPoint[2].m_dY - ((dParaLengthX - vecSysPoint[2].m_dX) * (vecSysPoint[0].m_dY - vecSysPoint[2].m_dY) / (vecSysPoint[2].m_dX - vecSysPoint[0].m_dX));
        double dEY = vecSysPoint[3].m_dY - ((dParaLengthX - vecSysPoint[3].m_dX) * (vecSysPoint[0].m_dY - vecSysPoint[3].m_dY) / (vecSysPoint[3].m_dX - vecSysPoint[0].m_dX));
        CdPoint pointDX(dParaLengthX, dDY);
        CdPoint pointEX(dParaLengthX, dEY);
        //再计算出各射线与坐标系上边界的交点
        double dParaLengthY = pointDataPointRectRightTop.m_dY - 30;
        double dDX = vecSysPoint[2].m_dX + ((vecSysPoint[2].m_dY - dParaLengthY) / ((vecSysPoint[0].m_dY - vecSysPoint[2].m_dY) / (vecSysPoint[2].m_dX - vecSysPoint[0].m_dX)));
        double dEX = vecSysPoint[3].m_dX + ((vecSysPoint[3].m_dY - dParaLengthY) / ((vecSysPoint[0].m_dY - vecSysPoint[3].m_dY) / (vecSysPoint[3].m_dX - vecSysPoint[0].m_dX)));
        CdPoint pointDY(dDX, dParaLengthY);
        CdPoint pointEY(dEX, dParaLengthY);

        pointD = pointDX.m_dX < pointDY.m_dX ? pointDX : pointDY;
        pointE = pointEX.m_dX < pointEY.m_dX ? pointEX : pointEY;
        CdPoint pointF(dParaLengthX, vecSysPoint[1].m_dY);

        vecSysPoint.push_back(pointD);
        vecSysPoint.push_back(pointE);
        vecSysPoint.push_back(pointF);

        QPen penVecLine;
        penVecLine.setWidth(2);
        penVecLine.setColor(m_colorTranVecLine);
        setPen(penVecLine);
        drawLine(GetQPoint(vecSysPoint[2]), GetQPoint(vecSysPoint[4]));
        drawLine(GetQPoint(vecSysPoint[3]), GetQPoint(vecSysPoint[5]));
        drawLine(GetQPoint(vecSysPoint[2]), GetQPoint(vecSysPoint[3]));

        penVecLine.setWidth(2);
        penVecLine.setColor(m_colorTranVecLine);
        penVecLine.setStyle(Qt::DashLine);
        setPen(penVecLine);
        drawLine(GetQPoint(vecSysPoint[1]), GetQPoint(vecSysPoint[2]));
        drawLine(GetQPoint(vecSysPoint[0]), GetQPoint(vecSysPoint[2]));
        drawLine(GetQPoint(vecSysPoint[0]), GetQPoint(vecSysPoint[3]));
        drawLine(GetQPoint(vecSysPoint[3]), GetQPoint(vecSysPoint[6]));

        penVecLine.setStyle(Qt::NoPen);
        QBrush brush;
        brush.setStyle(Qt::FDiagPattern);
        brush.setColor(m_colorTranFillVecLine);
        setPen(penVecLine);
        setBrush(brush);
        QPolygonF poly;
        poly.push_back(GetQPoint(vecSysPoint[2]));
        poly.push_back(GetQPoint(vecSysPoint[3]));
        poly.push_back(GetQPoint(vecSysPoint[5]));
        poly.push_back(GetQPoint(vecSysPoint[4]));
        drawPolygon(poly);
    }
}

void Qt_Painter::DrawXianLuChaDongQuXian(const vector<CdPoint> &vecChaDongPoint)
{
    if(vecChaDongPoint.size() == 4)
    {
        vector<CdPoint> vecTmpChaDongPoint = vecChaDongPoint;
        //转换为系统坐标
        vector<CdPoint> vecSysPoint;
        for(uint i = 0; i < vecTmpChaDongPoint.size(); i++)
        {
            vecSysPoint.push_back(m_pConvert->MapPointFromLogicToSys(vecTmpChaDongPoint[i]));
        }

        //数据点边界矩形的右上点
        CdPoint pointDataPointRectRightTop = m_pConvert->MapPointFromLogicToSys(CdPoint(m_pConvert->m_stuCoordinate.m_dRight / G_EnvironmentalVaraible::m_dCoordDataRatio, m_pConvert->m_stuCoordinate.m_dTop/G_EnvironmentalVaraible::m_dCoordDataRatio));
        //计算出射线与边界的交点
        CdPoint pointD;
        CdPoint pointE;
        //先计算出各射线与坐标系左边界的交点
        double dParaLengthX = pointDataPointRectRightTop.m_dX + 30;
        double dDY = vecSysPoint[2].m_dY - ((dParaLengthX - vecSysPoint[2].m_dX) * (vecSysPoint[0].m_dY - vecSysPoint[2].m_dY) / (vecSysPoint[2].m_dX - vecSysPoint[0].m_dX));
        double dEY = vecSysPoint[3].m_dY - ((dParaLengthX - vecSysPoint[3].m_dX) * (vecSysPoint[0].m_dY - vecSysPoint[3].m_dY) / (vecSysPoint[3].m_dX - vecSysPoint[0].m_dX));
        CdPoint pointDX(dParaLengthX, dDY);
        CdPoint pointEX(dParaLengthX, dEY);
        //再计算出各射线与坐标系上边界的交点
        double dParaLengthY = pointDataPointRectRightTop.m_dY - 30;
        double dDX = vecSysPoint[2].m_dX + ((vecSysPoint[2].m_dY - dParaLengthY) / ((vecSysPoint[0].m_dY - vecSysPoint[2].m_dY) / (vecSysPoint[2].m_dX - vecSysPoint[0].m_dX)));
        double dEX = vecSysPoint[2].m_dX + ((vecSysPoint[3].m_dY - dParaLengthY) / ((vecSysPoint[0].m_dY - vecSysPoint[3].m_dY) / (vecSysPoint[3].m_dX - vecSysPoint[0].m_dX)));
        CdPoint pointDY(dDX, dParaLengthY);
        CdPoint pointEY(dEX, dParaLengthY);

        pointD = pointDX.m_dX < pointDY.m_dX ? pointDX : pointDY;
        pointE = pointEX.m_dX < pointEY.m_dX ? pointEX : pointEY;
        CdPoint pointF(dParaLengthX, vecSysPoint[1].m_dY);

        vecSysPoint.push_back(pointD);
        vecSysPoint.push_back(pointE);
        vecSysPoint.push_back(pointF);

        QPen penVecLine;
        penVecLine.setWidth(2);
        penVecLine.setColor(m_colorTranVecLine);
        setPen(penVecLine);
        drawLine(GetQPoint(vecSysPoint[2]), GetQPoint(vecSysPoint[4]));
        drawLine(GetQPoint(vecSysPoint[3]), GetQPoint(vecSysPoint[5]));
        drawLine(GetQPoint(vecSysPoint[2]), GetQPoint(vecSysPoint[3]));

        penVecLine.setWidth(2);
        penVecLine.setColor(m_colorTranVecLine);
        penVecLine.setStyle(Qt::DashLine);
        setPen(penVecLine);
        drawLine(GetQPoint(vecSysPoint[1]), GetQPoint(vecSysPoint[2]));
        drawLine(GetQPoint(vecSysPoint[0]), GetQPoint(vecSysPoint[2]));
        drawLine(GetQPoint(vecSysPoint[0]), GetQPoint(vecSysPoint[3]));
        drawLine(GetQPoint(vecSysPoint[3]), GetQPoint(vecSysPoint[6]));

        penVecLine.setStyle(Qt::NoPen);
        QBrush brush;
        brush.setStyle(Qt::FDiagPattern);
        brush.setColor(m_colorTranFillVecLine);
        setPen(penVecLine);
        setBrush(brush);
        QPolygonF poly;
        poly.push_back(GetQPoint(vecSysPoint[2]));
        poly.push_back(GetQPoint(vecSysPoint[3]));
        poly.push_back(GetQPoint(vecSysPoint[5]));
        poly.push_back(GetQPoint(/*pointDataPointRectRightTop*/CdPoint(vecSysPoint[5].m_dX,vecSysPoint[4].m_dY)));
        poly.push_back(GetQPoint(vecSysPoint[4]));
        drawPolygon(poly);
    }
}
