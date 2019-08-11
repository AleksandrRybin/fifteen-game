#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile style(":/style/style.qss");
    style.open(QFile::ReadOnly);

    MainWindow w;
    w.setStyleSheet(style.readAll());
    w.show();

    style.close();
    return a.exec();
}
