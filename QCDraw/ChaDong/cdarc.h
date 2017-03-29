#ifndef CDARC_H
#define CDARC_H

#include "CdPoint.h"
#include "math.h"
#include "CdRect.h"

class CdArc
{
public:
    CdArc();

    CdRect GetBoundRect() const;
    CdPoint m_ptCenter;
    float m_radius;
    float m_startAngle;
    float m_spanAngle;
};

#endif // CDARC_H
