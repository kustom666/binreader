#include "cdebugconsole.h"
#include "ui_cdebugconsole.h"

CDebugConsole::CDebugConsole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDebugConsole)
{
    ui->setupUi(this);
}

CDebugConsole::~CDebugConsole()
{
    delete ui;
}
