#include "adminnotifmodel.h"

AdminNotifModel::AdminNotifModel()
{
    selectionModel = new QItemSelectionModel(this);
    dbManager = DBManager::getInstance();
}

void AdminNotifModel::create(AdminNotif notif)
{
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("INSERT INTO admin_notification "
                  "(message, typeNotif, date) VALUES "
                  "(:message, :typeNotif, :date)");

    query.bindValue(":message", notif.getMessage());
    query.bindValue(":typeNotif", notif.getTypeNotif());
    query.bindValue(":date", notif.getDate());

    query.exec();
    dbManager->close();

    readAll();
}

AdminNotif AdminNotifModel::read(int id)
{
    AdminNotif notif;

    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT * FROM admin_notification WHERE id=:id");
    query.bindValue(":id", id);

    query.exec();

    if (query.next()) {
        notif.setId(query.record().field("id").value().toInt());
        notif.setMessage(query.record().field("message").value().toString());
        notif.setTypeNotif(query.record().field("typeNotif").value().toString());
        notif.setDate(query.record().field("date").value().toString());
    } else {
        qDebug() << "Admin notification not found!";
    }

    dbManager->close();

    return notif;
}

QList<AdminNotif> AdminNotifModel::list()
{
    AdminNotif notif;
    QList<AdminNotif> notifs;

    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT * FROM admin_notification ORDER BY id DESC");
    query.exec();

    while (query.next())
    {
        notif.setId(query.record().field("id").value().toInt());
        notif.setMessage(query.record().field("message").value().toString());
        notif.setTypeNotif(query.record().field("typeNotif").value().toString());
        notif.setDate(query.record().field("date").value().toString());

        notifs.push_back(notif);
    }

    dbManager->close();

    return notifs;
}

void AdminNotifModel::readAll()
{
    dbManager->open();

    QSqlDatabase database = dbManager->database();

    this->setQuery("SELECT id, typeNotif, message, date "
                   "FROM admin_notification ORDER BY id DESC", database);
    setHeaderTitle();

    dbManager->close();
}

void AdminNotifModel::setHeaderTitle()
{
    this->setHeaderData(0, Qt::Horizontal, tr("ID"));
    this->setHeaderData(1, Qt::Horizontal, tr("Type"));
    this->setHeaderData(2, Qt::Horizontal, tr("Message"));
    this->setHeaderData(3, Qt::Horizontal, tr("Date"));
}
