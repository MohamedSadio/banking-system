#include "transactionmodel.h"
#include <QSqlError>

TransactionModel::TransactionModel()
{    
    selectionModel = new QItemSelectionModel(this);
    dbManager = DBManager::getInstance();
}

void TransactionModel::create(Transaction transaction)
{
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("INSERT INTO t_transactions "
                  "(idClient, type, idCompteTire, idCompteBeneficiaire, numeroCompteTire, numeroCompteBeneficiaire, montant, date, statut) VALUES "
                  "(:idClient, :type, :idCompteTire, :idCompteBeneficiaire, :numeroCompteTire, :numeroCompteBeneficiaire, :montant, :date, :statut)");

    query.bindValue(":type", transaction.getType());
    query.bindValue(":idClient", transaction.getIdClient());
    query.bindValue(":idCompteTire", transaction.getIdCompteTire());
    query.bindValue(":idCompteBeneficiaire", transaction.getIdCompteBeneficiaire());
    query.bindValue(":numeroCompteTire", transaction.getNumeroCompteTire());
    query.bindValue(":numeroCompteBeneficiaire", transaction.getNumeroCompteBeneficiaire());
    query.bindValue(":montant", transaction.getMontant());
	query.bindValue(":date", transaction.getDate());
	query.bindValue(":statut", transaction.getStatut());    

    query.exec();
    dbManager->close();

    qDebug("Transaction added successfully !");
    readAll(); // recupère les nouvelles données de la base ...
}

void TransactionModel::updateStatut(Transaction transaction)
{
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("UPDATE t_transactions SET "
                  "statut=:statut "
                  "WHERE id = :id");

    query.bindValue(":id", transaction.getId());
    query.bindValue(":statut", transaction.getStatut());    

    query.exec();
    dbManager->close();

    qDebug("Transaction updated successfully !");
    readAll(); // recupère les nouvelles données de la base ...
}

bool TransactionModel::rejeterTransaction(int idTransaction)
{
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("UPDATE t_transactions SET statut = 'Denied' WHERE id = :idTransaction");
    query.bindValue(":idTransaction", idTransaction);

    bool success = query.exec();

    if (!success) {
        qDebug() << "Erreur lors du gel du compte:" << query.lastError().text();
    }

    dbManager->close();
    return success;
}

Transaction TransactionModel::read(int id)
{    
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT id, type, numeroCompteTire,"
                  " numeroCompteBeneficiaire, montant, date, statut FROM t_transactions WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();

    this->setQuery(query);
    setHeaderTitle();

    dbManager->close();
    qDebug() << "TransactionModel::read() : Transaction with id " << id << " read !";
    Transaction transaction;
    transaction.setId(query.record().field("id").value().toInt());
    transaction.setType(query.record().field("type").value().toString());
    transaction.setNumeroCompteTire(query.record().field("numeroCompteTire").value().toString());
    transaction.setNumeroCompteBeneficiaire(query.record().field("numeroCompteBeneficiaire").value().toString());
    transaction.setMontant(query.record().field("montant").value().toDouble());
    transaction.setDate(query.record().field("date").value().toString());
    transaction.setStatut(query.record().field("statut").value().toString());

    return transaction;
}

Transaction TransactionModel::readByBeneficiary(QString accountNumber)
{
    dbManager->open();
    QSqlQuery query(dbManager->database());
    query.prepare("SELECT id, type, numeroCompteTire,"
                  " numeroCompteBeneficiaire, montant, date, statut FROM t_transactions WHERE numeroCompteBeneficiaire=:accountNumber");
    query.bindValue(":accountNumber", accountNumber);
    query.exec();
    Transaction transaction;
    if (query.next())
    {
        transaction.setId(query.record().field("id").value().toInt());
        transaction.setType(query.record().field("type").value().toString());
        transaction.setNumeroCompteTire(query.record().field("numeroCompteTire").value().toString());
        transaction.setNumeroCompteBeneficiaire(query.record().field("numeroCompteBeneficiaire").value().toString());
        transaction.setMontant(query.record().field("montant").value().toDouble());
        transaction.setDate(query.record().field("date").value().toString());
        transaction.setStatut(query.record().field("statut").value().toString());
    }
    dbManager->close();
    return transaction;
}

QList<Transaction> TransactionModel::list()
{
    Transaction transaction;
    QList<Transaction> transactions;

    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT * FROM t_transactions WHERE 1");
    query.exec();

    while (query.next())
    {
        transaction.setId(query.record().field("id").value().toInt());
        transaction.setId(query.record().field("idClient").value().toInt());
		transaction.setType(query.record().field("type").value().toString());
        transaction.setIdCompteTire(query.record().field("idCompteTire").value().toInt());
		transaction.setIdCompteBeneficiaire(query.record().field("idCompteBeneficiaire").value().toInt());
        transaction.setNumeroCompteTire(query.record().field("numeroCompteTire").value().toString());
		transaction.setNumeroCompteBeneficiaire(query.record().field("numeroCompteBeneficiaire").value().toString());		
        transaction.setMontant(query.record().field("montant").value().toDouble());
        transaction.setDate(query.record().field("date").value().toString());
        transaction.setStatut(query.record().field("statut").value().toString());
        
        transactions.push_back(transaction);
    }

    dbManager->close();

    return transactions;
}

void TransactionModel::readAll()
{
    dbManager->open();

    QSqlDatabase database = dbManager->database();

    this->setQuery("SELECT id, type, numeroCompteTire,"
					" numeroCompteBeneficiaire, montant, date, statut"
					" FROM t_transactions", database);
    setHeaderTitle();

    dbManager->close();
}

void TransactionModel::readAll(int accountId)
{
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT id, type, numeroCompteTire,"
                  " numeroCompteBeneficiaire, montant, date, statut FROM t_transactions WHERE idCompteTire=:accountId OR idCompteBeneficiaire=:accountId");
    query.bindValue(":accountId", accountId);
    query.exec();

    this->setQuery(query);
    setHeaderTitle();

    dbManager->close();
}

void TransactionModel::readAllVirement(int accountId)
{
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT id, type, numeroCompteTire, numeroCompteBeneficiaire, montant, date, statut "
                  "FROM t_transactions "
                  "WHERE (idCompteTire = :accountId OR idCompteBeneficiaire = :accountId) "
                  "AND type = 'VIREMENT' "
                  "AND statut = 'Waiting'");
    query.bindValue(":accountId", accountId);
    query.exec();

    this->setQuery(query);
    setHeaderTitle();

    dbManager->close();
}

void TransactionModel::readBy(int clientId)
{
    dbManager->open();
    QSqlQuery query(dbManager->database());

    query.prepare("SELECT id, type, numeroCompteTire,"
                  " numeroCompteBeneficiaire, montant, date, statut FROM t_transactions WHERE idClient=:idClient");
    query.bindValue(":idClient", clientId);
    query.exec();

    this->setQuery(query);
    setHeaderTitle();

    dbManager->close();
}

// void TransactionModel::read(int idTransaction)
// {
//     dbManager->open();
//     QSqlQuery query(dbManager->database());

//     query.prepare("SELECT id, type, numeroCompteTire,"
//                   " numeroCompteBeneficiaire, montant, date, statut FROM t_transactions WHERE id=:idTransaction");
//     query.bindValue(":idTransaction", idTransaction);
//     query.exec();

//     this->setQuery(query);
//     setHeaderTitle();

//     dbManager->close();
//     qDebug() << "TransactionModel::read() : Transaction with id " << idTransaction << " read !";
// }

void TransactionModel::setHeaderTitle()
{
    this->setHeaderData(0, Qt::Horizontal, tr("Id Transaction"));
    this->setHeaderData(1, Qt::Horizontal, tr("Type"));
    this->setHeaderData(2, Qt::Horizontal, tr("Compte Tire"));
    this->setHeaderData(3, Qt::Horizontal, tr("Compte Beneficiaire"));
    this->setHeaderData(4, Qt::Horizontal, tr("Montant"));
    this->setHeaderData(5, Qt::Horizontal, tr("Date"));
    this->setHeaderData(6, Qt::Horizontal, tr("Statut"));
}
