#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_is_rnd_chckbx_stateChanged(int new_state);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
