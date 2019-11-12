#ifndef WARNNINGDIALOG_H
#define WARNNINGDIALOG_H

#include <QWidget>

namespace Ui {
    class WarnningDialog;
}

class WarnningDialog : public QWidget
{
    Q_OBJECT

public:
    explicit WarnningDialog(QWidget *parent = 0);
    ~WarnningDialog();
    void setDialogstyle(QString str,QString style);

private:
    Ui::WarnningDialog *ui;
    QString m_str;


private slots:
    void on_WarnningDialog_Button_close_clicked();
};

#endif // WARNNINGDIALOG_H
