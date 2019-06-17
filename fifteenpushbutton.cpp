#include <QString>
#include <QIcon>

#include "fifteenpushbutton.h"

FifteenPushButton::FifteenPushButton(QWidget *parent) : QPushButton(parent)
{
    setFixedSize(QSize(55, 55));
}

void FifteenPushButton::swap(FifteenPushButton *lhs, FifteenPushButton *rhs)
{
    uint8_t tmp_num = lhs->_num;

    lhs->set_num(rhs->_num);
    rhs->set_num(tmp_num);
}

uint8_t FifteenPushButton::get_num() const
{
    return _num;
}

void FifteenPushButton::set_num(uint8_t num)
{
    _num = num;

    QString path = QStringLiteral(":/game/icons/img/%1.jpg").arg(_num);
    QIcon icon(path);

    setIcon(icon);
    setIconSize(QSize(60, 60));
}

uint8_t FifteenPushButton::get_idx() const
{
    return _idx;
}

void FifteenPushButton::set_idx(uint8_t idx)
{
    _idx = idx;
}

void FifteenPushButton::mousePressEvent(QMouseEvent *e)
{
    if (_num != 0) {
        emit fifteen_btn_clicked(_num, _idx);
    }
}
