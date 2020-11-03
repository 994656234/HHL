#include <QApplication>
#include "widget.h"
#include <QTextCodec>
#include "log4qt/propertyconfigurator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QDir tempDir;
    if(!tempDir.exists("OperationRecord/"))
    {
        tempDir.mkpath("OperationRecord/");
    }

    Log4Qt::PropertyConfigurator::configure(a.applicationDirPath()+ "/log4j.properties");

#ifndef USER_DEBUG_MODE
    a.setOverrideCursor(QCursor(Qt::BlankCursor));
#endif

    Widget w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();



    return a.exec();
}
