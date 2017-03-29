#ifndef _HH_CDCOORDINATE_H
#define _HH_CDCOORDINATE_H

#include <string>

class CdCoordinate
{
public:
    double m_dTop;
    double m_dLeft;
    double m_dBottom;
    double m_dRight;
    CdCoordinate();
    CdCoordinate(double dTop, double dLeft, double dBottom, double dRight);
    CdCoordinate(const CdCoordinate & cdCoordinate);
    CdCoordinate & operator = (const CdCoordinate & cdCoordinate);
    bool operator == (const CdCoordinate & cdCoordinate);
    double Width() const;
    double Height() const;
    std::string ToString();
};

#endif // _HH_CDCOORDINATE_H
