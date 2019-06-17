#include <QString>
#include <QIcon>
#include <QMessageBox>
#include <QFont>

#include "boardview.h"

BoardView::BoardView(QWidget *parent) : QWidget(parent)
{
    _model = nullptr;
    _grid = nullptr;

    _buttons.resize(16);
    for (quint8 i = 0; i < 16; i++) {
        _buttons[i] = nullptr;
    }
}

BoardView::~BoardView()
{
    delete _model;
}

void BoardView::set_new_model(bool is_rnd, quint16 complexity)
{
    if (_model != nullptr) {
        delete _model;
    }

    _model = new BoardModel(is_rnd, complexity);

    if (_grid == nullptr) {
        _grid = new QGridLayout(this);
        setLayout(_grid);

        for (quint8 i = 0; i < 16; i++) {
            _buttons[i] = new FifteenPushButton(this);
            _grid->addWidget(_buttons[i], i / 4, i % 4);
            connect(_buttons[i], &FifteenPushButton::fifteen_btn_clicked,
                    this, &BoardView::move);
        }
    }

    auto board = _model->get_board();

    for (quint8 i = 0; i < 16; i++) {
        _buttons[i]->set_idx(i);
        _buttons[i]->set_num(board[i]);
    }
}

void BoardView::set_start_board()
{
    _model->set_start_board();
    auto board = _model->get_board();

    for (quint8 i = 0; i < 16; i++) {
        _buttons[i]->set_num(board[i]);
    }
}

void BoardView::back_move()
{
    auto result = _model->back_move();
    if (result.first) {
        auto lhs = _buttons[result.second.first.toUInt()];
        auto rhs = _buttons[result.second.second.toUInt()];
        FifteenPushButton::swap(lhs, rhs);

        check_game_end();
    }
}

void BoardView::check_game_end()
{
    auto is_solved = _model->is_solved();
    if (is_solved.first) {
        quint64 num_shifts = is_solved.second.toUInt();
        auto msg = QStringLiteral("\n Количество совершённых перестановок: %1").arg(num_shifts);
        QMessageBox::information(this, QString("Игра закончена"), msg);
    }
}

void BoardView::move(quint8 idx)
{
    auto result = _model->move(idx);
    if (result.first) {
        quint8 nul_idx = result.second.toUInt();
        FifteenPushButton::swap(_buttons[idx], _buttons[nul_idx]);

        check_game_end();
    }
}
