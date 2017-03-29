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

    //����ϵ���ڲ����ݴ�С����ϵ�����ڲ����ݱ߽���γ��Դ�ϵ�����������ϵ�߽磩
    static double m_dCoordDataRatio;
};

#endif // G_ENVIRONMENTALVARAIBLE_H
