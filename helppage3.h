#ifndef HELPPAGE3_H
#define HELPPAGE3_H
#include "mybase.h"
#include "qpushbutton.h"

#include <QWidget>

namespace Ui {
    class HelpPage3;
}

class HelpPage3 : public MyBase
{
    Q_OBJECT

public:
    explicit HelpPage3(QWidget *parent = 0);
    ~HelpPage3();

private:
    Ui::HelpPage3 *ui;
    QList<QPushButton*>buttons;

private slots:
    void NBpressEvent();
};

#endif // HELPPAGE3_H
