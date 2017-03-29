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
    //类GraphicCursor进行实例化
    static GraphicCursor* getInstance()
    {
        if(!_instance.data())
        {
            _instance = QSharedPointer<GraphicCursor>(new GraphicCursor());
        }
        return _instance.data();
    }

    //设置光标并且返回ID
    //int  setCursorForSize(QWidget* widget, int sizeFlag);
    //设置光标
    //void  setCursorForID(QWidget* widget, int id);
    const QCursor& getCursorForSize(int sizeFlag);

    void setOverrideCursor(int cursorId);
    void setOverrideCursorFromSize(int sizeFlag);
private:
    //获取光标
    const QCursor& getCursorFromID(int id);

    GraphicCursor();
    static QSharedPointer<GraphicCursor> _instance;//实例
    QVector<QCursor> _cursor;//用于存储光标ID
    QCursor _defaultCursor;//错误光标
};



#endif // GRAPHICCURSOR_H
