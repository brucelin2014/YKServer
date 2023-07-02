// 2023-02-26, Bruce

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "impl/configimpl.h"
#include "interface/IZTServer_api.h"
#include "interface/IZTServer_api_Listener.h"
#include "impl/ztservice_thread.h"
#include "impl/ztservice_syncStatus_thread.h"
#include "interface/IDataParser.h"
#include "interface/IDataParser_Device.h"
#include "interface/IRespondData.h"
#include "interface/ITcpServer_Listener.h"
#include "util/tcpserver.h"
#include "impl/devicestatusmgr.h"
#include "impl/systemtray.h"
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow
        : public QMainWindow
        , public IZTServer_api_Listener
        , public ITcpServer_Listener
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // HTTP-返回结果
    virtual void OnRespond(const QString& urlRequest, const QString& respond) override;

    // HTTP-返回错误代码
    virtual void OnError(const QString& urlRequest, const int& errorCode) override;

    // TCP-Socket
    virtual void newConnection(const QString& peerAddress, const quint16& peerPort) override;

    // TCP
    virtual void readyRead(const QString& rev, const QString& peerAddress, const quint16& peerPort) override;

    // TCP
    virtual void SocketError(const QString& err, const QString& peerAddress, const quint16& peerPort) override;

    // TCP
    virtual void disconnected(const QString& peerAddress, const quint16& peerPort) override;

    // TCP
    virtual void acceptError(const QString& err) override;
    //

private:
    Ui::MainWindow *ui;

    ConfigImpl m_Config;
    IZTServer_api* m_pServer_api;
    ZTService_Thread* m_pService_plan;
    ZTService_syncStatus_Thread* m_pService_syncStatus;

    IDataParser* m_pDataParser;
    IDataParser_Device* m_pDataParser_Device;
    IRespondData* m_pResData;
    TcpServer m_tcpServer;
    DeviceStatusMgr m_deviceStatus;

    QString getTime();
    void SyncDeviceOnline();

    SystemTray* myTray; //自定义系统托盘

private slots:
    void on_btn_getTreatPlan_clicked();
    void on_btn_getTreatStatus_clicked();
    void on_btn_receiveDevicesData_clicked();
    void on_btn_submitReport_clicked();
    void on_btn_syncStatus_clicked();
    void on_btn_syncTreatStatus_clicked();
    void on_btn_testData_clicked();
    void on_cb_auto_run_stateChanged(int arg1);
    void on_btn_clear_clicked();
    void on_btn_clear_tcp_clicked();
    void on_btn_send_clicked();

    void ShowWindow(); //处理还原操作
    void SystemTrayActivated(QSystemTrayIcon::ActivationReason reason); //处理点击托盘操作

protected:
    virtual void closeEvent(QCloseEvent* event) override;

    void Send_Respond(IRespondData* pResData, const QString& sysCode);
    void Send_A1S(IRespondData* pResData);
    void Send_SL4(IRespondData* pResData);
    void Send_A1(IRespondData* pResData);
    void Send_PS1(IRespondData* pResData);
    void Send_A3(IRespondData* pResData);
    void Send_A6(IRespondData* pResData);
    void Send_A8(IRespondData* pResData);

    // 发送远程控制指令
    void Send_Control(IRespondData* pResData);
};
#endif // MAINWINDOW_H
