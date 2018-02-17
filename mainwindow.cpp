//---------------------------------------------------------------------------------------
//  FirewallLogReader
//
//  mainwindow.cpp
//
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSql>

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//---------------------------------------------------------------------------------------
//
// Open database
//
    QSqlDatabase LogDb = QSqlDatabase::addDatabase("QPSQL");
    LogDb.setDatabaseName("vmdevdb01");
    if (!LogDb.open())
        qDebug() << LogDb.lastError();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
