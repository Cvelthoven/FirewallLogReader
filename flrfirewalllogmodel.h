#ifndef FLRFIREWALLLOGMODEL_H
#define FLRFIREWALLLOGMODEL_H

#include <QStandardItemModel>

class flrFirewallLogModel : public QStandardItemModel
{
    Q_OBJECT
public:
    flrFirewallLogModel(QObject *parent);

};


//--------------- old code --------------------
//#include <QAbstractTableModel>


//class flrFirewallLogModel : public QAbstractTableModel
//{
//    Q_OBJECT
//public:
//    flrFirewallLogModel(QObject *parent);

//};

//#include <QMessageBox>
//#include <QSqlDatabase>
//#include <QString>
//#include <QStringList>
//#include <QTextStream>

//void flrCreateTblFirewall();
//void flrLoadLogFileFirewall(QString *strFirewallLogFileName);

//private:
//QMessageBox
//    msgBox;

//QTextStream tstLogFileFirewall;

//QSqlDatabase
//    sdbFirewall;

//QString
//    strDatabaseName,
//    strFileNameIn,
//    strHost,
//    strLogFileName,
//    strTblNameFirewall,
//    strPassword,
//    strUserId;

//QStringList
//    stlDbDrivers,
//    stlDbTables;

#endif // FLRFIREWALLLOGMODEL_H
