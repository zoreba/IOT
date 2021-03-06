#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <wiringPi.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    int ypos=2;
    for(int i= 0; i < 4 ; i++)
    {
        p.setBrush(QPalette::Button,Qt::yellow);
        p.setBrush(QPalette::ButtonText, Qt::blue);
        btn[i] = new QPushButton(QString("%1 Button").arg(i), this);
        btn[i]->setGeometry(ypos,220,260,220);
        ypos +=260;
        btn[i]->setPalette(p);
    }

    btn_start();

    connect(btn[0], SIGNAL(pressed()),this,SLOT(btn_click1()));

    connect(btn[1], SIGNAL(pressed()),this,SLOT(btn_click2()));

    connect(&timer, SIGNAL(timeout()), this, SLOT(btn_status()));
      this->timer.start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::btn_click1()
{
    chk[0] = digitalRead(1);
    if (chk[0] ==0) {
        wiringPiSetup();
        pinMode(1, OUTPUT);
        digitalWrite(1,HIGH);

    } else if(chk[0] ==1) {
        wiringPiSetup();
        pinMode(1, OUTPUT);
        digitalWrite(1,LOW);

    }
}
void MainWindow::btn_click2()
{
    chk[1] = digitalRead(4);
    if (chk[1] ==0) {
        wiringPiSetup();
        pinMode(4, OUTPUT);
        digitalWrite(4,HIGH);

    } else if(chk[1] ==1) {
        wiringPiSetup();
        pinMode(4, OUTPUT);
        digitalWrite(4,LOW);

    }

}
void MainWindow::btn_status()
{

    chk[0] = digitalRead(1);
    chk[1] = digitalRead(4);

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

}

void MainWindow::btn_start()
{
    wiringPiSetup();
 //   digitalWrite(1, LOW);
 //   digitalWrite(4, LOW);

    digitalWrite(1, HIGH);
    digitalWrite(4, HIGH);

}
