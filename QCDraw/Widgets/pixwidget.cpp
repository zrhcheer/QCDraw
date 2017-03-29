#include "pixwidget.h"

#include <QPainter>
#include "shrinktick.h"

PixWidget::PixWidget(QWidget *parent) :
    QWidget(parent)
{
    _shrink = NULL;
    _pixFlag = PIX_TINY;
    layout = new QHBoxLayout(this);
    this->setLayout(layout);
}

void PixWidget::setShrink(ShrinkInfo* shrink)
{
    _shrink = shrink;
    update();
}

void PixWidget::setTiny(bool tiny)
{
    _tiny = tiny;
}

void PixWidget::paintEvent(QPaintEvent *)
{
    Qt_Painter painter(this, &_shrink->shrinkData.getStuConvert());
    if(_tiny)
    {
        _shrink->shrinkData.drawSmallEntity(painter,this->size());
    }
    else
    {

        _shrink->shrinkData.drawEntity(painter,this->size(),m_iCurrentPointIndex,m_pointMouse);
    }
    /*QPainter painter(this);
    if(_shrink)
    {
        switch(_pixFlag)
        {
        case PIX_TINY:
            painter.drawPixmap(0,0,_shrink->pix);
            break;
        case PIX_BIG:
            break;
        }
    }*/
}

