#ifndef GRAPHICSTORAGE_H
#define GRAPHICSTORAGE_H
#include <QString>
#include <map>
#include "Graphics/graphic.h"
#include "qcdrawscene.h"
#include <QTextCodec>
using namespace std;

class GraphicStorage
{
public:
    GraphicStorage(bool bUtf8 = true);

    ///根据文件信息绘制基本电器元件
    bool loadQCD(const QString& strPath,QCDrawScene* scene);
    bool loadXML(const QString& strPath,QCDrawScene* scene);
    //保存已经添加的元件
    bool saveQCD(const QString& strPath,QCDrawScene* scene);
    bool saveXML(const QString& strPath,QCDrawScene* scene);
    int getTypeFromGraphicName(const string name);
    string getGraphicNameFromType(const int type);
    bool saveGraphic(const QString& strPath,QCDrawScene* scene);
    bool loadGraphic(const QString& strPath,QCDrawScene* scene);
private:
    bool _bUtf8;
};

#endif // GRAPHICSTORAGE_H
