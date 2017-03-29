#include "altermatorgraphic.h"
#include "codeconvertor.h"
const QString AlterMatorGraphic::_devName = CodeConvertor::fromLocal("发电机");

AlterMatorGraphic::AlterMatorGraphic()
{
    setType(Graphic::GRAPHIC_ALTERMATOR);
    this->setColor(QColor(22,149,19));
    _bOpen = true;
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(1);
}

void AlterMatorGraphic::setSize(const int &height)
{
    if(height < ELE_MIN_SIZE)
    {
        _size.setHeight(ELE_MIN_SIZE);
    }
    else
    {
        _size.setHeight(height);
    }
    _size.setWidth(height * 2 / 3);
}

QPointF AlterMatorGraphic::getPortPos(int pos)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        return _portPoints[Graphic::JOIN_BEGIN].getJoinPoint();
        break;
    default:
        assert(false);
        break;
    }
}

void AlterMatorGraphic::loadPortPos()
{
    float halfHeight = _size.height() / 2.0;
    switch(this->getDirect())
    {
    case POS_UP:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(0, -halfHeight));
        return;
    case POS_RIGHT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(halfHeight,0));
        return;
    case POS_DOWN:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(0, halfHeight));
        return;
    case POS_LEFT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(-halfHeight,0));
        return;
    }
}

void AlterMatorGraphic::prepareGraphic(QPainter *painter)
{
    GraphicBase::prepareGraphic(painter);
    switch(this->getDirect())
    {
    case POS_UP:
        break;
    case POS_RIGHT:
        painter->rotate(90);
        break;
    case POS_DOWN:
        painter->rotate(180);
        break;
    case POS_LEFT:
        painter->rotate(270);
        break;
    }
}

void AlterMatorGraphic::drawGraphic(QPainter *painter)
{
    float radius = _size.height() / 3;//半径

    painter->drawLine(0, - radius*3/2,
                      0, - radius/2);

    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(QPointF(0, radius / 2),radius ,radius);

    //    绘制贝塞尔曲线
    QPoint start_pos(0,- radius/2 + CONTROLSTYLE);
    QPoint end_pos(0, radius*3/2 - CONTROLSTYLE);
    //drawPath;
    QPainterPath path(start_pos);
    QPoint c1(radius * (1.73)/2 + CONTROLSTYLE,0 + 2*CONTROLSTYLE);
    QPoint c2(-radius * (1.73)/2 - CONTROLSTYLE,radius*3/4 - CONTROLSTYLE);
    path.cubicTo(c1 ,c2 ,end_pos );
    painter->drawPath(path);
}

