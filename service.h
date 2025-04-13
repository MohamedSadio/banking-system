#ifndef SERVICE_H
#define SERVICE_H
#include <QString>
#include <QDate>
#include "usermodel.h"
#include "accountmodel.h"
#include "transactionmodel.h"
#include "notifmodele.h"
#include "settingsmodel.h"
#include "adminnotifmodel.h"
#include "messagemodel.h"

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
    void approuverVirement(QString numeroCompteTire, QString numeroCompteBeneficiaire, double montant);
//    void rejeterVirement(int idTransaction);
    bool rejeterVirement(int idTransaction);

    bool updateSystemSettings(int transactionLimit, int minAmount, int maxAmount, bool notificationsEnabled);
    bool loadSystemSettings(int &transactionLimit, int &minAmount, int &maxAmount, bool &notificationsEnabled);
    bool areNotificationsEnabled();
    bool isTransactionAmountValid(int amount);

    bool envoyerMessage(int expediteurId, int destinataireId, QString objet, QString contenu);
    void listerMessagesRecus(int userId);
    void listerMessagesEnvoyes(int userId);
    Message lireMessage(int messageId);
    bool marquerMessageCommeLu(int messageId, bool lu);
    int getNombreMessagesNonLus(int userId);
    QList<User> listerUtilisateursPourMessage();
    QStringList getUserEmail(UserModel* userModel);
    int getEmailId(QString email);

    Service(UserModel* userModel);
    Service(UserModel* userModel, AccountModel* accountModel);
    Service(UserModel* userModel, AccountModel* accountModel, TransactionModel* transactionModel);
    Service(UserModel* userModel, AccountModel* accountModel, TransactionModel* transactionModel,NotifModele* notifModel);
    Service(UserModel* userModel, AccountModel* accountModel, TransactionModel* transactionModel,SettingsModel* settingsModel);
    Service(UserModel* userModel, AccountModel* accountModel, TransactionModel* transactionModel,SettingsModel* settingsModel, AdminNotifModel* adminNotifModel, NotifModele* notifModele);
    Service(UserModel* userModel, AccountModel* accountModel, TransactionModel* transactionModel,SettingsModel* settingsModel, AdminNotifModel* adminNotifModel, NotifModele* notifModele, MessageModel* messageModel);

private:
    UserModel* userModel;
    AccountModel* accountModel;
    TransactionModel* transactionModel;
    NotifModele* notifModele;
    SettingsModel* settingsModel;
    AdminNotifModel* adminNotifModel;
    MessageModel* messageModel;

    bool effectuerUnRetrait(int idClient, double montant);
    void effectuerUnVersement(int idClient, double montant);
    void effectuerUnVirement (int idClient, QString numeroCompteBeneficiaire, double montant);
};

#endif // SERVICE_H
