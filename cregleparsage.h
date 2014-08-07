#ifndef CREGLEPARSAGE_H
#define CREGLEPARSAGE_H

#include <QLibrary>
#include <QString>

class CRegleParsage
{
public:
    CRegleParsage();
    CRegleParsage(QString aNom, QString aType, int aTaille);

public:
    QString getMNom(){ return mNom; }
    void setMNom(QString aNom){ mNom = aNom; }

    QString getMType(){ return mType; }
    void setMType(QString aType){ mType = aType; }

    int getMTaille(){ return mTaille; }
    void setMTaille(int aTaille){ mTaille = aTaille; }

    QString getMRefNombre(){ return mRefNombre; }
    void setMRefNombre(QString aRefNombre){ mRefNombre = aRefNombre; }

    QList<CRegleParsage*> *getMEnfants(){ return mEnfants; }
    void setMEnfants(QList<CRegleParsage*> *aEnfants){ mEnfants = aEnfants; }

private:
    QString mNom;
    QString mType;
    int mTaille;
    QString mRefNombre;
    QList<CRegleParsage *> *mEnfants;
};

#endif // CREGLEPARSAGE_H
