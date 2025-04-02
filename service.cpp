#include "service.h"
#include "user.h"
#include <QtDebug>
#include <QMessageBox>

Service::Service(UserModel* _userModel) :
    userModel(_userModel){}

Service::Service(UserModel* _userModel, AccountModel* _accountModel) :
    userModel(_userModel), accountModel(_accountModel){}

Service::Service(UserModel* _userModel, AccountModel* _accountModel, TransactionModel* _transactionModel) :
    userModel(_userModel), accountModel(_accountModel), transactionModel (_transactionModel) {}

Role Service::authentifier(QString login, QString password)
{
    qDebug () << "Service::authentifier " << login << "-" << password << "";
    User user = userModel->readBy(login, password);
    return user.getEnumRole();
}

bool Service::authentifier(QString login, QString password, User& user)
{
    qDebug () << "Service::authentifier " << login << "-" << password << "";
    user = userModel->readBy(login, password);
    QString userRole = user.getRole();
    return userRole.compare("NOT_DEFINED") == 0 ? false : true;
}

void Service::ajouterUnUser(QString nom, QString login, QString password, QString country, QString birthdate, QString email, QString role, QString statut)
{
    User user(nom, login, password, country, birthdate, email, role, statut);
    userModel->create(user);
}

void Service::ajouterUnClient(QString nom, QString login, QString password, QString country, QString birthdate, QString email, QString statut, int idCreator)
{
    QString role = "CLIENT";
    User user(nom, login, password, country, birthdate, email, role, statut, idCreator);
    userModel->create(user);
}

void Service::modifierUnUser(QString nom, QString login, QString password, QString country, QString birthdate, QString email, QString role, QString statut)
{
    QModelIndex selectedIndex = userModel->getSelectionModel()->currentIndex();
    int selectedLine = selectedIndex.row();

    QSqlRecord selectedRecord = userModel->record(selectedLine);
    QSqlField fieldId = selectedRecord.field(0);

    int selectedId = fieldId.value().toInt();

    User user(selectedId, nom, login, password, country, birthdate, email, role, statut);
    userModel->update(user);
}

bool Service::rechercherUnUser(int id)
{
    User user = userModel->read(id);
    if (user.getId() == -1)
    {
        return false;
    }
    else
    {
        userModel->readBy(id); // Afficher sur le tableView la User trouvée !!!
        return true;
    }
}

void Service::supprimerUnUser()
{
    userModel->remove();
}

void Service::listerLesUsers()
{
    userModel->getSelectionModel()->reset();
    userModel->readAll();
}

void Service::listerLesClients(int id)
{
    userModel->getSelectionModel()->reset();
    userModel->readAllClients(id);
}

void Service::listerLesComptes(int clientId)
{
    accountModel->getSelectionModel()->reset();    
    accountModel->readBy(clientId);
}

void Service::listerLesTransactions()
{
    transactionModel->getSelectionModel()->reset();
    transactionModel->readAll();
}

void Service::listerLesTransactions(int clientId)
{
    transactionModel->getSelectionModel()->reset();
    transactionModel->readBy(clientId);
}

void Service::listerLesNotification(int clientId){
    notifModele->getSelectionModel()->reset();
    notifModele->readBy(clientId);
}

void Service::listerLesTransactionsDuCompte()
{
    QModelIndex selectedIndex = accountModel->getSelectionModel()->currentIndex();
    int selectedLine = selectedIndex.row();
    QSqlRecord selectedRecord = accountModel->record(selectedLine);
    QSqlField fieldId = selectedRecord.field(0);
    int accountId = fieldId.value().toInt();

    transactionModel->getSelectionModel()->reset();
    transactionModel->readAll(accountId);
}

void Service::listerLesTransactionsDuCompteSpecifique(int accountId)
{
    transactionModel->getSelectionModel()->reset();
    transactionModel->readAll(accountId);
}

double Service::getAccountBalance(const QString& accountNumber) {
    return accountModel->getAccountBalance(accountNumber);
}

QString Service::getAccountStatus(const QString& accountNumber) {
    return accountModel->getAccountStatus(accountNumber);
}

void Service::listerLesVirementDuCompte(int accountId)
{
    transactionModel->getSelectionModel()->reset();
    transactionModel->readAllVirement(accountId);
}

bool Service::effectuerUnRetrait(int idClient, double montant)
{
    QModelIndex selectedIndex = accountModel->getSelectionModel()->currentIndex();
    int selectedLine = selectedIndex.row();
    QSqlRecord selectedRecord = accountModel->record(selectedLine);
    QSqlField fieldId = selectedRecord.field(0);
    int accountId = fieldId.value().toInt();

    Account account = accountModel->read(accountId);
    if (account.getBalance() < montant)
    {
        return false;
    }

    QDate today = QDate::currentDate();
    QTime now = QTime::currentTime();

    account.setBalance(account.getBalance() - montant);
    accountModel->update(account);
    accountModel->readBy(idClient);

    Transaction transaction ("RETRAIT", idClient, accountId, -1, account.getNumber(), "NULL", montant, today.toString("yyyy-MM-ddT") + now.toString("HH:mm:ss.zzz"), "Completed");
    transactionModel->create(transaction);
    Notif notif(idClient,accountId,"Votre operation de Retrait sur le compte","a été effectué avec succés",today.toString("yyyy-MM-ddT") + now.toString("HH:mm:ss.zzz"));
    notifModele->create(notif);

    return true;
}

void Service::effectuerUnVersement(int idClient, double montant)
{
    QModelIndex selectedIndex = accountModel->getSelectionModel()->currentIndex();
    int selectedLine = selectedIndex.row();
    QSqlRecord selectedRecord = accountModel->record(selectedLine);
    QSqlField fieldId = selectedRecord.field(0);
    int accountId = fieldId.value().toInt();

    Account account = accountModel->read(accountId);
    QDate today = QDate::currentDate();
    QTime now = QTime::currentTime();

    account.setBalance(account.getBalance() + montant);
    accountModel->update(account);
    accountModel->readBy(idClient);

    Transaction transaction ("VERSEMENT", idClient, -1, accountId, "NULL", account.getNumber(), montant, today.toString("yyyy-MM-ddT") + now.toString("HH:mm:ss.zzz"), "Completed");
    transactionModel->create(transaction);
    Notif notif(idClient,accountId,"Votre operation de Versement sur le compte","a été effectué avec succés",today.toString("yyyy-MM-ddT") + now.toString("HH:mm:ss.zzz"));
    notifModele->create(notif);
}

void Service::effectuerUnVirement (int idClient, QString numeroCompteBeneficiaire, double montant)
{
    QModelIndex selectedIndex = accountModel->getSelectionModel()->currentIndex();
    int selectedLine = selectedIndex.row();
    QSqlRecord selectedRecord = accountModel->record(selectedLine);
    QSqlField fieldId = selectedRecord.field(0);
    int accountId = fieldId.value().toInt();

    Account account = accountModel->read(accountId);
    QDate today = QDate::currentDate();
    QTime now = QTime::currentTime();

    Transaction transaction ("VIREMENT", idClient, accountId, -1, account.getNumber(), numeroCompteBeneficiaire, montant, today.toString("yyyy-MM-ddT") + now.toString("HH:mm:ss.zzz"), "Waiting");
    transactionModel->create(transaction);
    Notif notif(idClient,accountId,"Votre operation de Virement sur le compte","a été effectué avec succés",today.toString("yyyy-MM-ddT") + now.toString("HH:mm:ss.zzz"));
    notifModele->create(notif);
}

void Service::executeTransaction(QMap<QString, QString> input, bool &status, QString &message)
{
    QString typeTransaction = input.value("typeTransaction");
    QString connectedUserId = input.value("connectedUserId");
    QString montant = input.value("montant");
    QString numeroBeneficiaire = input.value("numeroBeneficiaire");

    if (typeTransaction.compare("VERSEMENT") == 0)
    {
        effectuerUnVersement(connectedUserId.toInt(), montant.toDouble());
        message = "Versement effectué avec succès.";
    }
    else if (typeTransaction.compare("RETRAIT") == 0)
    {
        status = effectuerUnRetrait(connectedUserId.toInt(), montant.toDouble());
        if (status) message = "Retrait effectué avvec succès.";
        else message = "**ERR** Erreur lors de la transaction, veuillez vous rapprocher de votre gestionnaire.";
    }
    else if (typeTransaction.compare("VIREMENT") == 0)
    {
        qDebug () << typeTransaction << "- Service::executeTransaction";
        effectuerUnVirement(connectedUserId.toInt(), numeroBeneficiaire, montant.toDouble());
        message = "Le virement a été enrégistré et est en cours de traitement ... vous recevrez une notification.";
    }
    else
    {
        qDebug () << "typeTransaction " << typeTransaction << " - aucune transaction elligible - Service::executeTransaction";
    }
}

void Service::approuverVirement(QString numeroCompteTire, QString numeroCompteBeneficiaire, double montant)
{
    // Récupérer les informations des comptes à partir des numéros de compte
    Account compteTire = accountModel->readByAccountNumber(numeroCompteTire);
    Account compteBeneficiaire = accountModel->readByAccountNumber(numeroCompteBeneficiaire);

    // Vérifier si les comptes existent
    if (compteTire.getId() == -1 || compteBeneficiaire.getId() == -1) {
        qDebug() << "Erreur: Comptes introuvables.";
        return; // Sortir de la fonction si les comptes n'existent pas
    }

    // Vérifier si le solde du compte émetteur est suffisant
    if (compteTire.getBalance() < montant) {
        qDebug() << "Erreur: Solde insuffisant.";
        return; // Sortir de la fonction si le solde est insuffisant
    }

    // Effectuer le retrait sur le compte émetteur
    compteTire.setBalance(compteTire.getBalance() - montant);
    accountModel->update(compteTire);

    // Effectuer le versement sur le compte bénéficiaire
    compteBeneficiaire.setBalance(compteBeneficiaire.getBalance() + montant);
    accountModel->update(compteBeneficiaire);

    // Mettre à jour le statut de la transaction à "Completed"
    Transaction transaction = transactionModel->readByBeneficiary(numeroCompteBeneficiaire);
    transaction.setStatut("Completed");
    transactionModel->updateStatut(transaction);

    // Créer une transaction pour le bénéficiaire
    Transaction transactionBeneficiaire;
    transactionBeneficiaire.setType("VERSEMENT");
    transactionBeneficiaire.setIdClient(compteBeneficiaire.getIdClient());
    transactionBeneficiaire.setIdCompteTire(-1);
    transactionBeneficiaire.setIdCompteBeneficiaire(compteBeneficiaire.getId()); // Pas de compte bénéficiaire pour un versement
    transactionBeneficiaire.setNumeroCompteBeneficiaire(numeroCompteBeneficiaire);
    transactionBeneficiaire.setNumeroCompteTire(numeroCompteTire);
    transactionBeneficiaire.setMontant(montant);
    transactionBeneficiaire.setDate(QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz"));
    transactionBeneficiaire.setStatut("Completed");

    transactionModel->create(transactionBeneficiaire);

    // Créer une notification pour l'utilisateur
//    QDate today = QDate::currentDate();
//    QTime now = QTime::currentTime();
//    Notif notif(idClient, compteTire.getId(), "Votre virement a été approuvé.", "Le virement de " + QString::number(montant) + " vers le compte " + numeroCompteBeneficiaire + " a été effectué avec succès.", today.toString("yyyy-MM-ddT") + now.toString("HH:mm:ss.zzz"));
//    notifModele->create(notif);
}

bool Service::rejeterVirement(int idTransaction)
{
        return transactionModel->rejeterTransaction(idTransaction);
}

void Service::ajouterUnCompte(QMap<QString, QString> input)
{
    QString idClient = input.value("idClient");
    QString number = input.value("number");
    QString type = input.value("type");
    QString balance = input.value("balance");
    QString statut = input.value("statut");

    bool ok;
    double balanceValue = balance.toDouble(&ok);
    if (!ok) {
        qDebug() << "Erreur de conversion de balance.";
        return; // ou gérer l'erreur d'une autre manière
    }

    Account account(idClient.toInt(), number, type, balanceValue, statut);
    accountModel->create(account);
    //listerLesComptes(idClient.toInt()); // Supprimé, car readAll est déjà appelé
}

void Service::modifierUnCompte(QMap<QString, QString> input)
{
    QString accountId = input.value("accountId");
    QString idClient = input.value("idClient");
    QString number = input.value("number");
    QString balance = input.value("balance");
    QString type = input.value("type");
    QString statut = input.value("statut");

    bool ok;
    double balanceValue = balance.toDouble(&ok);
    if (!ok) {
        qDebug() << "Erreur de conversion de balance.";
        return; // ou gérer l'erreur d'une autre manière
    }

    Account account(accountId.toInt(), idClient.toInt(), number, type, balanceValue, statut);
    accountModel->update(account);
    //listerLesComptes(idClient.toInt()); // Supprimé, car readAll est déjà appelé
}

bool Service::gelerCompte(int accountId)
{
    return accountModel->gelerCompte(accountId);
}
