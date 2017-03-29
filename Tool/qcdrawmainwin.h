#ifndef QCDRAWDLG_H
#define QCDRAWDLG_H

#include <QMainWindow>
#include <QToolButton>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QToolBox>
#include <QLabel>
#include "toolwidget.h"
#include "../QCDraw/qcdrawview.h"
#include "controltoolwidget.h"
#include"specialtoolwidget.h"

#include "qcdrawscene.h"
namespace Ui {
class QCDrawMainWin;
}

class QCDrawMainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit QCDrawMainWin(QWidget *parent = 0);
    ~QCDrawMainWin();

private slots:
    void delSelectJoin();
    void backgroundButtonGroupClicked(QAbstractButton *button);
private:
    void initTool();
    void createWidgets(void);
    void createMenus(void);
    QWidget *createBackgroundCellWidget(const QString &text, const QString &image);

private:
    Ui::QCDrawMainWin *ui;
    QCDrawScene _drawScene;
    QCDrawView* _canvasView;
    QToolBar *_mainToolBar;
    QAction *_delConnAction;
    QAction *_verBusAction;
    QAction *_delAction;
    QAction *_rotateAction;
    QAction *_mirrorAction;
    QAction *_moveUpAction;  //add ljj
    QAction *_moveDownAction; //add ljj
    QAction *_moveLeftAction;  //add ljj
    QAction *_moveRightAction; //add ljj
    QAction *_newFileAction;
    QAction *_openFileAction;
    QAction *_horizontalAlign;
    QAction *_verticalAlign;
    QAction *_horBusAction;
    QAction *_inLineAction;
    QAction *_interLineAction;
    QAction *_inVirLineAction;
    QAction *_intervirLineAction;
    QAction *_saveAction;
    QAction *_saveAsAction;
    QAction *_delKneeAction;
    QWidget *_centralWidget;
    QVBoxLayout *_verticalLayout;
    QMenuBar * _menuBar;
    QStatusBar *_statusBar;
    QDockWidget *_dockWidget;
    ToolWidget *_toolWidget;
    SpecialToolWidget *_specialToolWidget;
    ControlToolWidget* _controlToolWidget;

    QToolBox *_toolBox;
    QButtonGroup *_backgroundButtonGroup;

    QMenu *_fileMenu;
    QMenu *_itemMenu;
    QMenu *_aboutMenu;

    QDoubleSpinBox* _scaleSpin;
    QComboBox* _sideCbbox;
};

#endif // QCDRAWDLG_H
