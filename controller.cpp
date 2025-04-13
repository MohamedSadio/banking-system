#include "controller.h"
#include <QMessageBox>

Controller::Controller(QObject* parent) :
    QObject(parent)
{
    qDebug("Controller Started.");
}

void Controller::execute()
{
    uiLoginIn.show();
}

void Controller::executeUserList()
{
    uiListUser.setTableViewModel(userModel);
    uiListUser.show();
    uiListUser.top();
    service.listerLesUsers();
    uiListUser.updateTitle(connectedUser.getNom());
}

void Controller::executeClientList()
{
    uiListAccount.setTableViewModel(accountModel);
    uiListClient.setTableViewModel(userModel);
    service.listerLesClients(connectedUser.getId());
    uiListClient.show();
    uiListClient.updateTitle (connectedUser.getNom());
    uiListClient.top();
}

void Controller::reloadTransactions()
{
    // Récupérer l'ID du compte sélectionné
    QModelIndex index = accountModel->getSelectionModel()->currentIndex();
    int selectedAccountLine = index.row();
    QSqlRecord selectedAccountRecord = accountModel->record(selectedAccountLine);
    QSqlField accountField = selectedAccountRecord.field(0);
    int accountId = accountField.value().toInt();

    // Appeler le service pour récupérer les transactions
    service.listerLesTransactionsDuCompteSpecifique(accountId);

    // Mettre à jour le modèle de données de uiListTransaction
    uiListTransaction.setTableViewModel(transactionModel);
}

void Controller::executeNotifListGerant()
{
    uiGerantNotif.setTableViewModel(gerantNotifModel);
    serviceGerant.listerLesNotificationGerant(connectedUser.getId());
    uiGerantNotif.show();
    uiGerantNotif.top();
    uiGerantNotif.updateTitle(connectedUser.getNom());
}

// Optionnel: Fonction pour recharger la liste des comptes
void Controller::reloadAccounts() {

    QModelIndex userIndex = userModel->getSelectionModel()->currentIndex();
    int selectedUserLine = userIndex.row();
    QSqlRecord selectedUserRecord = userModel->record(selectedUserLine);
    QSqlField userField = selectedUserRecord.field(0);
    int clientId = userField.value().toInt();

    service.listerLesComptes(clientId);
    uiListAccount.setTableViewModel(accountModel);
    uiListAccount.top();
}

/* Les slots de la fenêtre UILogin
 *
 */
void Controller::onSubmit_UILoginIn()
{
    QString login = uiLoginIn.getLogin();
    QString password = uiLoginIn.getPassword();

    qDebug () << "Controller::onSubmit_UILoginIn " << login << "-" << password << "";
    bool status = service.authentifier(login, password, connectedUser);

    if (status == true)
    {
        uiLoginIn.hide();

        switch (connectedUser.getEnumRole())
        {
            case ADMINISTRATEUR:
//                uiUser.show();
//                uiUser.reinit();
//                uiUser.deactivateUpdate();
//                uiUser.updateTitle (connectedUser.getNom());
            executeUserList();

            break;

            case CLIENT:
                uiClient.setTableViewModel(accountModel);
                uiClient.show();
                uiClient.hideTransactionForm();
                uiClient.updateTitle (connectedUser.getNom());
                service.listerLesComptes(connectedUser.getId());
                uiListAccount.setTableViewModel(accountModel);
                uiListAccount.top();
            break;

            case GESTIONNAIRE:
//                uiListAccount.setTableViewModel(accountModel);
//                uiListClient.setTableViewModel(userModel);
//                uiListClient.show();
//                service.listerLesClients();
//                uiListClient.updateTitle (connectedUser.getNom());
//                uiListClient.top();
                executeClientList();

            break;

            default:;
                // Nothing to be done!
        }
    }
    else
    {
        uiLoginIn.critical("Sign in",
            "Incorrect Login/Password, please try again !");
    }
}

void Controller::onExit_UILoginIn()
{
    if (true == uiLoginIn.question("Exit confirmation",
            "Do you really want to exit the application ?"))
        {
            uiLoginIn.close();
        }
}

/* Les slots de la fenêtre UIListUser
 *
 */

void Controller::onCreate_UIListUser()
{
    uiListUser.close();
    uiUser.show();
    uiUser.reinit();
    uiUser.deactivateUpdate();
    uiUser.setRoleEditable(true);
    uiUser.updateTitle (connectedUser.getNom());
}

void Controller::onUpdate_UIListUser()
{
    QModelIndex index = userModel->getSelectionModel()->currentIndex();

    if (index.isValid() == false)
    {
        uiListUser.warning("Mise a jour des informations d'une User",
                              "Veuillez selectionner une ligne svp ...");
    }
    else
    {
        uiListUser.close();

        int selectedLine = index.row();
        QSqlRecord selectedRecord = userModel->record(selectedLine);

        // Récupération des informations du record sélectionné !
        // Identifiant
        QSqlField field = selectedRecord.field(0);
        QString id = field.value().toString();

        // Nom
        field = selectedRecord.field(1);
        QString nom = field.value().toString();

        // Country
        field = selectedRecord.field(2);
        QString country = field.value().toString();

        // Birthdate
        field = selectedRecord.field(3);
        QString birthdate = field.value().toString();

        // Login
        field = selectedRecord.field(4);
        QString login = field.value().toString();

        // Password
        field = selectedRecord.field(5);
        QString password = field.value().toString();

        // Email
        field = selectedRecord.field(6);
        QString email = field.value().toString();

        // Rôle
        field = selectedRecord.field(7);
        QString role = field.value().toString();

        // Statut
        field = selectedRecord.field(8);
        QString statut = field.value().toString();

        // Remplissage des champs du formulaire avec les informations récupérés de la ligne sélectionnée
        // sur le QTableView de la fenêtre UIListUser
        uiUser.populate(id, nom, country, birthdate, login, password, email, role, statut);

        uiUser.show();
        uiUser.activateUpdate();
        uiUser.setRoleEditable(false);
        uiUser.setIdEditable(false);

    }
}

void Controller::onDelete_UIListUser()
{
    qDebug("Enter in function onDelete_UIListUser.");

    QModelIndex index = userModel->getSelectionModel()->currentIndex();
    if (index.isValid() == false)
    {
        uiListUser.warning("Suppression d'une User",
                              "Veuillez selectionner une ligne svp ...");
    }
    else
    {
        bool response = uiListUser.question("Suppression d'une User", "Voulez-vous vraiment supprimer cette User ?");
        if (response == true)
        {
            service.supprimerUnUser();
        }
    }
}

void Controller::onClose_UIListUser()
{
//    uiListUser.hide();

//    uiUser.reinit();
//    uiUser.show();
//    uiUser.deactivateUpdate();
//    uiUser.setRoleEditable(true);
    uiListUser.close();
    uiLoginIn.reinit();
    uiLoginIn.show();
}


/*...
 * Les slots de la fenêtre UIUser
 */
void Controller::onCreate_UIUser()
{
    qDebug("Enter the function onCreate_UIUser.");

    QString nom = uiUser.getNom();
    QString login = uiUser.getLogin();

    if (nom.isEmpty() || login.isEmpty())
    {

        uiUser.warning("Ajout d'une nouvelle User",
                            "Veuillez renseigner tous les champs svp.");
    }
    else
    {
        QString password = uiUser.getPassword();
        QString country = uiUser.getCountry();
        QString birthdate = uiUser.getBirthdate();
        QString email = uiUser.getEmail();
        QString role = uiUser.getRole();
        QString statut = uiUser.getStatut();

        service.ajouterUnUser (nom, login, password, country, birthdate, email, role, statut);
        uiUser.information("Ajout d'une nouvelle User",
                           "Nouveau Utilisateur crée avec success !");
        uiUser.reinit();
        uiUser.hide();
        executeUserList();

    }
}


void Controller::onUpdate_UIUser()
{
    QString nom = uiUser.getNom();
    QString login = uiUser.getLogin();

    if (nom.isEmpty() || login.isEmpty())
    {
        uiUser.warning("Mise a jour d'une User",
                       "Veuillez renseigner tous les champs svp.");
    }
    else
    {
        QString password = uiUser.getPassword();
        QString country = uiUser.getCountry();
        QString birthdate = uiUser.getBirthdate();
        QString email = uiUser.getEmail();
        QString role = uiUser.getRole();
        QString statut = uiUser.getStatut();

        service.modifierUnUser (nom, login, password, country, birthdate, email, role, statut);
        uiUser.information("Mise a jour d'une User",
                           "Utilisateur modifiée avec success !");
        uiUser.reinit();
        uiUser.hide();

        uiUser.deactivateUpdate();
        executeUserList();
        uiListUser.updateTitle (connectedUser.getNom());
    }
}

void Controller::onClose_UIUser()
{
//    uiUser.hide();

//    uiLoginIn.reinit();
//    uiLoginIn.show();
    uiUser.close();
    executeUserList();
}

void Controller::onComboBoxRoleChanged_UIUser()
{
    QString role = uiUser.getRole();
    if (role.compare("ADMINISTRATEUR") == 0)
    {
        uiUser.hideStatut();
    }
    else
    {
        uiUser.showStatut();
    }
}

void Controller::onSettings_UIListUser()
{
    uiListUser.hide();
    uiSettings.show();
}

void Controller::onNotifs_UIListUser()
{
    uiListUser.hide();
    uiAdminNotif.show();
}

void Controller::onMessages_UIListUser()
{
    uiListUser.hide();
    uiMessage.show();
    uiMessage.setComboxReceiver(service.getUserEmail(userModel));
}

/*
 * Les slots de la fenetre UIAddCLient
 */
void Controller::onCreate_UIAddClient()
{
    qDebug("Enter the function onCreate_UIAddClient.");

    QString nom = uiAddClient.getNom();
    QString login = uiAddClient.getLogin();

    if (nom.isEmpty() || login.isEmpty())
    {

        uiAddClient.warning("Ajout d'une nouvelle User",
                            "Veuillez renseigner tous les champs svp.");
    }
    else
    {
        QString password = uiAddClient.getPassword();
        QString country = uiAddClient.getCountry();
        QString birthdate = uiAddClient.getBirthdate();
        QString email = uiAddClient.getEmail();
        QString statut = uiAddClient.getStatut();
        int idCreator = connectedUser.getId();

        service.ajouterUnClient (nom, login, password, country, birthdate, email, statut, idCreator);
        uiAddClient.reinit();
    }
}

void Controller::onClose_UIAddClient()
{
    uiAddClient.close();
    executeClientList();
}


/*
 * Les slots de la fenêtre UINotif
 */
void Controller::onClose_UINotif(){
    uiNotif.hide();
    uiClient.show();
}

/*
 * Les slots de la fenêtre UIClient
 */
void Controller::onClose_UIClient()
{
    uiClient.hide();

    uiLoginIn.reinit();
    uiLoginIn.show();
}

void Controller::onOuvrir_UIClient()
{
    QModelIndex index = accountModel->getSelectionModel()->currentIndex();
    if (index.isValid() == false)
    {
        uiClient.warning("Ouverture de vos comptes",
                         "Veuillez selectionner un de vos comptes svp ...");
    }
    else
    {
        uiClient.hide();
        uiListTransaction.setTableViewModel(transactionModel);
        uiListTransaction.show();
        service.listerLesTransactionsDuCompte();
        uiListTransaction.top();
    }
}

void Controller::onVirement_UIClient()
{
    QModelIndex index = accountModel->getSelectionModel()->currentIndex();
    if (index.isValid() == false)
    {
        uiClient.warning("Opération de virement",
                         "Veuillez selectionner un de vos comptes svp ...");
    }
    else
    {
        uiClient.hideTransactionForm();
        uiClient.showTransactionForm("Entrer les informations du virement :", "VIREMENT");
    }
}

void Controller::onRetrait_UIClient()
{
    QModelIndex index = accountModel->getSelectionModel()->currentIndex();
    if (index.isValid() == false)
    {
        uiClient.warning("Opération de retrait",
                         "Veuillez selectionner un de vos comptes svp ...");
    }
    else
    {
        uiClient.hideTransactionForm();
        uiClient.showTransactionForm("Entrer les informations du retrait :", "RETRAIT");
    }
}

void Controller::onVersement_UIClient()
{
    QModelIndex index = accountModel->getSelectionModel()->currentIndex();
    if (index.isValid() == false)
    {
        uiClient.warning("Opération de depôt",
                         "Veuillez selectionner un de vos comptes svp ...");
    }
    else
    {
        uiClient.hideTransactionForm();
        uiClient.showTransactionForm("Entrer les informations du versement :", "VERSEMENT");
    }
}

void Controller::onHistorique_UIClient()
{
    uiClient.hide();
    uiListTransaction.setTableViewModel(transactionModel);
    uiListTransaction.show();
    service.listerLesTransactions(connectedUser.getId());
    uiListTransaction.top();
}

void Controller::onNotification_UIClient(){
    uiClient.hide();
    uiNotif.setTableViewModel(notifModel);
    uiNotif.show();
    service.listerLesNotification(connectedUser.getId());
    uiNotif.top();
}

void Controller::onOK_UIClient()
{
    QMap <QString, QString> input;
    bool ok {true};

    QString typeTransaction = uiClient.getTypeTransaction();
    input.insert("connectedUserId", QString::number(connectedUser.getId()));
    input.insert("typeTransaction", typeTransaction);

    QString montant = uiClient.getMontant();
    if (montant.compare("") == 0)
    {
        uiClient.critical("Contrôle de saisie", "Le montant n'est pas renseigné !!");
        ok = false;
    }
    else
    {
        input.insert("montant", montant);
        // -
        if (typeTransaction.compare("VIREMENT") == 0)
        {
            QString numeroBeneficiaire = uiClient.getNumeroBeneficiaire();
            if (numeroBeneficiaire.compare("") == 0)
            {
                uiClient.critical("Contrôle de saisie", "Le numéro du bénéficiaire n'est pas renseigné !!");
                ok = false;
            }
            else
            {
                qDebug () << numeroBeneficiaire << "- Controller::onOK_UIClient";
                input.insert("numeroBeneficiaire", numeroBeneficiaire);
            }
        }
    }

    if (ok)
    {        
        QString transaction_message;
        bool status {true};
        qDebug () << typeTransaction << "- Controller::onOK_UIClient";
        service.executeTransaction(input, status, transaction_message);
        if (status == true)
        {
            uiClient.hideTransactionForm();
            uiClient.information("Fin de la transation", transaction_message);
        }
        else
        {
            uiClient.critical("Echec de la transation", transaction_message);
        }
    }
}

void Controller::onCancel_UIClient()
{
    uiClient.hideTransactionForm();
}

/*
 * Les slots de la fenêtre UIListClient
 */
void Controller::onClose_UIListClient()
{
    uiListClient.hide();
    uiLoginIn.reinit();
    uiLoginIn.show();
}

void Controller::onOuvrir_UIListClient()
{
    QModelIndex index = userModel->getSelectionModel()->currentIndex();

    if (index.isValid() == false)
    {
        uiListUser.warning("Mise a jour des informations d'une User",
                           "Veuillez selectionner une ligne svp ...");
    }
    else
    {
        uiListClient.hide();
        // -
        int selectedLine = index.row();
        QSqlRecord selectedRecord = userModel->record(selectedLine);

        // Récupération des informations du client sélectionné
        currentClient.setId(selectedRecord.field(0).value().toInt());
        currentClient.setNom(selectedRecord.field(1).value().toString());
        currentClient.setCountry(selectedRecord.field(2).value().toString());
        currentClient.setBirthdate(selectedRecord.field(3).value().toString());
        currentClient.setLogin(selectedRecord.field(4).value().toString());
        currentClient.setPassword(selectedRecord.field(5).value().toString());
        currentClient.setEmail(selectedRecord.field(6).value().toString());
        currentClient.setRole(selectedRecord.field(7).value().toString());
        currentClient.setStatut(selectedRecord.field(8).value().toString());

        uiListAccount.show();
        uiListAccount.updateTitle(connectedUser.getNom());
        uiListAccount.updateAccountTitle(currentClient.getNom()); // Utilisation de currentClient
        service.listerLesComptes(currentClient.getId()); // Utilisation de currentClient
        uiListAccount.top();


        uiListAccount.show();
        uiListAccount.updateTitle (connectedUser.getNom());
        uiListAccount.updateAccountTitle(currentClient.getNom());
        service.listerLesComptes(currentClient.getId());
        uiListAccount.top();
    }
}

/*void Controller::onCreate_UIListClient()
{
    uiListClient.close();
    uiAddClient.setIdEditableFalse();
    uiAddClient.show();
    uiAddClient.reinit();
    uiAddClient.updateTitle (connectedUser.getNom());
}*/

void Controller::onNotifs_UIListClient()
{
    uiListClient.hide();
    executeNotifListGerant();
}

void Controller::onMessages_UIListClient()
{
    // uiListClient.hide();
    // uiMessage.show();
    // uiMessage.setComboxReceiver(service.getUserEmail(userModel));
}

/*
 * Les slots de la fenêtre UIListAccount
 */
void Controller::onNouveau_UIListAccount()
{
    QModelIndex index = userModel->getSelectionModel()->currentIndex();
    // -
    int selectedLine = index.row();
    QSqlRecord selectedRecord = userModel->record(selectedLine);
    QSqlField field = selectedRecord.field(0);
    int idClient = field.value().toInt();

    field = selectedRecord.field(1);
    QString nomClient = field.value().toString();

    uiAccount.updateTitle (nomClient);
    uiListAccount.hide();
    uiAccount.show();
    uiAccount.populate("-1", QString::number(idClient), "", "COURANT", "0", "ACTIF");

    uiAccount.deactivateUpdate();
}

void Controller::onModifier_UIListAccount()
{
    QModelIndex userIndex = userModel->getSelectionModel()->currentIndex();

    int selectedUserLine = userIndex.row();
    QSqlRecord selectedUserRecord = userModel->record(selectedUserLine);
    QSqlField userField = selectedUserRecord.field(0);
    QString idClient = userField.value().toString();
    userField = selectedUserRecord.field(1);
    QString nomClient = userField.value().toString();

    QModelIndex accountIndex = accountModel->getSelectionModel()->currentIndex();
    // -
    int selectedAccountLine = accountIndex.row();
    QSqlRecord selectedAccountRecord = accountModel->record(selectedAccountLine);
    QSqlField accountField = selectedAccountRecord.field(0);
    QString accountId = accountField.value().toString();

    accountField = selectedAccountRecord.field(2);
    QString number = accountField.value().toString();

    accountField = selectedAccountRecord.field(3);
    QString type = accountField.value().toString();

    accountField = selectedAccountRecord.field(4);
    QString balance = accountField.value().toString();

    accountField = selectedAccountRecord.field(5);
    QString statut = accountField.value().toString();

    uiAccount.updateTitle (nomClient);
    uiListAccount.hide();
    uiAccount.show();
    uiAccount.populate(accountId, idClient, number, type, balance, statut);

    uiAccount.deactivateCreate();
}

void Controller::onOuvrir_UIListAccount()
{
    QModelIndex index = accountModel->getSelectionModel()->currentIndex();
    if (index.isValid() == false)
    {
        uiClient.warning("Ouverture de vos comptes",
                         "Veuillez selectionner un de vos comptes svp ...");
    }
    else
    {
        uiListAccount.hide();
        uiListTransaction.setTableViewModel(transactionModel);
        uiListTransaction.show();
        service.listerLesTransactionsDuCompte();

        QModelIndex userIndex = userModel->getSelectionModel()->currentIndex();
        // -
        int selectedUserLine = userIndex.row();
        QSqlRecord selectedUserRecord = userModel->record(selectedUserLine);

        int selectedAccountLine = index.row();
        QSqlRecord selectedAccountRecord = accountModel->record(selectedAccountLine);

        QSqlField accountField = selectedAccountRecord.field(2);
        QString accountNumber = accountField.value().toString();
//        uiListTransaction.updateTitle(nomClient, "Les transactions effectuées sur le compte : " + accountNumber);
        uiListTransaction.updateTitle(currentClient.getNom(), "Les transactions effectuées sur le compte : " + accountNumber);

        uiListTransaction.top();
    }
}

void Controller::onClose_UIListAccount()
{
    uiListAccount.hide();        
    uiListClient.show();
}

void Controller::onGeler_UIListAccount()
{
    QModelIndex accountIndex = accountModel->getSelectionModel()->currentIndex();

    if (!accountIndex.isValid()) {
        // Aucun compte sélectionné
        uiListAccount.warning("Gel du compte", "Veuillez sélectionner un compte.");
        return;
    }

    // Récupérer l'ID du compte sélectionné
    int selectedAccountLine = accountIndex.row();
    QSqlRecord selectedAccountRecord = accountModel->record(selectedAccountLine);
    QSqlField accountField = selectedAccountRecord.field(0);
    int accountId = accountField.value().toInt();

    // Appeler le service pour geler le compte
    bool gelerSuccess = service.gelerCompte(accountId);

    if (gelerSuccess) {
        uiListAccount.information("Gel du compte", "Le compte a été gelé avec succès.");
        reloadAccounts();
    } else {
        uiListAccount.critical("Gel du compte", "Une erreur s'est produite lors du gel du compte.");
    }
}

/*
 * Les slots de la fenêtre UIListTransaction
 */
void Controller::onClose_UIListTransaction()
{
    uiListTransaction.close();
    if (connectedUser.getRole().compare("CLIENT") == 0)
        uiClient.show();
    else if (connectedUser.getRole().compare("GESTIONNAIRE") == 0)
        uiListAccount.show();
}

void Controller::onGoing_UIListTransaction()
{
    uiListTransaction.close();
    uiListVirement.setTableViewModel(transactionModel);
    uiListVirement.show();

    //Recuperation de l'idCompte
    QModelIndex index = accountModel->getSelectionModel()->currentIndex();
    int selectedAccountLine = index.row();
    QSqlRecord selectedAccountRecord = accountModel->record(selectedAccountLine);
    QSqlField accountField = selectedAccountRecord.field(0);
    int accountId = accountField.value().toInt();

    service.listerLesVirementDuCompte(accountId);
    uiListVirement.updateTitle(currentClient.getNom());
    uiListVirement.top();
}

void Controller::roleButton_UIListTransaction()
{
    QString role = connectedUser.getRole();
    if (role.compare("GESTIONNAIRE") == 0)
    {
        uiListTransaction.showButton();
    }
    else
    {
        uiListTransaction.hideButton();
    }
}

/*
 * Les slots de la fenêtre UIListVirement
 */
void Controller::onClose_UIListVirement()
{
    uiListVirement.close();
    uiListTransaction.show();
    reloadTransactions();
}

void Controller::onInspecter_UIListVirement()
{
    QModelIndex index = accountModel->getSelectionModel()->currentIndex();

    if (!index.isValid()) {
        uiListVirement.warning("Inspection du virement", "Veuillez sélectionner un virement.");
        return;
    }

    int selectedRow = index.row();
    QSqlRecord selectedRecord = transactionModel->record(selectedRow);

    // Récupérer les informations du virement à partir du modèle
    int idTransaction = selectedRecord.field("id").value().toInt();
    QString type = selectedRecord.field("type").value().toString();
    QString date = selectedRecord.field("date").value().toString();
    QString statutTransac = selectedRecord.field("statut").value().toString();
    QString compteTire = selectedRecord.field("numeroCompteTire").value().toString();
    QString compteBeneficiaire = selectedRecord.field("numeroCompteBeneficiaire").value().toString();
    double montant = selectedRecord.field("montant").value().toDouble();

    // Récupérer les informations des comptes (solde et statut)
    double soldeTire = service.getAccountBalance(compteTire);
    QString statutTire = service.getAccountStatus(compteTire);
    double soldeBeneficiaire = service.getAccountBalance(compteBeneficiaire);
    QString statutBeneficiaire = service.getAccountStatus(compteBeneficiaire);

    // Remplir l'interface UIInspectAccount avec les informations
    uiInspectAccount.reinit();
    uiInspectAccount.populateInfoVirement(QString::number(idTransaction), type, date, statutTransac, compteTire, compteBeneficiaire, QString::number(montant));
    uiInspectAccount.populateInfoComp(compteTire, QString::number(soldeTire), statutTire, compteBeneficiaire, QString::number(soldeBeneficiaire), statutBeneficiaire);

    // Afficher l'interface UIInspectAccount
    uiListVirement.close();
    uiInspectAccount.show();

//    currentVirementId = idTransaction; // Stocke l'ID pour les actions suivantes
}

/*
 * Les slots de la fenêtre UIInspectAccount
 */
void Controller::onClose_UIInspectAccount()
{
    uiInspectAccount.reinit();
    uiInspectAccount.close();
    uiListVirement.show();
    reloadAccounts();
}

void Controller::onApprouver_UIInspectAccount()
{
    // Récupérer l'ID du compte sélectionné
    QString compteTire = uiInspectAccount.getCompteTire();
    QString compteBeneficiaire = uiInspectAccount.getCompteBeneficiaire();
    double montant = uiInspectAccount.getMontant().toDouble();

    // Appeler le service pour approver le virement
    service.approuverVirement(compteTire, compteBeneficiaire, montant);
    uiInspectAccount.information("Virement Approuve", "La transaction a été approuve avec succès.");
    uiInspectAccount.reinit();
    uiInspectAccount.close();
    uiListAccount.show();
    reloadAccounts();
}

void Controller::onRejeter_UIInspectAccount()
{   
    // Récupérer l'ID du compte sélectionné
    int idTransaction = uiInspectAccount.getIdTransaction().toInt();

    // Appeler le service pour geler le compte
    bool rejet = service.rejeterVirement(idTransaction);

    if (rejet) {
        uiInspectAccount.information("Virement Rejette", "La transaction a été rejette avec succès.");
        uiInspectAccount.reinit();
        uiInspectAccount.close();
        uiListTransaction.show();
        reloadTransactions();
    } else {
        uiInspectAccount.critical("Virement Rejette", "Une erreur s'est produite");
        uiInspectAccount.close();
    }

}

/*
 * Les slots de la fenêtre UIAccount
 */
void Controller::onCreate_UIAccount()
{
    QMap<QString, QString> input;
    bool ok = true;

    QString idClient = uiAccount.getIdClient();
    input.insert("idClient", idClient);
    input.insert("type", uiAccount.getType());
    QString statut = uiAccount.getStatut(); // Récupérer le statut
    input.insert("statut", statut); // Ajouter le statut à la QMap

    QString accountNumber = uiAccount.getAccountNumber();
    if (accountNumber.isEmpty()) {
        uiClient.critical("Contrôle de saisie", "Le numéro de compte n'est pas renseigné !!");
        ok = false;
    } else {
        input.insert("number", accountNumber);
        QString balance = uiAccount.getBalance();
        if (balance.isEmpty()) {
            uiClient.critical("Contrôle de saisie", "Le solde initial n'est pas renseigné !!");
            ok = false;
        } else {
            input.insert("balance", balance);
        }
    }

    if (ok) {
        service.ajouterUnCompte(input);
        uiAccount.information("Fin de la transaction", "Compte ajouté avec succès.");
        uiAccount.populate("-1", idClient, "", "COURANT", "0", "ACTIF");
    }
}

void Controller::onUpdate_UIAccount()
{
    QMap<QString, QString> input;
    bool ok = true;

    QString accountId = uiAccount.getAccountId();
    input.insert("accountId", accountId);

    QString idClient = uiAccount.getIdClient();
    input.insert("idClient", idClient);

    QString balance = uiAccount.getBalance();
    input.insert("balance", balance);

    input.insert("type", uiAccount.getType());
    QString statut = uiAccount.getStatut(); // Récupérer le statut
    input.insert("statut", statut); // Ajouter le statut à la QMap

    QString accountNumber = uiAccount.getAccountNumber();
    if (accountNumber.isEmpty()) {
        uiClient.critical("Contrôle de saisie", "Le numéro de compte n'est pas renseigné !!");
        ok = false;
    } else {
        input.insert("number", accountNumber);
    }

    if (ok) {
        service.modifierUnCompte(input);
        uiAccount.information("Fin de l'opération", "Compte modifié avec succès.");
        uiAccount.hide();
        uiListAccount.show();
        uiListAccount.top();
        reloadAccounts();
    }
}

void Controller::onClose_UIAccount()
{
    uiAccount.hide();
    uiListAccount.show();
    reloadAccounts();
}

/*
 * Les slots de la fenêtre UISettings
 */
void Controller::onSave_UISettings()
{
    // Récupérer les valeurs des paramètres depuis l'interface
    int transactionLimit = uiSettings.getTransactionLimit();
    int minAmount = uiSettings.getMinimumAmount();
    int maxAmount = uiSettings.getMaximumAmount();
    bool notificationsEnabled = uiSettings.getNotifications();

    // Mettre à jour les paramètres dans la base de données
    bool success = service.updateSystemSettings(transactionLimit, minAmount, maxAmount, notificationsEnabled);

    if (success) {
        uiSettings.information("Paramètres système", "Les paramètres ont été enregistrés avec succès.");
        uiSettings.hide();
        uiUser.show();
    } else {
        uiSettings.critical("Paramètres système", "Une erreur est survenue lors de l'enregistrement des paramètres.");
    }
}

void Controller::onQuit_UISettings()
{
    uiSettings.hide();
    executeUserList();
}

void Controller::onQuit_UIAdminNotif()
{
    uiAdminNotif.hide();
    executeUserList();
}

void Controller::onQuit_UIGerantNotif()
{
    uiGerantNotif.hide();
    executeClientList();
}

/*
 * Les slots de la fenêtre UIMessage
 */

void Controller::onSend_UIMessage()
{
    int senderId = connectedUser.getId();
    QString emailReceiver = uiMessage.getSelectedReceiverId();
    int receiverId = service.getEmailId(emailReceiver);
    QString subject = uiMessage.getMessageSubject();
    QString content = uiMessage.getMessageContent();

    if (subject.isEmpty() || content.isEmpty()) {
        uiMessage.warning("Envoi impossible", "L'objet et le contenu du message sont obligatoires.");
        return;
    }

    // Enregistrer le message dans la base de données en utilisant la méthode service existante
    if (service.envoyerMessage(senderId, receiverId, subject, content)) {
        uiMessage.information("Envoi réussi", "Votre message a été envoyé avec succès.");
        uiMessage.clearMessageForm();

        service.listerMessagesEnvoyes(connectedUser.getId());
        uiMessage.getSentMessagesView()->setModel(messageModel);
    } else {
        uiMessage.critical("Erreur", "Une erreur est survenue lors de l'envoi du message.");
    }
}

void Controller::onRefresh_UIMessage()
{
    /*int activeTab = uiMessage.tabWidgetMessages->currentIndex();

    if (activeTab == 1) { // Messages reçus
        service.listerMessagesRecus(connectedUser.getId());
        uiMessage.getReceivedMessagesView()->setModel(messageModel);
    } else if (activeTab == 2) { // Messages envoyés
        service.listerMessagesEnvoyes(connectedUser.getId());
        uiMessage.getSentMessagesView()->setModel(messageModel);
    }*/
}

void Controller::onQuit_UIMessage()
{
    // Fermer la fenêtre des messages et revenir à la fenêtre utilisateur
    uiMessage.hide();
    executeUserList();
}

void Controller::onTabChanged_UIMessage(int tabIndex)
{
    if (tabIndex == 0) { // Nouveau message
        uiMessage.clearMessageForm();

        // Actualiser la liste des destinataires possibles
        uiMessage.clearRecipients();

        /*QList<User> users = service.listerUtilisateursPourMessage();
        for (const User &user : users) {
            if (user.getId() != connectedUser.getId()) {
                QString roleLabel = user.getRole() == CLIENT ? "Client" :
                                   (user.getRole() == GESTIONNAIRE ? "Gestionnaire" : "Administrateur");
                uiMessage.addReceiver(user.getId(), user.getNom(), roleLabel);
            }
        }*/
    } else if (tabIndex == 1) { // Messages reçus
        service.listerMessagesRecus(connectedUser.getId());
        uiMessage.getReceivedMessagesView()->setModel(messageModel);
    } else if (tabIndex == 2) { // Messages envoyés
        service.listerMessagesEnvoyes(connectedUser.getId());
        uiMessage.getSentMessagesView()->setModel(messageModel);
    }
}

void Controller::onOpenMessage_UIMessage(QModelIndex index)
{
    int messageId = messageModel->data(messageModel->index(index.row(), 0)).toInt();

    Message message = service.lireMessage(messageId);

    QTableView* currentView = qobject_cast<QTableView*>(QObject::sender());
    bool isReceivedMessage = (currentView == uiMessage.getReceivedMessagesView());

    if (isReceivedMessage && !message.getIsRead()) {
        service.marquerMessageCommeLu(messageId, true);
    }

    QString senderName;
    /*if (isReceivedMessage) {
        User sender = service.getUser(message.getSenderId());
        senderName = sender.getNom();
    } else {
        User receiver = service.getUser(message.getReceiverId());
        senderName = "À: " + receiver.getNom();
    }*/

    // Afficher les détails du message
    QDateTime date = QDateTime::currentDateTime();
    uiMessage.viewMessageDetails(senderName, message.getSubject(),
                               message.getContent(), date.toString("dd/MM/yyyy hh:mm"));
}

void Controller::onReply_UIMessage()
{
    /*int activeTab = uiMessage.tabWidgetMessages->currentIndex();
    if (activeTab != 3) {
        return; // Pas sur l'onglet de détail du message
    }

    int messageId = uiMessage.getSelectedMessageId();
    if (messageId == -1) {
        return;
    }

    Message originalMessage = service.getMessage(messageId);

    uiMessage.tabWidgetMessages->setCurrentIndex(0);

    for (int i = 0; i < uiMessage.comboBoxReceiver->count(); i++) {
        if (uiMessage.comboBoxReceiver->itemData(i).toInt() == originalMessage.getSenderId()) {
            uiMessage.comboBoxReceiver->setCurrentIndex(i);
            break;
        }
    }

    QString replySubject = "Re: " + originalMessage.getSubject();
    uiMessage.lineEditSubject->setText(replySubject);

    QString replyContent = "\n\n----- Message original -----\n" + originalMessage.getContent();
    uiMessage.textEditMessageContent->setText(replyContent);

    uiMessage.textEditMessageContent->moveCursor(QTextCursor::Start);*/
}

Controller::~Controller()
{
    qDebug("Controller Destroyed...");

    delete userModel;
}
