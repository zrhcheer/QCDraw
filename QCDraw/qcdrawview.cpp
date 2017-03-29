#include "qcdrawview.h"

#include <QDragEnterEvent>
#include "Graphics/graphicfactory.h"
//#include "Graphics/graphiccursor.h"

QCDrawView::QCDrawView(QWidget *parent) :
    QGraphicsView(parent)
{
    _bPress = false;
    this->setRenderHint(QPainter::Antialiasing);
    this->setMouseTracking(true);
    _scene = NULL;
    fileStr="";
}

//void QCDrawView::setCursorForID(int id)
//{
//    setCursor(GraphicCursor::getInstance()->getCursorFromID(id));
//}
void QCDrawView::setScene(QCDrawScene *scene)
{
    scene->setView(this);
    _scene = scene;
    QGraphicsView::setScene(scene);
}
bool QCDrawView::loadPixmap(QPixmap& pix)
{
    _scene->loadPixmap(pix);
    return true;
}

void QCDrawView::centerOn( const QPointF& pt)
{
    QGraphicsView::centerOn(pt);
}

void QCDrawView::centerOn( const Graphic* graphic)
{
    const QGraphicsItem* item = dynamic_cast<const QGraphicsItem*>(graphic);
    if(item)
    {
        QGraphicsView::centerOn(item);
    }
}

void QCDrawView::rotateSelectItem()
{
    if(_scene)
    {
        _scene->rotateSelectItem();
    }
}
void QCDrawView::delSelectItem()
{
    if(_scene)
    {
        _scene->delSelectItem();
    }
}
void QCDrawView::moveUp()//add ljj
{
    if(_scene)
    {
        int chose=1;
        _scene->movePosition(chose);
    }
}
void QCDrawView::moveDown() //add ljj
{
    if(_scene)
    {
        int chose=2;
        _scene->movePosition(chose);
    }
}
void QCDrawView::moveLeft() //add ljj
{
    if(_scene)
    {
        int chose=3;
        _scene->movePosition(chose);
    }
}
void QCDrawView::moveRight()//add ljj
{
    if(_scene)
    {
        int chose=4;
        _scene->movePosition(chose);
    }
}

bool QCDrawView::delSelectLineKnee()
{
    if(_scene)
    {
        _scene->delSelectLineKnee();
        return true;
    }
    return false;
}

bool QCDrawView::delSelectJoin(int selPos)
{
    if(_scene)
    {
        _scene->delSelectJoin(selPos);
        return false;
    }
    return true;
}

void QCDrawView::mirrorSelectItem()
{
    if(_scene)
    {
        _scene->mirrorSelectItem();
    }
}

void QCDrawView::createVerBus()
{
    if(_scene)
    {
        _scene->createBus(Graphic::POS_UP);
    }
}

void QCDrawView::createHorBus()
{
    if(_scene)
    {
        _scene->createBus(Graphic::POS_RIGHT);
    }
}

void QCDrawView::createInLine()
{
    if(_scene)
    {
        _scene->createLine(Graphic::LINE_NOR | Graphic::LINE_IN);
    }
}
void QCDrawView::createInterLine()
{
    if(_scene)
    {
        _scene->createLine(Graphic::LINE_NOR | Graphic::LINE_OUT);
    }
}

void QCDrawView::createInVirLine()
{
    if(_scene)
    {
        _scene->createLine(Graphic::LINE_VIR | Graphic::LINE_IN);
    }
}

void QCDrawView::createInterVirLine()
{
    if(_scene)
    {
        _scene->createLine(Graphic::LINE_VIR | Graphic::LINE_OUT);
    }
}
void QCDrawView::newFile()
{
    fileStr="";
    _scene->clear();
    _scene->setSceneRect(0,0,1000,600);

}

void QCDrawView::openFile()
{
    if(_scene)
    {
        QString fileName = QFileDialog::getOpenFileName(this,"打开",
                                                        QString("../hisdata/Graphics/"),
                                                        "*.qcd *.xml ;; *.qcd ;; *.xml" );
        fileStr=fileName.toStdString();
        _scene->loadGraphic(fileName);
    }
}

void QCDrawView::saveGraphic()
{
    if(_scene)
    {
        QString initDir="";
        if(""==fileStr)
        {
            initDir=QFileDialog::getSaveFileName(this,"保存",
                                                 QString("../hisdata/Graphics/unname.xml"),
                                                 "*.qcd *.xml ;; *.qcd ;; *.xml");
      //  int first=initDir.lastIndexOf("/");
      // QString type=initDir.right (initDir.length()-first-1);
            fileStr=initDir.toStdString();
        }
        else
        {
            initDir=QString::fromStdString(fileStr);
        }
        _scene->saveGraphic(initDir);
    }
}

void QCDrawView::saveAsGraphic()
{
    if(_scene)
    {
        string fileName="unname.xml";
        if(""!=fileStr)
        {
            size_t pos0=fileStr.find_last_of("/");
            fileName=fileStr.substr(pos0+1,fileStr.size()-pos0-1);
        }

        QString fileNameDir =QFileDialog::getSaveFileName(this,"另存为",
                                                          QString("../hisdata/Graphics/")+QString::fromStdString(fileName),
                                                          "*.qcd *.xml ;; *.qcd ;; *.xml");
         fileStr=fileNameDir.toStdString();
        _scene->saveGraphic(fileNameDir);
    }
}

void QCDrawView::loadGraphic()
{
    if(_scene)
    {
        _scene->loadGraphic("../hisdata/Graphics/NW.");
    }
}

void	QCDrawView::mouseMoveEvent ( QMouseEvent * event )
{
    QGraphicsView::mouseMoveEvent(event);
}

void	QCDrawView::mousePressEvent ( QMouseEvent * event )
{
    QGraphicsView::mousePressEvent(event);
}

void	QCDrawView::mouseReleaseEvent ( QMouseEvent * event )
{
    QGraphicsView::mouseReleaseEvent(event);
}

void QCDrawView::horizontalAlign(void)
{
    if(_scene)
    {
        _scene->horizontalAlign();
    }
}

void QCDrawView::verticalAlign(void)
{
    if(_scene)
    {
        _scene->verticalAlign();
    }
}
