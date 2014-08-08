#ifndef CIMPORTEXPORT_H
#define CIMPORTEXPORT_H

#include <fstream>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QList>
#include <QSpinBox>
#include <QWidget>

#include "cregleparsage.h"
#include "cchampbinaire.h"

class CImportExport
{
public:
    CImportExport(QWidget *parent);
    ~CImportExport();

    void OuvrirBinaire(QString aPath);
    QList<CChampBinaire *> *ParserBinaire(QList<CRegleParsage *> *aRegles);
    CChampBinaire *ParserInt(CRegleParsage *aRegle);
    QList<CChampBinaire *> * ParserBloc(QList<CRegleParsage *> *aRegle);

private:
    QFile *mBinaire;
//    unsigned char *mData;
    QByteArray mData;
    int mOffset;
    QWidget *mParent;

};

#endif // CIMPORTEXPORT_H
