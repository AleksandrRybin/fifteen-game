#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->board_view, &BoardView::moved, this, &MainWindow::on_moved);

    ui->complexity_num_sldr->setRange(1, 5);
    ui->complexity_num_sldr->setValue(1);
    ui->complexity_num_sldr->setSingleStep(1);

    check_back_move_btns(true, false);

    ui->board_view->set_new_model(true, ui->complexity_num_sldr->value());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_new_game_btn_clicked() {
    ui->board_view->set_new_model(true, ui->complexity_num_sldr->value());
    check_back_move_btns(true, false);
}

void MainWindow::on_start_again_btn_clicked() {
    ui->board_view->set_start_board();
    check_back_move_btns();
}

void MainWindow::on_back_move_btn_clicked() {
    ui->board_view->back_move();
    check_back_move_btns();
}

void MainWindow::on_moved() {
    check_back_move_btns();
}

void MainWindow::check_back_move_btns(const bool manual_mode, const bool value) {
    if (manual_mode) {
        ui->start_again_btn->setEnabled(value);
        ui->back_move_btn->setEnabled(value);
    } else {
        const bool is_back_move_buttons_enabled = ui->board_view->check_back_moves_available();
        ui->start_again_btn->setEnabled(is_back_move_buttons_enabled);
        ui->back_move_btn->setEnabled(is_back_move_buttons_enabled);
    }
}
