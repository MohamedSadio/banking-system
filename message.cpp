#include "message.h"

Message::Message() : id(-1), senderId(-1), receiverId(-1), isRead(false) {}

Message::Message(int senderId, int receiverId, QString subject, QString content)
    : id(-1), senderId(senderId), receiverId(receiverId), subject(subject), content(content),
      isRead(false) {
}

Message::Message(int senderId, int receiverId, QString subject, QString content, bool isRead)
    : senderId(senderId), receiverId(receiverId), subject(subject), content(content), isRead(isRead) {}

Message::Message(int id, int senderId, int receiverId, QString subject, QString content,
                 bool isRead)
    : id(id), senderId(senderId), receiverId(receiverId), subject(subject), content(content),
      isRead(isRead) {
}
