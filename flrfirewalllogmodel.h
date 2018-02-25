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
        strFileNameIn,
        strHost,
        strTblNameFirewall,
        strPassword,
        strUserId;

    QStringList
        stlDbDrivers,
        stlDbTables;

};

#endif // FLRFIREWALLLOGMODEL_H
