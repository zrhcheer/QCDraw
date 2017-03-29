#ifndef CDQUARDRANGLE_H
#define CDQUARDRANGLE_H

#include "CdPoint.h"
#include "CdRect.h"

class CdQuardrangle
{
public:
    CdPoint m_arrayPoint[4];
    CdQuardrangle();
    CdQuardrangle(const CdPoint & point1, const CdPoint & point2,
                  const CdPoint & point3, const CdPoint & point4);
    CdQuardrangle(const CdQuardrangle & cdQuardrangle);
    CdQuardrangle & operator = (const CdQuardrangle & cdQuardrangle);
    bool operator == (const CdQuardrangle & cdQuardrangle)const;
    //���Ƿ����ı����ڣ���������������ж������������ú��ı��λᱻorganized�������ı��α���Ҳ��Ϊ��
    bool IsPointInQuardrangle(const CdPoint & cdPoint);
    //�ı��ε��ĸ������Ƿ��������
    bool HasPoint(const CdPoint & cdPoint)const;
    //�����ı��Σ�ʹ�ð���˳����Ƽ��ɻ��Ƴ��ı���,�����Ƿ�ɹ������ʧ�����ʾ�ĸ��㲻�ܹ����ı���
    bool Organize();
    CdRect GetBoundRect() const;//ȡ�ñ߽����
private:
    //ʹ�ú��׹�ʽ�����������
    double GetTriangleArea(const CdPoint & pointA, const CdPoint & pointB, const CdPoint & pointC) const;
};

#endif // CDQUARDRANGLE_H
