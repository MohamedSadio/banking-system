#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>

class Message
{
public:
    Message();
    Message(int senderId, int receiverId, QString subject, QString content);
        Message(int id, int senderId, int receiverId, QString subject, QString content,
                bool isRead);

        // Getters
        int getId() { return id; }
        int getSenderId() { return senderId; }
        int getReceiverId() { return receiverId; }
        QString getSubject() { return subject; }
        QString getContent() { return content; }
        bool getIsRead() { return isRead; }

        // Setters
        void setId(int value) { id = value; }
        void setSenderId(int value) { senderId = value; }
        void setReceiverId(int value) { receiverId = value; }
        void setSubject(QString value) { subject = value; }
        void setContent(QString value) { content = value; }
        void setIsRead(bool value) { isRead = value; }

private:
    int id;
    int senderId;
    int receiverId;
    QString subject;
    QString content;
    bool isRead;
};

#endif // MESSAGE_H
