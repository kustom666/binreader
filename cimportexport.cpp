#include "cimportexport.h"

CImportExport::CImportExport(QWidget *parent) :
    mData(),
    mOffset(0)
{
    mParent = parent;
}

CImportExport::~CImportExport()
{
    if(mBinaire->isOpen())
    {
        mBinaire->close();
    }

    delete mBinaire;
}

void CImportExport::OuvrirBinaire(QString aPath)
{
    mBinaire = new QFile(aPath);
    mBinaire->open(QIODevice::ReadWrite);

    mData = mBinaire->readAll();
}

QList<CChampBinaire *> *CImportExport::ParserBinaire(QList<CRegleParsage *> *aRegles)
{
    QList<CChampBinaire *> *parsedBack = new QList<CChampBinaire *>();
    for(int i=0; i < aRegles->size(); ++i)
    {
        CRegleParsage *buffR = aRegles->at(i);
        if(buffR->getMType() == "bloc")
        {
            QString ref = buffR->getMRefNombre();
            int nbRepet = 1;
            for(int i=0; i < parsedBack->size(); i++)
            {
                CChampBinaire *buffChamp = parsedBack->at(i);
                if(buffChamp->getMLabel() == ref)
                {
                    QDataStream ds(buffChamp->getMData());
                    ds >> nbRepet;
                }
            }
            for(int i=0; i < nbRepet; ++i)
            {
                QList<CChampBinaire *> *parsedBlock;
                parsedBlock = ParserBloc(buffR->getMEnfants());
                parsedBack->append(*parsedBlock);
                delete parsedBlock;
            }
        }
        else if(buffR->getMType()== "int")
        {
           CChampBinaire *buffParse = ParserInt(buffR);
           parsedBack->append(buffParse);
        }
    }
    return parsedBack;
}

//void CImportExport::RecupererValeur()

CChampBinaire* CImportExport::ParserInt(CRegleParsage *aRegle)
{
    QByteArray buffer = mData.mid(mOffset, aRegle->getMTaille());
    mOffset += aRegle->getMTaille();
    CChampBinaire *elemParse = new CChampBinaire();
    QSpinBox *editeurInt = new QSpinBox(mParent);
    elemParse->getMData().clear();
    elemParse->setMData(buffer);
    elemParse->setMEditeur(editeurInt);
    elemParse->setMLabel(aRegle->getMNom());
    elemParse->setMType(aRegle->getMType());
    return elemParse;
}

QList<CChampBinaire *> *CImportExport::ParserBloc(QList<CRegleParsage *> *aRegles)
{
    QList<CChampBinaire *> *parsedBack = new QList<CChampBinaire *>();
    for(int i=0; i < aRegles->size(); ++i)
    {
        CRegleParsage *buffR = aRegles->at(i);
        if(buffR->getMType() == "bloc")
        {
            QString ref = buffR->getMRefNombre();
            int nbRepet = 1;
            for(int i=0; i < parsedBack->size(); i++)
            {
                CChampBinaire *buffChamp = parsedBack->at(i);
                if(buffChamp->getMLabel() == ref)
                {
                    QDataStream ds(buffChamp->getMData());
                    ds >> nbRepet;
                }
            }
            for(int i=0; i < nbRepet; ++i)
            {
                QList<CChampBinaire *> *parsedBlock;
                parsedBlock = ParserBloc(buffR->getMEnfants());
                parsedBack->append(*parsedBlock);
                delete parsedBlock;
            }
        }
        else if(buffR->getMType()== "int")
        {
           CChampBinaire *buffParse = ParserInt(buffR);
           parsedBack->append(buffParse);
        }
    }
    return parsedBack;
}
