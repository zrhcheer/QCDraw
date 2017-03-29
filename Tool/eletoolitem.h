#ifndef ELETOOLITEM_H
#define ELETOOLITEM_H

#include <QPushButton>
#include "Graphics/graphicbase.h"
#define ELEITEM_WIDTH 40
#define ELEDRAW_WIDTH 40

class EleToolItem : public QPushButton
{
public:
    EleToolItem(const QString& strText,QWidget *parent = 0);
    ~EleToolItem();
    void setGraphic(GraphicBase* graphic)
    {
        _graphic = graphic;
    }
    virtual QSize	sizeHint () const;
protected:
    virtual void  mousePressEvent (QMouseEvent * event );
    virtual void mouseMoveEvent(QMouseEvent * event);
     virtual void paintEvent(QPaintEvent * paintEvent);
private:
    GraphicBase* _graphic;
    QPoint _dragPosition;
    int _typeDrag;
};

#endif // ELETOOLITEM_H
