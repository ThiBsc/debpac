#include "processdpkgdeb.h"
#include <QMessageBox>

ProcessDpkgdeb::ProcessDpkgdeb(QObject *parent)
    : QProcess(parent)
{
    connect(this, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(commandIsFinished(int,QProcess::ExitStatus)));
}

ProcessDpkgdeb::~ProcessDpkgdeb()
{

}

void ProcessDpkgdeb::generatePackage(const QString &tmpfolder, const QString &outdebian)
{
    param_folder = tmpfolder;
    param_out = outdebian;
    start("gksudo", QStringList() << QString("dpkg-deb --build %1 %2").arg(param_folder).arg(param_out));
}

void ProcessDpkgdeb::commandIsFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::NormalExit) {
        if (exitCode == 0){
            QMessageBox::information(dynamic_cast<QWidget*>(parent()), tr("Generate status"), QString("dpkg-deb finish with code %1\nYou package is located to:\n%2").arg(exitCode).arg(param_out));
        } else {
            QMessageBox::critical(dynamic_cast<QWidget*>(parent()), tr("Generate status"), QString("dpkg-deb finish with code %1\nVerify your control file syntax or report the problem").arg(exitCode));
        }
    } else {
        QMessageBox::critical(dynamic_cast<QWidget*>(parent()), tr("Generate status"), QString("Error with the command line:\n%1").arg(program()));
    }
}
