#ifndef TCDOCONTROL_H
#define TCDOCONTROL_H

#include <QWidget>

namespace Ui {
    class TCDOControl;
}

class TCDOControl : public QWidget
{
    Q_OBJECT

public:
    explicit TCDOControl(QWidget *parent = 0);
    ~TCDOControl();
    void initialName(QList<QString> &names,QString str,QString traintype);
    void updateDo(QList<bool> &state);

private:
    Ui::TCDOControl *ui;
};

#endif // TCDOCONTROL_H
