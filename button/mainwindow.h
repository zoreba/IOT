#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFocusFrame>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QPushButton *btn[4];
    int chk[3] = {0,0,0};

private:
    Ui::MainWindow *ui;
    QTimer timer;
    QPalette p=palette();
    void btn_start();

private slots:
    void btn_click1();
    void btn_click2();
    void btn_status();
};

#endif // MAINWINDOW_H
