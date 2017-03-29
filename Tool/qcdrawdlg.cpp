#include "qcdrawdlg.h"
#include "ui_qcdrawdlg.h"
#include "eletoolitem.h"

QCDrawDlg::QCDrawDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCDrawDlg)
{
    ui->setupUi(this);
    //this->setWindowTitle("ÄãºÃ");
}

QCDrawDlg::~QCDrawDlg()
{
    delete ui;
}
