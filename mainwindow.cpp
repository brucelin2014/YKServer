// 2023-02-26, Bruce

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "impl/ztserver_api_http.h"
#include "impl/dataparserfactory.h"
#include "interface/IDataBase_Device.h"
#include "impl/dataparser_device.h"
#include "impl/dataparserfactory_device.h"
#include <QMessageBox>
#include "util/log.h"

#include "entity/data_device_data_a1s.h"
#include "entity/data_device_data_sl4.h"
#include "entity/data_device_data_a1.h"
#include "entity/data_device_data_a3_2.h"
#include "entity/data_device_data_a6_2.h"
#include "entity/data_device_data_a8.h"
#include "entity/data_device_data_ps1.h"

#include "entity/respondobj_a1s.h"
#include "entity/respondobj_sl4.h"
#include "entity/respondobj_a1.h"
#include "entity/respondobj_a3_2.h"
#include "entity/respondobj_a6_2.h"
#include "entity/respondobj_a8.h"
#include "entity/respondobj_ps1.h"

#include "entity/responddataobj_a1s.h"
#include "entity/responddataobj_a1.h"
#include "entity/responddataobj_a8.h"
#include "entity/responddataobj_a3_2.h"
#include "entity/responddataobj_a6_2.h"
#include "entity/responddataobj_ps1.h"

#include "entity/data_control.h"

#include "util/jsontools.h"
#include "impl/dataparser.h"
#include "impl/dataparser_treat_plan.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_pServer_api(nullptr)
    , m_pService_plan(nullptr)
    , m_pService_syncStatus(nullptr)
    , m_pDataParser(nullptr)
    , m_pDataParser_Device(nullptr)
    , m_pResData(nullptr)
    , m_tcpServer(this, this, 9898)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/yk.ico"));
    myTray = new SystemTray(this);

    connect(myTray, SIGNAL(showWidget()), this, SLOT(ShowWindow())); //关联信号和槽函数
    connect(myTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(SystemTrayActivated(QSystemTrayIcon::ActivationReason)));

    ui->cb_dev_status->addItem("开机");
    ui->cb_dev_status->addItem("待机");
    ui->cb_dev_status->addItem("治疗中");
    ui->cb_dev_status->addItem("离线");

    ui->cb_treat_status->addItem("开始治疗");
    ui->cb_treat_status->addItem("结束治疗");
    ui->cb_treat_status->addItem("拒绝治疗");

    m_Config.Load();

    // 数据解析器
    m_pDataParser = DataParserFactory::CreateDataParser(m_Config.Get_sysCode());

    ui->le_host_url->setText(m_Config.Get_host_url());
    ui->le_deviceId->setText(m_Config.Get_deviceId());
    ui->le_sysCode->setText(m_Config.Get_sysCode());

    // 定时获取数据服务
    m_pService_plan = new ZTService_Thread(this, this, &m_Config.m_ConfigObj);
    m_pService_plan->start();

    // 定时同步设备状态
    m_pService_syncStatus = new ZTService_syncStatus_Thread(this, this, &m_Config.m_ConfigObj, &m_deviceStatus);
    m_pService_syncStatus->start();

    // 主线程api服务
    m_pServer_api = new ZTServer_api_Http(this, this);
    ((ZTServer_api_Http*)m_pServer_api)->Set_host_url(ui->le_host_url->text());

    if (!ui->cb_auto_run->isChecked())
    {
        m_pService_plan->pause();
        m_pService_syncStatus->pause();
    }

    close();
}

MainWindow::~MainWindow()
{
    delete ui;

    if (m_pService_plan != nullptr)
    {
        delete m_pService_plan;
        m_pService_plan = nullptr;
    }
    if (m_pService_syncStatus != nullptr)
    {
        delete m_pService_syncStatus;
        m_pService_syncStatus = nullptr;
    }

    if (m_pServer_api != nullptr)
    {
        delete m_pServer_api;
        m_pServer_api = nullptr;
    }

    if (m_pDataParser != nullptr)
    {
        delete m_pDataParser;
        m_pDataParser = nullptr;
    }

    if (m_pDataParser_Device != nullptr)
    {
        delete m_pDataParser_Device;
        m_pDataParser_Device = nullptr;
    }

    if (m_pResData != nullptr)
    {
        delete m_pResData;
        m_pResData = nullptr;
    }
}

// HTTP-获取返回结果
void MainWindow::OnRespond(const QString& urlRequest, const QString& respond)
{
    // 解析中天平台HTTP返回数据
    ZTS_API api = GetApiType(urlRequest);
    DataParser dataParser;
    RespondObj* pResObj = dataParser.ParseData(respond);
    if (pResObj == nullptr)
        return;

    // 发送远程控制指令给设备
    if (api == API_getTreatStatus)
    {
        Send_Control(pResObj);
    }
    else if (api == API_getTreatPlan) // 下发医嘱
    {
        if (dataParser.UpdateObj(pResObj->obj))
        {
            // 发送治疗方案到设备
            Send_Respond(pResObj->obj);
            //
        }

        DataParser_Treat_Plan dataParser_treat;
        IRespondData* pResData = dataParser_treat.ParseData(api, pResObj->obj);
        if (pResData != nullptr)
        {
            // 处理计划治疗方案
            if (!pResData->GetPatientId().isEmpty())
            {
                if (m_pResData != nullptr)
                {
                    delete m_pResData;
                    m_pResData = nullptr;
                }
                m_pResData = pResData;

                QMetaObject::invokeMethod(qApp, [this, pResData] {
                    ui->le_recordId->setText(pResData->GetRecordId());
                    ui->le_patientID->setText(pResData->GetPatientId());
                    m_Config.m_ConfigObj.Set_recordId(pResData->GetRecordId());
                });
            }
            else
            {
                if (pResData != nullptr)
                {
                    delete pResData;
                    pResData = nullptr;
                }
            }
        }
    }
    delete pResObj;
    pResObj = nullptr;

    QMetaObject::invokeMethod(qApp, [this, urlRequest, respond] {
        ui->le_url->setText(urlRequest);
        ui->te_respond->append(tr("%1 >>> %2\r\n <<< %3").arg(getTime()).arg(urlRequest).arg(respond));
    });
}

// HTTP-返回错误代码
void MainWindow::OnError(const QString& urlRequest, const int& errorCode)
{
    QMetaObject::invokeMethod(qApp, [this, urlRequest, errorCode] {
        ui->le_url->setText(urlRequest);
        ui->te_respond->append(tr("%1 >>> %2\r\n 发生错误: %3").arg(getTime()).arg(urlRequest).arg(errorCode));
    });
}

// TCP
void MainWindow::newConnection(const QString& peerAddress, const quint16& peerPort)
{
    ui->te_tcp->append(QString("%1 [%2:%3] Soket Connected")
                       .arg(getTime())
                       .arg(peerAddress)
                       .arg(peerPort));
}

// TCP
void MainWindow::readyRead(const QString& rev, const QString& peerAddress, const quint16& peerPort)
{
    if (!rev.isEmpty())
    {
        DataParser_Device parser;
        IDataBase_Device* pData = parser.ParseData(&m_deviceStatus, &m_Config, m_pServer_api, rev); // Get data type
        if (pData != nullptr)
        {
            DataParserFactory_Device parserFactory;
            IDataParser_Device* pParser = parserFactory.CreateDataParser(m_Config.Get_sysCode(), pData->GetDataType()); // 创建数据解析器
            if (pParser != nullptr)
            {
                IDataBase_Device* pRet = pParser->ParseData(&m_deviceStatus, &m_Config, m_pServer_api, rev); // Parse data
            }
            else
            {
                ui->te_tcp->append(QString("%1 创建数据解析器失败！！！\r\n%2")
                                   .arg(getTime()).arg(rev));
            }
        }
    }
    ui->te_tcp->append(QString("%1 [%2:%3 <<< Receive:%4]")
                       .arg(getTime())
                       .arg(peerAddress)
                       .arg(peerPort)
                       .arg(rev));
}

// TCP
void MainWindow::SocketError(const QString& err, const QString& peerAddress, const quint16& peerPort)
{
    ui->te_tcp->append(QString("%1 [%2:%3] Soket Error:%4")
                       .arg(getTime())
                       .arg(peerAddress)
                       .arg(peerPort)
                       .arg(err));
}

// TCP
void MainWindow::disconnected(const QString& peerAddress, const quint16& peerPort)
{
    ui->te_tcp->append(QString("%1 [%2:%3] Soket Disonnected")
                       .arg(getTime())
                       .arg(peerAddress)
                       .arg(peerPort));
}

// TCP
void MainWindow::acceptError(const QString& err)
{
    ui->te_tcp->append("Server Error:" + err);
}

// 获取计划治疗方案
void MainWindow::on_btn_getTreatPlan_clicked()
{
    m_pServer_api->getTreatPlan(ui->le_deviceId->text(), ui->le_sysCode->text());

    ui->le_url->setText(((ZTServer_api_Http*)m_pServer_api)->GetRequestUrl());
}

// 获取治疗状态
void MainWindow::on_btn_getTreatStatus_clicked()
{
    m_pServer_api->getTreatStatus(ui->le_deviceId->text(), ui->le_recordId->text());

    ui->le_url->setText(((ZTServer_api_Http*)m_pServer_api)->GetRequestUrl());
}

// 提交设备治疗参数
void MainWindow::on_btn_receiveDevicesData_clicked()
{
    if (m_pResData != nullptr)
    {
        m_pServer_api->receiveDevicesData(m_pResData->ToJson());
    }

    ui->le_url->setText(((ZTServer_api_Http*)m_pServer_api)->GetRequestUrl());
}

// 提交治疗或评定报告
void MainWindow::on_btn_submitReport_clicked()
{
    QString filePath = m_Config.Get_report_folder() + "\\SL4_Training_Information_Report202262414011.pdf";
    m_pServer_api->submitReport(filePath, ui->le_deviceId->text(), ui->le_patientID->text(), ui->le_recordId->text());

    ui->le_url->setText(((ZTServer_api_Http*)m_pServer_api)->GetRequestUrl());
}

// 同步设备状态
void MainWindow::on_btn_syncStatus_clicked()
{
    QDateTime time;
    // 设备状态（1(开机);2(待机);3(治疗中);4(离线)）
    QString devStatus = QString::number(ui->cb_dev_status->currentIndex() + 1);
    m_pServer_api->syncStatus(ui->le_deviceId->text(), time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), devStatus);

    ui->le_url->setText(((ZTServer_api_Http*)m_pServer_api)->GetRequestUrl());
}

// 同步治疗状态
void MainWindow::on_btn_syncTreatStatus_clicked()
{
    QDateTime time;
    // 1:开始治疗；2：结束治疗;3：拒绝治疗
    QString status = QString::number(ui->cb_treat_status->currentIndex() + 1);
    m_pServer_api->syncTreatStatus(ui->le_deviceId->text(), ui->le_recordId->text(), status, time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    ui->le_url->setText(((ZTServer_api_Http*)m_pServer_api)->GetRequestUrl());
}

// 治疗方案下发测试
void MainWindow::on_btn_testData_clicked()
{
    m_pServer_api->testData(ui->le_deviceId->text());

    ui->le_url->setText(((ZTServer_api_Http*)m_pServer_api)->GetRequestUrl());
}

// 开始 / 暂停
void MainWindow::on_cb_auto_run_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        m_pService_plan->resume();
        m_pService_syncStatus->resume();
    }
    else if(arg1 == 0)
    {
        m_pService_plan->pause();
        m_pService_syncStatus->pause();
    }
}

// Clear Log
void MainWindow::on_btn_clear_clicked()
{
    ui->te_respond->clear();
}

QString MainWindow::getTime()
{
    QDateTime time;
    return QString("%1").arg(time.currentDateTime().toString("hh:mm:ss"));
}

// Clear tcp log
void MainWindow::on_btn_clear_tcp_clicked()
{
    ui->te_tcp->clear();
}

// Tcp send
void MainWindow::on_btn_send_clicked()
{
    m_tcpServer.Send(ui->le_send->text().toUtf8());
}

void MainWindow::ShowWindow()
{
    this->showNormal();
    this->raise();
    this->activateWindow();
}

void MainWindow::SystemTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:
    {
        ShowWindow();
        break;
    }
    case QSystemTrayIcon::DoubleClick:
    {
        ShowWindow();
        break;
    }
    default:
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
#if 0
    QMessageBox::StandardButton button = QMessageBox::question(this, tr("退出程序"), QString(tr("确认退出程序")), QMessageBox::Yes|QMessageBox::No);
    if (QMessageBox::No == button)
    {
        event->ignore(); // 忽略退出信号，程序继续进行
    }
    else if(QMessageBox::Yes == button)
    {
        event->accept(); // 接受退出信号，程序退出
    }
#endif

    if (myTray->isVisible())
    {
        hide(); //隐藏主窗口
        event->ignore(); //忽略这个消息
    }
    Log::instance()->info("\r\n*** Hide window ***");
}

// 发送远程控制指令
void MainWindow::Send_Control(RespondObj* pResObj)
{
    // 发送远程控制指令到设备
    Data_Control data;
    data.Status = pResObj->status;
    data.DataType = 6;

    m_tcpServer.Send(data.ToJson());

    ui->te_tcp->append(QString("%1 >>> Send： %2\r\n")
                       .arg(getTime())
                       .arg(data.ToJson().toStdString().c_str()));
}

// 发送医嘱数据
void MainWindow::Send_Respond(const QString& obj)
{
    m_tcpServer.Send(obj.toLatin1());

    ui->te_tcp->append(QString("%1 >>> Send： %2\r\n")
                       .arg(getTime())
                       .arg(obj.toStdString().c_str()));
}
