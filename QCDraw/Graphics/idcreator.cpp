#include "idcreator.h"

IDCreator::IDCreator(map<ulong64,Graphic*>& allElement):
    _allElement(allElement)
{
    setStationId(1);
}
ulong64  IDCreator::createInterId(uint16 secId)
{
    ulong64 tmpIdCursor = ((((ulong64)_idStation << 16) + secId) << 32) + 1;
    map<ulong64,Graphic*>::iterator iterEle = _allElement.find(tmpIdCursor);
    if(iterEle != _allElement.end())
    {
        tmpIdCursor++;
        iterEle ++;
        for(;iterEle != _allElement.end(); ++iterEle)
        {
            const ulong64& afterId = iterEle->first;
            if(afterId != tmpIdCursor)
            {
                return tmpIdCursor;
            }
            else
            {
                tmpIdCursor++;
            }
        }
        return tmpIdCursor;
    }
    else
    {
        return _idCursor;
    }
}

ulong64 IDCreator::createId()
{

    map<ulong64,Graphic*>::iterator iterEle = _allElement.find(_idCursor);
    if(iterEle != _allElement.end())
    {
        _idCursor++;
        iterEle ++;
        for(;iterEle != _allElement.end(); ++iterEle)
        {
            const ulong64& afterId = iterEle->first;
            if(afterId != _idCursor)
            {
                return _idCursor;
            }
            else
            {
                _idCursor++;
            }
        }
        return _idCursor;
    }
    else
    {
        return _idCursor;
    }
}
