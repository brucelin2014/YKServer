// 2023-03-21, Bruce
// https://www.likecs.com/show-307825644.html

#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QAction>
#include <QApplication>
#include <QMenu>

class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SystemTray(QWidget *parent = 0);
    ~SystemTray();

    void addAction();
    void createAction();

private:
    QMenu* myMenu;//托盘菜单
    QAction* restoreWinAction;//还原
    QAction* quitAction;//退出

signals:
    void showWidget();
private slots:
};

#endif // SYSTEMTRAY_H
