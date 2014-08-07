#include "mainfen.h"
#include "ui_mainfen.h"

MainFen::MainFen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainFen),
    mParseurXml()
{
    ui->setupUi(this);
    ConnectSignaux();
}

MainFen::~MainFen()
{
    delete ui;
}

void MainFen::ConnectSignaux()
{
    connect(ui->actionDescripteur, &QAction::triggered, this, &MainFen::OuvrirDescripteur);
}

void MainFen::OuvrirDescripteur()
{
    QString path = QFileDialog::getOpenFileName(this, "Choisir le fichier descripteur", "", "Fichiers XML : *.xml");
    mParseurXml.OuvrirFichier(path);
    listeParsage = mParseurXml.ParserXml();
}

void MainFen::OuvrirBinaire()
{
    QString path = QFileDialog::getOpenFileName(this, "Choisir le fichier binaire", "", "Tout type de fichier : *.*");
}
