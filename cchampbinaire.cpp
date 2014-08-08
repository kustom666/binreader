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
