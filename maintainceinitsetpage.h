#ifndef MAINTAINCEINITSETPAGE_H
#define MAINTAINCEINITSETPAGE_H
#include "mybase.h"
#include "MainGetDefaultPara.h"

#include <QWidget>

namespace Ui {
    class MaintainceInitSetPage;
}

class MaintainceInitSetPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceInitSetPage(QWidget *parent = 0);
    ~MaintainceInitSetPage();

private:
    Ui::MaintainceInitSetPage *ui;

private slots:
    void on_HMIReboot_pressed();
    void on_TC2Btn_pressed();
    void on_TC1Btn_pressed();
    void on_BTN_back_pressed();
};

#endif // MAINTAINCEINITSETPAGE_H
