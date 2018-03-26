//---------------------------------------------------------------------------------------
//
//  flrFirewallLogView
//
//  Class containing the presentatie layer of firewall log items
//
#include "flrfirewalllogview.h"

#include <QStandardItemModel>
#include <QStringList>


//---------------------------------------------------------------------------------------
//
//  Default constructor
//
flrFirewallLogView::flrFirewallLogView(QObject *parent)
    : QStandardItemModel(parent)
{
    initializeView();
}

//---------------------------------------------------------------------------------------
//
//  initializeView
//
void flrFirewallLogView::initializeView()
{
    QStringList stlHeaderLabels;

    stlHeaderLabels = QStringList() << tr("Timestamp") << tr("Rule");
    setHorizontalHeaderLabels(stlHeaderLabels);

}
