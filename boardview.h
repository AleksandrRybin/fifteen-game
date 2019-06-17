#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>

#include "boardmodel.h"
#include "fifteenpushbutton.h"

// представление игры
class BoardView : public QWidget
{
    Q_OBJECT
public:
    explicit BoardView(QWidget *parent = nullptr);
    ~BoardView();

    // установить новую расстановку
    // is_rnd - создать случайную расстановку или нет
    // complexity - сложность генерируемой расстановки
    void set_new_model(bool is_rnd, quint16 complexity);

    // установить начальную расстановку
    void set_start_board();

    // совершить шаг назад
    void back_move();

signals:

public slots:

private:

    // проверить решена ли расстановка
    // если да вывести результат
    void check_game_end();

    QGridLayout* _grid;                   // layout для кнопок - элементов игры
    QVector<FifteenPushButton*> _buttons; // кнопки - элементы игры
    BoardModel* _model;                   // игровая модель

private slots:

    // нажата игровая кнопка
    // если возможно совершить перестановку
    // idx - индекс нажатой кнопки
    void move(quint8 idx);
};

#endif // BOARDVIEW_H
