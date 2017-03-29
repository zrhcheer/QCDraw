#include "qcdrawdlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCDrawDlg w;
    w.show();
    
    return a.exec();
}
