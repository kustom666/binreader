#include "cchampbinaire.h"

CChampBinaire::CChampBinaire()
{
}
QByteArray CChampBinaire::getMData() const
{
    return mData;
}

void CChampBinaire::setMData(const QByteArray &value)
{
    mData = value;
}
QString CChampBinaire::getMType() const
{
    return mType;
}

void CChampBinaire::setMType(const QString &value)
{
    mType = value;
}
QString CChampBinaire::getMLabel() const
{
    return mLabel;
}

void CChampBinaire::setMLabel(const QString &value)
{
    mLabel = value;
}
QWidget *CChampBinaire::getMEditeur() const
{
    return mEditeur;
}

void CChampBinaire::setMEditeur(QWidget *value)
{
    mEditeur = value;
}
int CChampBinaire::getMTaille() const
{
    return mTaille;
}

void CChampBinaire::setMTaille(int value)
{
    mTaille = value;
}
int CChampBinaire::getMNombre() const
{
    return mNombre;
}

void CChampBinaire::setMNombre(int value)
{
    mNombre = value;
}

int CChampBinaire::RecupInt(CChampBinaire* aBin)
{
    QDataStream ds(aBin->getMData());
    int value = 0;

    if(aBin->getMType() == "int")
    {
        if(aBin->getMTaille() == 1)
        {
            value |= aBin->getMData()[0];
        }
        else if(aBin->getMTaille() == 4)
        {
            ds >> value;
        }
        else
        {
            //mConsoleDebug->Erreur(tr("La taille de l'entier est incorrecte"));
        }
    }
    else
    {
        //mConsoleDebug->Erreur(tr("Tentative de lecture d'un entier dans un champ d'un autre type"));
    }
    return value;
}
