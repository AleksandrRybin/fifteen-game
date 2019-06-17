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

    uint8_t get_num() const;
    void set_num(uint8_t num);

    uint8_t get_idx() const;
    void set_idx(uint8_t idx);

signals:
    void fifteen_btn_clicked(uint8_t num, uint8_t idx);

private:
    uint8_t _num;
    uint8_t _idx;

    virtual void mousePressEvent(QMouseEvent *e) override;
};

#endif // FIFTEENPUSHBUTTON_H
