#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QVector>
#include <QVariant>
#include <QPair>
#include <QStack>

// модель игры
class BoardModel
{
    static constexpr int _GAME_SHAPE = 4;
public:
    static constexpr int GAME_SIZE = _GAME_SHAPE * _GAME_SHAPE;

    BoardModel();

    // is_rnd - создать случайную расстановку или нет
    // complexity - сложность генерируемой расстановки
    BoardModel(bool is_rnd, int complexity);

    // проверить решена ли задача
    // если да то вернуть кол-во перестановок
    QPair<bool, QVariant> is_solved() const noexcept;

    // получить поле
    const QVector<int>& get_board() const noexcept;

    // вернуть к начальной расстановке
    void set_start_board();

    // совершить перестановку
    // если перестановка совершена вернуть
    // индекс пустой клетки, которая была переставлена
    // idx - индекс переставляемого элемента
    QPair<bool, QVariant> move(int idx);

    // вернуться на шаг назад
    // если успешно, то вернуть индексы элементов,
    // которые поменялись местами
    QPair<bool, QPair<QVariant, QVariant>> back_move();

private:
    enum class DIRECTION {
        UP = 1,
        DOWN,
        LEFT,
        RIGHT
    };

    // коэффицент сложности
    // количество перестановок при генерации = complexity * _complexity_coef
    static constexpr int _COMPLEXITY_COEF = 30;

    // пустой элемент
    static constexpr int _EMPTY_ELEMENT = 0;

    // проверить возможна ли перестановка в этом направлении
    static bool _check_direction(const int nul_idx, const DIRECTION direction);

    // проверить являются ли элементы по данным индексам соседями в данном направлении
    static bool _check_is_neighbour(const int lhs, const int rhs, const DIRECTION direction);

    // сделать перестановку если возможно
    static bool _make_move(QVector<int>& board, int& nul_idx, const DIRECTION direction);

    // получить решённую перестановку
    static QVector<int> _get_solved_board();

    // получить случайное направление
    static DIRECTION _gen_direction();

    // сгенерировать расстановку
    // complexity - сложность генерируемой расстановки
    static QPair<QVector<int>, int> _gen_board(int complexity);

    // проверить решена ли расстановка
    // board - расстановка для проверки
    static bool _check_solved(const QVector<int>& board);

    QVector<int>              _board;             // расстановка
    int                       _nul_index;         // индекс пустого элемента
    bool                      _is_solved;         // решена ли расстановка

    QVector<int>              _start_board;       // начальная расстановка
    int                       _start_nul_index;   // начальный индекс пустого элемента
    bool                      _start_is_solved;   // решена ли начальная расстановка

    int                       _num_shifts;        // кол-во совершённых перестановок
    QStack<QPair<int, int>>   _states;            // история перестановок
};

#endif // BOARDMODEL_H
