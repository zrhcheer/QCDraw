#include "controltoolwidget.h"
#include <QGridLayout>
#include "imagevbutton.h"
#include <QMouseEvent>
#include "Graphics/utilfunc.h"
#include <QApplication>
#include "Graphics/graphic.h"

ControlToolWidget::ControlToolWidget(QWidget *parent) :
    QWidget(parent)
{
    _mapCompSetting.insert(make_pair(Graphic::GRAPHIC_CONTROL_TABLE,
                                     CompentSetting("���ؼ�",":/images/tablecheck.png",Graphic::GRAPHIC_CONTROL_TABLE)));
    _mapCompSetting.insert(make_pair(Graphic::GRAPHIC_CONTROL_COMBOX,
                                     CompentSetting("�����б��",":/images/comboxcheck.png",Graphic::GRAPHIC_CONTROL_COMBOX)));
    _mapCompSetting.insert(make_pair(Graphic::GRAPHIC_CONTROL_LABLE,
                                     CompentSetting("��ǩ",":/images/labelcheck.png",Graphic::GRAPHIC_CONTROL_LABLE)));
    _mapCompSetting.insert(make_pair(Graphic::GRAPHIC_CONTROL_PUSHBUTTON,
                                     CompentSetting("��ť",":/images/btncheck.png",Graphic::GRAPHIC_CONTROL_PUSHBUTTON)));
    _mapCompSetting.insert(make_pair(Graphic::GRAPHIC_CONTROL_BARCHART,
                                     CompentSetting("��״ͼ",":/images/polarcheck.png",Graphic::GRAPHIC_CONTROL_BARCHART)));
    _mapCompSetting.insert(make_pair(Graphic::GRAPHIC_CONTROL_MUTICURVECHART,
                                     CompentSetting("����ͼ",":/images/polycheck.png",Graphic::GRAPHIC_CONTROL_MUTICURVECHART)));
    _mapCompSetting.insert(make_pair(Graphic::GRAPHIC_CONTROL_SIMICIRCLECHART,
                                     CompentSetting("����ͼ",":/images/piecheck.png",Graphic::GRAPHIC_CONTROL_SIMICIRCLECHART)));
    initTool();
}


void ControlToolWidget::controlButtonGroupPressed(int id)
{
    map<int,CompentSetting>::const_iterator iterCompSetting = _mapCompSetting.find(id);
    if(iterCompSetting == _mapCompSetting.end())
    {
        return;
    }
    const CompentSetting& tmpCompSetting = iterCompSetting->second;
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    // ��ip��ַ����
    QString strType = QString::number(id);
    mimeData->setData("custom/control",strType.toUtf8());
    drag->setMimeData(mimeData);

    // ����ͼƬ
    QPixmap drag_img(QString::fromStdString(tmpCompSetting._picPath));
    drag->setPixmap(drag_img);
    drag->setHotSpot(QPoint(drag_img.width() / 2,drag_img.height() / 2));

    Qt::DropAction resultAction = drag->exec(Qt::MoveAction);
    if(resultAction == Qt::MoveAction)
    {
        // ȷ���ƶ�����
        // �ò����Ѿ���Ŀ��������ܣ��Ҳ�������ΪMOVE��һ����˵Ӧ�ðѱ��϶��������Դ����ɾ��
    }
}

void ControlToolWidget::initTool()
{
    QGridLayout *backgroundLayout = new QGridLayout;
    connect(&_controlButtonGroup, SIGNAL(buttonPressed(int)),
            this, SLOT(controlButtonGroupPressed(int)));

    int row = 0;
    int col = 0;
    for(map<int,CompentSetting>::const_iterator iterCompSetting = _mapCompSetting.begin();
        iterCompSetting != _mapCompSetting.end(); ++iterCompSetting)
    {
        const CompentSetting& tmpSetting = iterCompSetting->second;
        QPushButton* tmpBtn = createBackgroundCellWidget(tmpSetting._name,tmpSetting._picPath);
        tmpBtn->setCheckable(true);
        _controlButtonGroup.addButton(tmpBtn,tmpSetting._id);
        backgroundLayout->addWidget(tmpBtn, row, col);
        col++;
        if(col > 2)
        {
            row++;
            col = 0;
        }
    }

    QSpacerItem *vSpacer = new QSpacerItem(20, 20,QSizePolicy::Minimum,QSizePolicy::Expanding);
    if(col > 0)
    {
        backgroundLayout->addItem(vSpacer,row + 1, 0);
    }
    else
    {
        backgroundLayout->addItem(vSpacer,row, 0);
    }
    //backgroundLayout->setColumnStretch(2, 10);
    this->setLayout(backgroundLayout);
}

QPushButton * ControlToolWidget::createBackgroundCellWidget(const string &text, const string &image)
{
    ImageVButton *button = new ImageVButton;
    button->setImage(QString::fromStdString(image),QString::fromStdString(image));
    button->setText(QString::fromStdString(text));
    button->setNormalColor(QColor(Qt::black));
    button->setSelectColor(QColor(Qt::black));
    button->setHovColor(QColor(Qt::black));
    return button;
}
