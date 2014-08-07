#ifndef CIMPORTEXPORT_H
#define CIMPORTEXPORT_H

#include <fstream>
#include <QByteArray>
#include <QDataStream>
#include <QFile>
#include <QList>

#include "cregleparsage.h"

class CImportExport
{
public:
    CImportExport();
    void OuvrirBinaire(QString aPath);
    QList<CRegleParsage *> *ParserBinaire(QList<CRegleParsage *> *aRegles);

private:
    QFile *mBinaire;
    unsigned char *mData;
    void ParserInt(CRegleParsage *aRegle);
    void ParserBloc(CRegleParsage *aRegle);
};

#endif // CIMPORTEXPORT_H
