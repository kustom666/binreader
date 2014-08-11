#ifndef MAINFEN_H
#define MAINFEN_H

#include <cmath>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QList>
#include <QMainWindow>
#include <QScrollArea>
#include <QSplitter>
#include <QTreeWidget>

#include <QFormLayout>

#include "cparseurxml.h"
#include "cregleparsage.h"
#include "cimportexport.h"
#include "cdebugconsole.h"
#include "parsingthread.h"

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
    void OuvrirBinaire();
    void HandleParsed(QList<CChampBinaire *> *aBinaires);
    void ChangerEdits(QTreeWidgetItem *item, int colonne);
    void AfficherGui();

private:
    void ConnectSignaux();
    void ClearListeParsage(QList<CRegleParsage *> *aListe);
    void ViderLayout(QLayout *layout);

private:
    Ui::MainFen *ui;
    QSplitter *mSplitter;
    QFormLayout *mMainLayout;
    QScrollArea *mScroll;
    QTreeWidget *mTree;
    CParseurXml mParseurXml;
    QList<CRegleParsage *> *listeParsage;
    CImportExport *mImportExport;
    CDebugConsole *mConsoleDebug;
    QList<CChampBinaire *> *mBinaires;
    ParsingThread mParsingThread;
    int mIndexRegles;
};

#endif // MAINFEN_H
