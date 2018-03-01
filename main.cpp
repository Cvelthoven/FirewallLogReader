#include "mainwindow.h"
#include "flrfirewalllogmodel.h"

#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Sophos log file reader");
    MainWindow w;
    w.show();

    return a.exec();
}
