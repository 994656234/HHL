#ifndef HELPPAGE4_H
#define HELPPAGE4_H
#include "mybase.h"
#include "qpushbutton.h"

#include <QWidget>

namespace Ui {
    class HelpPage4;
}

class HelpPage4 : public MyBase
{
    Q_OBJECT

public:
    explicit HelpPage4(QWidget *parent = 0);
    ~HelpPage4();

private:
    Ui::HelpPage4 *ui;
    QList<QPushButton*>buttons;

private slots:
    void NBpressEvent();
};

#endif // HELPPAGE4_H
