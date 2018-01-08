#ifndef PROCESSDPKGDEB_H
#define PROCESSDPKGDEB_H

#include <QProcess>

class ProcessDpkgdeb : public QProcess
{
    Q_OBJECT
public:
    ProcessDpkgdeb(QObject *parent = Q_NULLPTR);
    ~ProcessDpkgdeb();

private slots:
    void needToSendOutput();
    void needToSendError();

signals:
    void textFromStandardOutput(const QByteArray& output);
    void textFromStandardError(const QByteArray& error);

};

#endif // PROCESSDPKGDEB_H
