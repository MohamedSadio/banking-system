#ifndef ADMINNOTIF_H
#define ADMINNOTIF_H

#include <QString>

class AdminNotif
{
public:
    AdminNotif();

    AdminNotif(QString typeNotif, QString message, QString date);
    AdminNotif(int id, QString typeNotif, QString message, QString date);

    int getId() { return id; }
    QString getTypeNotif() { return typeNotif; }
    QString getMessage() { return message; }
    QString getDate() { return date; }

    void setId(int id) { this->id = id > 0 ? id : this->id; }
    void setTypeNotif(QString typeNotif) { this->typeNotif = typeNotif; }
    void setMessage(QString message) { this->message = message; }
    void setDate(QString date) { this->date = date; }

private:
    int id;
    QString typeNotif;
    QString message;
    QString date;
};

#endif // ADMINNOTIF_H
