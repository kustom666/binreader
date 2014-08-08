#ifndef PARSINGTHREAD_H
#define PARSINGTHREAD_H

#include <QThread>

class ParsingThread : public QThread
{
    Q_OBJECT
public:
    explicit ParsingThread(QObject *parent = 0);

signals:

public slots:

};

#endif // PARSINGTHREAD_H
