#ifndef GRAPHICCURSOR_H
#define GRAPHICCURSOR_H
#include <QVector>
#include <QCursor>
#include <boost/noncopyable.hpp>
#include <QSharedPointer>
class GraphicCursor : boost::noncopyable
{
public:
    enum ViewCursor
    {
        CURSOR_PEN,
        CURSOR_TRI,
        CURSOR_ANCHOR,
        CURSOR_CROSS,
        CURSOR_HAND,
        CURSOR_ARROW,
        CURSOR_SIZE,
        CURSOR_SizeVerCursor,
        CURSOR_SizeHorCursor,
        CURSOR_SizeBDiagCursor,
        CURSOR_SizeFDiagCursor,
        CURSOR_MAX
    };
    //��GraphicCursor����ʵ����
    static GraphicCursor* getInstance()
    {
        if(!_instance.data())
        {
            _instance = QSharedPointer<GraphicCursor>(new GraphicCursor());
        }
        return _instance.data();
    }

    //���ù�겢�ҷ���ID
    //int  setCursorForSize(QWidget* widget, int sizeFlag);
    //���ù��
    //void  setCursorForID(QWidget* widget, int id);
    const QCursor& getCursorForSize(int sizeFlag);

    void setOverrideCursor(int cursorId);
    void setOverrideCursorFromSize(int sizeFlag);
private:
    //��ȡ���
    const QCursor& getCursorFromID(int id);

    GraphicCursor();
    static QSharedPointer<GraphicCursor> _instance;//ʵ��
    QVector<QCursor> _cursor;//���ڴ洢���ID
    QCursor _defaultCursor;//������
};



#endif // GRAPHICCURSOR_H
