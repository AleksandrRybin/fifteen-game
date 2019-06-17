#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>

#include "boardmodel.h"
#include "fifteenpushbutton.h"

class BoardView : public QWidget
{
    Q_OBJECT
public:
    explicit BoardView(QWidget *parent = nullptr);
    ~BoardView();

    void set_new_model(bool is_rnd, size_t complexity);
    void set_start_board();
    void back_move();

signals:

public slots:

private:
    void check_game_end();

    QGridLayout* _grid;
    QVector<FifteenPushButton*> _buttons;
    BoardModel* _model;

private slots:
    void move(uint8_t num, uint8_t idx);
};

#endif // BOARDVIEW_H
