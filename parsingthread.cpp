#include "parsingthread.h"

ParsingThread::ParsingThread(QObject *parent) :
    QThread(parent)
{
    mIe = NULL;
    listeParsage = NULL;
    mBinaires = NULL;
}

ParsingThread::~ParsingThread()
{
}

void ParsingThread::run()
{
    if(mIe != NULL && listeParsage != NULL)
    {
        emit sendParsed(mIe->ParserBinaire(listeParsage));
        mIe = NULL;
        listeParsage = NULL;
    }
}
