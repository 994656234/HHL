#ifndef RIOMLCUVERSIONCONTROL_H
#define RIOMLCUVERSIONCONTROL_H

#include <QWidget>

namespace Ui {
    class RIOMLCUVersionControl;
}

class RIOMLCUVersionControl : public QWidget
{
    Q_OBJECT

public:
    explicit RIOMLCUVersionControl(QWidget *parent = 0);
    ~RIOMLCUVersionControl();
    void updateStatus(QList<QString> &status);

private:
    Ui::RIOMLCUVersionControl *ui;
};

#endif // RIOMLCUVERSIONCONTROL_H
