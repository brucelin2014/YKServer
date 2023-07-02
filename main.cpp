#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>
#include "util/log.h"
#include <QSharedMemory>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    static QSharedMemory *singleApp = new QSharedMemory("ZTServer_SingleApp");
    if (!singleApp->create(1)) //已经有一个程序运行，
    {
        qApp->quit();//退出当前程序
        return -1;
    }

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    QString configPath = QCoreApplication::applicationDirPath() + "/log.conf";
    Log::instance()->init(configPath);
    Log::instance()->info("\r\n*** Start ***");

    MainWindow w;
    w.show();
    w.showMinimized();
    return a.exec();
}
