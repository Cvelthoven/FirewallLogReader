//---------------------------------------------------------------------------------------
//
//  Class flrFirewallLogModel
//
//  This class handles the data interface with the underlying database for the
//  firewall log file.
//
#include "flrfirewalllogmodel.h"

#include <QDate>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QTextStream>
#include <QtSql>
#include <QString>
#include <QStringList>
#include <QTime>

//---------------------------------------------------------------------------------------
//
//  Constructor
//
//
flrFirewallLogModel::flrFirewallLogModel(QObject *parent)
    :QStandardItemModel(parent)
{
}


//---------------------------------------------------------------------------------------
//
//  flrLoadLogFileFirewall
//
void flrFirewallLogModel::flrConnectDB(QString *strDatabaseName, QString *strHostName, QString *strUserId, QString *strPassword)
{
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
    sdbFirewall.setHostName(*strHostName);
    sdbFirewall.setDatabaseName(*strDatabaseName);
    sdbFirewall.setPort(-1);
    if (!sdbFirewall.open(*strUserId,*strPassword))
    {
        msgBox.setText("Failed to open database");
        msgBox.exec();
        exit(0);
    }
    //-----------------------------------------------------------------------------------
    //
    //  Check tables
    //  Table names are all in lowercase
    //
    strTblNameFirewall = "flrfirewalllog";

    stlDbTables = sdbFirewall.tables();
    if (!stlDbTables.contains(strTblNameFirewall))
    {
        flrCreateTblFirewall(&strTblNameFirewall);
    }
}


//---------------------------------------------------------------------------------------
//
//  flrConvertLineToRecord
//
void flrFirewallLogModel::flrConvertLineToRecord(QString *strLogInputLine)
{
    int iFieldCnt = 0,
        iFieldLenght,
        iInputLineLength,
        iInLineUsed = 0,
        iYear,
        iMonth,
        iDay,
        iHour,
        iMin,
        iSec;

    QString strTemp;

    QStringList stlField;

    //-----------------------------------------------------------------------------------
    //
    //  Get all fields in inputline
    //
    iInputLineLength = strLogInputLine->size();
    while (iInLineUsed < iInputLineLength)
    {
        strTemp = strLogInputLine->section(" ",iFieldCnt,iFieldCnt);
        stlField.append(strTemp);
        iFieldLenght = strTemp.size();
        iInLineUsed += iFieldLenght + 1;
        iFieldCnt++;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Process fixed fields
    //
    //  Timestamp
    //  2017:12:26-00:00:02
    strTemp = stlField.at(0);
    strTemp.replace("-",":");
    iYear     = strTemp.section(":",0,0).toInt();
    iMonth    = strTemp.section(":",1,1).toInt();
    iDay      = strTemp.section(":",2,2).toInt();
    iHour     = strTemp.section(":",3,3).toInt();
    iMin      = strTemp.section(":",4,4).toInt();
    iSec      = strTemp.section(":",5,5).toInt();
    QDateTime qdtTimeStamp (QDate(iYear,iMonth,iDay),QTime(iHour,iMin,iSec));

    strTemp = stlField.at(8);
    strTemp = stlField.at(10);

    //-----------------------------------------------------------------------------------
    //
    //  Process remaining fields
    //
    for (iFieldCnt = 11; iFieldCnt < stlField.size();iFieldCnt++)
    {
        strTemp = stlField.at(iFieldCnt);
    }

    // INSERT INTO table (field1, field2) VALUES (1,eeee);

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
void flrFirewallLogModel::flrCreateTblFirewall(QString *flrTableName)
{
    QString strQuery;
    //-----------------------------------------------------------------------------------
    //
    //  Built create query to create Firewall table
    //
    strQuery = "CREATE TABLE " + *flrTableName + " (";
    strQuery.append(strFldfrwRecId + " SERIAL, ");
    strQuery.append(strFldfrwTimestamp + " timestamp, ");
//    strQuery.append("frwNodeName text, ");
//    strQuery.append("frwUlogD text, ");
//    strQuery.append("frwId integer, ");
//    strQuery.append("frwSys text, ");
//    strQuery.append("frwSub text, ");
//    strQuery.append("frwName text, ");
    strQuery.append(strFldfrwAction + " text, ");
    strQuery.append(strFldfrwFwRule + " int, ");
    strQuery.append(strFldfrwInterfaceIn + " text, ");
    strQuery.append(strFldfrwInterfaceOut + " text, ");
    strQuery.append(strFldfrwSourceMac + " text, ");
    strQuery.append(strFldfrwSourceIp + " text, ");
    strQuery.append(strFldfrwSourcePort + " integer, ");
    strQuery.append(strFldfrwDestMac + " text, ");
    strQuery.append(strFldfrwDestIp + " text, ");
    strQuery.append(strFldfrwDestPort + " integer, ");
    strQuery.append(strFldfrwMark + " text, ");
    strQuery.append(strFldfrwApp + " text, ");
    strQuery.append(strFldfrwProtocol + " text, ");
    strQuery.append(strFldfrwLength + " text, ");
    strQuery.append(strFldfrwTos + " text, ");
    strQuery.append(strFldfrwPrec + " text, ");
    strQuery.append(strFldfrwTtl + " text, ");
    strQuery.append(strFldfrwTcpFlags + " text, ");
    strQuery.append(strFldfrwType + " text, ");
    strQuery.append(strFldfrwCode + " text, ");
    strQuery.append("CONSTRAINT " + *flrTableName + "_pkey PRIMARY KEY (" + strFldfrwRecId + ")");
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
    strQuery = "CREATE INDEX " + *flrTableName + "_time ON " + *flrTableName + " (" + strFldfrwTimestamp + ");";
    if (!qQuery.exec(strQuery))
    {
        qDebug() << sdbFirewall.lastError();
    }

}


//---------------------------------------------------------------------------------------
//
//  flrLoadLogFileFirewall
//
void flrFirewallLogModel::flrLoadLogFileFirewall(QString *strFirewallLogFileName)
{
    QString
        strFirewallInputLine;

    //-----------------------------------------------------------------------------------
    //
    //  Open logfile
    //
    QFile qfiFirewallInput(*strFirewallLogFileName);
    if (qfiFirewallInput.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        //-------------------------------------------------------------------------------
        //
        //  Process file line by line
        //
        QTextStream qtsFirewallInput(&qfiFirewallInput);
        while (!qtsFirewallInput.atEnd())
        {
            strFirewallInputLine = qtsFirewallInput.readLine();
            flrConvertLineToRecord(&strFirewallInputLine);
        }
    }
    else
    {
        msgBox.setText("Failed to open firewall logfile");
        msgBox.exec();
    }


    //-----------------------------------------------------------------------------------
    //
    //  Close logfile
    //
    qfiFirewallInput.close();
}
