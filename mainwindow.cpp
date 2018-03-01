//---------------------------------------------------------------------------------------
//  FirewallLogReader
//
//  mainwindow.cpp
//
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flrfirewalllogmodel.h"

#include <QFileDialog>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   FirewallLogModel = new flrFirewallLogModel(this);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------------------------------------
//
//  File->Exit
//
void MainWindow::on_actionExit_triggered()
{
   exit(0);
}

//---------------------------------------------------------------------------------------
//
//  Firewall->Load logfile
//
void MainWindow::on_actionLoad_logfile_triggered()
{
    strFirewallLogFileName = QFileDialog::getOpenFileName(this,tr("Open Filewall logfile"));
    FirewallLogModel->flrLoadLogFileFirewall(&strFirewallLogFileName);

}
