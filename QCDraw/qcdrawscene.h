#ifndef QCDRAWSCENE_H
#define QCDRAWSCENE_H

#include <QGraphicsScene>
#include <string>
#include <map>
using namespace std;
#include "Graphics/graphicbase.h"
#include "Graphics/graphicconfig.h"
#include "Graphics/nodelink.h"
#include "Graphics/graphicknee.h"
#include "Graphics/graphicselector.h"
#include "Graphics/graphiccreator.h"
#include "Graphics/idcreator.h"
#include "Widgets/widgetgraphicbase.h"

#define SERIAL_CODE 0xa1a2a3a4
//#include "qcdrawview.h"
class QCDrawView;
class ShrinkTick;
class QCDrawScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum
    {
        OPER_SELECT,
        OPER_CREATE
    };
    enum  //added by ljj
    {
        MOVE_UP=1,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT
    };
    explicit QCDrawScene(QObject *parent = 0);
    explicit QCDrawScene(const GraphicConfig* config,QObject *parent = 0);

    //设置视图
    void setView(QCDrawView* view);
    //根据文件加载所有电器元件以及连线(将厂站、线路加载到_scene)
    bool loadGraphic(const QString& strPathName);
    //根据路径保存
    bool saveGraphic(const QString& strPath);

    //保存路径测试数据
    bool saveGraphicTest(const QString& strPath);

    //加载pix图形
    bool loadPixmap(QPixmap& pix);

    //刪除元件或者控件
    void removeGraphicItem(Graphic * item,bool bDel = true);
    void removeGraphicTotal(Graphic * item);
    void removeGraphicTotalByID(const ulong64& id);

    //得到拓扑图
    bool calcGraphicTopo(map<TopoJoin,int>& mapJoin);

    //获取画布大小
    void getCanvasSize(int& width,int& height);
    //设置画布大小
    void setCanvasSize(int& width,int& height);


    //添加元件
    void addGraphic(Graphic *graphic,bool bAdd = true)
    {
        //Graphic* graphic = dynamic_cast<Graphic*>(item);
        //assert(graphic);
        _allElement.insert(make_pair(graphic->getID(),graphic));
        if(bAdd)
        {
            QGraphicsItem* itemTmp = dynamic_cast<QGraphicsItem*>(graphic);
            QGraphicsScene::addItem(itemTmp);
        }
    }
    //添加控件
    void addWidget(WidgetGraphicBase* widgetGraphic)
    {
        QGraphicsScene::addWidget(widgetGraphic);
        _allElement.insert(make_pair(widgetGraphic->getID(),widgetGraphic));
    }
    //清空
    void clear()
    {
        _selector.clear();
        _allElement.clear();
        QGraphicsScene::clear();
    }
    bool isEmpty()
    {
        return _allElement.empty();
    }
    //查找元件
    Graphic* findGraphic(const ulong64& id)
    {
        map<ulong64,Graphic*>::iterator iterEle = _allElement.find(id);
        if(iterEle != _allElement.end())
        {
            return iterEle->second;
        }
        return NULL;
    }

    //设置名称
    void setName(const QString& name)
    {
        _name = name;
    }
    //获取名称
    const QString& getName() const
    {
        return _name;
    }
    //设置显示名称
    void setShowName(const QString& name)
    {
        _showName = name;
    }
    //获取显示的名称
    const QString& getShowName() const
    {
        return _showName;
    }
    //获取锁定状态
    const GraphicConfig* getConfig() const
    {
        return _config;
    }
    void setConfig(const GraphicConfig* config)
    {
        _config = config;
    }

    //获取显示的元件
    map<ulong64,Graphic*>& getAllElement()
    {
        return _allElement;
    }
//    set<WidgetGraphicBase*>& getAllControl()
//    {
//        return _allControl;
//    }
    //选中这点上的所有元件
    QList<GraphicPort> selectMultiJoinItem(const QPointF& selPoint);
    //获取鼠标点击的元件
    Graphic* selectSingleItem(const QPointF& selPoint);
    QCDrawView* getView()
    {
        return _view;
    }
    //设置光标
    //void setCursorFromID(int indexCursor);
    //设置厂站索引
    void setStationIndex(uint16 indexStation)
    {
        _indexStation = indexStation;
        _idCreator.setStationId(indexStation);
    }

    void setID(ulong64 id)
    {
        _id = id;
    }
    const ulong64& getID() const
    {
        return _id;
    }

    //创建ID
    ulong64 createId()
    {
        return _idCreator.createId();
    }
    //创建ID
    ulong64 createId(uint16 idStationSec)
    {
        return _idCreator.createInterId(idStationSec);
    }
    //上移/下移/左移/右移
    void movePosition( int&chose);
    //水平对齐
    void horizontalAlign(void);
    //垂直对齐
    void verticalAlign(void);
    //选择框选范围
    void selectScene(QPointF &point);
    //将框选范围内的元件置为选中
    void showSelectSceneItems(QPointF& point);
    ShrinkTick* addNewChaDong(Graphic* parentGraphic);
    void clearChaDong();

signals:
    ///
    /// \brief clickElement
    ///鼠标双击事件触发
    void clickElement(const Graphic*);//第一个参数是名字,第二个是类型
    void selectElement(GraphicSelector&,const int&,const bool&);
//    void clickRightElement(GraphicSelector&,const int&);
//    void selectStaElement(const QString&,const ulong64&);
protected:
    //加载背景
    virtual void	drawBackground ( QPainter * painter, const QRectF & rect );
    //元件拖入事件
    virtual void dragEnterEvent ( QGraphicsSceneDragDropEvent * event);
    //元件拖出事件
    virtual void dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
    //拖动元件事件
    virtual void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
    virtual void dropEvent ( QGraphicsSceneDragDropEvent * event );
    //鼠标点击事件
    virtual void	mousePressEvent (QGraphicsSceneMouseEvent * mouseEvent);
    //鼠标移动事件
    virtual void	mouseMoveEvent (QGraphicsSceneMouseEvent * mouseEvent);
    //鼠标释放事件
    virtual void	mouseReleaseEvent (QGraphicsSceneMouseEvent * mouseEvent);
    //鼠标双击事件
    virtual void	mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
//    virtual void dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
//    virtual void dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
//    virtual void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
//    virtual void dropEvent ( QGraphicsSceneDragDropEvent * event );

public slots:
    //旋转(选中元件)
    void rotateSelectItem();
    //镜像(选中元件)
    void mirrorSelectItem();
    //放缩(选中元件)
    double scaleSelectItem(double scale);
    //删除(选中元件)
    bool delSelectItem();
    //删除拐点
    bool delSelectLineKnee();
    //删除链接
    bool delSelectJoin(int selPos);
    //创建母线
    void createBus(int direct);
    //创建线路
    void createLine(int lineType);
    //设置选中的元件
    void showSelectItem(Graphic*selItem);


private:


    //得到选中元件
    Graphic* findCurrentEle(QGraphicsItem* graphic,bool bBasic = false);
    //计算设备结点編号
    void calcGraphicNode(map<TopoJoin,int>& mapJoin,Graphic* tmpGraphic,int& nodeInc);
    //使得给定点始终在当前矩形内部
    void	limitPoint(QPointF& scenePoint );

    QMap<ulong64,ShrinkTick*> _chaDongAll;
    QCDrawView* _view;//视图

    IDCreator _idCreator;//创建的ID
    //选中相关
    GraphicSelector _selector;//选中的元件
    GraphicCreator _creator;//要创建的元件

//    Graphic*	_selectItem;
//    GraphicKnee _knee;//选中线路或母线时选中的拐点，-1是没有选中
//    QPointF _selectPoint;
    uint16 _indexStation;//厂站索引

    ulong64 _id;//id
    QString _name;//名字
    QString _showName;//显示的名字
    const GraphicConfig* _config;//锁定状态
    map<ulong64,Graphic*> _allElement;//用于存储所有显示的元件
    //set<WidgetGraphicBase*> _allControl;
    int _oper;//OPER_SELECT,OPER_CREATE
    QColor _bkColor;
    QColor _foreColor;
    QPointF _beginPoint;//框选范围时的起始点
    QGraphicsRectItem *_rectItem;//框选范围时的矩形
    bool _isSelectScene;//是否在进行框选操作
};

#endif // QCDRAWSCENE_H
