#ifndef GRAPHICCONFIG_H
#define GRAPHICCONFIG_H

class GraphicConfig
{
public:
    GraphicConfig();
    //��ȡ����״̬
    bool getLock() const
    {
        return _bLock;
    }

    void setIsUtf8(const bool& bUtf8)
    {
        _bUtf8 = bUtf8;
    }
    const bool& getIsUtf8() const
    {
        return _bUtf8;
    }

private:
    bool _bLock;//�ǲ�������״̬
    bool _bUtf8;//�ǲ���UTF8ϵͳ
};

#endif // GRAPHICCONFIG_H
