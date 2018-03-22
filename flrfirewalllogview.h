#ifndef FLRFIREWALLLOGVIEW_H
#define FLRFIREWALLLOGVIEW_H

#include <QStandardItemModel>
#include <QObject>

class flrFirewallLogView : public QStandardItemModel
{
public:
    flrFirewallLogView(QObject *parent);

private:
    void initializeView();

};

#endif // FLRFIREWALLLOGVIEW_H
