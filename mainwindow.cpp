#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->is_rnd_chckbx->setCheckState(Qt::Checked);

    ui->complexity_num_sldr->setRange(1, 100);
    ui->complexity_num_sldr->setValue(15);
    ui->complexity_num_sldr->setSingleStep(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_is_rnd_chckbx_stateChanged(int new_state)
{
    if (new_state == Qt::Checked) {
        ui->complexity_num_sldr->setEnabled(true);
        ui->complexity_num_lbl->setNum(ui->complexity_num_sldr->value());
    }
    else if (new_state == Qt::Unchecked) {
        ui->complexity_num_sldr->setEnabled(false);
        ui->complexity_num_lbl->clear();
    }
}
