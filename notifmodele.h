#ifndef NOTIFMODELE_H
#define NOTIFMODELE_H

#include <QtDebug>
#include <QMetaType>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QModelIndex>

#include "notif.h"
#include "dbmanager.h"

class NotifModele : public QSqlQueryModel
{
public:
    NotifModele();
    ~NotifModele(){};
    QItemSelectionModel* getSelectionModel() { return selectionModel; }

    void create(Notif notif);
    Notif read(int id);

    QList<Notif> list();

    void readAll(int clientId);
    void readAll();

    void readBy(int clientId);
    void setHeaderTitle();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    DBManager* dbManager;
    QItemSelectionModel* selectionModel;
};

#endif // NOTIFMODELE_H
