#include "mainfen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainFen w;
    w.show();

    return a.exec();
}
