#ifndef GERANTNOTIFMODEL_H
#define GERANTNOTIFMODEL_H

#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QMetaType>
#include "gerantnotif.h"
#include "dbmanager.h"

class GerantNotifModel : public QSqlQueryModel
{
public:
    GerantNotifModel();
    QItemSelectionModel* getSelectionModel();

    void create(GerantNotif notif);
    GerantNotif read(int id);
    QList<GerantNotif> list();
    void readAll();
    void setHeaderTitle();

private:
    DBManager* dbManager;
    QItemSelectionModel* selectionModel;
};

#endif // GERANTNOTIFMODEL_H
