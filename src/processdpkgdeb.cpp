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
    emit textFromStandardOutput(std_output);
}

void ProcessDpkgdeb::needToSendError()
{
    QByteArray std_error = readAllStandardError();
    emit textFromStandardError(std_error);
}
