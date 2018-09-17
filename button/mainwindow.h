#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFocusFrame>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QPushButton *btn[3];
    int chk = 0;

private:
    Ui::MainWindow *ui;

private slots:
    void btn_click();
    void btn_pressed();
    void btn_released();
};

#endif // MAINWINDOW_H
