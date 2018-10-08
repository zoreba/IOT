#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QFocusFrame>
#include <QTimer>
#include <QMouseEvent>
#include <QLabel>
#include <QLCDNumber>
#include <QDate>
#include <QDateEdit>
#include <QTime>
#include <QTimeEdit>
#include <QLabel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    QPushButton *btn[7];
    QLCDNumber *lcd[2];
    QDate qd1;
    QString qd2;
    QTime qt1;
    QString qt2;
//    QDateEdit dateEdit;
//    QTimeEdit timeEdit;

//    QTimeEdit qt_1;

    int chk[4] = {0,0,0,0}; //button number init 1 is chois o is no chois

    int chk_move = 1; //buttons move mode 1 is move 0 is not move
    int chk_init = 0; //button init mode 0 is not init 1 is init
    int button_cnt = 4; //button key of btm[button_cnt] 0 ~ 3
    int rh = 0; // Height of button
    int rw = 0; // width of button

//    void lcd_time(QString qd_1, QString qt_1);

private:
    Ui::Dialog *ui;
    QTimer timer, *tud;
    QPalette p=palette();
//    QLabel *qd_l, *qt_l;
    void btn_start(); //button init
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void btn_click1();
    void btn_click2();
    void btn_click3();
    void btn_click4();
    void btn_click5();
    void btn_click6();
    void btn_click7();
    void btn_status();
    void tupdate();
    void on_pushButton_clicked();
};

#endif // DIALOG_H
