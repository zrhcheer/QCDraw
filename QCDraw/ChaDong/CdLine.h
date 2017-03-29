#ifndef CDLINE_H
#define CDLINE_H

#include "CdPoint.h"
#include "math.h"

class CdLine
{
public:
    CdPoint m_pointA;
    CdPoint m_pointB;
    int m_type;
    CdLine();
    CdLine(const CdPoint & pointA, const CdPoint & pointB, const int & type);
    CdLine(double dXA, double dYA, double dXB, double dYB, int type);
    CdLine(const CdLine & cdLine);
    CdLine & operator = (const CdLine & cdLine);
    bool operator == (const CdLine & cdLine) const;
    //�ж������߶��Ƿ񽻲棬��һ���߶εĶ˵�����һ���߶���ʱ����������Ϊ������
    bool IsCrossedWith(const CdLine & cdLine) const;
    CdPoint GetPercentPoint(int iPercent, bool bBeginFromA = true) const;
private:
    //������OA��OB�Ĳ���������ֱ��ǵ�O��A��B
    double GetCrossProduct(const CdPoint & pointO, const CdPoint & pointA, const CdPoint & pointB) const;
};

#endif // CDLINE_H
