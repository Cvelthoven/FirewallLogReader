#ifndef FLRFIREWALLLOGMODEL_H
#define FLRFIREWALLLOGMODEL_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QString>
#include <QStringList>

class flrFirewallLogModel
{
public:
    flrFirewallLogModel();
    void flrCreateTblFirewall();

private:
    QMessageBox
        msgBox;

    QSqlDatabase
        sdbFirewall;

    QString
        strDatabaseName,
        strTblNameFirewall,
        strHost,
        strUserId,
        strPassword;

    QStringList
        stlDbDrivers,
        stlDbTables;

};

#endif // FLRFIREWALLLOGMODEL_H
