#include <QString>
#include <QIcon>
#include <QMessageBox>
#include <QFont>

#include "boardview.h"

BoardView::BoardView(QWidget *parent)
    : QWidget(parent),
      _grid(nullptr),
      _model(nullptr) {

        _buttons.resize(BoardModel::GAME_SIZE);
        for (int i = 0; i < BoardModel::GAME_SIZE; i++) {
            _buttons[i] = nullptr;
    }
}

BoardView::~BoardView() {
    delete _model;
}

void BoardView::set_new_model(bool is_rnd, int complexity) {
    if (_model != nullptr) {
        delete _model;
    }

    _model = new BoardModel(is_rnd, complexity);

    if (_grid == nullptr) {
        _grid = new QGridLayout(this);

        for (int i = 0; i < BoardModel::GAME_SIZE; i++) {
            auto new_btn = new FifteenPushButton(this);
            new_btn->set_idx(i);
            _grid->addWidget(new_btn, i / BoardModel::GAME_SHAPE, i % BoardModel::GAME_SHAPE);
            connect(new_btn, &FifteenPushButton::fifteen_btn_clicked,
                    this, &BoardView::move);
            _buttons[i] = new_btn;
        }

        setLayout(_grid);
    }

    const auto board = _model->get_board();

    for (int i = 0; i < BoardModel::GAME_SIZE; i++) {
        _buttons[i]->set_num(board[i]);
    }
}

void BoardView::set_start_board() {
    _model->set_start_board();
    const auto board = _model->get_board();

    for (int i = 0; i < BoardModel::GAME_SIZE; i++) {
        _buttons[i]->set_num(board[i]);
    }
}

void BoardView::move(int idx) {
    const auto result = _model->move(idx);
    const auto is_moved = result.first;

    if (is_moved) {
        int nul_idx = result.second.toInt();
        FifteenPushButton::swap_nums(_buttons[idx], _buttons[nul_idx]);

        check_game_end();
    }
}

void BoardView::back_move() {
    const auto result = _model->back_move();
    const auto is_moved = result.first;

    if (is_moved) {
        const int lhs_idx = result.second.first.toInt();
        const int rhs_idx = result.second.second.toInt();
        auto lhs = _buttons[lhs_idx];
        auto rhs = _buttons[rhs_idx];

        FifteenPushButton::swap_nums(lhs, rhs);

        check_game_end();
    }
}

void BoardView::check_game_end() {
    const auto is_solved_result = _model->is_solved();
    const auto is_solved = is_solved_result.first;

    if (is_solved) {
        int num_shifts = is_solved_result.second.toInt();
        const auto msg = tr("Задача решена." "\n" "Использовано %1 перестановок.").arg(num_shifts);
        QMessageBox::information(this, tr("Игра закончена"), msg);
    }
}
