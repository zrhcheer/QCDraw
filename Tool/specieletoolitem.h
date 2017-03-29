#ifndef SPECIELETOOLITEM_H
#define SPECIELETOOLITEM_H

#include <QPushButton>
#include "Graphics/graphicbase.h"

#define ELEITEM_WIDTH 40
#define ELEDRAW_WIDTH 40

class SpeciEleToolItem : public QPushButton
{
    Q_OBJECT
public:
    explicit SpeciEleToolItem(const QString& strText,QWidget *parent = 0);
    ~SpeciEleToolItem();

    virtual QSize	sizeHint () const;
    void setGraphic(GraphicBase* graphic)
    {
        _speciGraphic = graphic;
    }
protected:
    virtual void  mousePressEvent (QMouseEvent * event );
    virtual void mouseMoveEvent(QMouseEvent * event);
     virtual void paintEvent(QPaintEvent * paintEvent);
     virtual void timerEvent( QTimerEvent * );

private:
    GraphicBase* _speciGraphic;
    QPoint _dragPosition;
    int _typeDrag;
    QColor _flagClr;
    
};

#endif // SPECIELETOOLITEM_H
