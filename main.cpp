#include "mainfen.h"
#include "cchampbinaire.h"
#include <QList>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QList<CChampBinaire *> >("QList<CChampBinaire *>");
    qRegisterMetaType<QList<CRegleParsage *> >("QList<CRegleParsage *>");
    MainFen w;
    w.show();

    return a.exec();
}
