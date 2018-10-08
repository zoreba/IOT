#include "dialog.h"
#include "ui_dialog.h"
#include <wiringPi.h>
#include <QDateTime>
#include <QPoint>
#include <QCursor>
#include <QDebug>
#include <QString>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    p.setBrush(QPalette::Button,Qt::yellow); //button의 기본색
    p.setBrush(QPalette::ButtonText, Qt::blue);//button의 Text

    btn[0] = new QPushButton(QString("%1's BUTTON").arg(1), this); //1's button
    btn[0]->setStyleSheet("font-size: 24px;");
    btn[0]->setGeometry(50,50,150,150);
    btn[0]->setPalette(p);

    btn[1] = new QPushButton(QString("%1's BUTTON").arg(2), this); //2's button
    btn[1]->setStyleSheet("font-size: 24px;");
    btn[1]->setGeometry(225,50,150,150);
    btn[1]->setPalette(p);

    btn[2] = new QPushButton(QString("%1's BUTTON").arg(3), this); //3's button
    btn[2]->setStyleSheet("font-size: 24px;");
    btn[2]->setGeometry(400,50,150,150);
    btn[2]->setPalette(p);

    btn[3] = new QPushButton(QString("%1's BUTTON").arg(4), this); //4's button
    btn[3]->setStyleSheet("font-size: 24px;");
    btn[3]->setGeometry(575,50,150,150);
    btn[3]->setPalette(p);

    btn[4] = new QPushButton(QString("BUTTON MOVE"), this); //button moves button
    btn[4]->setStyleSheet("font-size: 17px;");
    btn[4]->setGeometry(30,480,130,50);
    btn[4]->setPalette(p);

    btn[5] = new QPushButton(QString("BUTTON ORDER"), this); //button orders button
    btn[5]->setStyleSheet("font-size: 17px;");
    btn[5]->setGeometry(200,480,130,50);
    btn[5]->setPalette(p);

    btn[6] = new QPushButton(QString("SYSTEM INIT"), this); //system inits button
    btn[6]->setStyleSheet("font-size: 17px;");
    btn[6]->setGeometry(350,480,130,50);
    btn[6]->setPalette(p);


    btn_start();

    connect(btn[6], SIGNAL(pressed()),this,SLOT(btn_click7()));//button Order button
    connect(btn[5], SIGNAL(pressed()),this,SLOT(btn_click6()));//system init button
    connect(btn[4], SIGNAL(pressed()),this,SLOT(btn_click5()));//button Move button

    connect(btn[0], SIGNAL(pressed()),this,SLOT(btn_click1()));  // 1th button swith on/off
    connect(btn[1], SIGNAL(pressed()),this,SLOT(btn_click2()));  // 2th button swith on/off

    connect(btn[2], SIGNAL(pressed()), this,SLOT(btn_click3())); // 3th button swith on/off
    connect(btn[3], SIGNAL(pressed()), this,SLOT(btn_click4())); // 4th button swith on/off
    this->setMouseTracking(true);

    tud = new QTimer(this); // 타이머 생성
    connect(tud, SIGNAL(timeout()), this, SLOT(tupdate())); // 타이머가 타임아웃이 되면 tupdate()를 호출
    tud->start(1000);                                       // Digtal 시계를 작동시키기 위
//    tupdate();

    connect(&timer, SIGNAL(timeout()), this, SLOT(btn_status())); // Button의 색상을 변화시키기 위해
           this->timer.start(1000);				  // btn_status()함수를 초당으로 호
//    btn_click7();

}

void Dialog::mouseMoveEvent(QMouseEvent* event)    //button move를 위해 Mouse Event를 이용한다.
{
    if (chk_move == 0){
        if(button_cnt >= 0 && button_cnt <= 3 && event->buttons() && QEvent::MouseMove){

            btn[button_cnt]->raise();

            rh = btn[button_cnt]->height();
            rw = btn[button_cnt]->width();

            btn[button_cnt]->move(event->x() - rh/2,event->y() - rw/2); //mouse move event of button move

        }
    }
}

void Dialog::btn_click6() //button을 일렬로 정렬시키기 위해서 사용되고 색상을 원래 대로 바꾸는
{
    if (chk_move == 0) {
        p.setBrush(QPalette::Button,Qt::yellow);
        p.setBrush(QPalette::ButtonText, Qt::blue);
        btn[0]->setPalette(p);
        btn[1]->setPalette(p);
        btn[2]->setPalette(p);
        btn[3]->setPalette(p);
        btn[4]->setPalette(p);
        btn[4]->setText("BUTTON MOVE");

        btn[0]->setGeometry(50,50,150,150);
        btn[1]->setGeometry(225,50,150,150);
        btn[2]->setGeometry(400,50,150,150);
        btn[3]->setGeometry(575,50,150,150);
        connect(&timer, SIGNAL(timeout()), this, SLOT(btn_status()));
        this->timer.start(1000);
        chk_move = 1;
    }
}
void Dialog::btn_click7() //system 초기화를 하는
{
    wiringPiSetup();
    pinMode(1, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(1,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);

    connect(&timer, SIGNAL(timeout()), this, SLOT(btn_status()));
      this->timer.start(1000);
    p.setBrush(QPalette::Button,Qt::yellow);
    p.setBrush(QPalette::ButtonText, Qt::blue);
    btn[4]->setPalette(p);
    btn[4]->setText("BUTTON MOVE");
    chk_move = 1;
}
void Dialog::btn_click5() //button을 움직일수 있게 푸른 색으로 바꾸고 바뀐상태에서 다시 원래의 색상으로 변
{
    if (chk_move == 1) {  //chk_move 는 1일때 푸른색으로 바꾸고
        p.setBrush(QPalette::Button,Qt::blue);
        p.setBrush(QPalette::ButtonText, Qt::white);
        btn[0]->setPalette(p);
        btn[1]->setPalette(p);
        btn[2]->setPalette(p);
        btn[3]->setPalette(p);
        btn[4]->setPalette(p);
        btn[4]->setText("BUTTON STOP");
        connect(&timer, SIGNAL(timeout()), this, SLOT(btn_status()));
        this->timer.stop();
        chk_move = 0;
    } else if (chk_move == 0) { //chk_move 는 0일때 원래의 상태로 돌아간다.
        p.setBrush(QPalette::Button,Qt::yellow);
        p.setBrush(QPalette::ButtonText, Qt::blue);
        btn[0]->setPalette(p);
        btn[1]->setPalette(p);
        btn[2]->setPalette(p);
        btn[3]->setPalette(p);
        btn[4]->setPalette(p);
        btn[4]->setText("BUTTON MOVE");
        connect(&timer, SIGNAL(timeout()), this, SLOT(btn_status()));
        this->timer.start(1000);
        chk_move = 1;
    }
}

void Dialog::btn_click1() //1번 button을 눌러설때 on/off 기능
{
    button_cnt = 0;  // define of 0th button
    btn[button_cnt]->raise();
    if(chk_move == 1) {
        chk[0] = digitalRead(1);
        if (chk[0] ==0) {
            digitalWrite(1,HIGH);
        } else if(chk[0] ==1) {
            digitalWrite(1,LOW);
        }

    }

}
void Dialog::btn_click2() //2번 button을 눌러설때 on/off 기능
{
    button_cnt = 1;  // define of 1th button
    btn[button_cnt]->raise();
    if(chk_move == 1) {
        chk[1] = digitalRead(4);
        if (chk[1] ==0) {
            digitalWrite(4,HIGH);
        } else if(chk[1] ==1) {
            digitalWrite(4,LOW);
        }

    }

}
void Dialog::btn_click3()  //3번 button을 눌러설때 on/off 기능
{
    button_cnt = 2;  // define of 0th button
    btn[button_cnt]->raise();
    if(chk_move == 1) {
        chk[2] = digitalRead(5);
        if (chk[2] ==0) {
            digitalWrite(5,HIGH);
        } else if(chk[2] ==1) {
            digitalWrite(5,LOW);
        }

    }

}
void Dialog::btn_click4() //4번 button을 눌러설때 on/off 기능
{
    button_cnt = 3;  // define of 1th button
    btn[button_cnt]->raise();
    if(chk_move == 1) {
        chk[3] = digitalRead(6);
        if (chk[3] ==0) {
            digitalWrite(6,HIGH);
        } else if(chk[3] ==1) {
            digitalWrite(6,LOW);
        }

    }

}
void Dialog::btn_status() //초당으로 button의 상태를 check하면서 화면에 표시하는 기능
{
    wiringPiSetup();
    pinMode(1, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    chk[0] = digitalRead(1);
    chk[1] = digitalRead(4);
    chk[2] = digitalRead(5);
    chk[3] = digitalRead(6);

    if (chk[0] == 0) {
        p.setBrush(QPalette::Button,Qt::red);
        p.setBrush(QPalette::ButtonText, Qt::blue);
        btn[0]->setPalette(p);
    } else if(chk[0] == 1){
        p.setBrush(QPalette::Button,Qt::yellow);
        p.setBrush(QPalette::ButtonText, Qt::blue);
        btn[0]->setPalette(p);
    }

    if (chk[1] == 0) {
        p.setBrush(QPalette::Button,Qt::red);
        p.setBrush(QPalette::ButtonText, Qt::blue);
        btn[1]->setPalette(p);
    } else if (chk[1] == 1) {
        p.setBrush(QPalette::Button,Qt::yellow);
        p.setBrush(QPalette::ButtonText, Qt::blue);
        btn[1]->setPalette(p);
    }

    if (chk[2] == 0) {
        p.setBrush(QPalette::Button,Qt::red);
        p.setBrush(QPalette::ButtonText, Qt::blue);
        btn[2]->setPalette(p);
    } else if (chk[2] == 1) {
        p.setBrush(QPalette::Button,Qt::yellow);
        p.setBrush(QPalette::ButtonText, Qt::blue);
        btn[2]->setPalette(p);
    }

    if (chk[3] == 0) {
        p.setBrush(QPalette::Button,Qt::red);
        p.setBrush(QPalette::ButtonText, Qt::blue);
        btn[3]->setPalette(p);
    } else if (chk[3] == 1) {
        p.setBrush(QPalette::Button,Qt::yellow);
        p.setBrush(QPalette::ButtonText, Qt::blue);
        btn[3]->setPalette(p);
    }

}


void Dialog::btn_start() //button의 기능을 초기상태에서 시작하는 기능
{
    wiringPiSetup();
    pinMode(1, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);

    digitalWrite(1, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
}
void Dialog::tupdate()  //시간을 디지털 시계에 표시하기 위해
{
    qd1 = QDate::currentDate();
    qt1 = QTime::currentTime();
    qd2 = qd1.toString();
    qt2 = qt1.toString();

    ui->dateEdit->setDate(qd1);
    ui->timeEdit->setTime(qt1);
}
Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    close();
}
