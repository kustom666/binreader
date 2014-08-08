#include "cparseurxml.h"

CParseurXml::CParseurXml():
             mReader()
{
}

CParseurXml::~CParseurXml()
{
    if(mXml->isOpen())
    {
        mXml->close();
    }
    delete mXml;
}

void CParseurXml::OuvrirFichier(QString aPath)
{
    mXml = new QFile(aPath);
    mXml->open(QIODevice::ReadOnly | QIODevice::Text);
    mReader.setDevice(mXml);
}

QList<CRegleParsage *> *CParseurXml::ParserXml()
{
    QList<CRegleParsage *> *buffOut = new QList<CRegleParsage *>();
    while(mReader.readNextStartElement())
    {
        QString balise = mReader.name().toString();
        if(balise == "bloc")
        {
            LireBloc(buffOut);
        }
        else if(balise != "binaire")
        {
            LireElement(buffOut);
        }
    }
    return buffOut;
}

void CParseurXml::LireBloc(QList<CRegleParsage *> *aRegles)
{
    QString balise = mReader.name().toString();
    QString nom = mReader.attributes().value("nom").toString();
    QString taille = mReader.attributes().value("taille").toString();
    QString reference = mReader.attributes().value("nb").toString();

    CRegleParsage *buffRegle = new CRegleParsage(nom, balise, taille.toInt());
    buffRegle->setMRefNombre(reference);

    while(mReader.readNextStartElement())
    {
        balise = mReader.name().toString();
        if(balise == "bloc")
        {
            LireBloc(buffRegle->getMEnfants());
        }
        else
        {
            LireElement(buffRegle->getMEnfants());
        }
    }
    aRegles->push_back(buffRegle);
}

void CParseurXml::LireElement(QList<CRegleParsage *> *aRegles)
{
    QString balise = mReader.name().toString();
    QString nom = mReader.attributes().value("nom").toString();
    QString taille = mReader.attributes().value("taille").toString();
    QString reference = mReader.attributes().value("nb").toString();

    CRegleParsage *buffRegle = new CRegleParsage(nom, balise, taille.toInt());
    buffRegle->setMRefNombre(reference);

    aRegles->push_back(buffRegle);
    qDebug() << balise;
    mReader.skipCurrentElement();
}

