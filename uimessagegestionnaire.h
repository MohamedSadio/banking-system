#ifndef UIMESSAGEGESTIONNAIRE_H
#define UIMESSAGEGESTIONNAIRE_H

#include <QMainWindow>
#include <QTableView>
#include "uiabstractwindow.h"
#include "dbmanager.h"
#include <QSqlQuery>

namespace Ui {
class UIMessageGestionnaire;
}

class UIMessageGestionnaire : public QMainWindow, public UIAbstractWindow
{
    Q_OBJECT

public:
    explicit UIMessageGestionnaire(QWidget *parent = nullptr);
    UIMessageGestionnaire(QObject* controller);
    void updateTitle(QString libelle);

    QString getMessageContent();

    QString getSelectedReceiverId();
    QString getSelectedReceiverName();

    QString getMessageSubject();
    void setComboxReceiver(QStringList liste);

    void addReceiver(int userId, QString username, QString role);

    void clearRecipients();

    QTableView* getReceivedMessagesView();
    QTableView* getSentMessagesView();

    int getSelectedMessageId();

    void clearMessageForm();

    void viewMessageDetails(QString sender, QString subject,
                           QString content, QString date);
    ~UIMessageGestionnaire();

private:
    Ui::UIMessageGestionnaire *ui;
    DBManager* dbManager;
};

#endif // UIMESSAGEGESTIONNAIRE_H
