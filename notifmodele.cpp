#include "notifmodele.h"

NotifModele::NotifModele()
{

}

void NotifModele::create(Notif notif){
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("INSERT INTO notification"
                  "(message,typeNotif,idClient,date,number) VALUES"
                  ":message,:typeNotif,:idClient,:date,:number");

    query.bindValue(":message",notif.getMessage());
    query.bindValue(":typeNotif",notif.getTypeNotif());
    query.bindValue(":idClient",notif.getIdClient());
    query.bindValue(":date",notif.getDate());
    query.bindValue(":number",notif.getNumber());

    query.exec();
    dbManager->close();

    //qDebug("Account added successfully !");
    readAll(notif.getIdClient());
}

Notif NotifModele::read(int id){
    Notif notif;

    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT * FROM notification WHERE id=:id");
    query.bindValue(":id", id);

    query.exec();

    if (query.next()){
        //qDebug () << "account found!";

        notif.setId(query.record().field("id").value().toInt());
        notif.setMessage(query.record().field("message").value().toString());
        notif.setTypeNotif(query.record().field("typeNotif").value().toString());
        notif.setIdClient(query.record().field("idClient").value().toInt());
        notif.setDate(query.record().field("date").value().toString());
        notif.setNumber(query.record().field("number").value().toString());
    }else
    {
        qDebug () << "account not found!";
    }

    dbManager->close();

    return notif;
}

QList<Notif> NotifModele::list(){
    Notif notif;
    QList<Notif> notifs;

    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT * FROM notification WHERE 1");
    query.exec();

    while (query.next())
    {
        notif.setId(query.record().field("id").value().toInt());
        notif.setMessage(query.record().field("message").value().toString());
        notif.setTypeNotif(query.record().field("typeNotif").value().toString());
        notif.setIdClient(query.record().field("idClient").value().toInt());
        notif.setDate(query.record().field("date").value().toString());
        notif.setNumber(query.record().field("number").value().toString());

        notifs.push_back(notif);
    }

    dbManager->close();

    return notifs;
}

void NotifModele::readAll(int idClient){
    dbManager->open();

    QSqlDatabase database = dbManager->database();

    this->setQuery("SELECT id,message,typeNotif,idClient,date,number"
                   "FROM notification WHERE idClient=:idClient",database);
    this->query().bindValue(":clientId", idClient);
    setHeaderTitle();

    dbManager->close();
}

void NotifModele::readAll(){
    dbManager->open();

    QSqlDatabase database = dbManager->database();

    this->setQuery("SELECT id,message,typeNotif,idClient,date,number"
                   "FROM notification",database);
    setHeaderTitle();

    dbManager->close();
}

void NotifModele::readBy(int idClient){
    dbManager->open();
    QSqlQuery query(dbManager->database());
    query.prepare("SELECT id,message,typeNotif,idClient,date,number"
                  "FROM notification WHERE idClient=:idClient");
    query.bindValue(":clientId", idClient);
    query.exec();
    this->setQuery(query);
    setHeaderTitle();
    dbManager->close();
}

void NotifModele::setHeaderTitle(){
    this->setHeaderData(0, Qt::Horizontal, tr("typeNotif"));
    this->setHeaderData(0, Qt::Horizontal, tr("number"));
    this->setHeaderData(0, Qt::Horizontal, tr("message"));
    this->setHeaderData(0, Qt::Horizontal, tr("date"));
}
