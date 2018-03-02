#ifndef FLRFIREWALLLOGMODEL_H
#define FLRFIREWALLLOGMODEL_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QString>
#include <QStringList>

class flrFirewallLogModel : public QStandardItemModel
{
    Q_OBJECT
public:
    flrFirewallLogModel(QObject *parent);
    void flrConnectDB(QString *strDatabaseName, QString *strHostName, QString *strUserId, QString *strPassword);
    void flrCreateTblFirewall(QString *flrTableName);
    void flrLoadLogFileFirewall(QString *strFirewallLogFileName);

private:
    QSqlDatabase
        sdbFirewall;

    QMessageBox
        msgBox;

    QString
        strTblNameFirewall;

    QStringList
        stlDbDrivers,
        stlDbTables;

};

#endif // FLRFIREWALLLOGMODEL_H
