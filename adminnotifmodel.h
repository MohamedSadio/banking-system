#ifndef ADMINNOTIFMODEL_H
#define ADMINNOTIFMODEL_H

#include <QtDebug>
#include <QMetaType>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QModelIndex>

#include "adminnotif.h"
#include "dbmanager.h"

class AdminNotifModel : public QSqlQueryModel
{
public:
    AdminNotifModel();
    QItemSelectionModel* getSelectionModel() { return selectionModel; }

    void create(AdminNotif notif);
    AdminNotif read(int id);
    QList<AdminNotif> list();
    void readAll();
    void setHeaderTitle();

private:
    DBManager* dbManager;
    QItemSelectionModel* selectionModel;
};

#endif // ADMINNOTIFMODEL_H
