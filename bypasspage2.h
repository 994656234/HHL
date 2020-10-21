#ifndef BYPASSPAGE2_H
#define BYPASSPAGE2_H

#include <QWidget>
#include "mybase.h"
#include "qpushbutton.h"
#include "qlabel.h"

namespace Ui {
class ByPassPage2;
}

class ByPassPage2 : public MyBase
{
    Q_OBJECT

public:
    explicit ByPassPage2(QWidget *parent = 0);
    ~ByPassPage2();
    void updatePage();

private slots:
 void pushButtonPressedEvent();

private:
    Ui::ByPassPage2 *ui;
    void setStatus(QLabel* lbl,bool status);
};

#endif // BYPASSPAGE2_H
