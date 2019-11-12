#ifndef HELPPAGE_H
#define HELPPAGE_H
#include "mybase.h"
#include "qpushbutton.h"

#include <QWidget>

namespace Ui {
    class HelpPage;
}

class HelpPage : public MyBase
{
    Q_OBJECT

public:
    explicit HelpPage(QWidget *parent = 0);
    ~HelpPage();

private:
    Ui::HelpPage *ui;
    QList<QPushButton*>buttons;

private slots:
    void NBpressEvent();
};

#endif // HELPPAGE_H
