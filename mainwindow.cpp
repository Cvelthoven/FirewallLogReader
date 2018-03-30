//---------------------------------------------------------------------------------------
//  FirewallLogReader
//
//  mainwindow.cpp
//
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flrfirewalllogmodel.h"
#include "flrfirewalllogview.h"

#include <QGuiApplication>
#include <QFileDialog>
#include <QSettings>
#include <QString>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    FirewallLogModel = new flrFirewallLogModel(this);
    IntializeProgram();
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

//---------------------------------------------------------------------------------------
//
//  Files->Connect database
//
void MainWindow::on_actionConnect_DB_triggered()
{
    //-----------------------------------------------------------------------------------
    //
    //  Get and set settings
    //
    QSettings programDefaults;
    QVariant temp = programDefaults.value("DatabaseName");
    strDatabaseName = temp.toString();
    temp = programDefaults.value("DatabaseHost");
    strHost = temp.toString();
    temp = programDefaults.value("UserId");
    strUserId = temp.toString();
    temp = programDefaults.value("Password");
    strPassword = temp.toString();
    FirewallLogModel->flrConnectDB(&strDatabaseName,&strHost,&strUserId,&strPassword);
}

//---------------------------------------------------------------------------------------
//
//  Intialize program settings
//
void MainWindow::dbConnect()
{
    QSettings programDefaults;
    QVariant temp = programDefaults.value("DatabaseName");
    strDatabaseName = temp.toString();
    temp = programDefaults.value("DatabaseHost");
    strHost = temp.toString();
    temp = programDefaults.value("UserId");
    strUserId = temp.toString();
    temp = programDefaults.value("Password");
    strPassword = temp.toString();
    FirewallLogModel->flrConnectDB(&strDatabaseName,&strHost,&strUserId,&strPassword);

}


//---------------------------------------------------------------------------------------
//
//  Intialize program settings
//
void MainWindow::IntializeProgram()
{
    //-----------------------------------------------------------------------------------
    //
    //  Set application environment definitions
    //
    QCoreApplication::setOrganizationName("CVelthoven");
    QCoreApplication::setOrganizationDomain("CVelthoven.com");
    QCoreApplication::setApplicationName("FirewallLogReader");

    //-----------------------------------------------------------------------------------
    //
    //  Connect configured database with configured settings
    //
    QSettings programDefaults;
    QVariant temp = programDefaults.value("DatabaseName");
    if (temp.isValid())
        dbConnect();
    //-----------------------------------------------------------------------------------
    //
    //  Write application defaults to conf file or registry and connect to default
    //
    else
    {
        setDefaultSettings();
        dbConnect();
    }
}


//---------------------------------------------------------------------------------------
//
//  Set default application settings
//
//  Default linux location: /home/<user>/.config/CVelthoven/FirewallLogReader.conf
//
void MainWindow::setDefaultSettings()
{

    QSettings programDefaults;
    programDefaults.setValue("DatabaseName","vmdevdb01");
    programDefaults.setValue("DatabaseHost","localhost");
    programDefaults.setValue("UserId","vmlindev01admin");
    programDefaults.setValue("Password","#NS01fr#LDrz76#");
    programDefaults.setValue("FireWall/logTableName", "flrfirewalllog");


}
