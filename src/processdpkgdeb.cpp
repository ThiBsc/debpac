#include "processdpkgdeb.h"

ProcessDpkgdeb::ProcessDpkgdeb(QObject *parent)
    : QProcess(parent)
{
    connect(this, SIGNAL(readyReadStandardOutput()), this, SLOT(needToSendOutput()));
    connect(this, SIGNAL(readyReadStandardError()), this, SLOT(needToSendError()));
}

ProcessDpkgdeb::~ProcessDpkgdeb()
{

}

#include <QDebug>
void ProcessDpkgdeb::needToSendOutput()
{
    QByteArray std_output = readAllStandardOutput();
    QString str_output = std_output.toStdString().c_str();
    qDebug() << str_output;
    emit textFromStandardOutput(str_output);
}

void ProcessDpkgdeb::needToSendError()
{
    QByteArray std_error = readAllStandardError();
    QString str_error = std_error.toStdString().c_str();
    qDebug() << str_error;
    emit textFromStandardError(str_error);
}
