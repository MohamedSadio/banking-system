#include "uiinspectaccount.h"
#include "ui_uiinspectaccount.h"

UIInspectAccount::UIInspectAccount(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIInspectAccount)
{
    ui->setupUi(this);
}

UIInspectAccount::UIInspectAccount(QObject* controller):
    ui(new Ui::UIInspectAccount)
{
    ui->setupUi(this);

    connect(ui->pushButtonAnnuler, SIGNAL(clicked()), controller, SLOT());
    connect(ui->pushButtonRejeter, SIGNAL(clicked()), controller, SLOT());
    connect(ui->pushButtonApprouver, SIGNAL(clicked()), controller, SLOT());
}

QString UIInspectAccount::getIdTransaction()
{
    return ui->lineEditIdTransaction->text();
}

QString UIInspectAccount::getType()
{
    return ui->lineEditType->text();
}

QString UIInspectAccount::getDate()
{
    return ui->lineEditDate->text();
}

QString UIInspectAccount::getStatutTransaction()
{
    return ui->lineEditStatutTransac->text();
}

QString UIInspectAccount::getCompteTire()
{
    return ui->lineEditCompTire->text();
}

QString UIInspectAccount::getCompteBeneficiaire()
{
    return ui->lineEditComBenef->text();
}

QString UIInspectAccount::getMontant()
{
    return ui->lineEditMontant->text();
}

QString UIInspectAccount::getCompteTireSolde()
{
    return ui->lineEditSoldeTire->text();
}

QString UIInspectAccount::getCompteTireStatut()
{
    return ui->lineEditStatutTire->text();
}

QString UIInspectAccount::getCompteBeneficiaireSolde()
{
    return ui->lineEditSoldeBenef->text();
}

QString UIInspectAccount::getCompteBeneficiaireStatut()
{
    return ui->lineEditStatutBenef->text();
}

void UIInspectAccount::populateInfoVirement( QString idTransaction,  QString type,  QString date,  QString statutTransac,
                                             QString compteTire,  QString compteBeneficiaire,  QString montant)
{
    ui->lineEditIdTransaction->setText(idTransaction);
    ui->lineEditType->setText(type);
    ui->lineEditDate->setText(date);
    ui->lineEditStatutTransac->setText(statutTransac);
    ui->lineEditCompTire->setText(compteTire);
    ui->lineEditComBenef->setText(compteBeneficiaire);
    ui->lineEditMontant->setText(montant);
}

void UIInspectAccount::populateInfoComp( QString compteTire,  QString soldeTire,  QString statutTire,
                                         QString compteBeneficiaire,  QString soldeBeneficiaire,  QString statutBeneficiaire)
{
    ui->lineEditComptTire->setText(compteTire);
    ui->lineEditSoldeTire->setText(soldeTire);
    ui->lineEditStatutTire->setText(statutTire);
    ui->lineEditCompBenef->setText(compteBeneficiaire);
    ui->lineEditSoldeBenef->setText(soldeBeneficiaire);
    ui->lineEditStatutBenef->setText(statutBeneficiaire);
}
#include "uiinspectaccount.h"

void UIInspectAccount::reinit()
{
    ui->lineEditIdTransaction->clear();
    ui->lineEditType->clear();
    ui->lineEditDate->clear();
    ui->lineEditStatutTransac->clear();
    ui->lineEditCompTire->clear();
    ui->lineEditComBenef->clear();
    ui->lineEditMontant->clear();
    ui->lineEditComptTire->clear();
    ui->lineEditSoldeTire->clear();
    ui->lineEditStatutTire->clear();
    ui->lineEditSoldeBenef->clear();
    ui->lineEditStatutBenef->clear();
}

void UIInspectAccount::updateTitle(QString libelle)
{
    this->setWindowTitle("Client : " + libelle);
}
UIInspectAccount::~UIInspectAccount()
{
    delete ui;
}
