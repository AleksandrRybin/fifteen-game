#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QVector>
#include <QVariant>
#include <QPair>
#include <QStack>

#include <random>

class BoardModel
{
public:
    BoardModel();
    BoardModel(bool is_rnd, size_t complexity);

    QPair<bool, QVariant> is_solved() const;
    const QVector<uint8_t>& get_board() const;

    void set_start_board();

    QPair<bool, QVariant> move(uint8_t idx);
    QPair<bool, QPair<QVariant, QVariant>> back_move();

private:
    static QPair<QVector<uint8_t>, uint8_t> _gen_board(size_t complexity);
    static std::random_device _rd;
    static uint8_t _complexity_coef;

    static bool _check_solved(const QVector<uint8_t>& board);

    QVector<uint8_t> _board;
    QVector<uint8_t> _start_board;
    QStack<QPair<uint8_t, uint8_t>> _states;
    uint64_t _num_shifts;
    uint8_t _nul_index;
    bool _is_solved;
};

#endif // BOARDMODEL_H
