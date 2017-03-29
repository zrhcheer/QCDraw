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

    ///�����ļ���Ϣ���ƻ�������Ԫ��
    bool loadQCD(const QString& strPath,QCDrawScene* scene);
    bool loadXML(const QString& strPath,QCDrawScene* scene);
    //�����Ѿ���ӵ�Ԫ��
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
