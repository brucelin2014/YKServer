QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += $$PWD

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ZTS_def.cpp \
    entity/configobj.cpp \
    entity/data_control.cpp \
    entity/data_device_data_a1.cpp \
    entity/data_device_data_a1s.cpp \
    entity/data_device_data_a3_2.cpp \
    entity/data_device_data_a6_2.cpp \
    entity/data_device_data_a8.cpp \
    entity/data_device_data_ps1.cpp \
    entity/data_device_data_sl4.cpp \
    entity/data_device_heart.cpp \
    entity/data_device_report.cpp \
    entity/data_device_respond.cpp \
    entity/database_device.cpp \
    entity/patientobj.cpp \
    entity/responddatabase.cpp \
    entity/responddataobj_a1.cpp \
    entity/responddataobj_a1s.cpp \
    entity/responddataobj_a3_2.cpp \
    entity/responddataobj_a6_2.cpp \
    entity/responddataobj_a8.cpp \
    entity/responddataobj_ps1.cpp \
    entity/responddataobj_sl4.cpp \
    entity/respondobj.cpp \
    entity/respondobj_a1.cpp \
    entity/respondobj_a1s.cpp \
    entity/respondobj_a3_2.cpp \
    entity/respondobj_a6_2.cpp \
    entity/respondobj_a8.cpp \
    entity/respondobj_device.cpp \
    entity/respondobj_ps1.cpp \
    entity/respondobj_sl4.cpp \
    entity/respondobj_treat_plan.cpp \
    impl/configimpl.cpp \
    impl/dataparser.cpp \
    impl/dataparser_a1.cpp \
    impl/dataparser_a1_device_data.cpp \
    impl/dataparser_a1s.cpp \
    impl/dataparser_a1s_device_data.cpp \
    impl/dataparser_a3_2.cpp \
    impl/dataparser_a3_2_device_data.cpp \
    impl/dataparser_a6_2.cpp \
    impl/dataparser_a6_2_device_data.cpp \
    impl/dataparser_a8.cpp \
    impl/dataparser_a8_device_data.cpp \
    impl/dataparser_device.cpp \
    impl/dataparser_device_heart.cpp \
    impl/dataparser_device_report.cpp \
    impl/dataparser_device_respond.cpp \
    impl/dataparser_ps1.cpp \
    impl/dataparser_ps1_device_data.cpp \
    impl/dataparser_sl4.cpp \
    impl/dataparser_sl4_device_data.cpp \
    impl/dataparser_treat_plan.cpp \
    impl/dataparserfactory.cpp \
    impl/dataparserfactory_device.cpp \
    impl/dataparserfactory_device_a1.cpp \
    impl/dataparserfactory_device_a1s.cpp \
    impl/dataparserfactory_device_a3_2.cpp \
    impl/dataparserfactory_device_a6_2.cpp \
    impl/dataparserfactory_device_a8.cpp \
    impl/dataparserfactory_device_ps1.cpp \
    impl/dataparserfactory_device_sl4.cpp \
    impl/devicestatusmgr.cpp \
    impl/systemtray.cpp \
    impl/ztserver_api_http.cpp \
    impl/ztservice_syncStatus_thread.cpp \
    impl/ztservice_tcp_thread.cpp \
    impl/ztservice_thread.cpp \
    main.cpp \
    mainwindow.cpp \
    util/httpclient.cpp \
    util/jsontools.cpp \
    util/log.cpp \
    util/logmgr.cpp \
    util/qstringtools.cpp \
    util/tcpserver.cpp \

HEADERS += \
    ZTS_def.h \
    entity/configobj.h \
    entity/data_control.h \
    entity/data_device_data_a1.h \
    entity/data_device_data_a1s.h \
    entity/data_device_data_a3_2.h \
    entity/data_device_data_a6_2.h \
    entity/data_device_data_a8.h \
    entity/data_device_data_ps1.h \
    entity/data_device_data_sl4.h \
    entity/data_device_heart.h \
    entity/data_device_report.h \
    entity/data_device_respond.h \
    entity/database_device.h \
    entity/patientobj.h \
    entity/responddatabase.h \
    entity/responddataobj_a1.h \
    entity/responddataobj_a1s.h \
    entity/responddataobj_a3_2.h \
    entity/responddataobj_a6_2.h \
    entity/responddataobj_a8.h \
    entity/responddataobj_ps1.h \
    entity/responddataobj_sl4.h \
    entity/respondobj.h \
    entity/respondobj_a1.h \
    entity/respondobj_a1s.h \
    entity/respondobj_a3_2.h \
    entity/respondobj_a6_2.h \
    entity/respondobj_a8.h \
    entity/respondobj_device.h \
    entity/respondobj_ps1.h \
    entity/respondobj_sl4.h \
    entity/respondobj_treat_plan.h \
    impl/configimpl.h \
    impl/dataparser.h \
    impl/dataparser_a1.h \
    impl/dataparser_a1_device_data.h \
    impl/dataparser_a1s.h \
    impl/dataparser_a1s_device_data.h \
    impl/dataparser_a3_2.h \
    impl/dataparser_a3_2_device_data.h \
    impl/dataparser_a6_2.h \
    impl/dataparser_a6_2_device_data.h \
    impl/dataparser_a8.h \
    impl/dataparser_a8_device_data.h \
    impl/dataparser_device.h \
    impl/dataparser_device_heart.h \
    impl/dataparser_device_report.h \
    impl/dataparser_device_respond.h \
    impl/dataparser_ps1.h \
    impl/dataparser_ps1_device_data.h \
    impl/dataparser_sl4.h \
    impl/dataparser_sl4_device_data.h \
    impl/dataparser_treat_plan.h \
    impl/dataparserfactory.h \
    impl/dataparserfactory_device.h \
    impl/dataparserfactory_device_a1.h \
    impl/dataparserfactory_device_a1s.h \
    impl/dataparserfactory_device_a3_2.h \
    impl/dataparserfactory_device_a6_2.h \
    impl/dataparserfactory_device_a8.h \
    impl/dataparserfactory_device_ps1.h \
    impl/dataparserfactory_device_sl4.h \
    impl/devicestatusmgr.h \
    impl/systemtray.h \
    impl/ztserver_api_http.h \
    impl/ztservice_syncStatus_thread.h \
    impl/ztservice_tcp_thread.h \
    impl/ztservice_thread.h \
    interface/IConfig.h \
    interface/IDataBase_Device.h \
    interface/IDataParser.h \
    interface/IDataParser_Device.h \
    interface/IDeviceStatus.h \
    interface/IRespondData.h \
    interface/ITcpServer_Listener.h \
    interface/IZTServer_api.h \
    interface/IZTServer_api_Listener.h \
    interface/IZTServer_tcp_Listener.h \
    mainwindow.h \
    util/httpclient.h \
    util/jsontools.h \
    util/log.h \
    util/logmgr.h \
    util/qstringtools.h \
    util/tcpserver.h \

FORMS += \
    mainwindow.ui

# Add Log4qt libary
INCLUDEPATH += $$PWD/lib/log4qt/src
LIBS += -L$$PWD/lib/log4qt/lib -llog4qt

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrc.qrc

RC_ICONS = yk.ico
