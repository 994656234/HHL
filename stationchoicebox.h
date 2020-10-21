#ifndef STATIONCHOICEBOX_H
#define STATIONCHOICEBOX_H
#include "qpushbutton.h"
#include "qmap.h"

#include <QWidget>

namespace Ui {
class StationChoiceBox;
}

class StationChoiceBox : public QWidget
{
    Q_OBJECT

public:
    explicit StationChoiceBox(QWidget *parent = 0);
    ~StationChoiceBox();
    int getStationIds(bool single);
    QString getStationNames(bool single);
    void setStates(int state);
    int getId();
    QString getName();
    QList<int> getIdList();
    QList<QString> getNameList();
    void clearData();
    void clearJumpData();

private:
    Ui::StationChoiceBox *ui;
    QList<QPushButton *> butons;
    int id;
    QString name;
    QList<int> idList;
    QList<QString> nameList;
    int state;
    void allButtonrelease();

private slots:
    void buttonsPressedEvnet();
};

#endif // STATIONCHOICEBOX_H
