#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QString>
#include <QTableView>

#include "flrfirewalllogmodel.h"
#include "flrfirewalllogview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionLoad_logfile_triggered();

    void on_actionConnect_DB_triggered();

private:
    void createModelAndView();
    void dbConnect();
    void IntializeProgram();
    void setDefaultSettings();

    Ui::MainWindow *ui;

    flrFirewallLogModel *FirewallLogModel;

    QString
        strDatabaseName,
        strHost,
        strFirewallLogFileName,
        strUserId,
        strPassword;

    flrFirewallLogView
        *FirewallLogView;

};

#endif // MAINWINDOW_H
