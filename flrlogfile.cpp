//---------------------------------------------------------------------------------------
//
//  flrLogfile
//
//  Class containing the application logfile
//
#include "flrlogfile.h"
#include "mainwindow.h"

#include <QSettings>
#include <QString>

flrLogFile::flrLogFile(QObject *parent)
{
    //-----------------------------------------------------------------------------------
    //
    //  Retrieve logfile path and name
    //
    QSettings programDefaults(parent) ;
    QVariant temp = programDefaults.value("DatabaseName");
    if (temp.isValid())
    {
        QString strLogFilePath = temp.toString();
        temp = programDefaults.value("Logfile");
        QString strLogFileName = temp.toString();
    }
    else
    {
        programDefaults.setValue("LogPath","test");
        programDefaults.setValue("Logfile","FirewallLogReaderLog.log");

    }

}
