#include "warnningdialog.h"
#include "ui_warnningdialog.h"

WarnningDialog::WarnningDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WarnningDialog)
{
    ui->setupUi(this);
}

WarnningDialog::~WarnningDialog()
{
    delete ui;
}
void WarnningDialog::setDialogstyle(QString str,QString style)
{
    ui->WarnningDialog_Label_str->setText(str);
}

void WarnningDialog::on_WarnningDialog_Button_close_clicked()
{
    this->close();
}
