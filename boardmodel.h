#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QVector>
#include <QVariant>
#include <QPair>

class BoardModel
{
public:
    BoardModel();
    BoardModel(bool is_rnd, size_t complexity);

    bool is_solved() const;
    const QVector<uint8_t>& get_board() const;

    QPair<bool, QVariant> move(uint8_t idx);

private:
    static QPair<QVector<uint8_t>, uint8_t> gen_board(size_t complexity);
    static bool check_solved(const QVector<uint8_t>& board);

    QVector<uint8_t> _board;
    uint8_t _nul_index;
    bool _is_solved;
};

#endif // BOARDMODEL_H
