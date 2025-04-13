#include "gerantnotifmodel.h"

GerantNotifModel::GerantNotifModel()
{
    selectionModel = new QItemSelectionModel(this);
    dbManager = DBManager::getInstance();
}

QItemSelectionModel* GerantNotifModel::getSelectionModel()
{
    return selectionModel;
}

void GerantNotifModel::create(GerantNotif notif)
{
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("INSERT INTO gerant_notification (role, typeNotif, referenceId, message, date) "
                  "VALUES (:role, :typeNotif, :referenceId, :message, :date)");

    query.bindValue(":role", notif.getRole());
    query.bindValue(":typeNotif", notif.getTypeNotif());
    query.bindValue(":referenceId", notif.getReferenceId());
    query.bindValue(":message", notif.getMessage());
    query.bindValue(":date", notif.getDate());

    query.exec();
    dbManager->close();

    readAll();
}

GerantNotif GerantNotifModel::read(int id)
{
    GerantNotif notif;

    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT * FROM gerant_notification WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    if (query.next())
    {
        notif.setId(query.value("id").toInt());
        notif.setRole(query.value("role").toString());
        notif.setTypeNotif(query.value("typeNotif").toString());
        notif.setReferenceId(query.value("referenceId").toInt());
        notif.setMessage(query.value("message").toString());
        notif.setDate(query.value("date").toString());
    }

    dbManager->close();
    return notif;
}

QList<GerantNotif> GerantNotifModel::list()
{
    QList<GerantNotif> notifs;

    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT * FROM gerant_notification ORDER BY id DESC");
    query.exec();

    while (query.next())
    {
        GerantNotif notif;
        notif.setId(query.value("id").toInt());
        notif.setRole(query.value("role").toString());
        notif.setTypeNotif(query.value("typeNotif").toString());
        notif.setReferenceId(query.value("referenceId").toInt());
        notif.setMessage(query.value("message").toString());
        notif.setDate(query.value("date").toString());
        notifs.append(notif);
    }

    dbManager->close();
    return notifs;
}

void GerantNotifModel::readAll()
{
    dbManager->open();

    QSqlDatabase database = dbManager->database();
    this->setQuery("SELECT id, role, typeNotif, referenceId, message, date FROM gerant_notification ORDER BY id DESC", database);
    setHeaderTitle();

    dbManager->close();
}

void GerantNotifModel::setHeaderTitle()
{
    this->setHeaderData(0, Qt::Horizontal, tr("ID"));
    this->setHeaderData(1, Qt::Horizontal, tr("Role"));
    this->setHeaderData(2, Qt::Horizontal, tr("Type"));
    this->setHeaderData(3, Qt::Horizontal, tr("Référence"));
    this->setHeaderData(4, Qt::Horizontal, tr("Message"));
    this->setHeaderData(5, Qt::Horizontal, tr("Date"));
}
