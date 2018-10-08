#include "dialog.h"
#include <QApplication>
#include <QStyle>
#include <QStyleOptionTitleBar>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString style =" dlg::title {" " height: 0px;" " font-weight: bold;" " color: #000000;" " background: #ffffff;" " }";

    a.setStyleSheet(style);
    Dialog dlg(0);
    dlg.exec();
}
