#include "cchampbinaire.h"

CChampBinaire::CChampBinaire()
{
    mEnfants = NULL;
}

int CChampBinaire::RecupInt(CChampBinaire* aBin)
{
    QDataStream ds(aBin->getMData());
    int value = 0;

    if(aBin->getMType() == "int")
    {
        if(aBin->getMTaille() == 1)
        {
            value |= (unsigned char)aBin->getMData()[0];
        }
        else if(aBin->getMTaille() == 2)
        {
            value |= (unsigned char)aBin->getMData()[0] << 8;
            value |= (unsigned char)aBin->getMData()[1];
        }
        else if(aBin->getMTaille() == 3)
        {
            value |= (unsigned char)aBin->getMData()[0] << 16;
            value |= (unsigned char)aBin->getMData()[1] << 8;
            value |= (unsigned char)aBin->getMData()[2];
        }
        else if(aBin->getMTaille() == 4)
        {
            ds >> value;
        }
        else if(aBin->getMTaille() == 6)
        {
            value |= (unsigned char)aBin->getMData()[0] << 24;
            value |= (unsigned char)aBin->getMData()[1] << 16;
            value |= (unsigned char)aBin->getMData()[2] << 8;
            value |= (unsigned char)aBin->getMData()[3];
        }
    }
    return value;
}

void CChampBinaire::AfficheVal(CChampBinaire *aBin)
{
    if(aBin->getMType() == "int")
    {
        QSpinBox *edit = (QSpinBox *) aBin->getMEditeur();
        edit->setMaximum(pow(2.0f, 8*aBin->getMTaille())-1);
        edit->setValue(CChampBinaire::RecupInt(aBin));
        edit->setVisible(true);
//                connect(edit, &QSpinBox::valueChange)
    }
    else if(aBin->getMType() == "texte")
    {
        QLineEdit *edit = (QLineEdit *) aBin->getMEditeur();
        edit->setText("placeholder");
        edit->setVisible(true);
    }
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

QList<CChampBinaire *>* CChampBinaire::getMEnfants() const
{
    return mEnfants;
}

void CChampBinaire::setMEnfants(QList<CChampBinaire *> *value)
{
    mEnfants = value;
}

