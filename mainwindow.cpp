//---------------------------------------------------------------------------------------
//  FirewallLogReader
//
//  mainwindow.cpp
//
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flrfirewalllogmodel.h"


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

