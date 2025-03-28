#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QInputDialog>
#include <QDir>

#include "service.h"
#include "uiloginin.h"
#include "uiuser.h"
#include "uilistuser.h"
#include "uilistclient.h"
#include "uilistaccount.h"
#include "uilisttransaction.h"
#include "uiclient.h"
#include "uiaccount.h"
#include "uinotif.h"

class Controller : public QObject
{
    Q_OBJECT

private:
    // Le contrôleur dispose des références aux fenêtres qu'il gère
    UILoginIn uiLoginIn {this};
    UIUser uiUser {this};
    UIListUser uiListUser {this};
    UIListClient uiListClient {this};
    UIListAccount uiListAccount {this};
    UIClient uiClient {this};
    UIListTransaction uiListTransaction {this};
    UIAccount uiAccount {this};
    UINotif uiNotif{this};

    Role connectedUserType;
    User connectedUser;

    UserModel* userModel = new UserModel;
    AccountModel* accountModel = new AccountModel;
    TransactionModel* transactionModel = new TransactionModel;
    NotifModele* notifModel = new NotifModele;

    Service service {userModel, accountModel, transactionModel}; // Le classe service pour déclencher les fonctionnalités

public:
    explicit Controller(QObject* parent = nullptr);
    ~Controller();
    void execute();

private slots:
    /* Les slots de la fenêtre UIListUser
     *
     */
    void onUpdate_UIListUser();
    void onDelete_UIListUser();
    void onClose_UIListUser();
    void onComboBoxRoleChanged_UIUser();

    /*
     * Les slots de la fenêtre UIUser
     */
    void onCreate_UIUser();
    void onFind_UIUser();
    void onUpdate_UIUser();
    void onList_UIUser();
    void onClose_UIUser();

    /*
     * Les slots de la fenêtre UILoginIn
     */
    void onSubmit_UILoginIn();
    void onExit_UILoginIn();

    /*
     * Les slots de la fenêtre UIClient
     */
    void onClose_UIClient();
    void onOuvrir_UIClient();
    void onVirement_UIClient();
    void onRetrait_UIClient();
    void onVersement_UIClient();
    void onHistorique_UIClient();
    void onNotification_UIClient();
    void onOK_UIClient();
    void onCancel_UIClient();

    /*
     * Les slots de la fenêtre UIListClient
     */
    void onClose_UIListClient();
    void onOuvrir_UIListClient();

    /*
     * Les slots de la fenêtre UIListAccount
     */
    void onNouveau_UIListAccount();
    void onModifier_UIListAccount();
    void onOuvrir_UIListAccount();
    void onClose_UIListAccount();

    /*
     * Les slots de la fenêtre UIListTransaction
     */
    void onClose_UIListTransaction();

    /*
     * Les slots de la fenêtre UIAccount
     */
    void onCreate_UIAccount();
    void onUpdate_UIAccount();
    void onClose_UIAccount();

    /*
     * Les slots de la fenêtre UINotif
     */
    void onClose_UINotif();
};
#endif // CONTROLLER_H

