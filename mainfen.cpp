#include "mainfen.h"
#include "ui_mainfen.h"

MainFen::MainFen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainFen),
    mParseurXml(),
    mParsingThread(this)
{
    ui->setupUi(this);
    mSplitter = new QSplitter(this);
    mTree = new QTreeWidget(this);
    mScroll = new QScrollArea(this);
    mMainLayout = new QFormLayout(mScroll);
    mImportExport = new CImportExport(0);

    mBinaires = NULL;
    listeParsage = NULL;

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
    connect(&mParsingThread, &ParsingThread::sendParsed, this, &MainFen::HandleParsed);
    connect(&mParsingThread, &ParsingThread::finished, &mParsingThread, &QObject::deleteLater);
}

void MainFen::OuvrirDescripteur()
{
    QString path = QFileDialog::getOpenFileName(this, "Choisir le fichier descripteur", "", "Fichiers XML : *.xml");
    mParseurXml.OuvrirFichier(path);
    listeParsage = mParseurXml.ParserXml();
    ui->actionBinaire->setDisabled(false);
//    AffichierGui();
}

void MainFen::OuvrirBinaire()
{
    QString path = QFileDialog::getOpenFileName(this, "Choisir le fichier binaire", "", "Tout type de fichier : *.*");
    mImportExport->OuvrirBinaire(path);
    mBinaires = mImportExport->ParserBinaire(listeParsage);
    qDebug() << "Parsing Fini";
    ui->actionExporterBinaire->setDisabled(false);
    ui->actionRechargeBinaire->setDisabled(false);
    AfficherGui();
    connect(mTree, &QTreeWidget::itemClicked, this, &MainFen::ChangerEdits);
//    mParsingThread.setMIe(mImportExport);
//    mParsingThread.setListeParsage(listeParsage);
//    mParsingThread.start();
}

void MainFen::ChangerEdits(QTreeWidgetItem *item, int colonne)
{
    ViderLayout(mMainLayout);
    int index = mTree->indexOfTopLevelItem(item);
    CChampBinaire *bin = mBinaires->at(index);
    mMainLayout->insertRow(0, bin->getMLabel(), bin->getMEditeur());
    QByteArray data = bin->getMData();
    QDataStream ds(data);

    if(bin->getMType() == "int")
    {
        QSpinBox *sp = (QSpinBox *) bin->getMEditeur();
        sp->setMaximum(pow(2, 8*bin->getMTaille()));
        sp->setMinimum(0);
        int value;

        if(bin->getMTaille() == 1)
        {
            value = 0;
            value |= bin->getMData().data()[0];
        }
        else if(bin->getMTaille() == 4)
        {
            ds >> value;
        }
        else
        {
            mConsoleDebug->Erreur(QString("La taille de l'entier est incorrecte"));
        }
        sp->setValue(value);

    }
    bin->getMEditeur()->show();
}

void MainFen::AfficherGui()
{
    for(int i=0; i < mBinaires->size(); ++i)
    {
        CChampBinaire *bin = mBinaires->at(i);
        QTreeWidgetItem *branche = new QTreeWidgetItem(mTree);
        branche->setText(0, bin->getMLabel());
    }
}

void MainFen::ClearListeParsage(QList<CRegleParsage *> *aListe)
{
    if(aListe != NULL)
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
}

void MainFen::HandleParsed(QList<CChampBinaire *> *aBinaires)
{
    mBinaires = aBinaires;
    qDebug() << "Parsing Fini";
}

void MainFen::ViderLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item=layout->itemAt(0)) != 0)
    {
        if(item->layout())
        {
            ViderLayout(item->layout());
        }
        for(int i=0; i < layout->count(); ++i)
        {
            layout->takeAt(i)->widget()->hide();
        }
    }

}
