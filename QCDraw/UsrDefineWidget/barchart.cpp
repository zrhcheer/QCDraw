
#include "barchart.h"
#include <iostream>

#define UNUSED(x) (void)x
using namespace std;
#define THRESHOLD 60

BarChart::BarChart(QWidget *parent):
    QFrame(parent)

{
    //painter = painter;
    //painter->setFont(font);
    cX = 0;
    cY = 0;
    cW = 100;
    cH = 100;
    m_strTitle = "分项指标合格率";
    m_yAxis = 100;
}



BarChart::~BarChart()
{
    pieces.clear();
}

void BarChart::setMyTitle(const QString& strTitle)
{
    m_strTitle =  strTitle;
}

void BarChart::setYAxis(double dbY)
{
    m_yAxis = dbY;
}

int BarChart::addPiece(const QString& name, Qt::GlobalColor color,Qt::GlobalColor colorJ,float Percentage)
{
    PieceNC& piece = pieces[name];
    piece.setName(name);
    piece.setColor(color,colorJ);
    piece.setPerc(Percentage);

    return pieces.size() - 1;
}
int BarChart::addPiece(const QString& name, QColor color, QColor colorJ, float Percentage)
{
    PieceNC& piece = pieces[name];
    piece.setName(name);
    piece.setColor(color,colorJ);
    piece.setPerc(Percentage);
    return pieces.size() - 1;
}
bool BarChart::setPieceValue(const QString& name,float Percentage)
{
    if(pieces.end() == pieces.find(name))
    {
        return false;
    }
    pieces[name].setPerc(Percentage);
    return true;
}

int BarChart::setCords(double x, double y, double w, double h)
{
    this->cX = x;
    this->cY = y;
    this->cW = w;
    this->cH = h;

    return 0;
}

int BarChart::draw(QPainter *painter)
{

    painter->save();
    //绘制边框及背景
    //    QBrush brush(QColor::fromRgb(0, 0, 0));
    QColor clrText = palette().text().color();
    QBrush brush(palette().background());

    painter->setBrush(brush);
    //QPen bkPen(brush.color());
    painter->setPen(brush.color());

    painter->drawRect(this->contentsRect().adjusted(1,1,-1,-1));

    //绘边框
    /* painter->setPen(clrText);
    painter->drawLine(0,0, this->width(),0);
    //painter->drawLine(this->width(),0 ,this->width(),this->height() );
    painter->drawLine(0,this->height(), this->width(),this->height());*/

    painter->restore();

    //绘制内容
    painter->save();
    //绘制标题
    QColor clrBright = this->palette().brightText().color();
//    painter->setPen(clrBright);
//    painter->drawText(wBorder + 3,wBorder +  painter->fontMetrics().height(),m_strTitle);
    painter->restore();

    double pDist = 23;
    double pW = (cW-(pieces.size())*pDist)/pieces.size();

    double szFont = pW / 3;
    if(szFont < 8)
    {
        szFont = 8;
    }

    if(szFont > (cX -5) / 4 )
    {
        szFont = (cX -5) / 4;
    }
    //绘制内容
    painter->save();
    painter->setPen(clrText);
    QFont font("宋体",szFont,QFont::Bold);
    painter->setFont(font);
    painter->setBrush(QBrush(clrText));

    /*QLinearGradient gradient(cX+cW/2,cY,cX+cW/2,cY+cH);
    gradient.setColorAt(0,Qt::black);*/

    //pen.setWidth(0);
    painter->setPen(Qt::SolidLine);

    int fontHeight = painter->fontMetrics().height();
    QMap<QString,PieceNC>::Iterator iterPie =  pieces.begin();
    for (int i = 0;iterPie != pieces.end(); iterPie++,i++)
    {
        PieceNC& tmpPie = iterPie.value();
        int percent = 0;
        if(tmpPie.pPerc < THRESHOLD) {
            percent =  cH *  tmpPie.pPerc / (THRESHOLD * 5);
            if(percent < 2)
            {
                percent = 2;
            }
        }
        else
        {
            percent = cH / 5 + cH * (tmpPie.pPerc - THRESHOLD)  / (100 - THRESHOLD) * 4/ 5;
        }

        //弧度渐变
        QLinearGradient conicalGradient(0,100,0,0);
       //创建了一个QConicalGradient对象实例，参数分别为中心坐标和初始角度

       conicalGradient.setColorAt(0,tmpPie.rgbColorJ);
       conicalGradient.setColorAt(1,tmpPie.rgbColor);
        painter->setBrush(QBrush(conicalGradient));
        painter->setPen(Qt::SolidLine);
        painter->drawRect(cX+pDist+i*(pW + pDist),cY+cH,pW,- percent);
        //draw drawEllipse
        QString label;
        label = QString::number(tmpPie.pPerc)+"%";
        if(tmpPie.pPerc > 30)
        {
            painter->setPen(Qt::white);
            painter->setBrush(QBrush(Qt::white));
            painter->drawEllipse(cX+pDist+i*(pW + pDist),cY+cH- percent - pW / 2,pW, pW );
            painter->setPen(Qt::black);
            painter->drawText(cX+pDist+i*(pW + pDist)+pW/2-painter->fontMetrics().width(label)/2,
                              cY+cH- percent /*-painter->fontMetrics().height()/2 - 1+pW/2*/,label);
        }
        else
        {
            painter->setPen(Qt::white);
            painter->drawText(cX+pDist+i*(pW + pDist)+pW/2-painter->fontMetrics().width(label)/2,
                              cY+cH- percent - fontHeight / 5 /*-painter->fontMetrics().height()/2 - 1+pW/2*/,label);
        }
    }
    //painter->setPen(Qt::SolidLine);
    painter->setPen(clrText);

    QString strYLabel = QString::number(100);
    int realFontSize = (cX -6)  / strYLabel.size();
    QFont fontMark("宋体",realFontSize,QFont::Normal);
    painter->setFont(fontMark);

    QFontMetrics fontMetrics(fontMark);
    int hFont = fontMetrics.height();

    int Count =100;
    for (int i=0;i<5;i++)
    {
            //QString label = QString::number(Count) + "%";;
           QString label = QString::number(Count);
            painter->drawLine(cX-3,cY+cH/10*i*2,cX,cY+cH/10*i*2);
            painter->drawText(cX-fontMetrics.width(label) - 5,cY + cH * i *2/ 10+ hFont / 3,label);

//               painter->drawLine(cX-3,cY+cH/10*i,cX,cY+cH/10*i);
//               if(0 == i % 2)
//               {
//                   QString label = QString::number(m_yAxis - m_yAxis * i / 10);
//                   painter->drawText(cX-fontMetrics.width(label) - 7,cY + cH * i / 10+ hFont / 3, label);
//               }
       // painter->drawText(cX-20,cY+cH/10*i,QString::number(Count)+"%");
        Count = Count - 10;
    }
    //画坐标軸
    painter->drawLine(cX,cY+cH,cX,cY - 6);         //??ü Y
    painter->drawLine(cX,cY+cH,cX+cW + 6,cY+cH);   //??ü ?
    //画箭头
    /*painter->drawLine(cX - 2,cY - 5,cX,cY - 10);
    painter->drawLine(cX + 2,cY - 5,cX,cY - 10);

    painter->drawLine(cX + cW + 5,cY  + cH - 2,cX+cW + 10,cY+cH);
    painter->drawLine(cX + cW + 5,cY  + cH + 2,cX+cW + 10,cY+cH);*/

    painter->restore();
    return 0;
}

int BarChart::drawLegend(QPainter *painter)
{

    double pDist = 15;
    double pW = (cW-(pieces.size())*pDist)/pieces.size();
    QColor clrText = palette().text().color();
    QPen pen(clrText);

    painter->save();
    painter->setPen(pen);

    int maxText = 1;
    QMap<QString,PieceNC>::Iterator iterPie =  pieces.begin();
    for (;iterPie != pieces.end(); iterPie++)
    {
        PieceNC& tmpPie = iterPie.value();
        if(maxText < tmpPie.pname.length())
        {
            maxText = tmpPie.pname.length();
        }
    }
    int szFont = (pDist + pW) / maxText ;
    if(szFont < 7)
    {
        szFont = 7;
    }


    QFont font("宋体",szFont,QFont::Normal);
    painter->setFont(font);
    int yFontPos = painter->fontMetrics().height() * 5 / 4;

    iterPie =  pieces.begin();
    for (int i = 0;iterPie != pieces.end(); iterPie++,i++)
    {
        PieceNC& tmpPie = iterPie.value();
        int xPos = cX+pDist+i*(pW + pDist)+pW/2-painter->fontMetrics().width(tmpPie.pname)/2;
        if(xPos < cX+pDist+i*(pW + pDist) -pDist /2 )
        {
            xPos = cX+pDist+i*(pW + pDist) -pDist /2;
        }

        painter->drawText(xPos,
                          cY + cH + yFontPos ,
                          tmpPie.pname);
    }
    painter->restore();
    return 0;
}

void BarChart::AllClear()
{
    pieces.clear();
}

void BarChart::paintEvent(QPaintEvent * paintEvent)
{
    UNUSED(paintEvent);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    setCords(25, 10, width() - 45, height() - 42);
    draw(&painter);
    drawLegend(&painter);
}

PieceNC::PieceNC()
{
}
void PieceNC::setName(QString name)
{
    pname = name;
}
void PieceNC::setColor(Qt::GlobalColor color,Qt::GlobalColor colorJ)
{
    rgbColor = color;
    rgbColorJ = colorJ;
}
void PieceNC::setColor(QColor color,QColor colorJ)
{
    rgbColor = color;
    rgbColorJ = colorJ;
}

void PieceNC::setPerc(float Percentage)
{
    if(Percentage > 100)
        Percentage = 100;
    if(Percentage < 0)
        Percentage = 0;
    pPerc = Percentage;
}
