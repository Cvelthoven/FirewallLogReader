#ifndef FLRFIREWALLLOGMODEL_H
#define FLRFIREWALLLOGMODEL_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QString>
#include <QStringList>
#include <QTextStream>

class flrFirewallLogModel : public QStandardItemModel
{
    Q_OBJECT
public:
    flrFirewallLogModel(QObject *parent);
    void flrConnectDB(QString *strDatabaseName, QString *strHostName, QString *strUserId, QString *strPassword);
    void flrConvertLineToRecord(QString *strLogInputLine);
    void flrCreateTblFirewall(QString *flrTableName);
    void flrLoadLogFileFirewall(QString *strFirewallLogFileName);

private:
    QSqlDatabase
        sdbFirewall;

    QMessageBox
        msgBox;

    QString
        strTblNameFirewall,
        strFldfrwRecId =  "frwRecId",
        strFldfrwTimestamp = "frwTimestamp",
        strFldfrwAction = "frwAction",
        strFldfrwFwRule = "frwFwRule",
        strFldfrwInterfaceIn = "frwInterfaceIn",
        strFldfrwInterfaceOut = "frwInterfaceOut",
        strFldfrwSourceMac = "frwSourceMac",
        strFldfrwSourceIp = "frwSourceIp",
        strFldfrwSourcePort = "frwSourcePort",
        strFldfrwDestMac = "frwDestMac",
        strFldfrwDestIp = "frwDestIp",
        strFldfrwDestPort = "frwDestPort",
        strFldfrwMark = "frwMark",
        strFldfrwApp = "frwApp",
        strFldfrwProtocol = "frwProtocol",
        strFldfrwLength = "frwLength",
        strFldfrwTos = "frwTos",
        strFldfrwPrec = "frwPrec",
        strFldfrwTtl = "frwTtl",
        strFldfrwTcpFlags = "frwTcpFlags",
        strFldfrwType = "frwType",
        strFldfrwCode = "frwCode";

    QStringList
        stlDbDrivers,
        stlDbTables;

};

#endif // FLRFIREWALLLOGMODEL_H
