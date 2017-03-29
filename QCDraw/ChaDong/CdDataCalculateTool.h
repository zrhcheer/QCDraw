#ifndef CDDATACALCULATETOOL_H
#define CDDATACALCULATETOOL_H


class CdData;
class CdDataCalculateTool
{
private:
    CdDataCalculateTool();
public:
    //比较两个double类型大小，1大于2返回大于0，等于返回0，小于返回小于0
    static int DoubleCompare(double dValue1, double dValue2);
    static double DoubleAbsolute(double dValue);
    //根据数据情况确定坐标系边界
    static void CalculateCoordinate(CdData & stuData, bool bflag = true);
public:
    //坐标系与内部数据大小比例系数（内部数据边界矩形乘以此系数计算出坐标系边界）
    static double m_dCoordDataRatio;
};

#endif // CDDATACALCULATETOOL_H
