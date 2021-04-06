#ifndef MAINTAINCELAT_RLDPAGE_H
#define MAINTAINCELAT_RLDPAGE_H

#include <QWidget>
#include "mybase.h"
#include "qlist.h"
#include "qpushbutton.h"
#include "qlabel.h"
namespace Ui {
class MaintainceLAT_RLDPage;
}

class MaintainceLAT_RLDPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceLAT_RLDPage(QWidget *parent = 0);
    ~MaintainceLAT_RLDPage();
    void updatePage();

private:
    Ui::MaintainceLAT_RLDPage *ui;
    QList<QPushButton *> buttons;
    void SetLabelStatus(QList<QLabel *>lb,QList<bool >status);
    QList<QLabel *>labels;
    QList<bool >status;
private slots:
    void NBpressEvent();
};

#endif // MAINTAINCELAT_RLDPAGE_H
