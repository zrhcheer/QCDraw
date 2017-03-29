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

    //������ͼ
    void setView(QCDrawView* view);
    //�����ļ��������е���Ԫ���Լ�����(����վ����·���ص�_scene)
    bool loadGraphic(const QString& strPathName);
    //����·������
    bool saveGraphic(const QString& strPath);

    //����·����������
    bool saveGraphicTest(const QString& strPath);

    //����pixͼ��
    bool loadPixmap(QPixmap& pix);

    //�h��Ԫ�����߿ؼ�
    void removeGraphicItem(Graphic * item,bool bDel = true);
    void removeGraphicTotal(Graphic * item);
    void removeGraphicTotalByID(const ulong64& id);

    //�õ�����ͼ
    bool calcGraphicTopo(map<TopoJoin,int>& mapJoin);

    //��ȡ������С
    void getCanvasSize(int& width,int& height);
    //���û�����С
    void setCanvasSize(int& width,int& height);


    //���Ԫ��
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
    //��ӿؼ�
    void addWidget(WidgetGraphicBase* widgetGraphic)
    {
        QGraphicsScene::addWidget(widgetGraphic);
        _allElement.insert(make_pair(widgetGraphic->getID(),widgetGraphic));
    }
    //���
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
    //����Ԫ��
    Graphic* findGraphic(const ulong64& id)
    {
        map<ulong64,Graphic*>::iterator iterEle = _allElement.find(id);
        if(iterEle != _allElement.end())
        {
            return iterEle->second;
        }
        return NULL;
    }

    //��������
    void setName(const QString& name)
    {
        _name = name;
    }
    //��ȡ����
    const QString& getName() const
    {
        return _name;
    }
    //������ʾ����
    void setShowName(const QString& name)
    {
        _showName = name;
    }
    //��ȡ��ʾ������
    const QString& getShowName() const
    {
        return _showName;
    }
    //��ȡ����״̬
    const GraphicConfig* getConfig() const
    {
        return _config;
    }
    void setConfig(const GraphicConfig* config)
    {
        _config = config;
    }

    //��ȡ��ʾ��Ԫ��
    map<ulong64,Graphic*>& getAllElement()
    {
        return _allElement;
    }
//    set<WidgetGraphicBase*>& getAllControl()
//    {
//        return _allControl;
//    }
    //ѡ������ϵ�����Ԫ��
    QList<GraphicPort> selectMultiJoinItem(const QPointF& selPoint);
    //��ȡ�������Ԫ��
    Graphic* selectSingleItem(const QPointF& selPoint);
    QCDrawView* getView()
    {
        return _view;
    }
    //���ù��
    //void setCursorFromID(int indexCursor);
    //���ó�վ����
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

    //����ID
    ulong64 createId()
    {
        return _idCreator.createId();
    }
    //����ID
    ulong64 createId(uint16 idStationSec)
    {
        return _idCreator.createInterId(idStationSec);
    }
    //����/����/����/����
    void movePosition( int&chose);
    //ˮƽ����
    void horizontalAlign(void);
    //��ֱ����
    void verticalAlign(void);
    //ѡ���ѡ��Χ
    void selectScene(QPointF &point);
    //����ѡ��Χ�ڵ�Ԫ����Ϊѡ��
    void showSelectSceneItems(QPointF& point);
    ShrinkTick* addNewChaDong(Graphic* parentGraphic);
    void clearChaDong();

signals:
    ///
    /// \brief clickElement
    ///���˫���¼�����
    void clickElement(const Graphic*);//��һ������������,�ڶ���������
    void selectElement(GraphicSelector&,const int&,const bool&);
//    void clickRightElement(GraphicSelector&,const int&);
//    void selectStaElement(const QString&,const ulong64&);
protected:
    //���ر���
    virtual void	drawBackground ( QPainter * painter, const QRectF & rect );
    //Ԫ�������¼�
    virtual void dragEnterEvent ( QGraphicsSceneDragDropEvent * event);
    //Ԫ���ϳ��¼�
    virtual void dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
    //�϶�Ԫ���¼�
    virtual void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
    virtual void dropEvent ( QGraphicsSceneDragDropEvent * event );
    //������¼�
    virtual void	mousePressEvent (QGraphicsSceneMouseEvent * mouseEvent);
    //����ƶ��¼�
    virtual void	mouseMoveEvent (QGraphicsSceneMouseEvent * mouseEvent);
    //����ͷ��¼�
    virtual void	mouseReleaseEvent (QGraphicsSceneMouseEvent * mouseEvent);
    //���˫���¼�
    virtual void	mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
//    virtual void dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
//    virtual void dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
//    virtual void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
//    virtual void dropEvent ( QGraphicsSceneDragDropEvent * event );

public slots:
    //��ת(ѡ��Ԫ��)
    void rotateSelectItem();
    //����(ѡ��Ԫ��)
    void mirrorSelectItem();
    //����(ѡ��Ԫ��)
    double scaleSelectItem(double scale);
    //ɾ��(ѡ��Ԫ��)
    bool delSelectItem();
    //ɾ���յ�
    bool delSelectLineKnee();
    //ɾ������
    bool delSelectJoin(int selPos);
    //����ĸ��
    void createBus(int direct);
    //������·
    void createLine(int lineType);
    //����ѡ�е�Ԫ��
    void showSelectItem(Graphic*selItem);


private:


    //�õ�ѡ��Ԫ��
    Graphic* findCurrentEle(QGraphicsItem* graphic,bool bBasic = false);
    //�����豸��㾎��
    void calcGraphicNode(map<TopoJoin,int>& mapJoin,Graphic* tmpGraphic,int& nodeInc);
    //ʹ�ø�����ʼ���ڵ�ǰ�����ڲ�
    void	limitPoint(QPointF& scenePoint );

    QMap<ulong64,ShrinkTick*> _chaDongAll;
    QCDrawView* _view;//��ͼ

    IDCreator _idCreator;//������ID
    //ѡ�����
    GraphicSelector _selector;//ѡ�е�Ԫ��
    GraphicCreator _creator;//Ҫ������Ԫ��

//    Graphic*	_selectItem;
//    GraphicKnee _knee;//ѡ����·��ĸ��ʱѡ�еĹյ㣬-1��û��ѡ��
//    QPointF _selectPoint;
    uint16 _indexStation;//��վ����

    ulong64 _id;//id
    QString _name;//����
    QString _showName;//��ʾ������
    const GraphicConfig* _config;//����״̬
    map<ulong64,Graphic*> _allElement;//���ڴ洢������ʾ��Ԫ��
    //set<WidgetGraphicBase*> _allControl;
    int _oper;//OPER_SELECT,OPER_CREATE
    QColor _bkColor;
    QColor _foreColor;
    QPointF _beginPoint;//��ѡ��Χʱ����ʼ��
    QGraphicsRectItem *_rectItem;//��ѡ��Χʱ�ľ���
    bool _isSelectScene;//�Ƿ��ڽ��п�ѡ����
};

#endif // QCDRAWSCENE_H
