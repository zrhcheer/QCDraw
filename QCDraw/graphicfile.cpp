#include "graphicfile.h"
#include <assert.h>

GraphicFile::GraphicFile(const bool& bUft8) :
    _bUtf8(bUft8)
{
    _fh = NULL;
}
GraphicFile::~GraphicFile()
{
    if(_fh)
    {
        _file.close();
        fclose(_fh);
    }
}

bool GraphicFile::open(const QString& strPath,QFile::OpenMode flag)
{
    if(_fh)
    {
        _file.close();
        fclose(_fh);
        _fh = NULL;
    }
    if(_bUtf8)
    {
        if(QFile::ReadOnly == flag)
        {
            _fh = fopen(strPath.toUtf8().data(),"r");
        }
        else if(QFile::WriteOnly == flag)
        {
            _fh = fopen(strPath.toUtf8().data(),"w");
        }
        else
        {
            assert(false);
        }
    }
    else
    {
        if(QFile::ReadOnly == flag)
        {
            _fh = fopen(strPath.toStdString().c_str(),"r");
        }
        else if(QFile::WriteOnly == flag)
        {
            _fh = fopen(strPath.toStdString().c_str(),"w");
        }
        else
        {
            assert(false);
        }
    }

    if(!_fh)
    {
        return false;
    }

    if (!_file.open(_fh,flag))
    {
        fclose(_fh);
        _fh = NULL;
        return false;
    }
    return true;
}
