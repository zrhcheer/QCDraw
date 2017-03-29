#ifndef CONTROLTOOLWIDGET_H
#define CONTROLTOOLWIDGET_H

#include <QWidget>
#include <map>
#include <QPushButton>
#include <QButtonGroup>
using namespace std;

struct CompentSetting
{
    CompentSetting(const string& name,const string& picPath,int id) :
        _name(name),_picPath(picPath)
    {
        _id = id;
    }

    string _name;
    string _picPath;
    int _id;
};

class ControlToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlToolWidget(QWidget *parent = 0);

private slots:
    void controlButtonGroupPressed (int id);
private:
    void initTool();
    QPushButton* createBackgroundCellWidget(const string &text, const string &image);
    map<int,CompentSetting> _mapCompSetting;
    QButtonGroup  _controlButtonGroup;

};

#endif // CONTROLTOOLWIDGET_H
