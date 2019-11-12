#ifndef MAINTAINCEWHEELDIAMETERSETPAGE_H
#define MAINTAINCEWHEELDIAMETERSETPAGE_H
#include "mybase.h"
#include "warnningdialog.h"
#include "qpushbutton.h"
#include "qtimer.h"
#include "MainGetDefaultPara.h"

#include <QWidget>

namespace Ui {
    class MaintainceWheelDiameterSetPage;
}


enum WHEELSELECT
{
    TC1SELECT= 0,
    MP1SELECT,
    M1SELECT,
    M2SELECT,
    MP2SELECT,
    TC2SELECT,
    ALLSELECT,
    RESET,
    TRAINSET,

};

class MaintainceWheelDiameterSetPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceWheelDiameterSetPage(QWidget *parent = 0);
    ~MaintainceWheelDiameterSetPage();
    void updatePage();

private:
    Ui::MaintainceWheelDiameterSetPage *ui;
    void allButtonRelease();
    void resetSaveFlg();
    WarnningDialog* warnningDialog;
    WHEELSELECT m_wheelselect;
    QTimer* timer;
    bool wheelset;
    bool trainNumset;
    MainGetDefaultPara *getParam;

    QList <QPushButton* > wheel_buttons;
    QString m_Btnname,m_Inputvalue;
    int m_WheelBtnIndex;
    QList<unsigned char *> m_wheelvalue;
    QList<int> m_wheelTextValue;
    QList<bool* > m_wheelsaveflag;

public slots:
   void myKeyPressEvent(QString key);

private slots:
    void on_BTN9_pressed();
    void on_BTNHome_pressed();
    void on_BTN1_pressed();
    void WheelButtonsEvent();
    void NumKeyboardEvent();
    void timer2sEvent();
signals:
    void myKeyPress(QString key);
};

#endif // MAINTAINCEWHEELDIAMETERSETPAGE_H
