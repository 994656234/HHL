#ifndef BYPASSPAGE_H
#define BYPASSPAGE_H
#include "mybase.h"
#include "qpushbutton.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class ByPassPage;
}

class ByPassPage : public MyBase
{
    Q_OBJECT

public:
    explicit ByPassPage(QWidget *parent = 0);
    ~ByPassPage();
    void updatePage();

private:
    Ui::ByPassPage *ui;
    void setStatus(QLabel* lbl,bool status);

private slots:
    void pushButtonPressedEvent();
};

#endif // BYPASSPAGE_H
