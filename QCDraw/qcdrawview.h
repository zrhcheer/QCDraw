#ifndef QCDRAWVIEW_H
#define QCDRAWVIEW_H
#include <QFileDialog>
#include <QGraphicsView>
#include "qcdrawscene.h"
#include <QCursor>
#include <QTextCodec>
class QCDrawView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QCDrawView(QWidget *parent = 0);
    //设置场景
    void setScene(QCDrawScene* scene);
    //设置光标
    //void setCursorForID(int id);
    //加载pix图形
    bool loadPixmap(QPixmap& pix);
    //滚动窗口的内容,以确保项目集中在视图中。
    void centerOn( const QPointF& pt);
    void centerOn( const Graphic* graphic);
    QString GBKTOUTF8(const QString &inStr);
protected:
    //鼠标移动事件
    virtual void	mouseMoveEvent ( QMouseEvent * event );
    //鼠标点击事件
    virtual void	mousePressEvent ( QMouseEvent * event );
    //鼠标释放事件
    virtual void	mouseReleaseEvent ( QMouseEvent * event );
public  slots:
    //旋转被选择元件
    void rotateSelectItem();
    //删除被选择元件
    void delSelectItem();
    //删除被选则线路拐点
    bool delSelectLineKnee();
    //删除被选则元件在selPos处的链接
    bool delSelectJoin(int selPos);
    //镜像被选则元件
    void mirrorSelectItem();
    //创建纵向母线
    void createVerBus();
    //创建横向母线
    void createHorBus();
    //创建站内线
    void createInLine();
    void createInterLine();
    //创建站内连线
    void createInVirLine();
    //创建站间连线
    void createInterVirLine();
    //新建
    void newFile();
    //保存
    void saveGraphic();
    //另存为
    void saveAsGraphic();
    //恢复
    void loadGraphic();
    //打开
    void openFile();
    //上移
    void moveUp(); //add ljj
    //下移
    void moveDown(); //
    //左移
    void moveLeft();//
    //右移
    void moveRight();//
    //横向对齐
    void horizontalAlign(void);
    //纵向对齐
    void verticalAlign(void);

    const GraphicConfig* getConfig() const
    {
        return &_config;
    }

    void setIsUtf8(const bool& bUtf8)
    {
        _config.setIsUtf8(bUtf8);
    }

protected:
    GraphicConfig _config;//锁定状态
private:
    bool _bPress;
    QPoint  tmpPoint2;
    QCDrawScene* _scene;
    string fileStr;

};

#endif // QCDRAWVIEW_H
