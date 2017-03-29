#include "widgetgraphicbase.h"
#include <QPainter>
#include "Graphics/graphiccursor.h"

WidgetGraphicBase::WidgetGraphicBase(QWidget* parent) :
    QWidget(parent),_minSize(100,20)
{
    _bHorChange = true;
    _bVerChange = true;
    _curWidget = NULL;

    _topLayout = new QHBoxLayout();
    _topLayout->setContentsMargins(6,6,6,6);
    setLayout(_topLayout);
    setAttribute(Qt::WA_TranslucentBackground);
}

void WidgetGraphicBase::setCurWidget(QWidget* curWidget)
{
    if(_curWidget)
    {
        _topLayout->removeWidget(_curWidget);
        delete _curWidget;
    }
    _curWidget = curWidget;
    _topLayout->addWidget(_curWidget);
}
bool WidgetGraphicBase::isPointOver(const QPointF& point) const
{
    QPointF curPoint = point - this->pos();
    QSize size = this->size();
    if(curPoint.x() < 0 || curPoint.x() > size.width())
    {
        return false;
    }
    if(curPoint.y() < 0 || curPoint.y() > size.height())
    {
        return false;
    }
    return true;
}

//bool WidgetGraphicBase::setCursorForSize(int sizeFlag)
//{
//    int curId = GraphicCursor::getInstance()->setCursorForSize(this,sizeFlag);
//    if(!curId)
//    {
//        GraphicCursor::getInstance()->setCursorForID(this,GraphicCursor::CURSOR_ARROW);
//        if(_curWidget)
//        {
//            GraphicCursor::getInstance()->setCursorForID(this,GraphicCursor::CURSOR_ARROW);
//        }
//    }
//    else
//    {
//        if(_curWidget)
//        {
//            GraphicCursor::getInstance()->setCursorForID(this,curId);
//        }
//    }
//    return true;
//}
//bool  WidgetGraphicBase::setCursorForID(int id)
//{
//    GraphicCursor::getInstance()->setCursorForID(this,id);
//    if(_curWidget)
//    {
//        GraphicCursor::getInstance()->setCursorForID(_curWidget,id);
//    }
//    return true;
//}

void	WidgetGraphicBase::paintEvent (QPaintEvent * event )
{
    QWidget::paintEvent(event);
    if(this->getSelect())
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing);//反锯齿，使边缘更加平滑
        QRect rect = this->rect();
        painter.save();
        painter.setBrush(QBrush(Qt::green));
        painter.setPen(QPen(QBrush(Qt::black),1));
        painter.drawRect(0,0,6,6);
        painter.drawRect(0,rect.bottom() - 6,6,6);
        painter.drawRect(rect.right()-6,0,6,6);
        painter.drawRect(rect.right()-6,rect.bottom() - 6,6,6);

        QPointF centerPoint = rect.center();
        painter.drawRect(0,centerPoint.y() - 3,6,6);
        painter.drawRect(centerPoint.x() - 3,0,6,6);
        painter.drawRect(rect.right() - 6,centerPoint.y() - 3,6,6);
        painter.drawRect(centerPoint.x() - 3,rect.bottom() - 6,6,6);

        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(QBrush(Qt::blue),1,Qt::DashDotLine));
        painter.drawRect(rect);
        painter.restore();
    }
}
void WidgetGraphicBase::changeSizeFromSide(const QPointF& curPoint,const int& sizeFlag)
{
    QPoint pointPos = this->pos();
    QSize sizeMin = this->minimumSize();
    if(sizeMin.width() < _minSize.width())
    {
        sizeMin.setWidth(_minSize.width());
    }
    if(sizeMin.height() < _minSize.height())
    {
        sizeMin.setHeight(_minSize.height());
    }
    QSize size = this->size();
    if(sizeFlag &  Graphic::SIZECH_LEFT)
    {
        int leftPos = curPoint.x();
        int width =  pointPos.x() -curPoint.x() + size.width();
        if(pointPos.x() - curPoint.x() + size.width() < sizeMin.width())
        {
            leftPos = pointPos.x() + size.width() -  sizeMin.width();
            width = sizeMin.width();
        }
        if(sizeFlag & Graphic::SIZECH_TOP)
        {
            int topPos = curPoint.y();
            int height = pointPos.y() - curPoint.y() + size.height();
            if(pointPos.y() - curPoint.y() + size.height() < sizeMin.height())
            {
                topPos = pointPos.y() + size.height() -  sizeMin.height();
                height = sizeMin.height();
            }
            this->setGeometry(leftPos,topPos,width,height);
        }
        else if(sizeFlag & Graphic::SIZECH_BOM)
        {
            int bomPos = curPoint.y();
            int height = curPoint.y() - pointPos.y();
            if(height < sizeMin.height())
            {
                bomPos = pointPos.y() + sizeMin.height();
                height = sizeMin.height();
            }
            this->setGeometry(leftPos,pointPos.y(),width,height);
        }
        else
        {
            this->setGeometry(leftPos,pointPos.y(),width,size.height());
        }
    }
    else if(sizeFlag &  Graphic::SIZECH_RIGHT)
    {
        int width = curPoint.x() - pointPos.x();
        if(width < sizeMin.width())
        {
            width = sizeMin.width();
        }
        if(sizeFlag & Graphic::SIZECH_TOP)
        {
            int topPos = curPoint.y();
            int height = pointPos.y() - curPoint.y() + size.height();
            if(height < sizeMin.height())
            {
                topPos =  pointPos.y() + size.height() - sizeMin.height();
                height = sizeMin.height();
            }
            this->setGeometry(pointPos.x(),topPos,width,height);
        }
        else if(sizeFlag & Graphic::SIZECH_BOM)
        {
            int height = curPoint.y() - pointPos.y();
            if(height < sizeMin.height())
            {
                height = sizeMin.height();
            }
            this->setGeometry(pointPos.x(),pointPos.y(),width,height);
        }
        else
        {
            this->setGeometry(pointPos.x(),pointPos.y(),width,size.height());
        }
    }
    else
    {
        if(sizeFlag & Graphic::SIZECH_TOP)
        {
            int topPos = curPoint.y();
            int height = pointPos.y() - curPoint.y() + size.height();
            if(height < sizeMin.height())
            {
                topPos =  pointPos.y() + size.height() - sizeMin.height();
                height = sizeMin.height();
            }
            this->setGeometry(pointPos.x(),topPos,size.width(),height);
        }
        else if(sizeFlag & Graphic::SIZECH_BOM)
        {
            int height = curPoint.y() - pointPos.y();
            if(height < sizeMin.height())
            {
                height = sizeMin.height();
            }
            this->setGeometry(pointPos.x(),pointPos.y(),size.width(),height);
        }
    }
    this->update();
}

int WidgetGraphicBase::getSizeChangeFlag(const QPointF& point)
{
    QSize size = this->size();
    QPointF curPoint = point - this->pos();
    if(curPoint.x() < 0 || curPoint.x() > size.width() || curPoint.y() < 0 || curPoint.y() > size.height())
    {
        return 0;
    }
    if(curPoint.x() < 6)//
    {
        if(curPoint.y() < 6)
        {
            return SIZECH_LEFT | SIZECH_TOP;
        }
        else if(curPoint.y() > size.height() / 2 - 3 && curPoint.y() < size.height() / 2 + 3)
        {
            return SIZECH_LEFT;
        }
        else if(curPoint.y() > size.height() - 6)
        {
            return SIZECH_LEFT | SIZECH_BOM;
        }
    }
    else if(curPoint.x() > size.width() / 2 - 3 && curPoint.x() < size.width() / 2 + 3)
    {
        if(curPoint.y() < 6)
        {
            return SIZECH_TOP;
        }
        else if(curPoint.y() > size.height() - 6)
        {
            return SIZECH_BOM;
        }
    }
    else if(curPoint.x() > size.width() - 6)
    {
        if(curPoint.y() < 6)
        {
            return SIZECH_RIGHT | SIZECH_TOP;
        }
        else if(curPoint.y() > size.height() / 2 - 3 && curPoint.y() < size.height() / 2 + 3)
        {
            return SIZECH_RIGHT;
        }
        else if(curPoint.y() > size.height() - 6)
        {
            return SIZECH_RIGHT | SIZECH_BOM;
        }
    }
    return 0;
}
