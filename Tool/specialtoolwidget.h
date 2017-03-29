#ifndef SPECIALTOOLWIDGET_H
#define SPECIALTOOLWIDGET_H

#include <QWidget>

class SpecialToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpecialToolWidget(QWidget *parent = 0);

private:
    void initTool();
    
signals:
    
public slots:

};

#endif // SPECIALTOOLWIDGET_H
