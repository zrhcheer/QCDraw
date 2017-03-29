#include "codeconvertor.h"
#include <QTextCodec>

bool CodeConvertor::_bFirst = true;
CodeConvertor::CodeConvertor()
{
}
QString CodeConvertor::fromLocal(const char* str)
{
    if(_bFirst)
    {
        _bFirst = false;
        QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
        //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    }
    return str;
}
