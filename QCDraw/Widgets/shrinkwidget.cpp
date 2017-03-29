#include "shrinkwidget.h"
#include "ui_shrinkwidget.h"

#include "ChaDong/roundandquardrangle.h"
#include <QCheckBox>

#define PIX_SIZE 15

ShrinkWidget::ShrinkWidget(QWidget *parent) :
    QWidget(parent),_tabPix(":/chadong.png"),
    ui(new Ui::ShrinkWidget)
{
    ui->setupUi(this);

    _bTiny = true;
    _headerLayout = new QVBoxLayout(ui->tabWidget);
    _headerLayout->setContentsMargins(0,0,0,0);
    _headerLayout->setSpacing(0);

    _headerLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    ui->tabWidget->setLayout(_headerLayout);
    ui->tabWidget->setFixedWidth(PIX_SIZE);

    connect(&_btnGroup, SIGNAL(buttonClicked(const int &)),
            this, SLOT(clickShrinkItem(const int &)));
}

ShrinkWidget::~ShrinkWidget()
{
    delete ui;
}
void ShrinkWidget::setTiny(bool tiny)
{
    _bTiny = tiny;
    ui->contentWidget->setTiny(_bTiny);
}
//void	ShrinkWidget::mouseDoubleClickEvent ( QMouseEvent * event )
//{
//    if(_bTiny)
//    {
//        this->resize(700,600);
//        this->setAttribute(Qt::WA_TranslucentBackground,false);
//    }
//    else
//    {
//        this->resize(70,60);
//        this->setAttribute(Qt::WA_TranslucentBackground);
//    }
//    _bTiny = !_bTiny;
//    ui->contentWidget->setTiny(_bTiny);
//}

void ShrinkWidget::addShrink(const QString& name,const CdData& shrinkData)
{
    ShrinkInfo* tmpShrink = new ShrinkInfo;
    tmpShrink->name = name;
    tmpShrink->shrinkData= shrinkData;
    addShrink(tmpShrink);
}

void ShrinkWidget::addShrink(ShrinkInfo* tmpShrink)
{
    _tabShrink.push_back(tmpShrink);
    QCheckBox * toolBtn = new QCheckBox (ui->tabWidget);
    toolBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    toolBtn->setFixedSize(PIX_SIZE,PIX_SIZE);
    toolBtn->setCheckable(true);
    toolBtn->setIcon(QIcon(_tabPix));
    _btnGroup.addButton(toolBtn,_tabShrink.size() - 1);
    _headerLayout->insertWidget(_tabShrink.size() - 1,toolBtn);
    if(1 == _tabShrink.size())
    {
        toolBtn->setChecked(true);
        clickShrinkItem(0);
    }
}

void ShrinkWidget::clickShrinkItem(const int & index)
{
    ShrinkInfo* shrink = _tabShrink[index];
    ui->contentWidget->setShrink(shrink);
}

void ShrinkWidget::setCurShrink(int index)
{
}
