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
    BoardModel(bool is_rnd, quint16 complexity);

    QPair<bool, QVariant> is_solved() const;
    const QVector<quint8>& get_board() const;

    void set_start_board();

    QPair<bool, QVariant> move(quint8 idx);
    QPair<bool, QPair<QVariant, QVariant>> back_move();

private:
    static QPair<QVector<quint8>, quint8> _gen_board(quint16 complexity);
    static std::random_device _rd;
    static quint8 _complexity_coef;

    static bool _check_solved(const QVector<quint8>& board);

    QVector<quint8> _board;
    QVector<quint8> _start_board;
    QStack<QPair<quint8, quint8>> _states;
    quint64 _num_shifts;
    quint8 _nul_index;
    bool _is_solved;
};

#endif // BOARDMODEL_H
