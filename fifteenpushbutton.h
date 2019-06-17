#ifndef FIFTEENPUSHBUTTON_H
#define FIFTEENPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

class FifteenPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit FifteenPushButton(QWidget *parent = nullptr);

    static void swap(FifteenPushButton* lhs, FifteenPushButton* rhs);

    quint8 get_num() const;
    void set_num(quint8 num);

    quint8 get_idx() const;
    void set_idx(quint8 idx);

signals:
    void fifteen_btn_clicked(quint8 idx);

private:
    quint8 _num;
    quint8 _idx;

    virtual void mousePressEvent(QMouseEvent *e) override;
};

#endif // FIFTEENPUSHBUTTON_H
