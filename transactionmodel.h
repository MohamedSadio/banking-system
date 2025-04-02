#ifndef TRANSATIONMODEL_H
#define TRANSATIONMODEL_H
#include "dbmanager.h"
#include "transaction.h"
#include <QtDebug>
#include <QMetaType>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QModelIndex>

class TransactionModel : public QSqlQueryModel
{
private:
    DBManager* dbManager;
    // Permet d'avoir à tout moment les informations
    // sur l'élélement sélectionné sur la vue.
    QItemSelectionModel* selectionModel;

public:
    TransactionModel();
    ~TransactionModel() {}
    QItemSelectionModel* getSelectionModel() { return selectionModel; }
    void create(Transaction transaction);
    void updateStatut(Transaction transaction);
    Transaction read(int id); // Modifier le type de retour à Transaction
    Transaction readByBeneficiary(QString accountNumber);

    QList<Transaction> list();

    // Rafraîchit la collection et la tableView ...
    void readAll();
    void readAll(int accountId);
    void readAllVirement(int accountId);
    void setHeaderTitle();
    void readBy(int clientId);
    bool rejeterTransaction(int idTransaction);
};

#endif // TRANSATIONMODEL_H
