#ifndef UTILFUNC_H
#define UTILFUNC_H
#include <QPointF>
class UtilFunc
{
public:
    UtilFunc();
    //��ȡ��ԭ�㵽������ĳ���
    static float manhattanLength(const QPointF& tmpPoint);
};

#endif // UTILFUNC_H
