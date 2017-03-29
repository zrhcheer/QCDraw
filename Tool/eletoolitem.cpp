#include "eletoolitem.h"
#include <QMouseEvent>
#include <QApplication>
#include "Graphics/utilfunc.h"

EleToolItem::EleToolItem(const QString& strText,QWidget *parent) :
    QPushButton(parent)
{
    _graphic = NULL;
    this->setText(strText);
    this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    this->setCheckable(true);
    int height = this->fontMetrics().height();
    this->setFixedHeight(height + ELEITEM_WIDTH);
}
EleToolItem::~EleToolItem()
{
    if(_graphic)
    {
        delete _graphic;
    }
}

QSize EleToolItem::sizeHint () const
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
void EleToolItem::paintEvent(QPaintEvent * paintEvent)
{
    QPainter painter(this);
    QString strName = this->text();
    painter.setRenderHints(QPainter::Antialiasing);//反锯齿，使边缘更加平滑
    QRect rect = this->rect();
    int fontHeight = this->fontMetrics().height();
    if(_graphic)
    {
        _graphic->setPos(rect.width() / 2,(rect.height() - fontHeight) / 2);
        _graphic->setSize(rect.height() - fontHeight);
        painter.save();
        painter.translate(_graphic->pos());
        _graphic->prepareGraphic(&painter);
        _graphic->drawGraphic(&painter);
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

void EleToolItem::mouseMoveEvent ( QMouseEvent * event )
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
    QString strType = QString::number(_graphic->getType());
    mimeData->setData("custom/graphic",strType.toUtf8());
    drag->setMimeData(mimeData);

    _graphic->setScale(1);

    QPixmap drag_img(_graphic->getSize());
    drag_img.fill(Qt::transparent);
    QPainter painter(&drag_img);

    painter.translate(_graphic->getSize().width()/ 2,_graphic->getSize().height() / 2);
    _graphic->prepareGraphic(&painter);
    _graphic->drawGraphic(&painter);
    drag->setPixmap(drag_img);
    drag->setHotSpot(QPoint(_graphic->getSize().width() / 2,_graphic->getSize().height() / 2));

    Qt::DropAction resultAction = drag->exec(Qt::MoveAction);
    if(resultAction == Qt::MoveAction)
    {
        // 确认移动操作
        // 该操作已经被目标操作接受，且操作类型为MOVE，一般来说应该把被拖动的物体从源窗口删除
    }

    QPushButton::mouseMoveEvent(event);
}

void EleToolItem::mousePressEvent ( QMouseEvent * event )
{
    if (event->button() == Qt::LeftButton)
    {
        //_typeDrag = _groupTool.checkedId ();
        //QAbstractButton* btn = 	_groupTool.button (_typeDrag);
        _dragPosition= event->pos();
    }
    QPushButton::mousePressEvent(event);
}
