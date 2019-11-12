#ifndef EMDIALOGPAGE_H
#define EMDIALOGPAGE_H

#include <QWidget>

namespace Ui {
    class EMDialogPage;
}

class EMDialogPage : public QWidget
{
    Q_OBJECT

public:
    explicit EMDialogPage(QWidget *parent = 0);
    ~EMDialogPage();
    void setLabelText(QString txt);

private:
    Ui::EMDialogPage *ui;
};

#endif // EMDIALOGPAGE_H
