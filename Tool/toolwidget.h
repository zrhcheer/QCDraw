#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>
#include <QButtonGroup>


class ToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ToolWidget(QWidget *parent = 0);
    
protected:
    QSize sizeHint() const;
    //bool eventFilter(QObject * target , QEvent * event );
private:
    void initTool();

signals:
public slots:
    //void clickToolItem(const int& type);
private:

    QButtonGroup _groupTool;
    bool _bResize;
};

#endif // TOOLWIDGET_H
