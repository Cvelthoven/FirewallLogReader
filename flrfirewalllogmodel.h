#ifndef FLRFIREWALLLOGMODEL_H
#define FLRFIREWALLLOGMODEL_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QTextStream>

class flrFirewallLogModel
{
public:
    flrFirewallLogModel();
    void flrCreateTblFirewall();
    void flrLoadLogFileFirewall();

private:
    QMessageBox
        msgBox;

    QTextStream tstLogFileFirewall;

    QSqlDatabase
        sdbFirewall;

    QString
        strDatabaseName,
        strFileNameIn,
        strHost,
        strLogFileName,
        strTblNameFirewall,
        strPassword,
        strUserId;

    QStringList
        stlDbDrivers,
        stlDbTables;

};

#endif // FLRFIREWALLLOGMODEL_H
