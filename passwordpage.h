#ifndef PASSWORDPAGE_H
#define PASSWORDPAGE_H
#include "mybase.h"
#include "MainGetDefaultPara.h"

#include <QWidget>

namespace Ui {
    class PasswordPage;
}

class PasswordPage : public MyBase
{
    Q_OBJECT

public:
    explicit PasswordPage(QWidget *parent = 0);
    ~PasswordPage();
    static int passWordLength;
    static QString password;

private:
    Ui::PasswordPage *ui;
    MainGetDefaultPara *getParam;

private slots:
    void on_BTNNum1_pressed();
    void on_BTNNum2_pressed();
    void on_BTNNum3_pressed();
    void on_BTNNum4_pressed();
    void on_BTNNum5_pressed();
    void on_BTNNum6_pressed();
    void on_BTNNum7_pressed();
    void on_BTNNum8_pressed();
    void on_BTNNum9_pressed();
    void on_BTNNum0_pressed();
    void on_BTNNumC_pressed();
    void on_BTN9OK_pressed();
    void on_BTN1back_pressed();
    void on_BTNNumClear_pressed();
};

#endif // PASSWORDPAGE_H
