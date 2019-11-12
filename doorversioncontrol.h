#ifndef DOORVERSIONCONTROL_H
#define DOORVERSIONCONTROL_H

#include <QWidget>
#include "database.h"
#include "mybase.h"

namespace Ui {
    class DoorVersionControl;
}

class DoorVersionControl : public QWidget
{
    Q_OBJECT

public:
    explicit DoorVersionControl(QWidget *parent = 0);
    ~DoorVersionControl();
    void updateStatus(QList<QString> &status);
    void updatePage();

private:
    Ui::DoorVersionControl *ui;
};

#endif // DOORVERSIONCONTROL_H
