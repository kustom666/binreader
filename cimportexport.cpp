#include "cimportexport.h"

CImportExport::CImportExport()
{
}

void CImportExport::OuvrirBinaire(QString aPath)
{/*
    mBinaire = new QFile(aPath);
    mBinaire->open(QIODevice::ReadWrite);*/

    std::ifstream monFichier;
    monFichier.open(aPath.toStdString().c_str(), ios::in |ios::binary | ios::ate);
    if(monFichier.is_open())
    {
        std::streampos size = monFichier.tellg();
        data = new char [size];
        monFichier.seekg(0, ios::beg);
        monFichier.read(data, size);
        monFichier.close();
    }
}

QList<CRegleParsage *> *CImportExport::ParserBinaire(QList<CRegleParsage *> *aRegles)
{
    for(int i=0; i < aRegles->size(); ++i)
    {
        CRegleParsage *buffR = aRegles->at(i);
        if(buffR->getMType() == "bloc")
        {
            ParserBloc(buffR->getMEnfants());
        }
        else if(buffR->getMType()== "int")
        {

        }
    }
}

//void CImportExport::RecupererValeur()

void CImportExport::ParserInt(CRegleParsage *aRegle)
{
    int valeur;
    for(int i=0; i < aRegle->getMTaille(); ++i)
    {
        valeur =
    }
    std::cout <<
}

void CImportExport::ParserBloc(CRegleParsage *aRegle)
{

}
