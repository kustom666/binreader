#ifndef MAINFEN_H
#define MAINFEN_H

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

private:
    void ConnectSignaux();
    void AfficherGui();
    void ClearListeParsage(QList<CRegleParsage *> *aListe);

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

};

#endif // MAINFEN_H
