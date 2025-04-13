#include "messagemodel.h"
#include <QSqlError>

MessageModel::MessageModel()
{
    selectionModel = new QItemSelectionModel(this);
    dbManager = DBManager::getInstance();
}

bool MessageModel::create(Message message) {
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("INSERT INTO t_messages "
                     "(senderId, receiverId, subject, content, isRead) "
                     "VALUES (:senderId, :receiverId, :subject, :content, :isRead)");

    query.bindValue(":senderId", message.getSenderId());
    query.bindValue(":receiverId", message.getReceiverId());
    query.bindValue(":subject", message.getSubject());
    query.bindValue(":content", message.getContent());
    query.bindValue(":isRead", message.getIsRead());

    bool success = query.exec();

    if (!success) {
        qDebug() << "Error creating message: " << query.lastError().text();
    } else {
        qDebug() << "Message created successfully!";
    }

    dbManager->close();
    return success;
}

Message MessageModel::read(int id) {
    Message message;
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT * FROM t_messages WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        message.setId(query.value("id").toInt());
        message.setSenderId(query.value("senderId").toInt());
        message.setReceiverId(query.value("receiverId").toInt());
        message.setSubject(query.value("subject").toString());
        message.setContent(query.value("content").toString());
        message.setIsRead(query.value("isRead").toBool());
    } else {
        qDebug() << "Error reading message: " << query.lastError().text();
    }

    dbManager->close();
    return message;
}

bool MessageModel::update(Message message) {
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("UPDATE t_messages SET "
                  "senderId = :senderId, "
                  "receiverId = :receiverId, "
                  "subject = :subject, "
                  "content = :content, "
                  "isRead = :isRead, "
                  "WHERE id = :id");

    query.bindValue(":id", message.getId());
    query.bindValue(":senderId", message.getSenderId());
    query.bindValue(":receiverId", message.getReceiverId());
    query.bindValue(":subject", message.getSubject());
    query.bindValue(":content", message.getContent());
    query.bindValue(":isRead", message.getIsRead());

    bool success = query.exec();

    if (!success) {
        qDebug() << "Error updating message: " << query.lastError().text();
    } else {
        qDebug() << "Message updated successfully!";
    }

    dbManager->close();
    return success;
}

bool MessageModel::remove(int id) {
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("DELETE FROM t_messages WHERE id = :id");
    query.bindValue(":id", id);

    bool success = query.exec();

    if (!success) {
        qDebug() << "Error deleting message: " << query.lastError().text();
    } else {
        qDebug() << "Message deleted successfully!";
    }

    dbManager->close();
    return success;
}

void MessageModel::readAllReceivedMessages(int userId) {
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT m.id, u.nom AS sender_name, m.subject, m.isRead "
                  "FROM t_messages m "
                  "JOIN t_users u ON m.senderId = u.id "
                  "WHERE m.receiverId = :user_id  ");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qDebug() << "Error fetching received messages: " << query.lastError().text();
    }

    this->setQuery(std::move(query));
    setInboxHeaderTitle();

    dbManager->close();
}

void MessageModel::readAllSentMessages(int userId) {
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT m.id, u.nom AS receiver_name, m.subject, "
                  "CASE WHEN m.isRead = 1 THEN 'Oui' ELSE 'Non' END AS read_status "
                  "FROM t_messages m "
                  "JOIN t_users u ON m.receiverId = u.id "
                  "WHERE m.senderId = :user_id");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qDebug() << "Error fetching sent messages: " << query.lastError().text();
    }

    this->setQuery(std::move(query));
    setSentHeaderTitle();

    dbManager->close();
}

void MessageModel::markAsRead(int messageId) {
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("UPDATE t_messages SET isRead = 1 WHERE id = :id");
    query.bindValue(":id", messageId);

    if (!query.exec()) {
        qDebug() << "Error marking message as read: " << query.lastError().text();
    }

    dbManager->close();
}

int MessageModel::getUnreadMessageCount(int userId) {
    int count = 0;
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT COUNT(*) FROM t_messages "
                  "WHERE receiverId = :user_id AND isRead = 0 AND is_receiver_deleted = 0");
    query.bindValue(":user_id", userId);

    if (query.exec() && query.next()) {
        count = query.value(0).toInt();
    } else {
        qDebug() << "Error counting unread messages: " << query.lastError().text();
    }

    dbManager->close();
    return count;
}

void MessageModel::setInboxHeaderTitle() {
    this->setHeaderData(0, Qt::Horizontal, tr("ID"));
    this->setHeaderData(1, Qt::Horizontal, tr("Expéditeur"));
    this->setHeaderData(2, Qt::Horizontal, tr("Objet"));
    this->setHeaderData(3, Qt::Horizontal, tr("Lu"));
}

void MessageModel::setSentHeaderTitle() {
    this->setHeaderData(0, Qt::Horizontal, tr("ID"));
    this->setHeaderData(1, Qt::Horizontal, tr("Destinataire"));
    this->setHeaderData(2, Qt::Horizontal, tr("Objet"));
    this->setHeaderData(3, Qt::Horizontal, tr("Lu"));
}
