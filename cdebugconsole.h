#ifndef CDEBUGCONSOLE_H
#define CDEBUGCONSOLE_H

#include <QDialog>

namespace Ui {
class CDebugConsole;
}

class CDebugConsole : public QDialog
{
    Q_OBJECT

public:
    explicit CDebugConsole(QWidget *parent = 0);
    ~CDebugConsole();

private:
    Ui::CDebugConsole *ui;
};

#endif // CDEBUGCONSOLE_H
