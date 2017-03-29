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
    //�����м��ȱ��ID
    ulong64 createInterId(uint16 secId);
    //����ID
    ulong64 createId();
    //���ó�վID
    void setStationId(uint16 idStation)
    {
        _idStation = idStation;
        _idCursor = ((ulong64)_idStation <<  48) + 1;
    }
    //ɾ��ID
    void delId(const ulong64& idDel)
    {
        if(_idCursor > idDel)
        {
            _idCursor = idDel;
        }
    }

private:
    uint16 _idStation;//��վID
    map<ulong64,Graphic*>& _allElement;//���ڱ�������Ԫ��
    ulong64 _idCursor;//��ǰ���ID
};

#endif // IDCREATOR_H
