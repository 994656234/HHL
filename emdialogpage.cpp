#include "emdialogpage.h"
#include "ui_emdialogpage.h"

EMDialogPage::EMDialogPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EMDialogPage)
{
    ui->setupUi(this);
}

EMDialogPage::~EMDialogPage()
{
    delete ui;
}


void EMDialogPage::setLabelText(QString txt)
{
    ui->lbl_mode->setText(txt);
}
