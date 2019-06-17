#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "boardview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_new_game_btn_clicked();

    void on_start_again_btn_clicked();

    void on_back_move_btn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
