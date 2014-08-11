#ifndef CDEBUGCONSOLE_H
#define CDEBUGCONSOLE_H

#include <QDialog>
#include <QDateTime>
#include <QList>
#include <ostream>

namespace Ui {
class CDebugConsole;
}

class CDebugConsole : public QDialog
{
    Q_OBJECT

public:
    explicit CDebugConsole(QWidget *parent = 0);
    ~CDebugConsole();

    friend std::ostream &operator<<(std::ostream &out, QString message);


    void Erreur(QString aMessage);
    void Info(QString aMessage);
    void Warning(QString aMessage);
private:
    Ui::CDebugConsole *ui;
    QString mErreurs;
};



#endif // CDEBUGCONSOLE_H
