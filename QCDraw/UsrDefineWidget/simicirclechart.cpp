#include "simicirclechart.h"

#include <QFontMetrics>
#include <QPainterPath>
#include <qmath.h>

const double PAI = 3.14159265358979323;

SimiCircleChart::SimiCircleChart(QWidget *parent) :
    QFrame(parent)
{
    m_curPercent = 0;
    m_strTitle = "综合合格率";
}

SimiCircleChart::~SimiCircleChart()
{
}

void SimiCircleChart::paintEvent(QPaintEvent * paintEvent)
{

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);//反锯齿，使边缘更加平滑

    setCords(25, 15, width() - 50, height() - 50);
    draw(&painter);
    QFrame::paintEvent(paintEvent);
}
void SimiCircleChart::setPercent(const int& percent)
{
    int cur = percent;
    if(cur < 0)
    {
        cur = 0;
    }
    else if(cur > 100)
    {
        cur = 100;
    }

    if(cur != m_curPercent)
    {
        m_curPercent = cur;
        update();
    }

}

int SimiCircleChart::draw(QPainter* painter)
{

    int Per_x, Per_y;
    int Big_R=50 ,Small_R =35;
    Big_R = (this->width() > this->height()) ? (this->height() - 10) / 2 : (this->width() - 10) /2 ;
    Small_R = 0.7 * Big_R;
    //setPercent(80.00);
    painter->save();
    //绘制边框及背景
    //    QBrush brush(QColor::fm_strTitle = "分项指标合格率";romRgb(0, 0, 0));
    QBrush brush(palette().background());

    painter->setBrush(brush);
    painter->setPen(brush.color());

    painter->drawRect( this->contentsRect().adjusted(1,1,-1,-1));
    //painter->drawRect(2, 2, this->width() - 4, this->height() - 4);

    //绘边框
    /* painter->setPen(clrText);
    painter->drawLine(0,0, this->width(),0);
    painter->drawLine(0,0, 0 ,this->height());
    painter->drawLine(0,this->height(), this->width(),this->height());

    QPen dotPen(Qt::DashLine);
    dotPen.setColor(clrText);
    painter->setPen(dotPen);
    painter->drawLine(this->width(),0 + 5,this->width(),this->height() - 5);*/


    painter->restore();

    //绘制内容
    painter->save();
    //绘制标题
    QColor clrBright = this->palette().brightText().color();
//    painter->setPen(clrBright);
//    painter->drawText(wBorder + 3,wBorder + painter->fontMetrics().height(),m_strTitle);
    painter->restore();

    //得到圆扇半径

    QRect Contrect = this->contentsRect();

    painter->setBrush(QBrush(Qt::green));
    painter->setPen(Qt::green);
    QRect rec(Contrect.right()/2 -Big_R ,Contrect.bottom()/2-Big_R,Big_R*2,Big_R*2);
    painter->drawPie(rec,90*16,m_curPercent/100*360*16);

    painter->setBrush(QBrush(Qt::red));
    painter->setPen(Qt::red);
    painter->drawPie(rec,m_curPercent/100*360*16+90*16,(100-m_curPercent)/100*360*16);

    painter->setBrush(QBrush(QColor(255,255,255,140)));
    painter->setPen(QColor(255,255,255,0));
    QRect rec2(Contrect.right()/2 -Small_R ,Contrect.bottom()/2-Small_R,Small_R*2,Small_R*2);
    painter->drawPie(rec2,0,360*16);

    Per_x = Contrect.right()/2 - Small_R*sin((90-m_curPercent/100*360+90)*M_PI/180);
    Per_y = Contrect.bottom()/2-Small_R * sin((m_curPercent/100*360+90)*M_PI/180);

    painter->setBrush(QColor(255,255,255,200));
    painter->setPen(QColor(255,255,255,0));
    painter->drawEllipse(Per_x-13,Per_y-13,26,26);

    painter->setBrush(QBrush(Qt::black));
    painter->setPen(Qt::SolidLine);
    painter->drawText(Per_x-10,Per_y+3, QString::number(m_curPercent)+"%");
    //   QPainterPath path;
    //   path.moveTo(xCenter + inRadus ,yCenter);
    //   path.lineTo(xCenter + radus ,yCenter);

    //   path.arcTo(xCenter - radus,yCenter - radus,radus * 2,radus * 2,
    //              0 ,  180 );
    //   path.lineTo(xCenter - inRadus ,yCenter);
    //   path.arcTo(xCenter - inRadus,yCenter - inRadus,inRadus * 2,inRadus * 2,
    //             180 ,  -180 );
    //   painter->drawPath(path);

    //   if(m_curPercent >= 0)
    //   {
    //       QFont font("宋体",8,QFont::Bold);
    //       QFontMetrics fm(font);

    //       QString fmt("%1%");
    //       QString strPer = fmt.arg(m_curPercent);


    //       int textWidthInPixels = fm.width(strPer);
    //       int textHeightInPixels = fm.height();
    //       painter->setFont(font);
    //       painter->drawText(xCenter - textWidthInPixels /2, yCenter + textHeightInPixels + ballRadus + 2,strPer );
    //   }
    //    //QPainterPathStroker painterPathStroker;
    //   // painterPathStroker.
    //    //画图柄
    //    //double radus = 30;
    //    painter->save();
    //    //画指针
    //    painter->setBrush(QColor(40,40,40));
    //    painter->setPen(Qt::SolidLine);
    //    const double bomRadus = 3;
    //    const double topRadus = 1.5;

    //    //const double beamArc = (m_posPointer - 90) * PAI / 180;
    //    double posPointer = 180 - m_curPercent * 180 / 100;

    //    painter->translate(xCenter,yCenter);
    //    painter->rotate(-posPointer);

    //    const double heightBeam = radus * 9  / 10;

    //    QPolygonF pointerPolygon;
    //    pointerPolygon << QPointF(0,bomRadus);
    //    pointerPolygon << QPointF(heightBeam,topRadus);
    //    pointerPolygon << QPointF(heightBeam,-topRadus);
    //    pointerPolygon << QPointF(0,-bomRadus);

    //    painter->drawPolygon(pointerPolygon);
    //    painter->restore();
    //   // pointerPolygon.

    //    painter->save();
    //    painter->setBrush(QBrush(Qt::black));
    //    painter->setPen(Qt::SolidLine);
    //    QRadialGradient radialGradient(m_cX + m_cW / 2,m_cY + m_cH, ballRadus,m_cX + m_cW / 2,m_cY + m_cH);
    //    radialGradient.setColorAt(0.0, Qt::white);
    //    radialGradient.setColorAt(0.7, Qt::black);
    //    radialGradient.setColorAt(1.0, QColor(50,50,50));
    //    painter->setBrush(QBrush(radialGradient));
    //    painter->drawEllipse(QPointF(m_cX + m_cW / 2,m_cY + m_cH),ballRadus,ballRadus);

    //    painter->restore();
    return 0;
}

int SimiCircleChart::setCords(double x, double y, double w, double h)
{
    this->m_cX = x;
    this->m_cY = y;
    this->m_cW = w;
    this->m_cH = h;
    return 0;
}
