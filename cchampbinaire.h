#ifndef CCHAMPBINAIRE_H
#define CCHAMPBINAIRE_H

#include <QByteArray>
#include <QDebug>
#include <QList>
#include <QString>
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

private:
    QWidget *mEditeur;
    QString mLabel;
    QString mType;
    QByteArray mData;
    int mTaille;
    int mNombre;
};

#endif // CCHAMPBINAIRE_H
