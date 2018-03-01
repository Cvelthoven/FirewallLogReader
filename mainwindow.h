#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableView>

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


private:
    Ui::MainWindow *ui;

//    QTableView *flrFirewallLogView;
    flrFirewallLogModel *FirewallLogModel;


};

#endif // MAINWINDOW_H
