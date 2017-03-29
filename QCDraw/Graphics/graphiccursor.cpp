#include "graphiccursor.h"
#include "graphic.h"
#include <QWidget>
#include <QApplication>

QSharedPointer<GraphicCursor> GraphicCursor::_instance;
GraphicCursor::GraphicCursor()
{
    _defaultCursor = QCursor(Qt::ArrowCursor);
    _cursor.resize(CURSOR_MAX);
    _cursor[CURSOR_PEN] =QCursor(QPixmap(":/pen.png"),7,0);
    _cursor[CURSOR_TRI] =QCursor(QPixmap(":/tri.png"),0,0);
    _cursor[CURSOR_ANCHOR] =QCursor(QPixmap(":/anchor.png"),15,0);
    _cursor[CURSOR_CROSS] = QCursor(Qt::CrossCursor);
    _cursor[CURSOR_HAND] = QCursor(Qt::OpenHandCursor);
    _cursor[CURSOR_ARROW] = QCursor(Qt::ArrowCursor);
    _cursor[CURSOR_SIZE] = QCursor(Qt::SizeAllCursor);
    _cursor[CURSOR_SizeVerCursor] = Qt::SizeVerCursor;
    _cursor[CURSOR_SizeHorCursor] = Qt::SizeHorCursor;
    _cursor[CURSOR_SizeBDiagCursor] =Qt::SizeBDiagCursor;
    _cursor[CURSOR_SizeFDiagCursor] = Qt::SizeFDiagCursor;

}

const QCursor& GraphicCursor::getCursorForSize(int sizeFlag)
{
    int cursorId = 0;
    if(sizeFlag & Graphic::SIZECH_LEFT)
    {
        if(sizeFlag & Graphic::SIZECH_TOP)
        {
            cursorId = CURSOR_SizeFDiagCursor;
        }
        else if(sizeFlag & Graphic::SIZECH_BOM)
        {
            cursorId = CURSOR_SizeBDiagCursor;
        }
        else
        {
            cursorId = CURSOR_SizeHorCursor;
        }
    }
    else if(sizeFlag & Graphic::SIZECH_RIGHT)
    {
        if(sizeFlag & Graphic::SIZECH_TOP)
        {
            cursorId = CURSOR_SizeBDiagCursor;
        }
        else if(sizeFlag & Graphic::SIZECH_BOM)
        {
            cursorId = CURSOR_SizeFDiagCursor;
        }
        else
        {
            cursorId = CURSOR_SizeHorCursor;
        }
    }
    else
    {
        if((sizeFlag & Graphic::SIZECH_TOP) || (sizeFlag & Graphic::SIZECH_BOM))
        {
            cursorId = CURSOR_SizeVerCursor;
        }
    }
    return getCursorFromID(cursorId);
}

//int  GraphicCursor::setCursorForSize(QWidget* widget, int sizeFlag)
//{
//    if(!widget)
//    {
//        return 0;
//    }
//    widget->setCursor(getCursorForSize(sizeFlag));
//    return 0;
//}
//void  GraphicCursor::setCursorForID(QWidget* widget, int id)
//{
//    if(!widget)
//    {
//        return;
//    }
//    if(id >= 0 && id <CURSOR_MAX)
//    {
//        widget->setCursor(_cursor[id]);
//        return;
//    }
//    return widget->setCursor(_defaultCursor);
//}

const QCursor& GraphicCursor::getCursorFromID(int id)
{
    if(id >= 0 && id <CURSOR_MAX)
    {
        return _cursor[id];
    }
    return _defaultCursor;
}

void GraphicCursor::setOverrideCursor(int cursorId)
{
    QApplication::setOverrideCursor(getCursorFromID(cursorId));
}

void GraphicCursor::setOverrideCursorFromSize(int sizeFlag)
{
    QApplication::setOverrideCursor(getCursorForSize(sizeFlag));
}
