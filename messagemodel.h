#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include "dbmanager.h"
#include "message.h"
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QModelIndex>

class MessageModel : public QSqlQueryModel
{
public:
    MessageModel();
    ~MessageModel() {}

    QItemSelectionModel* getSelectionModel() { return selectionModel; }

    bool create(Message message);
    Message read(int id);
    bool update(Message message);
    bool remove(int id);

    void readAllReceivedMessages(int userId);
    void readAllSentMessages(int userId);
    void markAsRead(int messageId);
    int getUnreadMessageCount(int userId);

    // Helper methods
    void setInboxHeaderTitle();
    void setSentHeaderTitle();

private:
    DBManager* dbManager;
    QItemSelectionModel* selectionModel;
};

#endif // MESSAGEMODEL_H
