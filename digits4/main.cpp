#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Быки и коровы");
    w.setMinimumHeight(548);
    w.setMaximumHeight(548);
    w.setMinimumWidth(520);
    w.setMaximumWidth(520);
    w.show();
    return a.exec();
}
