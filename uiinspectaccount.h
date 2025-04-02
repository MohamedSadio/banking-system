#ifndef UIINSPECTACCOUNT_H
#define UIINSPECTACCOUNT_H

#include "uiabstractwindow.h"

#include <QMainWindow>

namespace Ui {
class UIInspectAccount;
}

class UIInspectAccount : public QMainWindow, public UIAbstractWindow
{
    Q_OBJECT

public:
    explicit UIInspectAccount(QWidget *parent = nullptr);
    UIInspectAccount(QObject* controller);

    QString getIdTransaction();

    ~UIInspectAccount();

    QString getType();
    QString getDate();
    QString getStatutTransaction();
    QString getCompteTire();
    QString getCompteBene();
    QString getMontant();
    QString getCompteBeneficiaire();
    QString getCompteTireSolde();
    QString getCompteTireStatut();
    QString getCompteBeneficiaireSolde();
    QString getCompteBeneficiaireStatut();
    void populateInfoVirement(QString idTransaction, QString type, QString date, QString statutTransac, QString compteTire, QString compteBeneficiaire, QString montant);

    void populateInfoComp(QString compteTire, QString soldeTire, QString statutTire, QString compteBeneficiaire, QString soldeBeneficiaire, QString statutBeneficiaire);

    void reinit();

    void updateTitle (QString libelle);

private:
    Ui::UIInspectAccount *ui;
};

#endif // UIINSPECTACCOUNT_H
