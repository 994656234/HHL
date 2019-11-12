#ifndef MYBASE_H
#define MYBASE_H

#include "global.h"
#include <QWidget>
#include "database.h"
#include "log4qt.h"
#include "qdatetime.h"

class MyBase : public QWidget
{
    Q_OBJECT
public:
    explicit MyBase(QWidget *parent = 0);
    void setMyBase(enum pagePosition position, QString name);
    virtual void updatePage();

public:
    static int currentPage;
    static Database *database;
    QString name;
    int Position;

public slots:
signals:
    void changePage(int);
};

#endif // MYBASE_H
