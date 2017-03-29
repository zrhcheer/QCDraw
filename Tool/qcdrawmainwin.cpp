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
    _delAction->setText("删除");
    QIcon icon;
    icon.addFile((":/images/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
    _delAction->setIcon(icon);
    _rotateAction = new QAction(this);
    _rotateAction->setObjectName(QString::fromUtf8("rotateAction"));
    _rotateAction->setText("旋转");
    _mirrorAction = new QAction(this);
    _mirrorAction->setObjectName(QString::fromUtf8("mirrorAction"));
    _mirrorAction->setText("镜像");
    _verBusAction = new QAction(this);
    _verBusAction->setObjectName(QString::fromUtf8("verBusAction"));
    _verBusAction->setText("纵向母线");
    _horBusAction = new QAction(this);
    _horBusAction->setObjectName(QString::fromUtf8("horBusAction"));
    _horBusAction->setText("横向母线");
    _inLineAction = new QAction(this);
    _inLineAction->setObjectName(QString::fromUtf8("inLineAction"));
    _inLineAction->setText("站内线");
    _interLineAction = new QAction(this);
    _interLineAction->setObjectName(QString::fromUtf8("interLineAction"));
    _interLineAction->setText("站间线");
    _inVirLineAction = new QAction(this);
    _inVirLineAction->setObjectName(QString::fromUtf8("inVirLineAction"));
    _inVirLineAction->setText("站内连线");
    _intervirLineAction = new QAction(this);
    _intervirLineAction->setObjectName(QString::fromUtf8("intervirLineAction"));
    _intervirLineAction->setText("站间连线");

    //add ljj
    _moveUpAction = new QAction(this);
    _moveUpAction->setObjectName(QString::fromUtf8("moveUp"));
    _moveUpAction->setText("上移");
    _moveDownAction = new QAction(this);
    _moveDownAction->setObjectName(QString::fromUtf8("moveDown"));
    _moveDownAction->setText("下移");
    _moveLeftAction = new QAction(this);
    _moveLeftAction->setObjectName(QString::fromUtf8("moveLeft"));
    _moveLeftAction->setText("左移");
    _moveRightAction = new QAction(this);
    _moveRightAction->setObjectName(QString::fromUtf8("moveRight"));
    _moveRightAction->setText("右移");

    _openFileAction = new QAction(this);
    _openFileAction->setObjectName(QString::fromUtf8("openFile"));
    _openFileAction->setText("打开");
    //add ljj

    _horizontalAlign = new QAction(this);
    _horizontalAlign->setObjectName(QString::fromUtf8("horizontalAlign"));
    _horizontalAlign->setText("横向对齐");
    _verticalAlign = new QAction(this);
    _verticalAlign->setObjectName(QString::fromUtf8("verticalAlign"));
    _verticalAlign->setText("纵向对齐");

    _saveAction = new QAction(this);
    _saveAction->setObjectName(QString::fromUtf8("saveAction"));
    _saveAction->setText("保存");

    _newFileAction = new QAction(this);
    _newFileAction->setObjectName(QString::fromUtf8("newAction"));
    _newFileAction->setText("新建");


    _saveAsAction = new QAction(this);
    _saveAsAction->setObjectName(QString::fromUtf8("saveAsAction"));
    _saveAsAction->setText("另存为");

    _delConnAction = new QAction(this);
    _delConnAction->setObjectName(QString::fromUtf8("delConnAction"));
    _delConnAction->setText("删除连接");
    _delKneeAction = new QAction(this);
    _delKneeAction->setObjectName(QString::fromUtf8("delKneeAction"));
    _delKneeAction->setText("删除拐点");

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
    setMenuBar(_menuBar);//菜单bar

    _mainToolBar = new QToolBar(this);
    _mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    addToolBar(Qt::TopToolBarArea, _mainToolBar);//工具bar

    _statusBar = new QStatusBar(this);
    _statusBar->setObjectName(QString::fromUtf8("statusBar"));
    setStatusBar(_statusBar);

    _toolWidget = new ToolWidget();   //电力元件
    _toolWidget->setObjectName(QString::fromUtf8("toolWidget"));

    _controlToolWidget = new ControlToolWidget();  //显示控件

    _specialToolWidget = new SpecialToolWidget();//特殊控件显示

    _toolBox = new QToolBox;
    _toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    _toolBox->setMinimumWidth(235);

    _toolBox->addItem(_toolWidget, tr("电力元件"));
    _toolBox->addItem(_controlToolWidget,tr("显示控件"));
    _toolBox->addItem(_specialToolWidget,tr("特殊图形控件"));

    _dockWidget = new QDockWidget(this); //嵌套布局
    _dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
    _dockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);//特性
    _dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);

    _dockWidget->setWidget(_toolBox);
    addDockWidget(static_cast<Qt::DockWidgetArea>(1), _dockWidget);

    _mainToolBar->addAction(_delAction);//工具bar
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
    QObject::connect(_moveUpAction, SIGNAL(triggered()), _canvasView, SLOT(moveUp()));//triggered 触发
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
    _fileMenu = menuBar()->addMenu(tr("&文件"));  //菜单
    _fileMenu->addAction(_newFileAction);
    _fileMenu->addAction(_openFileAction);
    _fileMenu->addAction(_saveAction);
    _fileMenu->addAction(_saveAsAction);

    _itemMenu = menuBar()->addMenu(tr("&操作"));
    _itemMenu->addAction(_delAction);
    _itemMenu->addSeparator();
    _itemMenu->addAction(_rotateAction);
    _itemMenu->addAction(_mirrorAction);

    _aboutMenu = menuBar()->addMenu(tr("&帮助"));
    _aboutMenu->addAction(_saveAction);
}

void QCDrawMainWin::initTool()
{
    _scaleSpin->setMinimum(0.5);
    _scaleSpin->setMaximum(5);
    _scaleSpin->setSingleStep(0.5);
    _mainToolBar->insertWidget(_delConnAction,_scaleSpin);

    _sideCbbox->addItem("高(始)端",Graphic::JOIN_BEGIN);
    _sideCbbox->addItem("中端",Graphic::JOIN_MID);
    _sideCbbox->addItem("低(末)端",Graphic::JOIN_END);
    _sideCbbox->setCurrentIndex(0);
    _mainToolBar->insertWidget(_delConnAction,_sideCbbox);

    _mainToolBar->insertSeparator(ui->verBusAction);
    connect(_scaleSpin,SIGNAL(valueChanged(double)),&_drawScene,SLOT(scaleSelectItem(double))); // change size
}

void QCDrawMainWin::delSelectJoin()  //删除连接
{
    int index = _sideCbbox->currentIndex(); //高中低
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

    QGridLayout *layout = new QGridLayout;  //GridLayout网格布局
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
