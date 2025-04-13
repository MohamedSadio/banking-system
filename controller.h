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
#include "uilistvirement.h"
#include "uiaddclient.h"
#include "uiinspectaccount.h"
#include "uisettings.h"
#include "uiadminnotif.h"
#include "uimessage.h"
#include "uimessagegestionnaire.h"

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
    UIAddClient uiAddClient {this};
    UiListVirement uiListVirement {this};
    UIInspectAccount uiInspectAccount {this};
    UISettings uiSettings {this};
    UIAdminNotif uiAdminNotif {this};
    UIMessage uiMessage {this};
    UIMessageGestionnaire uiMessageGestionnaire {this};

    Role connectedUserType;
    User connectedUser;
    User currentClient;

    UserModel* userModel = new UserModel;
    AccountModel* accountModel = new AccountModel;
    TransactionModel* transactionModel = new TransactionModel;
    NotifModele* notifModel = new NotifModele;
    AdminNotifModel* adminNotifModel = new AdminNotifModel;
    SettingsModel* settingsModel = new SettingsModel;
    MessageModel* messageModel = new MessageModel;

    Service service {userModel, accountModel, transactionModel, settingsModel, adminNotifModel, notifModel, messageModel}; // Le classe service pour déclencher les fonctionnalités

public:
    explicit Controller(QObject* parent = nullptr);
    ~Controller();
    void execute();
    void executeUserList();
    void executeClientList();
    void reloadTransactions();
    void reloadAccounts();

private slots:
    /* Les slots de la fenêtre UIListUser
     *
     */
    void onCreate_UIListUser();
    void onUpdate_UIListUser();
    void onDelete_UIListUser();
    void onClose_UIListUser();
    void onSettings_UIListUser();
    void onNotifs_UIListUser();
    void onMessages_UIListUser();
    void onComboBoxRoleChanged_UIUser();

    /*
     * Les slots de la fenêtre UIUser
     */
    void onCreate_UIUser();
    void onUpdate_UIUser();
    void onClose_UIUser();

    /*
     * Les slots de la fenetre UIAddCLient
     */
    void onCreate_UIAddClient();
    void onClose_UIAddClient();


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
    void onMessages_UIClient();

    /*
     * Les slots de la fenêtre UIListClient
     */
    void onClose_UIListClient();
    void onOuvrir_UIListClient();
    void onMessage_UIListClient();

    /*
     * Les slots de la fenêtre UIListAccount
     */
    void onNouveau_UIListAccount();
    void onModifier_UIListAccount();
    void onOuvrir_UIListAccount();
    void onClose_UIListAccount();
    void onGeler_UIListAccount();

    /*
     * Les slots de la fenêtre UIListTransaction
     */
    void onClose_UIListTransaction();
    void onGoing_UIListTransaction();
    void roleButton_UIListTransaction();

    /*
     * Les slots de la fenêtre UIListVirement
     */
    void onClose_UIListVirement();
    void onInspecter_UIListVirement();

    /*
     * Les slots de la fenêtre UIInspectAccount
     */
    void onClose_UIInspectAccount();
    void onApprouver_UIInspectAccount();
    void onRejeter_UIInspectAccount();

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

    /*
     * Les slots de la fenêtre UISettings
     */
    void onSave_UISettings();
    void onQuit_UISettings();

    /*
     * Les slots de la fenêtre UIAdminNotif
     */
    void onQuit_UIAdminNotif();

    /*
     * Les slots de la fenêtre UIMessage
     */
    void onSend_UIMessage();
    void onQuit_UIMessage();
    void onTabChanged_UIMessage(int);
    void onOpenMessage_UIMessage(QModelIndex index);

    /*
     * Les slots de la fenêtre UIMessageGestionnaire
     */
    void onSend_UIMessageGestionnaire();
    void onQuit_UIMessageGestionnaire();
    void onTabChanged_UIMessageGestionnaire(int);
    void onOpenMessage_UIMessageGestionnaire(QModelIndex index);

};
#endif // CONTROLLER_H

