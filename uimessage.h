#ifndef UIMESSAGE_H
#define UIMESSAGE_H

#include <QMainWindow>
#include <QTableView>
#include "uiabstractwindow.h"
#include "dbmanager.h"
#include <QSqlQuery>

namespace Ui {
class UIMessage;
}

class UIMessage : public QMainWindow, public UIAbstractWindow
{
    Q_OBJECT

public:
    explicit UIMessage(QWidget *parent = nullptr);
    UIMessage(QObject* controller);
    void updateTitle(QString libelle);

    QString getMessageContent();

    int getSelectedReceiverId();
    QString getSelectedReceiverName();

    QString getMessageSubject();

    void addReceiver(int userId, QString username, QString role);

    void clearRecipients();

    QTableView* getReceivedMessagesView();
    QTableView* getSentMessagesView();

    int getSelectedMessageId();

    void clearMessageForm();

    void viewMessageDetails(QString sender, QString subject,
                           QString content, QString date);

    ~UIMessage();

private:
    Ui::UIMessage *ui;
    DBManager* dbManager;
    QMap<int, QString> m_userMap;
    void loadUsers();
};

#endif // UIMESSAGE_H
