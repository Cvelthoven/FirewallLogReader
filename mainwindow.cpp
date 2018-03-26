//---------------------------------------------------------------------------------------
//  FirewallLogReader
//
//  mainwindow.cpp
//
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flrfirewalllogmodel.h"
#include "flrfirewalllogview.h"

#include <QFileDialog>
#include <QString>
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
//  createModelAndView
//
void MainWindow::createModelAndView()
{

}

//---------------------------------------------------------------------------------------
//
//  Menu items
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
    if (strFirewallLogFileName.length() != 0)
        FirewallLogModel->flrLoadLogFileFirewall(&strFirewallLogFileName);

}

void MainWindow::on_actionConnect_DB_triggered()
{
    //-----------------------------------------------------------------------------------
    //
    //  Get and set settings
    //
    strDatabaseName = "vmdevdb01";
    strHost = "localhost";
    strUserId = "vmlindev01admin";
    strPassword = "#NS01fr#LDrz76#";
    FirewallLogModel->flrConnectDB(&strDatabaseName,&strHost,&strUserId,&strPassword);
}
