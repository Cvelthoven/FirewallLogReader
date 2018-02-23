//---------------------------------------------------------------------------------------
//  FirewallLogReader
//
//  mainwindow.cpp
//
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flrfirewalllogmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    flrFirewallLogModel FirewallData;

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
