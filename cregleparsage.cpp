#include "cregleparsage.h"

CRegleParsage::CRegleParsage() :
    mNom("Inconnu"),
    mType("inconnu"),
    mTaille(0),
    mRefNombre("")
{
    mEnfants = new QList<CRegleParsage *>();
}

CRegleParsage::CRegleParsage(QString aNom, QString aType, int aTaille) :
    mRefNombre("")
{
    mNom = aNom;
    mType = aType;
    mTaille = aTaille;
    mEnfants = new QList<CRegleParsage *>();
}

