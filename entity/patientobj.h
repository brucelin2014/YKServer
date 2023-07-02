// 2023-03-03, Bruce

#ifndef PATIENTOBJ_H
#define PATIENTOBJ_H

#include <QObject>

// 患者信息
class PatientObj : public QObject
{
    Q_OBJECT
public:
    PatientObj();

    QString patientName;
    QString patientId;
    QString sex;
    QString age;
};

#endif // PATIENTOBJ_H
