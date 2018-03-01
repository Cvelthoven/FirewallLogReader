#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "flrfirewalllogmodel.h"

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

private:
    Ui::MainWindow *ui;

    flrFirewallLogModel *FirewallLogModel;

    QString strFirewallLogFileName;
};

#endif // MAINWINDOW_H
