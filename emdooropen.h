#ifndef EMDOOROPEN_H
#define EMDOOROPEN_H

#include <QWidget>

namespace Ui {
class EmDoorOPen;
}

class EmDoorOPen : public QWidget
{
    Q_OBJECT

public:
    explicit EmDoorOPen(QWidget *parent = 0);
    ~EmDoorOPen();

private slots:
    void on_pushButton_pressed();

private:
    Ui::EmDoorOPen *ui;
};

#endif // EMDOOROPEN_H
