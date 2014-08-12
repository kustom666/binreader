#ifndef CCHAMPBINAIRE_H
#define CCHAMPBINAIRE_H

#include <cmath>
#include <QByteArray>
#include <QDebug>
#include <QList>
#include <QLineEdit>
#include <QString>
#include <QSpinBox>
#include <QWidget>

class CChampBinaire
{
public:
    CChampBinaire();

    QByteArray getMData() const;
    void setMData(const QByteArray &value);

    QString getMType() const;
    void setMType(const QString &value);

    QString getMLabel() const;
    void setMLabel(const QString &value);

    QWidget *getMEditeur() const;
    void setMEditeur(QWidget *value);

    int getMTaille() const;
    void setMTaille(int value);

    int getMNombre() const;
    void setMNombre(int value);

    static int RecupInt(CChampBinaire* aBin);
    static void AfficheVal(CChampBinaire *aBin);

    QList<CChampBinaire *> *getMEnfants() const;
    void setMEnfants(QList<CChampBinaire *> *value);

private:
    QWidget *mEditeur;
    QString mLabel;
    QString mType;
    QByteArray mData;
    int mTaille;
    int mNombre;
    QList<CChampBinaire *> *mEnfants;
};

#endif // CCHAMPBINAIRE_H
