#include <QString>

#include "fifteenpushbutton.h"
#include "boardmodel.h"

FifteenPushButton::FifteenPushButton(QWidget *parent)
    : QPushButton(parent) {
    setFixedSize(QSize(57, 55));
}

void FifteenPushButton::swap_nums(FifteenPushButton *lhs, FifteenPushButton *rhs) noexcept {
    int tmp_num = lhs->_num;
    lhs->set_num(rhs->_num);
    rhs->set_num(tmp_num);
}

int FifteenPushButton::get_num() const noexcept {
    return _num;
}

void FifteenPushButton::set_num(int num) noexcept {
    _num = num;
    setText(QString::number(_num));
}

int FifteenPushButton::get_idx() const noexcept {
    return _idx;
}

void FifteenPushButton::set_idx(int idx) noexcept {
    _idx = idx;
}

void FifteenPushButton::mousePressEvent(QMouseEvent *e) {
    if (_num != BoardModel::EMPTY_ELEMENT) {
        emit fifteen_btn_clicked(_idx);
    }
}
