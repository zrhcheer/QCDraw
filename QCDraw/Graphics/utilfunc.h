#ifndef UTILFUNC_H
#define UTILFUNC_H
#include <QPointF>
class UtilFunc
{
public:
    UtilFunc();
    //获取从原点到给定点的长度
    static float manhattanLength(const QPointF& tmpPoint);
};

#endif // UTILFUNC_H
