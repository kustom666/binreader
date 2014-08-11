#ifndef PARSINGTHREAD_H
#define PARSINGTHREAD_H

#include <QThread>
#include "cimportexport.h"
#include "cchampbinaire.h"
#include "cregleparsage.h"

class ParsingThread : public QThread
{
    Q_OBJECT
public:
    explicit ParsingThread(QObject *parent = 0);
//    void setMIe(CImportExport *aIe) { mIe = aIe; }
//    void setListeParsage(QList<CRegleParsage *> *aListeParsage){ listeParsage = aListeParsage; }
//    void setMBinaires(QList<CChampBinaire *> *aBinaires){ mBinaires = aBinaires; }
    void run(CImportExport *mIe, QList<CRegleParsage *> *listeParsage ,QList<CChampBinaire *> *mBinaires);

    ~ParsingThread();
signals:
    void sendParsed(QList<CChampBinaire *> *aBinaires);

private:

};

#endif // PARSINGTHREAD_H
