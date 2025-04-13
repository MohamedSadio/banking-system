#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QString>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDebug>
#include <QItemSelectionModel>
#include <QModelIndex>

#include "dbmanager.h"

class SettingsModel : public QSqlQueryModel
{
public:
    SettingsModel();

    bool initializeSettings();
    bool updateSettings(int transactionLimit, int minAmount, int maxAmount, bool notifications);
    bool loadSettings(int &transactionLimit, int &minAmount, int &maxAmount, bool &notifications);


private:
    DBManager* dbManager;
    QItemSelectionModel* selectionModel;

    const int DEFAULT_TRANSACTION_LIMIT = 10000.0;
    const int DEFAULT_MIN_AMOUNT = 10.0;
    const int DEFAULT_MAX_AMOUNT = 5000.0;
    const bool DEFAULT_NOTIFICATIONS_ENABLED = true;
};

#endif // SETTINGSMODEL_H
