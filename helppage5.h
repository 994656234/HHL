#ifndef HELPPAGE5_H
#define HELPPAGE5_H
#include "mybase.h"
#include "qpushbutton.h"

#include <QWidget>

namespace Ui {
    class HelpPage5;
}

class HelpPage5 : public MyBase
{
    Q_OBJECT

public:
    explicit HelpPage5(QWidget *parent = 0);
    ~HelpPage5();

private:
    Ui::HelpPage5 *ui;
    QList<QPushButton*>buttons;

private slots:
    void NBpressEvent();
};

#endif // HELPPAGE5_H
