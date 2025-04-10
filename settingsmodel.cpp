#include "settingsmodel.h"
#include <QSqlError>

SettingsModel::SettingsModel()
{
    selectionModel = new QItemSelectionModel(this);
    dbManager = DBManager::getInstance();

    initializeSettings();
}

bool SettingsModel::initializeSettings()
{
    dbManager->open();
    // Vérifier si des paramètres existent déjà
    QSqlQuery query(dbManager->database());
    query.prepare("SELECT COUNT(*) FROM system_settings");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la vérification des paramètres:" << query.lastError().text();
        dbManager->close();
    }

    query.next();
    int count = query.value(0).toInt();

    // Si aucun paramètre n'existe, insérer les valeurs par défaut
    if (count == 0) {
        query.prepare("INSERT INTO system_settings (id, transaction_limit, min_amount, max_amount, notifications_enabled) "
                     "VALUES (1, :transaction_limit, :min_amount, :max_amount, :notifications_enabled)");
        query.bindValue(":transaction_limit", DEFAULT_TRANSACTION_LIMIT);
        query.bindValue(":min_amount", DEFAULT_MIN_AMOUNT);
        query.bindValue(":max_amount", DEFAULT_MAX_AMOUNT);
        query.bindValue(":notifications_enabled", DEFAULT_NOTIFICATIONS_ENABLED ? 1 : 0);

        if (!query.exec()) {
            qDebug() << "Erreur lors de l'initialisation des paramètres:" << query.lastError().text();
            dbManager->close();
        }
    }
    dbManager->close();
}

bool SettingsModel::updateSettings(int transactionLimit, int minAmount, int maxAmount, bool notifications)
{
    dbManager->open();
    QSqlQuery query(dbManager->database());
    query.prepare("UPDATE system_settings SET "
                 "transaction_limit = :transaction_limit, "
                 "min_amount = :min_amount, "
                 "max_amount = :max_amount, "
                 "notifications_enabled = :notifications_enabled "
                 "WHERE id = 1");

    query.bindValue(":transaction_limit", transactionLimit);
    query.bindValue(":min_amount", minAmount);
    query.bindValue(":max_amount", maxAmount);
    query.bindValue(":notifications_enabled", notifications ? 1 : 0);

    bool success = query.exec();
    if (!success) {
       qDebug() << "Erreur lors de la mise à jour des paramètres:" << query.lastError().text();
    }

    dbManager->close();
    return success;
}

bool SettingsModel::loadSettings(int &transactionLimit, int &minAmount, int &maxAmount, bool &notifications)
{
    dbManager->open();
    QSqlQuery query(dbManager->database());
    query.prepare("SELECT transaction_limit, min_amount, max_amount, notifications_enabled FROM system_settings WHERE id = 1");

    if (!query.exec()) {
        qDebug() << "Erreur lors du chargement des paramètres:" << query.lastError().text();
        dbManager->close();
    }

    bool success = false;
    if (query.next()) {
       transactionLimit = query.value(0).toInt();
       minAmount = query.value(1).toInt();
       maxAmount = query.value(2).toInt();
       notifications = query.value(3).toInt() == 1;
       success = true;
    } else {
       transactionLimit = DEFAULT_TRANSACTION_LIMIT;
       minAmount = DEFAULT_MIN_AMOUNT;
       maxAmount = DEFAULT_MAX_AMOUNT;
       notifications = DEFAULT_NOTIFICATIONS_ENABLED;
       success = false;
    }

    dbManager->close();
    return success;
}
