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
    QString path = QFileDialog::getOpenFileName(this, tr("Choisir le fichier descripteur"), tr(""), tr("Fichiers XML : *.xml"));
    if(!path.isEmpty())
    {
        mParseurXml.OuvrirFichier(path);
        listeParsage = mParseurXml.ParserXml();
        ui->actionBinaire->setDisabled(false);
        ui->statusBar->showMessage(tr("Fichier de description chargé"), 3000);
    }
    else
    {
        mConsoleDebug->Warning(tr("Fichier XML introuvable"));
    }
}

void MainFen::OuvrirBinaire()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Choisir le fichier binaire"), tr(""), tr("Tout type de fichier : *.*"));
    if(!path.isEmpty())
    {
        mImportExport->OuvrirBinaire(path);
        mParsingThread.run(mImportExport, listeParsage, mBinaires);
        ui->actionExporterBinaire->setDisabled(false);
        ui->actionRechargeBinaire->setDisabled(false);
        connect(mTree, &QTreeWidget::itemClicked, this, &MainFen::ChangerEdits);
    }
    else
    {
        mConsoleDebug->Warning(tr("Fichier binaire introuvable"));
    }
}

void MainFen::ChangerEdits(QTreeWidgetItem *item, int colonne)
{
    ViderLayout(mMainLayout);
    QList<int> indexes;
    int indexPar = 0;
    QTreeWidgetItem *buff = item;
    while(buff != NULL)
    {
        if(buff->parent() != NULL)
        {
            int indexSub = buff->parent()->indexOfChild(buff);
            indexes.push_back(indexSub);
        }
        else
        {
            indexPar = mTree->indexOfTopLevelItem(buff);
        }
        buff = buff->parent();
    }
    qDebug() << "Index parent : " + QString::number(indexPar);
    if(!indexes.isEmpty())
    {
         qDebug() << "Index enfant : " + QString::number(indexes.at(0));
    }

    qDebug() << "Taille mBinaires" + QString::number(mBinaires->size());
    CChampBinaire *pack = mBinaires->at(indexPar);
    if(!indexes.isEmpty())
    {
        if(pack->getMType() == "bloc")
        {
            CChampBinaire *elem = pack->getMEnfants()->at(indexes.at(0));
            mMainLayout->insertRow(0, elem->getMLabel(), elem->getMEditeur());
        }
        else
        {

        }
    }
    else
    {
        if(pack->getMType() != "bloc")
        {
            mMainLayout->insertRow(0, pack->getMLabel(), pack->getMEditeur());
        }
    }

//    if(index != -1)
//    {
//        CChampBinaire *bin = mBinaires->at(index);
//        qDebug() << "Index : " + QString::number(index);
//        if(bin->getMType() != "bloc")
//        {
//            mMainLayout->insertRow(0, bin->getMLabel(), bin->getMEditeur());
//            QByteArray data = bin->getMData();
//            QDataStream ds(data);

//            if(bin->getMType() == "int")
//            {
//                QSpinBox *sp = (QSpinBox *) bin->getMEditeur();
//                sp->setMaximum(pow(2, 8*bin->getMTaille()));
//                sp->setEnabled(true);
//                int value = CChampBinaire::RecupInt(bin);
//                qDebug() << "Valeur : " << value;
//                sp->setValue(value);
//            }
//            bin->getMEditeur()->show();
//        }
//    }
//    else
//    {
//        mConsoleDebug->Erreur("Impossible de retrouver la valeur liée à l'élément " + QString::number(index));
//    }
}

void MainFen::AfficherGui()
{
    for(int i=0; i < mBinaires->size(); ++i)
    {
        qDebug() << "Taille binaire affichage : " +  QString::number(mBinaires->size());
        CChampBinaire *bin = mBinaires->at(i);
        if(bin->getMType() == "bloc")
        {
            AfficherBloc(bin, mTree->invisibleRootItem());
        }
        else
        {
            QTreeWidgetItem *branche = new QTreeWidgetItem(mTree);
            branche->setText(0, bin->getMLabel());
        }
    }
}

void MainFen::AfficherBloc(CChampBinaire *aBin, QTreeWidgetItem *aRoot)
{
    QTreeWidgetItem *branche = new QTreeWidgetItem(aRoot);
    branche->setText(0, aBin->getMLabel());
    for(int i=0; i < aBin->getMEnfants()->size(); ++i)
    {
        CChampBinaire *binFeuille = aBin->getMEnfants()->at(i);
        QTreeWidgetItem *feuille = new QTreeWidgetItem(branche);
        feuille->setText(0, binFeuille->getMLabel());
        if(binFeuille->getMEnfants() != NULL)
        {
            AfficherBloc(binFeuille, feuille);
        }
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
    ui->statusBar->showMessage(tr("Lecture du binaire terminée"), 3000);
    AfficherGui();
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
