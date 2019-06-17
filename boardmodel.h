#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QVector>
#include <QVariant>
#include <QPair>
#include <QStack>

// модель игры
class BoardModel
{
public:
    BoardModel();

    // is_rnd - создать случайную расстановку или нет
    // complexity - сложность генерируемой расстановки
    BoardModel(bool is_rnd, quint16 complexity);

    // проверить решена ли задача
    // если да то вернуть кол-во перестановок
    QPair<bool, QVariant> is_solved() const;

    // получить поле
    const QVector<quint8>& get_board() const;

    // вернуть к начальной расстановке
    void set_start_board();

    // совершить перестановку
    // если перестановка совершена вернуть
    // индекс пустой клетки, которая была переставлена
    // idx - индекс переставляемого элемента
    QPair<bool, QVariant> move(quint8 idx);

    // вернуться на шаг назад
    // если успешно, то вернуть индексы элементов,
    // которые поменялись местами
    QPair<bool, QPair<QVariant, QVariant>> back_move();

private:

    // сгенерировать расстановку
    // complexity - сложность генерируемой расстановки
    static QPair<QVector<quint8>, quint8> _gen_board(quint16 complexity);

    // коэффицент сложности
    // количество перестановок при генерации = complexity * _complexity_coef
    static quint8 _complexity_coef;

    // проверить решена ли расстановка
    // board - расстановка для проверки
    static bool _check_solved(const QVector<quint8>& board);

    QVector<quint8> _board;                // расстановка
    QVector<quint8> _start_board;          // начальная расстановка
    QStack<QPair<quint8, quint8>> _states; // история перестановок
    quint64 _num_shifts;                   // кол-во совершённых перестановок
    quint8 _nul_index;                     // индекс пустого элемента
    bool _is_solved;                       // решена ли расстановка
};

#endif // BOARDMODEL_H
