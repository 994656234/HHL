#ifndef DOCONTROL_H
#define DOCONTROL_H
#include "global.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class DoControl;
}

class DoControl : public QWidget
{
    Q_OBJECT

public:
    explicit DoControl(QWidget *parent = 0);
    ~DoControl();
    void initialName(QList<QString> &names,QString str,QString traintype);
    void updateDo(QList<bool> &state);

private:
    Ui::DoControl *ui;
};

#endif // DOCONTROL_H
