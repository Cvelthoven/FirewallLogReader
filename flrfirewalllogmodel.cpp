//---------------------------------------------------------------------------------------
//
//  Class flrFirewallLogModel
//
//  This class handles the data interface with the underlying database for the
//  firewall log file.
//
#include "flrfirewalllogmodel.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QtSql>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  Constructor
//
//  Opens database
//
flrFirewallLogModel::flrFirewallLogModel()
{

    //-----------------------------------------------------------------------------------
    //
    //  Get and set settings
    //
    strDatabaseName = "vmdevdb01";
    strHost = "localhost";
    strUserId = "vmlindev01admin";
    strPassword = "#NS01fr#LDrz76#";
    strTblNameFirewall = "flrFirewallLog";

    //-----------------------------------------------------------------------------------
    //
    //  Connect to database
    //
    stlDbDrivers = QSqlDatabase::drivers();
    if (!stlDbDrivers.contains("QPSQL"))
    {
        msgBox.setText("Postgress SQL driver not found");
        msgBox.exec();
        exit(0);
    }

    sdbFirewall = QSqlDatabase::addDatabase("QPSQL");
    sdbFirewall.setHostName(strHost);
    sdbFirewall.setDatabaseName(strDatabaseName);
    sdbFirewall.setPort(-1);
    if (!sdbFirewall.open(strUserId,strPassword))
    {
        msgBox.setText("Failed to open database");
        msgBox.exec();
        exit(0);
    }

    //-----------------------------------------------------------------------------------
    //
    //  Check tables
    //
    stlDbTables = sdbFirewall.tables();
    if (!stlDbTables.contains(strTblNameFirewall))
    {
        flrCreateTblFirewall();
    }

    //-----------------------------------------------------------------------------------
    //
    //  Load firewall logfile
    //


}

//---------------------------------------------------------------------------------------
//
//  flrCreateTblFirewall
//
//  Creates the table with firewall records
//
//    CREATE TABLE public.test
//    (
//      id integer NOT NULL,
//      data text,
//      CONSTRAINT test_pkey PRIMARY KEY (id)
//    )
void flrFirewallLogModel::flrCreateTblFirewall()
{
    QString strQuery;
    //-----------------------------------------------------------------------------------
    //
    //  Built create query to create Firewall table
    //
    strQuery = "CREATE TABLE " + strTblNameFirewall + " (";
    strQuery.append("frwRecId integer NOT NULL, ");
    strQuery.append("frwTimestamp timestamp, ");
//    strQuery.append("frwNodeName text, ");
//    strQuery.append("frwUlogD text, ");
//    strQuery.append("frwId integer, ");
//    strQuery.append("frwSys text, ");
//    strQuery.append("frwSub text, ");
//    strQuery.append("frwName text, ");
    strQuery.append("frwAction text, ");
    strQuery.append("frwFwRule int, ");
    strQuery.append("frwInterfaceIn text, ");
    strQuery.append("frwInterfaceOut text, ");
    strQuery.append("frwSourceMac text, ");
    strQuery.append("frwSourceIp text, ");
    strQuery.append("frwSourcePort integer, ");
    strQuery.append("frwDestMac text, ");
    strQuery.append("frwDestIp text, ");
    strQuery.append("frwDestPort integer, ");
    strQuery.append("frwMark text, ");
    strQuery.append("frwApp text, ");
    strQuery.append("frwProtocol text, ");
    strQuery.append("frwLength text, ");
    strQuery.append("frwTos text, ");
    strQuery.append("frwPrec text, ");
    strQuery.append("frwTtl text, ");
    strQuery.append("frwTcpFlags text, ");
    strQuery.append("frwType text, ");
    strQuery.append("frwCode text, ");
    strQuery.append("CONSTRAINT " + strTblNameFirewall + "_pkey PRIMARY KEY (frwRecId)");
    strQuery.append(");");

    //-----------------------------------------------------------------------------------
    //
    //  Create table
    //
    QSqlQuery qQuery("",sdbFirewall);
    if (!qQuery.exec(strQuery))
    {
        qDebug() << sdbFirewall.lastError();
    }
    strQuery = "CREATE INDEX " + strTblNameFirewall + "_time ON " + strTblNameFirewall + " (frwTimestamp);";
    if (!qQuery.exec(strQuery))
    {
        qDebug() << sdbFirewall.lastError();
    }

}

//---------------------------------------------------------------------------------------
//
//  flrCreateTblFirewall
//
//  Creates the table with firewall records
//
//    CREATE TABLE public.test
//    (
//      id integer NOT NULL,
//      data text,
//      CONSTRAINT test_pkey PRIMARY KEY (id)
//    )
void flrFirewallLogModel::flrLoadLogFileFirewall()
{

    strLogFileName = "FirewallInput.log";

    //-----------------------------------------------------------------------------------
    //
    //  Open logfile
    //
    QFile qfiFirewallInput(strLogFileName);
    if (!qfiFirewallInput.open(QFile::ReadOnly))
    {
        msgBox.setText("Failed to open firewall logfile");
        msgBox.exec();
    }
}
