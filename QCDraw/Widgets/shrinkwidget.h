#ifndef SHRINKWIDGET_H
#define SHRINKWIDGET_H

#include <QWidget>
#include <QVector>
#include <QButtonGroup>
#include <QVBoxLayout>
#include "Graphics/graphic.h"
#include "ChaDong/CdData.h"

namespace Ui {
class ShrinkWidget;
}

class RoundAndQuardrangle;
struct ShrinkInfo
{
    ShrinkInfo()
    {
    }

    QString name;//名字
    QPixmap pix;//标签图片
    CdData  shrinkData;
};

class ShrinkWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ShrinkWidget(QWidget *parent = 0);
    ~ShrinkWidget();

    void addShrink(ShrinkInfo* tmpShrink);

    void setCurShrink(int index);

    void addShrink(const QString& name,const CdData& shrinkData);

    void setTiny(bool tiny);
protected:
    //virtual void	mouseDoubleClickEvent ( QMouseEvent * event );
public slots:
    void clickShrinkItem(const int &);

private:
    Ui::ShrinkWidget *ui;
    QVector<ShrinkInfo*> _tabShrink;
    QButtonGroup _btnGroup;
    QPixmap _tabPix;
    QVBoxLayout* _headerLayout;

    QSize _minSize;//用于保存最小大小
    QVector<GraphicPort> _vecPort;//用于保存链接点
    bool _bTiny;
};

#endif // SHRINKWIDGET_H
