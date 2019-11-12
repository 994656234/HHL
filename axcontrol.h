#ifndef AXCONTROL_H
#define AXCONTROL_H

#include <QWidget>

namespace Ui {
    class AXControl;
}

class AXControl : public QWidget
{
    Q_OBJECT

public:
    explicit AXControl(QWidget *parent = 0);
    ~AXControl();
    void updateAx(QList<QString> &state);
    void initialName(QList<QString> &names);

private:
    Ui::AXControl *ui;
};

#endif // AXCONTROL_H
