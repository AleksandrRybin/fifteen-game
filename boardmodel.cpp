#include <QRandomGenerator>

#include "boardmodel.h"

BoardModel::BoardModel()
    : _board(_get_solved_board()),
      _nul_index(GAME_SIZE - 1),
      _is_solved(true),
      _start_nul_index(_nul_index),
      _start_is_solved(_is_solved),
      _num_shifts(0),
      _states{} {}

BoardModel::BoardModel(bool is_rnd, int complexity)
    : BoardModel() {
    if (is_rnd) {
        _states.reserve(complexity * _COMPLEXITY_COEF);

        while (_is_solved) {
            const auto rnd_result = _gen_board(complexity * _COMPLEXITY_COEF);
            const auto board      = rnd_result.first;
            const auto nul_index  = rnd_result.second;
            const auto is_solved  = _check_solved(board);

            if (!is_solved) {
                _is_solved   = is_solved;
                _board       = board;
                _start_board = _board;
                _nul_index   = nul_index;
            }
        }
    }
}

QPair<bool, QVariant> BoardModel::is_solved() const noexcept {
    if (_is_solved) {
        return {true, QVariant(_num_shifts)};
    } else {
        return {false, QVariant()};
    }
}

const QVector<int>& BoardModel::get_board() const noexcept {
    return _board;
}

void BoardModel::set_start_board() {
    if (_num_shifts != 0) {
        _board      = _start_board;
        _nul_index  = _start_nul_index;
        _is_solved  = _start_is_solved;
        _num_shifts = 0;
        _states.clear();
    }
}

QPair<bool, QVariant> BoardModel::move(int idx) {
    bool result = false;
    int swap_idx;

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
        _is_solved = _check_solved(_board);
        _num_shifts++;
        _states.push({idx, swap_idx});

        return {true, QVariant(swap_idx)};
    } else {
        return {false, QVariant()};
    }
}

QPair<bool, QPair<QVariant, QVariant> > BoardModel::back_move() {
    if (!_states.empty()) {
        const auto prev = _states.pop();
        qSwap(_board[prev.first], _board[prev.second]);
        _nul_index = prev.second;
        _num_shifts--;
        _is_solved = _check_solved(_board);

        return {true, {QVariant(prev.first), QVariant(prev.second)}};
    } else {
        return {false, {QVariant(), QVariant()}};
    }
}

QPair<QVector<int>, int> BoardModel::_gen_board(int complexity) {
    auto final_state = _get_solved_board();

    int nul_index = GAME_SIZE - 1;

    auto gen = QRandomGenerator::global();

    for (int i = 0; i < complexity; i++) {
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

QVector<int> BoardModel::_get_solved_board() {
    QVector<int> final_state(GAME_SIZE);
    for (int i = 0; i < GAME_SIZE; i++) {
        final_state[i] = i + 1;
    }
    final_state[GAME_SIZE - 1] = _EMPTY_ELEMENT;

    return final_state;
}

bool BoardModel::_check_solved(const QVector<int>& board) {
    int num_invs = 0;

    for (int i = 0; i < GAME_SIZE; i++) {
        if (board[i] != (i + 1) % GAME_SIZE) {
            num_invs++;
        }
    }

    return num_invs == 0;
}
