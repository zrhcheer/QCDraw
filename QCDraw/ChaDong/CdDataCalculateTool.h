#ifndef CDDATACALCULATETOOL_H
#define CDDATACALCULATETOOL_H


class CdData;
class CdDataCalculateTool
{
private:
    CdDataCalculateTool();
public:
    //�Ƚ�����double���ʹ�С��1����2���ش���0�����ڷ���0��С�ڷ���С��0
    static int DoubleCompare(double dValue1, double dValue2);
    static double DoubleAbsolute(double dValue);
    //�����������ȷ������ϵ�߽�
    static void CalculateCoordinate(CdData & stuData, bool bflag = true);
public:
    //����ϵ���ڲ����ݴ�С����ϵ�����ڲ����ݱ߽���γ��Դ�ϵ�����������ϵ�߽磩
    static double m_dCoordDataRatio;
};

#endif // CDDATACALCULATETOOL_H
