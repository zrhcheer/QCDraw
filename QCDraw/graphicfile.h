#ifndef GRAPHICFILE_H
#define GRAPHICFILE_H
#include <stdio.h>
#include <QFile>
#include <QDataStream>
class GraphicFile
{
public:
    GraphicFile(const bool& bUft8 = true);
    ~GraphicFile();
    bool open(const QString& strPath,QFile::OpenMode flag);
    QFile* getFile()
    {
        return &_file;
    }

private:
    FILE * _fh;
    QFile  _file;
    bool _bUtf8;
};

#endif // GRAPHICFILE_H
