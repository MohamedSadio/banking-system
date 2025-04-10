#include "notifmodele.h"
#include <QSqlError>  // Ajoutez cette ligne

NotifModele::NotifModele()
{
    selectionModel = new QItemSelectionModel(this);
    dbManager = DBManager::getInstance();
}


void NotifModele::create(Notif notif){
    qDebug() << "Début de create()";
    dbManager->open();

    qDebug() << "Base de donnée ouverte";

    if (!dbManager->database().isOpen()) {
        qDebug() << "La base de données n'est pas ouverte!";
        return;
    }

    if (!dbManager) {
            qDebug() << "dbManager est null!";
            return;
        }
    QSqlQuery query(dbManager->database());

    // Corrigez la requête SQL
    query.prepare("INSERT INTO notification "
                  "(message,typeNotif,idClient,date,number) VALUES "
                  "(:message,:typeNotif,:idClient,:date,:number)");

    qDebug() << "Message:" << notif.getMessage();
    qDebug() << "Type:" << notif.getTypeNotif();
    qDebug() << "IdClient:" << notif.getIdClient();
    qDebug() << "Date:" << notif.getDate();
    qDebug() << "Number:" << notif.getNumber();

    query.bindValue(":message", notif.getMessage());
    query.bindValue(":typeNotif", notif.getTypeNotif());
    query.bindValue(":idClient", notif.getIdClient());
    query.bindValue(":date", notif.getDate());
    query.bindValue(":number", notif.getNumber());

    bool success = query.exec();
    if (!success) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
    } else {
        qDebug() << "Notification ajoutée avec succès!";
    }

    dbManager->close();

    readAll(notif.getIdClient());

    qDebug() << "Fin de create()";
}

/*
void NotifModele::create(Notif notif) {
    qDebug() << "Début de create() - version simplifiée";
    // Ne rien faire d'autre
     dbManager->open();
    qDebug() << "Fin de create() - version simplifiée";
}
*/

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

void NotifModele::readAll(int idClient) {
    dbManager->open();

    QSqlDatabase database = dbManager->database();

    this->setQuery("SELECT typeNotif, number, message, date FROM notification WHERE idClient=:idClient", database);
    this->query().bindValue(":idClient", idClient);
    setHeaderTitle();

    dbManager->close();
}

void NotifModele::readAll() {
    dbManager->open();

    QSqlDatabase database = dbManager->database();

    this->setQuery("SELECT typeNotif, number, message, date FROM notification", database);
    setHeaderTitle();

    dbManager->close();
}

void NotifModele::readBy(int idClient) {
    dbManager->open();
    QSqlQuery query(dbManager->database());
    query.prepare("SELECT typeNotif, number, message, date FROM notification WHERE idClient=:idClient");
    query.bindValue(":idClient", idClient);
    query.exec();
    this->setQuery(query);
    setHeaderTitle();
    dbManager->close();
}

void NotifModele::setHeaderTitle() {
    this->setHeaderData(0, Qt::Horizontal, tr("typeNotif"));
    this->setHeaderData(1, Qt::Horizontal, tr("number"));
    this->setHeaderData(2, Qt::Horizontal, tr("message"));
    this->setHeaderData(3, Qt::Horizontal, tr("date"));
}

QVariant NotifModele::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // Pour l'affichage, nous combinons toutes les colonnes
    if (role == Qt::DisplayRole) {
        // Récupérer les colonnes de votre modèle
        QString typeNotif = QSqlQueryModel::data(this->index(index.row(), 0)).toString();
        QString number = QSqlQueryModel::data(this->index(index.row(), 1)).toString();
        QString message = QSqlQueryModel::data(this->index(index.row(), 2)).toString();
        QString date = QSqlQueryModel::data(this->index(index.row(), 3)).toString();

        // Format combiné pour affichage dans le ListView
        return QString("%1 [%2] - %3 (%4)").arg(typeNotif, number, message, date);
    }

    // Pour les autres rôles, utiliser le comportement par défaut
    return QSqlQueryModel::data(index, role);
}
