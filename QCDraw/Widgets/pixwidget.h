#ifndef PIXWIDGET_H
#define PIXWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include "ChaDong/CdPoint.h"

class ShrinkInfo;
class PixWidget : public QWidget
{
    Q_OBJECT
public:
    enum
    {
        PIX_BIG,
        PIX_TINY
    };
    explicit PixWidget(QWidget *parent = 0);
    
    void setShrink(ShrinkInfo* shrink);

    void setTiny(bool tiny);

protected:
     virtual void paintEvent(QPaintEvent *);
signals:
    
public slots:
    
private:
    QHBoxLayout* layout;
    ShrinkInfo* _shrink;
    int _pixFlag;
    int m_iCurrentPointIndex;
    CdPoint m_pointMouse;

    bool _tiny;
};

#endif // PIXWIDGET_H
