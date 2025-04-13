#ifndef UIMESSAGECLIENT_H
#define UIMESSAGECLIENT_H

#include <QMainWindow>
#include <QTableView>
#include "uiabstractwindow.h"
#include "dbmanager.h"
#include <QSqlQuery>


namespace Ui {
class UIMessageClient;
}

class UIMessageClient : public QMainWindow, public UIAbstractWindow
{
    Q_OBJECT

public:
    explicit UIMessageClient(QWidget *parent = nullptr);

    UIMessageClient(QObject* controller);

    void updateTitle(QString libelle);

    QString getMessageContent();

    QString getSelectedReceiverId();
    QString getSelectedReceiverName();

    QString getMessageSubject();
    void setComboxReceiver(QStringList liste);
    void setComboReceiverClient(QString email);

    void addReceiver(int userId, QString username, QString role);

    void clearRecipients();

    QTableView* getReceivedMessagesView();
    QTableView* getSentMessagesView();

    int getSelectedMessageId();

    void clearMessageForm();

    void viewMessageDetails(QString sender, QString subject,
                           QString content, QString date);

    ~UIMessageClient();

private:
    Ui::UIMessageClient *ui;
    DBManager* dbManager;
    QMap<int, QString> m_userMap;
    void loadUsers();
};

#endif // UIMESSAGECLIENT_H
