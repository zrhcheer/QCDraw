#ifndef QCDRAWDLG_H
#define QCDRAWDLG_H

#include <QDialog>

namespace Ui {
class QCDrawDlg;
}

class QCDrawDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit QCDrawDlg(QWidget *parent = 0);
    ~QCDrawDlg();
    

private:
    Ui::QCDrawDlg *ui;
};

#endif // QCDRAWDLG_H
