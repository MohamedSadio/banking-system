#include "uiaddclient.h"
#include "ui_uiaddclient.h"

UIAddClient::UIAddClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UIAddClient)
{
    ui->setupUi(this);
}

UIAddClient::UIAddClient(QObject* controller) :
    ui(new Ui::UIAddClient)
{
    qDebug("Contruction/Initialisation de la fenêtre UIAddClient ...");
    ui->setupUi(this);

    connect(ui->pushButtonClose, SIGNAL(clicked()), controller, SLOT(onClose_UIAddClient()));
    connect(ui->pushButtonCreate, SIGNAL(clicked()), controller, SLOT(onCreate_UIAddClient()));
}
QString UIAddClient::getNom()
{
    return ui->lineEditNom->text();
}

QString UIAddClient::getPassword()
{
    return ui->lineEditPassword->text();
}

QString UIAddClient::getLogin()
{
    return ui->lineEditLogin->text();
}

QString UIAddClient::getStatut()
{
    return ui->comboBoxStatut->currentText();
}

QString UIAddClient::getCountry()
{
    return ui->comboBoxCountry->currentText();
}

QString UIAddClient::getBirthdate()
{
    return ui->dateEditBirthdate->text();
}

QString UIAddClient::getEmail()
{
    return ui->lineEditEmail->text();
}

void UIAddClient::reinit()
{
    populate("-1", "", "Senegal", "01/01/2000", "", "", "", "");
}

void UIAddClient::populate (QString identifiant, QString nom, QString country, QString birthdate, QString login, QString password
                      , QString email, QString statut)
{
    ui->lineEditIdentifiant->setText(identifiant);
    ui->lineEditNom->setText(nom);
    ui->comboBoxCountry->setCurrentText(country);
    ui->dateEditBirthdate->setDate(QDate::fromString(birthdate, "dd/MM/yyyy"));
    ui->lineEditLogin->setText(login);
    ui->lineEditPassword->setText(password);
    ui->lineEditEmail->setText(email);
    ui->comboBoxStatut->setCurrentText(statut);
}

void UIAddClient::setIdEditableFalse()
{
    ui->lineEditIdentifiant->setEnabled(false);
}

void UIAddClient::updateTitle(QString libelle)
{
    this->setWindowTitle(windowTitle() + libelle);
}

UIAddClient::~UIAddClient()
{
    delete ui;
}
