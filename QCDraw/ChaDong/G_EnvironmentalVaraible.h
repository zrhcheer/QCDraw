#ifndef G_ENVIRONMENTALVARAIBLE_H
#define G_ENVIRONMENTALVARAIBLE_H

enum SystemCompile
{
    QT_MSGBOX,
    QT_CONSOLE,
    VC
};

class G_EnvironmentalVaraible
{
private:
    virtual ~G_EnvironmentalVaraible() = 0;
public:
    static double g_dPrecision;
    static SystemCompile g_sysCompile;

    //坐标系与内部数据大小比例系数（内部数据边界矩形乘以此系数计算出坐标系边界）
    static double m_dCoordDataRatio;
};

#endif // G_ENVIRONMENTALVARAIBLE_H
