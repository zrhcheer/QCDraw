#include "dynamicpointgraphic.h"

const QString DynamicPointGraphic::_devName = CodeConvertor::fromLocal("动态点");

DynamicPointGraphic::DynamicPointGraphic()
{
    setType(Graphic::GRAPHIC_DYNAMIC);
    this->setColor(QColor(255,0,0));

    _flagClr = QColor(0,255,0);
    _lightClr = QColor(0,0,255);
    _isFlag = false;

    _portPoints.resize(1);
    _portPoints[0].setJoinPoint(QPointF(0,0));
    _portPoints[0].setJoinType(GraphicPortPoint::JOIN_MUTI);

    startTimer(500);
}

void DynamicPointGraphic::timerEvent( QTimerEvent * )
{
    if(_flagClr == QColor(0,0,255))
    {
        _flagClr =QColor(0,255,0);
    }
    else
    {
        _flagClr = QColor(0,0,255);
    }

    this->update();
}

void DynamicPointGraphic::prepareGraphic(QPainter *painter)
{
    GraphicBase::prepareGraphic(painter);
}

void DynamicPointGraphic::drawGraphic(QPainter *painter)
{
    if(!_isFlag)
    {
        painter->setBrush(QBrush(_flagClr));
        painter->setPen(QPen(_flagClr));
        painter->drawEllipse(QPoint(0,0),_size.width() / 2 -4,_size.height() / 2 - 4);
    }
    else
    {
        QPainterPath painterPath;
        painterPath.addEllipse(QPoint(0,0),_size.width() / 2 -4,_size.height() / 2 - 4);
        painterPath.addEllipse(QPoint(0,0),_size.width() / 3 - 2 ,_size.height() / 3 - 2 );
        painterPath.setFillRule(Qt::OddEvenFill);
        painter->drawPath(painterPath);

        painter->save();
        QPainterPath painterInPath;
        painterInPath.addEllipse(QPoint(0,0),_size.width() / 3 - 2,_size.height() / 3 - 2);
        painterInPath.addEllipse(QPoint(0,0),_size.width() / 6 ,_size.height() / 6 );
        painterInPath.setFillRule(Qt::OddEvenFill);
        painter->setBrush(QBrush(_flagClr));
        painter->drawPath(painterInPath);
        painter->restore();
    }
}
void DynamicPointGraphic::setPosition(const QPointF& pos)
{
    this->setPos(pos);
    //对线进行移动
    //    for(QVector<GraphicPort>::Iterator iterJoint = _port.begin();
    //        iterJoint != _port.end(); ++iterJoint)
    //    {
    //        GraphicPort& tmpPort = *iterJoint;
    //        LineGraphic* tmpGraphic = dynamic_cast<LineGraphic*>(tmpPort.getGraphic());
    //        if(tmpGraphic)
    //        {
    //            int direct = tmpPort.getLinkPos();
    //            tmpGraphic->setJointPointDis(direct,this->pos(),this->getSize().width() / 2);
    //        }
    //    }
}
