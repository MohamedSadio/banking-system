#ifndef NOTIF_H
#define NOTIF_H
#include <QString>
#include <QDateTime>

class Notif
{
public:
    Notif(int idClient,QString number,QString typeNotif,QString message,QString date);
    Notif(int id,QString typeNotif,QString message,QString date);
    Notif(int id,int idClient,QString number,QString typeNotif,QString message,QString date);

    Notif();

    int getId(){return  id;}
    int getIdClient () {return idClient;}
    QString getNumber(){return  number;}
    QString getTypeNotif(){return typeNotif;}
    QString getMessage(){return message;}
    QString getDate(){return date;}

    void setId(int id){this->id = id > 0 ? id : this->id;}
    void setIdClient (int idClient) {this->idClient = idClient > 0 ? idClient : this->idClient;}
    void setNumber (QString number) {this->number = number;}
    void setTypeNotif (QString typeNotif) {this->typeNotif= typeNotif;}
    void setMessage(QString message){this->message = message;}
    void setDate(QString date){this->date = date;}

private:
    int id;
    int idClient;
    QString number;
    QString typeNotif;
    QString message;
    QString date;
};

#endif // NOTIF_H
