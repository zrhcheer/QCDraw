#include "specieletoolitem.h"
#include "Graphics/utilfunc.h"

#include <QMouseEvent>
#include <QApplication>

SpeciEleToolItem::SpeciEleToolItem(const QString& strText,QWidget *parent) :
    QPushButton(parent)
{
    _speciGraphic = NULL;
    this->setText(strText);
    this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    this->setCheckable(true);
    int height = this->fontMetrics().height();
    this->setFixedHeight(height + ELEITEM_WIDTH);
    startTimer(500);
    _flagClr =QColor(0,255,0);
}
SpeciEleToolItem::~SpeciEleToolItem()
{
    if(_speciGraphic)
    {
        delete _speciGraphic;
    }
}
void SpeciEleToolItem::timerEvent( QTimerEvent * )
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


QSize SpeciEleToolItem::sizeHint () const
{
    QSize sz = QWidget::sizeHint();
    int height = this->fontMetrics().height();
    QString strName = this->text();
    int width = this->fontMetrics().width(strName);
    if(width > ELEITEM_WIDTH)
    {
        return QSize(width,height + ELEITEM_WIDTH);
    }
    else
    {
        return QSize(ELEITEM_WIDTH,height + ELEITEM_WIDTH);
    }
}

void SpeciEleToolItem::mouseMoveEvent ( QMouseEvent * event )
{
    if (!(event->buttons() & Qt::LeftButton))
    {
        return;
    }
    if ( UtilFunc::manhattanLength(event->pos() - _dragPosition) < QApplication::startDragDistance())
    {
        return;
    }

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    // 把ip地址传出
    QString strType = QString::number(_speciGraphic->getType());
    mimeData->setData("custom/graphic",strType.toUtf8());
    drag->setMimeData(mimeData);

    _speciGraphic->setScale(1);

    QPixmap drag_img(_speciGraphic->getSize());
    drag_img.fill(Qt::transparent);
    QPainter painter(&drag_img);

    painter.translate(_speciGraphic->getSize().width()/ 2,_speciGraphic->getSize().height() / 2);
    _speciGraphic->prepareGraphic(&painter);
    _speciGraphic->drawGraphic(&painter);
    drag->setPixmap(drag_img);
    drag->setHotSpot(QPoint(_speciGraphic->getSize().width() / 2,_speciGraphic->getSize().height() / 2));

    Qt::DropAction resultAction = drag->exec(Qt::MoveAction);
    if(resultAction == Qt::MoveAction)
    {
        // 确认移动操作
        // 该操作已经被目标操作接受，且操作类型为MOVE，一般来说应该把被拖动的物体从源窗口删除
    }
    QPushButton::mouseMoveEvent(event);
}

void SpeciEleToolItem::paintEvent(QPaintEvent * paintEvent)
{
    QPainter painter(this);
    QString strName = this->text();
    painter.setRenderHints(QPainter::Antialiasing);//反锯齿，使边缘更加平滑
    QRect rect = this->rect();
    int fontHeight = this->fontMetrics().height();
    if(_speciGraphic)
    {
        _speciGraphic->setPos(rect.width() / 2,(rect.height() - fontHeight) / 2);
        _speciGraphic->setSize(rect.height() - fontHeight);
        painter.save();
        painter.translate(_speciGraphic->pos());
        _speciGraphic->prepareGraphic(&painter);
        painter.setPen(_flagClr);
        _speciGraphic->drawGraphic(&painter);
        painter.restore();
    }
    if(this->isChecked())
    {
        painter.save();
        painter.setBrush(QBrush(Qt::black));
        painter.setPen(Qt::white);
        painter.drawRect(rect.left(),rect.bottom() - fontHeight,rect.width(),fontHeight);
        painter.drawText(rect.left(),rect.bottom() - fontHeight,rect.width(),fontHeight,
                         Qt::AlignCenter,strName);
        painter.restore();
    }
    else
    {
        painter.drawText(rect.left(),rect.bottom() - fontHeight,rect.width(),fontHeight,
                         Qt::AlignCenter,strName);
    }
    QWidget::paintEvent(paintEvent);
}

void SpeciEleToolItem::mousePressEvent ( QMouseEvent * event )
{
    if (event->button() == Qt::LeftButton)
    {
        _dragPosition= event->pos();
    }
    QPushButton::mousePressEvent(event);
}
