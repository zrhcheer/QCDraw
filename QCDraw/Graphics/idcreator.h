#ifndef IDCREATOR_H
#define IDCREATOR_H
typedef unsigned long long ulong64;
typedef unsigned short int uint16;
typedef unsigned  int uint32;
#include <map>
#include "graphic.h"
using namespace std;

class IDCreator
{
public:
    IDCreator(map<ulong64,Graphic*>& allElement);
    //创建中间空缺的ID
    ulong64 createInterId(uint16 secId);
    //创建ID
    ulong64 createId();
    //设置厂站ID
    void setStationId(uint16 idStation)
    {
        _idStation = idStation;
        _idCursor = ((ulong64)_idStation <<  48) + 1;
    }
    //删除ID
    void delId(const ulong64& idDel)
    {
        if(_idCursor > idDel)
        {
            _idCursor = idDel;
        }
    }

private:
    uint16 _idStation;//厂站ID
    map<ulong64,Graphic*>& _allElement;//用于保存所有元件
    ulong64 _idCursor;//当前光标ID
};

#endif // IDCREATOR_H
