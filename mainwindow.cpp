#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->complexity_num_sldr->setRange(1, 100);
    ui->complexity_num_sldr->setValue(15);
    ui->complexity_num_sldr->setSingleStep(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}
