#ifndef FLRAPPLICATIONSETTINGS_H
#define FLRAPPLICATIONSETTINGS_H

#include <QString>

class flrApplicationSettings
{
public:
    flrApplicationSettings();
    QString flrGetAppSetting(const QString *strSettingName);
};

#endif // FLRAPPLICATIONSETTINGS_H
