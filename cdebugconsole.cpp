#include "cdebugconsole.h"
#include "ui_cdebugconsole.h"

CDebugConsole::CDebugConsole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDebugConsole)
{
    ui->setupUi(this);
    mErreurs.append("<style>p.erreur{color: red;}\np.warning{color: yellow;}\np.info{color: green;}</style>");
}

CDebugConsole::~CDebugConsole()
{
    delete ui;
}

void CDebugConsole::Erreur(QString aMessage)
{
    QString message = "<p class=\"erreur\">[" + QDateTime::currentDateTime().toString() + "] " + aMessage + "</p>";
    mErreurs.append(message);
    ui->textBrowser->setHtml(mErreurs);
}
