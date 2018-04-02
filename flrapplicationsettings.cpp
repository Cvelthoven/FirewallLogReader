//---------------------------------------------------------------------------------------
//
//  flrApplicationSettings
//
//  Retrieve and maintain application settings
//
#include "flrapplicationsettings.h"

#include <QCoreApplication>
#include <QSettings>
#include <QString>

//---------------------------------------------------------------------------------------
//
//  Default contructor
//
flrApplicationSettings::flrApplicationSettings()
{
    //-----------------------------------------------------------------------------------
    //
    //  Set application environment definitions
    //
    QCoreApplication::setOrganizationName("CVelthoven");
    QCoreApplication::setOrganizationDomain("CVelthoven.com");
    QCoreApplication::setApplicationName("FirewallLogReader");

}

//---------------------------------------------------------------------------------------
//
//  flrGetAppSetting
//
//  retrieve application setting value
//
QString flrApplicationSettings::flrGetAppSetting(const QString *strSettingName)
{

    QSettings programDefaults;
    QVariant temp = programDefaults.value(*strSettingName);
    QString strSettingValue = temp.toString();
    return strSettingValue;
}
