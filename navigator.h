#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <QWidget>
#include "mybase.h"
#include "qpushbutton.h"
#include "qvector.h"

namespace Ui {
    class Navigator;
}

class Navigator : public MyBase
{
    Q_OBJECT

public:
    explicit Navigator(QWidget *parent = 0);
    ~Navigator();
    void refreshAllButtons();
    void updatePage();

private:
    Ui::Navigator *ui;
    QList<QPushButton*>buttons;
private slots:
    void NBpressEvent();

};

#endif // NAVIGATOR_H
