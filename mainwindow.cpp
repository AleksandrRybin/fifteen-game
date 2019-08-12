#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->complexity_num_sldr->setRange(1, 10);
    ui->complexity_num_sldr->setValue(1);
    ui->complexity_num_sldr->setSingleStep(1);

    ui->board_view->set_new_model(true, ui->complexity_num_sldr->value());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_new_game_btn_clicked() {
    ui->board_view->set_new_model(true, ui->complexity_num_sldr->value());
}

void MainWindow::on_start_again_btn_clicked() {
    ui->board_view->set_start_board();
}

void MainWindow::on_back_move_btn_clicked() {
    ui->board_view->back_move();
}
