#ifndef TCDICONTROL_H
#define TCDICONTROL_H

#include <QWidget>

namespace Ui {
    class TCDIControl;
}

class TCDIControl : public QWidget
{
    Q_OBJECT

public:
    explicit TCDIControl(QWidget *parent = 0);
    ~TCDIControl();
    void initialName(QList<QString> &names,QString str,QString traintype);
    void updateDi(QList<bool> &state);

private:
    Ui::TCDIControl *ui;
};

#endif // TCDICONTROL_H
