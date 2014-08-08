#ifndef CPARSEURXML_H
#define CPARSEURXML_H

#include <QDebug>
#include <QFile>
#include <QList>
#include <QXmlStreamReader>

#include "cregleparsage.h"

class CParseurXml
{
public:
    explicit CParseurXml();
    ~CParseurXml();

    void OuvrirFichier(QString aPath);

    QList<CRegleParsage *> *ParserXml();
    void LireBloc(QList<CRegleParsage *> *aRegles);
    void LireElement(QList<CRegleParsage *> *aRegles);

private:
    QXmlStreamReader mReader;
    QFile *mXml;
};

#endif // CPARSEURXML_H
