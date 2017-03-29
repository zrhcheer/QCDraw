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
    //���ó���
    void setScene(QCDrawScene* scene);
    //���ù��
    //void setCursorForID(int id);
    //����pixͼ��
    bool loadPixmap(QPixmap& pix);
    //�������ڵ�����,��ȷ����Ŀ��������ͼ�С�
    void centerOn( const QPointF& pt);
    void centerOn( const Graphic* graphic);
    QString GBKTOUTF8(const QString &inStr);
protected:
    //����ƶ��¼�
    virtual void	mouseMoveEvent ( QMouseEvent * event );
    //������¼�
    virtual void	mousePressEvent ( QMouseEvent * event );
    //����ͷ��¼�
    virtual void	mouseReleaseEvent ( QMouseEvent * event );
public  slots:
    //��ת��ѡ��Ԫ��
    void rotateSelectItem();
    //ɾ����ѡ��Ԫ��
    void delSelectItem();
    //ɾ����ѡ����·�յ�
    bool delSelectLineKnee();
    //ɾ����ѡ��Ԫ����selPos��������
    bool delSelectJoin(int selPos);
    //����ѡ��Ԫ��
    void mirrorSelectItem();
    //��������ĸ��
    void createVerBus();
    //��������ĸ��
    void createHorBus();
    //����վ����
    void createInLine();
    void createInterLine();
    //����վ������
    void createInVirLine();
    //����վ������
    void createInterVirLine();
    //�½�
    void newFile();
    //����
    void saveGraphic();
    //���Ϊ
    void saveAsGraphic();
    //�ָ�
    void loadGraphic();
    //��
    void openFile();
    //����
    void moveUp(); //add ljj
    //����
    void moveDown(); //
    //����
    void moveLeft();//
    //����
    void moveRight();//
    //�������
    void horizontalAlign(void);
    //�������
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
    GraphicConfig _config;//����״̬
private:
    bool _bPress;
    QPoint  tmpPoint2;
    QCDrawScene* _scene;
    string fileStr;

};

#endif // QCDRAWVIEW_H
