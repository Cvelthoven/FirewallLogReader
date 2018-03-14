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
//  flrAppendQuery
//
void flrFirewallLogModel::flrAppendQuery(QString *strQueryP1,QString *strQueryP2)
{
    //-----------------------------------------------------------------------------------
    //
    //  Built Query part 1
    //
    strQueryPart1.append(",");
    strQueryPart1.append(strQueryP1);

    //-----------------------------------------------------------------------------------
    //
    //  Built Query part 2
    //
    strQueryPart2.append(",\'");
    strQueryPart2.append(strQueryP2);
    strQueryPart2.append("\'");
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
int flrFirewallLogModel::flrConvertLineToRecord(QString *strLogInputLine)
{
    int
        iSourcePortVal,
        iDestPortVal,
        iFieldCnt = 0,
        iFieldLenght,
        iFwRuleNumber,
        iInputLineLength,
        iInLineUsed = 0,
        iReturnCode = 0,
        iYear,
        iMonth,
        iDay,
        iHour,
        iMin,
        iSec;

    QString strActionVal,
            strInterfaceInVal,
            strInterfaceOutVal,
            strSourceMacVal,
            strSourceIpVal,
            strDestMacVal,
            strDestIpVal,
            strMarkVal,
            strAppVal,
            strProtocolVal,
            strLengthVal,
            strTosVal,
            strPrecVal,
            strTtlVal,
            strTcpFlagsVal,
            strTypeVal,
            strCodeVal,
            strFieldName,
            strQuery,
            strTemp;

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

    //----------------------------------------------------------------------------------
    //
    //  Initialize query parts
    strQueryPart1 = "INSERT INTO " + strTblNameFirewall + " (";
    strQueryPart2 = ") VALUES (";

    //----------------------------------------------------------------------------------
    //
    //  Firewall rule number to check for further processing
    //
    strTemp = stlField.at(10);
    iFwRuleNumber = strTemp.section("\"",1,1).toInt();

    //-----------------------------------------------------------------------------------
    //
    //  Exclude default rules 60001,60002 and 60003
    if (!((iFwRuleNumber == 60001)||(iFwRuleNumber == 60002)||(iFwRuleNumber == 60003)))
    {
        //-----------------------------------------------------------------------------------
        //
        //  Process fixed fields
        //
        //  Timestamp
        //  First argument
        strTemp = stlField.at(0);
        strTemp.replace("-",":");
        iYear     = strTemp.section(":",0,0).toInt();
        iMonth    = strTemp.section(":",1,1).toInt();
        iDay      = strTemp.section(":",2,2).toInt();
        iHour     = strTemp.section(":",3,3).toInt();
        iMin      = strTemp.section(":",4,4).toInt();
        iSec      = strTemp.section(":",5,5).toInt();
        QDateTime qdtTimeStamp (QDate(iYear,iMonth,iDay),QTime(iHour,iMin,iSec));
        strTemp = qdtTimeStamp.toString();
        strQueryPart1.append(strFldfrwTimestamp);
        strQueryPart2.append("\'");
        strQueryPart2.append(strTemp);
        strQueryPart2.append("\'");

        //
        //  Action
        //
        strTemp = stlField.at(8);
        strActionVal = strTemp.section("\"",0,0);
        flrAppendQuery(&strFldfrwAction,&strActionVal);

        //
        //  Firewallrule
        //
        strTemp = QString("%1").arg(iFwRuleNumber);
        flrAppendQuery(&strFldfrwFwRule,&strTemp);

        //-------------------------------------------------------------------------------
        //
        //  Process remaining fields
        //
        for (iFieldCnt = 11; iFieldCnt < stlField.size();iFieldCnt++)
        {
            strTemp = stlField.at(iFieldCnt);
            strFieldName = strTemp.section("=",0,0);
            if (strFieldName == "app")
            {
                strAppVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwApp,&strAppVal);
            }
            if (strFieldName == "code")
            {
                strCodeVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwCode,&strCodeVal);
            }
            if (strFieldName == "dstip")
            {
                strDestIpVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwDestIp,&strDestIpVal);
            }
            if (strFieldName == "dstmac")
            {
                strDestMacVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwDestMac,&strDestMacVal);
            }
            if (strFieldName == "dstport")
            {
                iDestPortVal = strTemp.section("\"",1,1).toInt();
                strTemp = QString("%1").arg(iDestPortVal);
                flrAppendQuery(&strFldfrwDestPort,&strTemp);
            }
            if (strFieldName == "initf")
            {
                strInterfaceInVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwInterfaceIn,&strInterfaceInVal);
            }
            if (strFieldName == "length")
            {
                strLengthVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwLength,&strLengthVal);
            }
            if (strFieldName == "mark")
            {
                strMarkVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwMark,&strMarkVal);
            }
            if (strFieldName == "outitf")
            {
                strInterfaceOutVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwInterfaceOut,&strInterfaceOutVal);
            }
            if (strFieldName == "prec")
            {
                strPrecVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwPrec,&strPrecVal);
            }
            if (strFieldName == "proto")
            {
                strProtocolVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwProtocol,&strProtocolVal);
            }
            if (strFieldName == "srcip")
            {
                strSourceIpVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwSourceIp,&strSourceIpVal);
            }
            if (strFieldName == "srcmac")
            {
                strSourceMacVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwSourceMac,&strSourceMacVal);
            }
            if (strFieldName == "srcport")
            {
                iSourcePortVal = strTemp.section("\"",1,1).toInt();
                strTemp = QString("%1").arg(iSourcePortVal);
                flrAppendQuery(&strFldfrwSourcePort,&strTemp);
            }
            if (strFieldName == "tcpflags")
            {
                strTcpFlagsVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwTcpFlags,&strTcpFlagsVal);
            }
            if (strFieldName == "tos")
            {
                strTosVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwTos,&strTosVal);
            }
            if (strFieldName == "ttl")
            {
                strTtlVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwTtl,&strTtlVal);
            }
            if (strFieldName == "type")
            {
                strTypeVal = strTemp.section("\"",1,1);
                flrAppendQuery(&strFldfrwType,&strTypeVal);
            }
        }
        //-------------------------------------------------------------------------------
        //
        //  Insert record to database
        //
        strQueryPart2.append(");");
        strQuery = strQueryPart1 + strQueryPart2;
        QSqlQuery qQuery("",sdbFirewall);
        if (!qQuery.exec(strQuery))
        {
            qDebug() << sdbFirewall.lastError();
        }
        else
        {
            iReturnCode = 1;
        }
    }

    return(iReturnCode);
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
    int iTotalLines = 0,
        iTotalRecords = 0;


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
            iTotalRecords = iTotalRecords + flrConvertLineToRecord(&strFirewallInputLine);
            iTotalLines++;
        }
        QString strMessage = QString("Total lines processed: %1. Total records added: %2").arg(iTotalLines).arg(iTotalRecords);
        msgBox.setText(strMessage);
        msgBox.exec();
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
