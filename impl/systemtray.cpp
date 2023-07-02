// 2023-03-21, Bruce

#include "systemtray.h"

SystemTray::SystemTray(QWidget *parent)
    : QSystemTrayIcon(parent)
{
    createAction();
    addAction();
}

SystemTray::~SystemTray()
{

}

void SystemTray::createAction()
{
    restoreWinAction = new QAction("还原", this);
    quitAction =       new QAction("退出", this);

    myMenu = new QMenu();

    this->setIcon(QIcon(":/yk.ico"));
    this->setToolTip("YKServer");

    connect(restoreWinAction, SIGNAL(triggered()), this, SIGNAL(showWidget()));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    this->setContextMenu(myMenu);     //设置托盘上下文菜单
    this->show();
}

void SystemTray::addAction()
{
    myMenu->addAction(restoreWinAction);
    myMenu->addAction(quitAction);
}
