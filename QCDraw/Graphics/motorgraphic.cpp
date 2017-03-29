#include "motorgraphic.h"

const QString MotorGraphic::_devName = CodeConvertor::fromLocal("µç¶¯»ú");

MotorGraphic::MotorGraphic()
{
    setType(Graphic::GRAPHIC_MOTOR);
    this->setColor(QColor(22,149,19));
    _bOpen = true;
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(1);
}

void MotorGraphic::setSize(const int &height)
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

QPointF MotorGraphic::getPortPos(int pos)
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

void MotorGraphic::loadPortPos()
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

void MotorGraphic::prepareGraphic(QPainter *painter)
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

void MotorGraphic::drawGraphic(QPainter *painter)
{
    float radius = _size.height() / 3;//°ë¾¶

    painter->drawLine(0, - radius*3/2,
                      0, - radius/2);

    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(QPointF(0, radius / 2),radius ,radius);

    //    »æÖÆ±´Èû¶ûÇúÏß
    QPoint start_pos(radius / 3,- 0.207*radius);
    QPoint end_pos(radius / 3,radius / 2);

    //drawPath;
    QPainterPath path(start_pos);
    QPoint c1(- radius,0.293 * radius);
    QPoint c2(radius / 3,radius / 2);
    path.cubicTo(c1 ,c2 ,end_pos);
    painter->drawPath(path);

//    //    »æÖÆ±´Èû¶ûÇúÏß
    QPoint start_posII(radius/3, radius / 2);
    QPoint end_posII(radius/3,1.207 * radius);

    //drawPath;
//    QPainterPath pathII(start_posII);
    QPoint c1II(- radius,0.957 * radius);
    QPoint c2II(radius / 3,1.207 * radius);
    path.cubicTo(c1II ,c2II ,end_posII);
    painter->drawPath(path);
}















