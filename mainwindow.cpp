//---------------------------------------------------------------------------------------
//  FirewallLogReader
//
//  mainwindow.cpp
//
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSql>
#include <QStringList>

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//---------------------------------------------------------------------------------------
//
// Variables
//
    QSqlDatabase LogDb;

    QString dataBaseName ="vmdevdb01",
            host = "localhost",//    localhost,vmlindev01
            user = "vmlindev01admin",
            password = "#NS01fr#LDrz76#";

    QStringList DbDrivers,
            dbTables,
            connectioNames;

    //-----------------------------------------------------------------------------------
    //
    // Find available sql drivers
    //
    DbDrivers = QSqlDatabase::drivers();
    if (!DbDrivers.contains("QPSQL"))
        exit(0);

    //-----------------------------------------------------------------------------------
    //
    // Connect to database
    //
    LogDb = QSqlDatabase::addDatabase("QPSQL");
    LogDb.setHostName(host);
    LogDb.setDatabaseName(dataBaseName);
    LogDb.setPort(-1);//    5432
    if (LogDb.open(user,password))
    {
            QSqlQuery query("", LogDb);
            query.exec("SELECT * FROM test");
            qDebug() << LogDb.lastError();
            while (query.next())
            {
                QString field01 = query.value(0).toString();
                QString field02 = query.value(1).toString();
                qDebug() << field01 << " " << field02;
            }

    }
    else
        qDebug() << LogDb.lastError();



    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
