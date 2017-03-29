#ifndef GRAPHICCONFIG_H
#define GRAPHICCONFIG_H

class GraphicConfig
{
public:
    GraphicConfig();
    //获取锁定状态
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
    bool _bLock;//是不是锁定状态
    bool _bUtf8;//是不是UTF8系统
};

#endif // GRAPHICCONFIG_H
