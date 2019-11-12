#ifndef DICONTROL_H
#define DICONTROL_H
#include "global.h"

#include <QWidget>

namespace Ui {
    class DIControl;
}

class DIControl : public QWidget
{
    Q_OBJECT

public:
    explicit DIControl(QWidget *parent = 0);
    ~DIControl();
    void initialName(QList<QString> &names,QString str,QString traintype);
    void updateDi(QList<bool> &state);

private:
    Ui::DIControl *ui;
};

#endif // DICONTROL_H
