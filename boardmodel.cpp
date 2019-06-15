#include "boardmodel.h"

#include <random>

BoardModel::BoardModel()
{
    _board = {1,  2,  3,  4,
              5,  6,  7,  8,
              9,  10, 11, 12,
              13, 14, 15, 0};

    _nul_index = 15;
    _is_solved = true;
}

BoardModel::BoardModel(bool is_rnd, size_t complexity)
    : BoardModel()
{
    if (is_rnd) {
        while (_is_solved) {
            auto rnd_result = BoardModel::gen_board(complexity);
            if (BoardModel::check_solved(rnd_result.first)) {
                _is_solved = false;
                _board = rnd_result.first;
                _nul_index = rnd_result.second;
            }
        }
    }
}

const QVector<uint8_t> &BoardModel::get_board() const
{
    return _board;
}

QPair<bool, QVariant> BoardModel::move(uint8_t idx)
{
    bool result = false;

    if (_nul_index > 3) {
        // Возможно движение вверх

        if (_nul_index - 4 == idx) {
            qSwap(_board[_nul_index], _board[_nul_index - 4]);
            _nul_index -= 4;

            result = true;
        }
    }

    if (_nul_index < 12) {
        // Возможно движение вниз

        if (_nul_index + 4 == idx) {
            qSwap(_board[_nul_index], _board[_nul_index + 4]);
            _nul_index += 4;

            result = true;
        }
    }

    if (_nul_index % 4) {
        // Возможно движение влево

        if (_nul_index - 1 == idx) {
            qSwap(_board[_nul_index], _board[_nul_index - 1]);
            _nul_index--;

            result = true;
        }
    }

    if (_nul_index % 4 != 3) {
        // Возможно движение вправо

        if (_nul_index + 1 == idx) {
            qSwap(_board[_nul_index], _board[_nul_index + 1]);
            _nul_index++;

            result = true;
        }
    }

    if (result) {
        _is_solved = BoardModel::check_solved(_board);

        return {true, QVariant(_nul_index)};
    }
    else {
        return {false, QVariant()};
    }
}

QPair<QVector<uint8_t>, uint8_t> BoardModel::gen_board(size_t complexity)
{
    QVector<uint8_t> final_state = {1,  2,  3,  4,
                                    5,  6,  7,  8,
                                    9,  10, 11, 12,
                                    13, 14, 15, 0};
    uint8_t nul_index = 15;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dist(1, 4);

    for (size_t i = 0; i < complexity; i++) {
        switch (dist(gen)) {
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

bool BoardModel::check_solved(const QVector<uint8_t> &board)
{
    uint8_t num_invs = 0;
    for (size_t i = 0; i < 16; i++) {
        if (board[i] != (i + 1) % 16) {
            num_invs++;
        }
    }

    return num_invs == 0;
}
