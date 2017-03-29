#include "specialtoolwidget.h"

#include <assert.h>
#include <QGridLayout>
#include <QSpacerItem>

#include "Graphics/graphicfactory.h"
#include "Graphics/graphicbase.h"
#include"specieletoolitem.h"
#include"SpecialGraphics/dynamicpointgraphic.h"

SpecialToolWidget::SpecialToolWidget(QWidget *parent) :
    QWidget(parent)
{
    initTool();
}

void SpecialToolWidget::initTool()
{
    //    int colMax = 3;
    SpeciEleToolItem* drawItem = NULL;
//    int row = 0;
//    int col = 0;
    //    int rowMax  = 0;
    //    if(Graphic::GRAPHIC_MAX  % colMax)
    //    {
    //        rowMax = Graphic::GRAPHIC_MAX / colMax + 1;
    //    }
    //    else
    //    {
    //        rowMax = Graphic::GRAPHIC_MAX / colMax;
    //    }
//    QGridLayout* mainLayout = new QGridLayout(this);
    //    for(int i = 0; i < Graphic::GRAPHIC_MAX; ++i)
    //    {
    drawItem = new SpeciEleToolItem("",this);

    GraphicBase* graphic = GraphicFactory::createGraphic(Graphic::GRAPHIC_DYNAMIC);
    if(graphic)
    {
        drawItem->setGraphic(graphic);
        drawItem->setText(graphic->getDevName());
    }
    else
    {
        assert(false);
    }

    //        _groupTool.addButton(drawItem,i);
//    mainLayout->addWidget(drawItem,row,col);
    //        col++;
    //        if(col >= colMax)
    //        {
    //            row++;
    //            col = 0;
    //        }
    //    }
//    mainLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding),
//                        row+1,0);
//    this->setLayout(mainLayout);
}
