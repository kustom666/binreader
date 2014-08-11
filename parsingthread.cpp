#include "parsingthread.h"

ParsingThread::ParsingThread(QObject *parent) :
    QThread(parent)
{
}

ParsingThread::~ParsingThread()
{
}

void ParsingThread::run(CImportExport *mIe, QList<CRegleParsage *> *listeParsage ,QList<CChampBinaire *> *mBinaires)
{
    if(mIe != NULL && listeParsage != NULL)
    {
        mBinaires = mIe->ParserBinaire(listeParsage);
        emit sendParsed(mBinaires);
        mIe = NULL;
        listeParsage = NULL;
    }
}
