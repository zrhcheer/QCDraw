#include "qcdrawmainwin.h"
#include "ui_qcdrawmainwin.h"
#include "eletoolitem.h"
#include "Graphics/graphicfactory.h"

QCDrawMainWin::QCDrawMainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QCDrawMainWin)
{
    ui->setupUi(this);
    createWidgets();
    initTool();
    createMenus();

    _canvasView->setScene(&_drawScene);
    _drawScene.setSceneRect(0,0,1000,600);
    _drawScene.setConfig(_canvasView->getConfig());
}
QCDrawMainWin::~QCDrawMainWin()
{
    delete ui;
}

void QCDrawMainWin::createWidgets(void)
{
    _scaleSpin = new QDoubleSpinBox(this);
    _sideCbbox = new QComboBox(this);
    _delAction = new QAction(this);
    _delAction->setObjectName(QString::fromUtf8("delAction"));
    _delAction->setText("ɾ��");
    QIcon icon;
    icon.addFile((":/images/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
    _delAction->setIcon(icon);
    _rotateAction = new QAction(this);
    _rotateAction->setObjectName(QString::fromUtf8("rotateAction"));
    _rotateAction->setText("��ת");
    _mirrorAction = new QAction(this);
    _mirrorAction->setObjectName(QString::fromUtf8("mirrorAction"));
    _mirrorAction->setText("����");
    _verBusAction = new QAction(this);
    _verBusAction->setObjectName(QString::fromUtf8("verBusAction"));
    _verBusAction->setText("����ĸ��");
    _horBusAction = new QAction(this);
    _horBusAction->setObjectName(QString::fromUtf8("horBusAction"));
    _horBusAction->setText("����ĸ��");
    _inLineAction = new QAction(this);
    _inLineAction->setObjectName(QString::fromUtf8("inLineAction"));
    _inLineAction->setText("վ����");
    _interLineAction = new QAction(this);
    _interLineAction->setObjectName(QString::fromUtf8("interLineAction"));
    _interLineAction->setText("վ����");
    _inVirLineAction = new QAction(this);
    _inVirLineAction->setObjectName(QString::fromUtf8("inVirLineAction"));
    _inVirLineAction->setText("վ������");
    _intervirLineAction = new QAction(this);
    _intervirLineAction->setObjectName(QString::fromUtf8("intervirLineAction"));
    _intervirLineAction->setText("վ������");

    //add ljj
    _moveUpAction = new QAction(this);
    _moveUpAction->setObjectName(QString::fromUtf8("moveUp"));
    _moveUpAction->setText("����");
    _moveDownAction = new QAction(this);
    _moveDownAction->setObjectName(QString::fromUtf8("moveDown"));
    _moveDownAction->setText("����");
    _moveLeftAction = new QAction(this);
    _moveLeftAction->setObjectName(QString::fromUtf8("moveLeft"));
    _moveLeftAction->setText("����");
    _moveRightAction = new QAction(this);
    _moveRightAction->setObjectName(QString::fromUtf8("moveRight"));
    _moveRightAction->setText("����");

    _openFileAction = new QAction(this);
    _openFileAction->setObjectName(QString::fromUtf8("openFile"));
    _openFileAction->setText("��");
    //add ljj

    _horizontalAlign = new QAction(this);
    _horizontalAlign->setObjectName(QString::fromUtf8("horizontalAlign"));
    _horizontalAlign->setText("�������");
    _verticalAlign = new QAction(this);
    _verticalAlign->setObjectName(QString::fromUtf8("verticalAlign"));
    _verticalAlign->setText("�������");

    _saveAction = new QAction(this);
    _saveAction->setObjectName(QString::fromUtf8("saveAction"));
    _saveAction->setText("����");

    _newFileAction = new QAction(this);
    _newFileAction->setObjectName(QString::fromUtf8("newAction"));
    _newFileAction->setText("�½�");


    _saveAsAction = new QAction(this);
    _saveAsAction->setObjectName(QString::fromUtf8("saveAsAction"));
    _saveAsAction->setText("���Ϊ");

    _delConnAction = new QAction(this);
    _delConnAction->setObjectName(QString::fromUtf8("delConnAction"));
    _delConnAction->setText("ɾ������");
    _delKneeAction = new QAction(this);
    _delKneeAction->setObjectName(QString::fromUtf8("delKneeAction"));
    _delKneeAction->setText("ɾ���յ�");

    _centralWidget = new QWidget(this);
    _centralWidget->setObjectName(QString::fromUtf8("centralWidget"));

    _verticalLayout = new QVBoxLayout(_centralWidget);
    _verticalLayout->setSpacing(6);
    _verticalLayout->setContentsMargins(11, 11, 11, 11);
    _verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

    _canvasView = new QCDrawView(_centralWidget);
    _canvasView->setObjectName(QString::fromUtf8("canvasView"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(_canvasView->sizePolicy().hasHeightForWidth());
    _canvasView->setSizePolicy(sizePolicy);

    _verticalLayout->addWidget(_canvasView);

    setCentralWidget(_centralWidget);

    _menuBar = new QMenuBar(this);
    _menuBar->setObjectName(QString::fromUtf8("menuBar"));
    _menuBar->setGeometry(QRect(0, 0, 588, 25));
    setMenuBar(_menuBar);//�˵�bar

    _mainToolBar = new QToolBar(this);
    _mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    addToolBar(Qt::TopToolBarArea, _mainToolBar);//����bar

    _statusBar = new QStatusBar(this);
    _statusBar->setObjectName(QString::fromUtf8("statusBar"));
    setStatusBar(_statusBar);

    _toolWidget = new ToolWidget();   //����Ԫ��
    _toolWidget->setObjectName(QString::fromUtf8("toolWidget"));

    _controlToolWidget = new ControlToolWidget();  //��ʾ�ؼ�

    _specialToolWidget = new SpecialToolWidget();//����ؼ���ʾ

    _toolBox = new QToolBox;
    _toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    _toolBox->setMinimumWidth(235);

    _toolBox->addItem(_toolWidget, tr("����Ԫ��"));
    _toolBox->addItem(_controlToolWidget,tr("��ʾ�ؼ�"));
    _toolBox->addItem(_specialToolWidget,tr("����ͼ�οؼ�"));

    _dockWidget = new QDockWidget(this); //Ƕ�ײ���
    _dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
    _dockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);//����
    _dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);

    _dockWidget->setWidget(_toolBox);
    addDockWidget(static_cast<Qt::DockWidgetArea>(1), _dockWidget);

    _mainToolBar->addAction(_delAction);//����bar
    _mainToolBar->addAction(_rotateAction);
    _mainToolBar->addAction(_mirrorAction);

    _mainToolBar->addAction(_delConnAction);
    _mainToolBar->addAction(_delKneeAction);
    _mainToolBar->addSeparator();

    _mainToolBar->addAction(_verBusAction);
    _mainToolBar->addAction(_horBusAction);
    _mainToolBar->addSeparator();

    _mainToolBar->addAction(_inLineAction);
    _mainToolBar->addAction(_interLineAction);
    _mainToolBar->addAction(_inVirLineAction);
    _mainToolBar->addAction(_intervirLineAction);
    _mainToolBar->addSeparator();

    _mainToolBar->addAction(_moveUpAction);
    _mainToolBar->addAction(_moveDownAction);
    _mainToolBar->addAction(_moveLeftAction);
    _mainToolBar->addAction(_moveRightAction);
    _mainToolBar->addSeparator();

    _mainToolBar->addAction(_horizontalAlign);
    _mainToolBar->addAction(_verticalAlign);

    _mainToolBar->addSeparator();
    _mainToolBar->addAction(_saveAction);

    QObject::connect(_newFileAction, SIGNAL(triggered()), _canvasView, SLOT(newFile()));
    QObject::connect(_openFileAction, SIGNAL(triggered()), _canvasView, SLOT(openFile()));
    QObject::connect(_moveUpAction, SIGNAL(triggered()), _canvasView, SLOT(moveUp()));//triggered ����
    QObject::connect(_moveDownAction, SIGNAL(triggered()), _canvasView, SLOT(moveDown()));
    QObject::connect(_moveLeftAction, SIGNAL(triggered()), _canvasView, SLOT(moveLeft()));
    QObject::connect(_moveRightAction, SIGNAL(triggered()), _canvasView, SLOT(moveRight()));
    QObject::connect(_delAction, SIGNAL(triggered()), _canvasView, SLOT(delSelectItem()));
    QObject::connect(_rotateAction, SIGNAL(triggered()), _canvasView, SLOT(rotateSelectItem()));
    QObject::connect(_mirrorAction, SIGNAL(triggered()), _canvasView, SLOT(mirrorSelectItem()));
    QObject::connect(_verBusAction, SIGNAL(triggered()), _canvasView, SLOT(createVerBus()));
    QObject::connect(_horBusAction, SIGNAL(triggered()), _canvasView, SLOT(createHorBus()));
    QObject::connect(_inLineAction, SIGNAL(triggered()), _canvasView, SLOT(createInLine()));
    QObject::connect(_inVirLineAction, SIGNAL(triggered()), _canvasView, SLOT(createInVirLine()));
    QObject::connect(_intervirLineAction, SIGNAL(triggered()), _canvasView, SLOT(createInterVirLine()));
    QObject::connect(_delKneeAction, SIGNAL(triggered()), _canvasView, SLOT(delSelectLineKnee()));
    QObject::connect(_horizontalAlign, SIGNAL(triggered()), _canvasView, SLOT(horizontalAlign()));
    QObject::connect(_verticalAlign, SIGNAL(triggered()), _canvasView, SLOT(verticalAlign()));
    QObject::connect(_delConnAction, SIGNAL(triggered()), this, SLOT(delSelectJoin()));
    QObject::connect(_saveAction, SIGNAL(triggered()), _canvasView, SLOT(saveGraphic()));
    QObject::connect( _saveAsAction, SIGNAL(triggered()), _canvasView, SLOT(saveAsGraphic()));
    QMetaObject::connectSlotsByName(this);
}

void QCDrawMainWin::createMenus(void)
{
    _fileMenu = menuBar()->addMenu(tr("&�ļ�"));  //�˵�
    _fileMenu->addAction(_newFileAction);
    _fileMenu->addAction(_openFileAction);
    _fileMenu->addAction(_saveAction);
    _fileMenu->addAction(_saveAsAction);

    _itemMenu = menuBar()->addMenu(tr("&����"));
    _itemMenu->addAction(_delAction);
    _itemMenu->addSeparator();
    _itemMenu->addAction(_rotateAction);
    _itemMenu->addAction(_mirrorAction);

    _aboutMenu = menuBar()->addMenu(tr("&����"));
    _aboutMenu->addAction(_saveAction);
}

void QCDrawMainWin::initTool()
{
    _scaleSpin->setMinimum(0.5);
    _scaleSpin->setMaximum(5);
    _scaleSpin->setSingleStep(0.5);
    _mainToolBar->insertWidget(_delConnAction,_scaleSpin);

    _sideCbbox->addItem("��(ʼ)��",Graphic::JOIN_BEGIN);
    _sideCbbox->addItem("�ж�",Graphic::JOIN_MID);
    _sideCbbox->addItem("��(ĩ)��",Graphic::JOIN_END);
    _sideCbbox->setCurrentIndex(0);
    _mainToolBar->insertWidget(_delConnAction,_sideCbbox);

    _mainToolBar->insertSeparator(ui->verBusAction);
    connect(_scaleSpin,SIGNAL(valueChanged(double)),&_drawScene,SLOT(scaleSelectItem(double))); // change size
}

void QCDrawMainWin::delSelectJoin()  //ɾ������
{
    int index = _sideCbbox->currentIndex(); //���е�
    if(index >= 0)
    {
        int pos = _sideCbbox->itemData(index).toInt();
        _canvasView->delSelectJoin(pos);
    }
}

QWidget * QCDrawMainWin::createBackgroundCellWidget(const QString &text, const QString &image)
{
    QToolButton *button = new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    _backgroundButtonGroup->addButton(button);

    QGridLayout *layout = new QGridLayout;  //GridLayout���񲼾�
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

void QCDrawMainWin::backgroundButtonGroupClicked(QAbstractButton *button)
{
    QList<QAbstractButton *> buttons = _backgroundButtonGroup->buttons();
    foreach (QAbstractButton *myButton, buttons)
    {
        if (myButton != button)
            button->setChecked(false);
    }
    QString text = button->text();
    if (text == tr("Blue Grid"))
        _drawScene.setBackgroundBrush(QPixmap(":/images/background1.png"));
    else if (text == tr("White Grid"))
        _drawScene.setBackgroundBrush(QPixmap(":/images/background2.png"));
    else if (text == tr("Gray Grid"))
        _drawScene.setBackgroundBrush(QPixmap(":/images/background3.png"));
    else
        _drawScene.setBackgroundBrush(QPixmap(":/images/background4.png"));

    _drawScene.update();
    _canvasView->update();
}
