#ifndef SERVICE_H
#define SERVICE_H
#include <QString>
#include <QDate>
#include "usermodel.h"
#include "accountmodel.h"
#include "transactionmodel.h"
#include "notifmodele.h"

class Service
{

public:
    Role authentifier (QString login, QString password);
    bool authentifier(QString login, QString password, User& user);

    void ajouterUnUser(QString nom, QString login, QString password, QString country, QString birthdate, QString email, QString role, QString statut);
    void modifierUnUser(QString nom, QString login, QString password, QString country, QString birthdate, QString email, QString role, QString statut);
    void ajouterUnCompte(QMap<QString, QString> input);
    void ajouterUnClient(QString nom, QString login, QString password, QString country, QString birthdate, QString email, QString statut, int idCreator);
    void modifierUnCompte(QMap<QString, QString> input);
    bool gelerCompte(int accountId);
    void supprimerUnUser();
    bool rechercherUnUser(int id);
    void listerLesUsers();
    void listerLesClients(int id);
    void listerLesTransactions();
    void listerLesTransactionsDuCompte();
    void listerLesTransactionsDuCompteSpecifique(int accountId);
    void listerLesVirementDuCompte(int id);
    void listerLesComptes(int clientId);
    void listerLesTransactions(int clientId);
    void listerLesNotification(int clientId);
    double getAccountBalance(const QString& accountNumber);
    QString getAccountStatus(const QString& accountNumber);
    // -
    void executeTransaction (QMap<QString, QString> input, bool &status, QString &message);

    Service(UserModel* userModel);
    Service(UserModel* userModel, AccountModel* accountModel);
    Service(UserModel* userModel, AccountModel* accountModel, TransactionModel* transactionModel);
    Service(UserModel* userModel, AccountModel* accountModel, TransactionModel* transactionModel,NotifModele notifModel);

private:
    UserModel* userModel;
    AccountModel* accountModel;
    TransactionModel* transactionModel;
    NotifModele* notifModele;

    bool effectuerUnRetrait(int idClient, double montant);
    void effectuerUnVersement(int idClient, double montant);
    void effectuerUnVirement (int idClient, QString numeroCompteBeneficiaire, double montant);
};

#endif // SERVICE_H
