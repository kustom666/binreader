#ifndef CCHAMPBINAIRE_H
#define CCHAMPBINAIRE_H

#include <QByteArray>
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

private:
    QWidget *mEditeur;
    QString mLabel;
    QString mType;
    QByteArray mData;
};

#endif // CCHAMPBINAIRE_H
