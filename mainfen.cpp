#include "mainfen.h"
#include "ui_mainfen.h"

MainFen::MainFen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainFen),
    mParseurXml()
{
    ui->setupUi(this);
    mSplitter = new QSplitter(this);
    mTree = new QTreeWidget(this);
    mScroll = new QScrollArea(this);
    mMainLayout = new QFormLayout(mScroll);
    mImportExport = new CImportExport(this);

    mSplitter->addWidget(mTree);
    mSplitter->addWidget(mScroll);
    QList<int> sizes;
    sizes.push_back(150);
    sizes.push_back(490);
    mSplitter->setSizes(sizes);
    mSplitter->setCollapsible(0, false);
    mSplitter->setCollapsible(1, false);

    mConsoleDebug = new CDebugConsole(this);

    mTree->headerItem()->setText(0, "Structure");

    ui->centralWidget->layout()->addWidget(mSplitter);
    ui->actionBinaire->setDisabled(true);
    ui->actionExporterBinaire->setDisabled(true);
    ui->actionRechargeBinaire->setDisabled(true);
    ConnectSignaux();
}

MainFen::~MainFen()
{
    delete ui;
    if(listeParsage != NULL)
    {
        ClearListeParsage(listeParsage);
        delete listeParsage;
    }
    if(mBinaires != NULL)
    {
        for(int i = 0; i < mBinaires->count(); ++i)
        {
            delete mBinaires->takeAt(0);
        }
        delete mBinaires;
    }
    delete mImportExport;
}

void MainFen::ConnectSignaux()
{
    connect(ui->actionDescripteur, &QAction::triggered, this, &MainFen::OuvrirDescripteur);
    connect(ui->actionBinaire, &QAction::triggered, this, &MainFen::OuvrirBinaire);
    connect(ui->actionConsole, &QAction::triggered, mConsoleDebug, &CDebugConsole::show);
}

void MainFen::OuvrirDescripteur()
{
    QString path = QFileDialog::getOpenFileName(this, "Choisir le fichier descripteur", "", "Fichiers XML : *.xml");
    mParseurXml.OuvrirFichier(path);
    listeParsage = mParseurXml.ParserXml();
    ui->actionBinaire->setDisabled(false);
    ui->actionExporterBinaire->setDisabled(false);
    ui->actionRechargeBinaire->setDisabled(false);
//    AffichierGui();
}

void MainFen::OuvrirBinaire()
{
    QString path = QFileDialog::getOpenFileName(this, "Choisir le fichier binaire", "", "Tout type de fichier : *.*");
    mImportExport->OuvrirBinaire(path);
    mBinaires = mImportExport->ParserBinaire(listeParsage);
}

void MainFen::AfficherGui()
{

}

void MainFen::ClearListeParsage(QList<CRegleParsage *> *aListe)
{
    for(int i=0; i < aListe->size(); ++i)
    {
        if(aListe->at(i)->getMEnfants() != NULL)
        {
            ClearListeParsage(aListe->at(i)->getMEnfants());
        }
        delete aListe->at(i)->getMEnfants();
        delete aListe->at(i);
    }
}
