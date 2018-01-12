#ifndef PROCESSDPKGDEB_H
#define PROCESSDPKGDEB_H

#include <QProcess>

/**
 * @brief The ProcessDpkgdeb class
 * The process to manage the generation of the .deb file
 */

class ProcessDpkgdeb : public QProcess
{
    Q_OBJECT
public:
    ProcessDpkgdeb(QObject *parent = Q_NULLPTR);
    ~ProcessDpkgdeb();
    void generatePackage(const QString& tmpfolder, const QString& outdebian);

private slots:
    void commandIsFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    QString param_folder;
    QString param_out;

};

#endif // PROCESSDPKGDEB_H
