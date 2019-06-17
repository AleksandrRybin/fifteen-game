#include <QRandomGenerator>

#include "boardmodel.h"

quint8 BoardModel::_complexity_coef(15);

BoardModel::BoardModel()
{
    _board = {1,  2,  3,  4,
              5,  6,  7,  8,
              9,  10, 11, 12,
              13, 14, 15, 0};

    _start_board = _board;

    _nul_index = 15;
    _is_solved = true;
    _num_shifts = 0;
}

BoardModel::BoardModel(bool is_rnd, quint16 complexity)
    : BoardModel()
{
    if (is_rnd) {
        _states.reserve(complexity * BoardModel::_complexity_coef);

        while (_is_solved) {
            auto rnd_result = BoardModel::_gen_board(complexity * BoardModel::_complexity_coef);

            if (!BoardModel::_check_solved(rnd_result.first)) {
                _is_solved = false;
                _board = rnd_result.first;
                _start_board = _board;
                _nul_index = rnd_result.second;
            }
        }
    }
}

QPair<bool, QVariant> BoardModel::is_solved() const
{
    if (_is_solved) {
        return {true, QVariant(_num_shifts)};
    }
    else {
        return {false, QVariant()};
    }
}

const QVector<quint8> &BoardModel::get_board() const
{
    return _board;
}

void BoardModel::set_start_board()
{
    if (_num_shifts != 0) {
        _board = _start_board;

        for (quint8 i = 0; i < 16; i++) {
            if (_board[i] == 0) {
                _nul_index = i;
                break;
            }
        }

        _is_solved = BoardModel::_check_solved(_board);
        _num_shifts = 0;
        _states.clear();
    }
}

QPair<bool, QVariant> BoardModel::move(quint8 idx)
{
    bool result = false;
    quint8 swap_idx;

    if (_nul_index > 3) {
        // Возможно движение вверх

        if (_nul_index - 4 == idx) {
            qSwap(_board[_nul_index], _board[_nul_index - 4]);
            swap_idx = _nul_index;
            _nul_index -= 4;

            result = true;
        }
    }

    if (_nul_index < 12) {
        // Возможно движение вниз

        if (_nul_index + 4 == idx) {
            qSwap(_board[_nul_index], _board[_nul_index + 4]);
            swap_idx = _nul_index;
            _nul_index += 4;

            result = true;
        }
    }

    if (_nul_index % 4) {
        // Возможно движение влево

        if (_nul_index - 1 == idx) {
            qSwap(_board[_nul_index], _board[_nul_index - 1]);
            swap_idx = _nul_index;
            _nul_index--;

            result = true;
        }
    }

    if (_nul_index % 4 != 3) {
        // Возможно движение вправо

        if (_nul_index + 1 == idx) {
            qSwap(_board[_nul_index], _board[_nul_index + 1]);
            swap_idx = _nul_index;
            _nul_index++;

            result = true;
        }
    }

    if (result) {
        _is_solved = BoardModel::_check_solved(_board);
        _num_shifts++;
        _states.push({idx, swap_idx});

        return {true, QVariant(swap_idx)};
    }
    else {
        return {false, QVariant()};
    }
}

QPair<bool, QPair<QVariant, QVariant> > BoardModel::back_move()
{
    if (!_states.empty()) {
        auto prev = _states.pop();
        qSwap(_board[prev.first], _board[prev.second]);
        _nul_index = prev.second;
        _num_shifts--;
        _is_solved = BoardModel::_check_solved(_board);

        return {true, {QVariant(prev.first), QVariant(prev.second)}};
    }
    else {
        return {false, {QVariant(), QVariant()}};
    }
}

QPair<QVector<quint8>, quint8> BoardModel::_gen_board(quint16 complexity)
{
    QVector<quint8> final_state = {1,  2,  3,  4,
                                    5,  6,  7,  8,
                                    9,  10, 11, 12,
                                    13, 14, 15, 0};
    quint8 nul_index = 15;

    auto gen = QRandomGenerator::global();

    for (quint16 i = 0; i < complexity; i++) {
        switch (gen->bounded(1, 5)) {

        case 1:

            // движение вверх

            if (nul_index > 3) {
                qSwap(final_state[nul_index], final_state[nul_index - 4]);
                nul_index -= 4;
            }

            break;

        case 2:

            // движение вниз

            if (nul_index < 12) {
                qSwap(final_state[nul_index], final_state[nul_index + 4]);
                nul_index += 4;
            }

            break;

        case 3:

            // движение влево

            if (nul_index % 4) {
                qSwap(final_state[nul_index], final_state[nul_index - 1]);
                nul_index--;
            }

            break;

        case 4:

            // движение вправо

            if (nul_index % 4 != 3) {
                qSwap(final_state[nul_index], final_state[nul_index + 1]);
                nul_index++;
            }

            break;

        default:

            break;
        }
    }

    return {final_state, nul_index};
}

bool BoardModel::_check_solved(const QVector<quint8> &board)
{
    quint8 num_invs = 0;

    for (quint8 i = 0; i < 16; i++) {
        if (board[i] != (i + 1) % 16) {
            num_invs++;
        }
    }

    return num_invs == 0;
}
