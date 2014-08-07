#ifndef MAINFEN_H
#define MAINFEN_H

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QList>
#include <QMainWindow>

#include "cparseurxml.h"
#include "cregleparsage.h"
#include "cimportexport.h"

namespace Ui {
class MainFen;
}

class MainFen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainFen(QWidget *parent = 0);
    ~MainFen();

public slots:
    void OuvrirDescripteur();

private:
    void ConnectSignaux();
    void OuvrirBinaire();

private:
    Ui::MainFen *ui;
    CParseurXml mParseurXml;

    QList<CRegleParsage *> *listeParsage;
};

#endif // MAINFEN_H
