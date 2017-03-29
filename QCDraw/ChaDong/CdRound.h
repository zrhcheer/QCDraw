#ifndef CDROUND_H
#define CDROUND_H
#include "CdPoint.h"
#include "CdRect.h"

class CdRound
{
public:
    CdPoint m_pointCenter;
    double m_dRadius;
    bool _isDot;//�Ƿ�������
    CdRound();
    CdRound(CdPoint pointCenter, double dRadius,bool isDot = false);
    CdRound(const CdRound & cdRound);
    CdRound & operator = (const CdRound & cdRound);
    bool operator == (const CdRound & cdRound) const;
    //���Ƿ���Բ�ڣ��ж������ǵ㵽Բ�ĵľ����Ƿ�С�ڰ뾶������Բ��ҲΪtrue
    bool IsPointInRound(const CdPoint & cdPoint) const;
    CdRect GetBoundRect() const;//ȡ�ñ߽����
};

#endif // CDROUND_H
