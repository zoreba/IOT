#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <wiringPi.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int ypos=30;
    for(int i= 0; i < 3 ; i++)
    {
        QPalette p=palette();
        p.setBrush(QPalette::Button,Qt::yellow);
        p.setBrush(QPalette::ButtonText, Qt::blue);
        btn[i] = new QPushButton(QString("%1 Button").arg(i), this);
        btn[i]->setGeometry(ypos,50,100,50);
        ypos +=100;
        btn[i]->setPalette(p);
    }

//    QPushButton *b=new QPushButton;


    connect(btn[0], SIGNAL(clicked()),this,SLOT(btn_click()));
    connect(btn[0], SIGNAL(pressed()),this,SLOT(btn_pressed()));
    connect(btn[0], SIGNAL(released()),this,SLOT(btn_released()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::btn_click()
{
    qDebug("Button Click");
}
void MainWindow::btn_pressed()
{
    if (chk ==0) {
        wiringPiSetup();
        pinMode(1, OUTPUT);
        digitalWrite(1,HIGH);
        chk = digitalRead(1);
        if (chk == 1) {
            QPalette p=palette();
            p.setBrush(QPalette::Button,Qt::red);
            p.setBrush(QPalette::ButtonText, Qt::blue);
            btn[0]->setPalette(p);
        }

//        chk = 1;
    } else if(chk ==1) {
        wiringPiSetup();
        pinMode(1, OUTPUT);
        digitalWrite(1,LOW);
        chk = digitalRead(1);
        if (chk == 0){
            QPalette p=palette();
            p.setBrush(QPalette::Button,Qt::yellow);
            p.setBrush(QPalette::ButtonText, Qt::blue);
            btn[0]->setPalette(p);
        }

//        chk = 0;
    }
    qDebug("Button Pressed");
}
void MainWindow::btn_released()
{
    qDebug("Button Released");
}
