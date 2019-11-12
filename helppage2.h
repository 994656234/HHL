#ifndef HELPPAGE2_H
#define HELPPAGE2_H
#include "mybase.h"
#include "qpushbutton.h"

#include <QWidget>

namespace Ui {
    class HelpPage2;
}

class HelpPage2 : public MyBase
{
    Q_OBJECT

public:
    explicit HelpPage2(QWidget *parent = 0);
    ~HelpPage2();

private:
    Ui::HelpPage2 *ui;
    QList<QPushButton*>buttons;

private slots:
    void NBpressEvent();
};

#endif // HELPPAGE2_H
