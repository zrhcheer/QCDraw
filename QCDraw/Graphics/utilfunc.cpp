#include "utilfunc.h"
#include <math.h>
UtilFunc::UtilFunc()
{
}
float UtilFunc::manhattanLength(const QPointF& tmpPoint)
{
#ifdef OLDVERSION
    return sqrt(tmpPoint.x() * tmpPoint.x() + tmpPoint.y() * tmpPoint.y());
#else
    return tmpPoint.manhattanLength();
#endif
}
