#include <QString>
#include <QIcon>

#include "fifteenpushbutton.h"

FifteenPushButton::FifteenPushButton(QWidget *parent) : QPushButton(parent)
{
    setFixedSize(QSize(57, 55));
}

void FifteenPushButton::swap_nums(FifteenPushButton *lhs, FifteenPushButton *rhs)
{
    quint8 tmp_num = lhs->_num;

    lhs->set_num(rhs->_num);
    rhs->set_num(tmp_num);
}

quint8 FifteenPushButton::get_num() const
{
    return _num;
}

void FifteenPushButton::set_num(quint8 num)
{
    _num = num;

    QString path = QStringLiteral(":/game/icons/img/%1.jpg").arg(_num);
    QIcon icon(path);

    setIcon(icon);
    setIconSize(QSize(60, 60));
}

quint8 FifteenPushButton::get_idx() const
{
    return _idx;
}

void FifteenPushButton::set_idx(quint8 idx)
{
    _idx = idx;
}

void FifteenPushButton::mousePressEvent(QMouseEvent *e)
{
    if (_num != 0) {
        emit fifteen_btn_clicked(_idx);
    }
}
