#include "toolwidget.h"

#include <assert.h>
#include <QGridLayout>
#include <QSpacerItem>
#include "eletoolitem.h"
#include "qcdrawscene.h"
#include "Graphics/graphicfactory.h"
#include "Graphics/graphicbase.h"

ToolWidget::ToolWidget(QWidget *parent) :
    QWidget(parent)
{
    initTool();
}

QSize ToolWidget::sizeHint() const   //返回一个被推荐的尺寸ToolWidget
{
    QSize size = QWidget::sizeHint();
    size.setWidth(ELEITEM_WIDTH * 3);//40*3
    return size;
}
void ToolWidget::initTool()
{
    int colMax = 3; //col=column 竖行   row=row 横行
    EleToolItem* drawItem = NULL;
    int row = 0;
    int col = 0;
    int rowMax  = 0;
    if(Graphic::GRAPHIC_MAX  % colMax)
    {
        rowMax = Graphic::GRAPHIC_MAX / colMax + 1;
    }
    else
    {
        rowMax = Graphic::GRAPHIC_MAX / colMax;  //行数
    }

    QGridLayout* mainLayout = new QGridLayout(this);//栅格布局

    for(int i = 0; i < Graphic::GRAPHIC_MAX; ++i)
    {
        if(i != Graphic::GRAPHIC_DYNAMIC)
        {
            drawItem = new EleToolItem("",this);
            GraphicBase* graphic = GraphicFactory::createGraphic(i);

            if(graphic)
            {
                drawItem->setGraphic(graphic);
                drawItem->setText(graphic->getDevName());
            }
            else
            {
                assert(false);
            }
            _groupTool.addButton(drawItem,i);
            mainLayout->addWidget(drawItem,row,col);
            col++;
            if(col >= colMax)
            {
                row++;
                col = 0;
            }
        }
    }
    mainLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding),
                        row+1,0); //器件之间 间隔设置  美化
    this->setLayout(mainLayout);
}


