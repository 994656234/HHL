#ifndef MAINTAINCELCUSUBSYSTEMPAGE_H
#define MAINTAINCELCUSUBSYSTEMPAGE_H
#include "mybase.h"
#include "qpushbutton.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class MaintainceLCUSubsystemPage;
}

static int current_LCU;
static int currentPage_LCU;

class MaintainceLCUSubsystemPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceLCUSubsystemPage(QWidget *parent = 0);
    ~MaintainceLCUSubsystemPage();
    void updatePage();

private:
    Ui::MaintainceLCUSubsystemPage *ui;
    QList<QPushButton *> buttons,buttonLCUs;
    QList<QLabel*> lbl_row1_names,lbl_row2_names,lbl_row3_names,lbl_row4_names,lbl_row1_values,lbl_row2_values,lbl_row3_values,lbl_row4_values;
    QList<QString> row1Names,row2Names,row3Names,row4Names;
    QList<bool> row1Values,row2Values,row3Values,row4Values;
    void refreshAllButtons();
    void setLCUStatus(QList<QLabel*> lbl,QList<QString> status);
    QList<QString> changeSignalStatus(QList<bool> status);
    QList<QString> value1;

private slots:
    void on_BTN8_pressed();
    void on_BTN7_pressed();
    void pushButtonPressedEvent();
};

#endif // MAINTAINCELCUSUBSYSTEMPAGE_H
