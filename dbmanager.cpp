#include "dbmanager.h"
#include "QDebug"

// initialisation de l'instance a null
DBManager* DBManager::instance = nullptr;

DBManager::DBManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbFullPath = "C:\\Qt-workspace-c++\\Database\\banking_system1.db";
    db.setDatabaseName(dbFullPath);

    qDebug("Connection opened successfully with database.");
    qDebug("Singleton DBManager initialized.");

    qDebug() << db.databaseName();
}

bool DBManager::open()
{
    qDebug() << "Database open1";
    if (db.isOpen()) return true;
     qDebug() << "Database open2";
    if (db.open()) return true;
    else
    {
        qDebug("Failed to open connection.");
        return false;
    }
    qDebug() << "Database open3";
}

void DBManager::close()
{
    if (db.isOpen()) db.close();
}

DBManager* DBManager::getInstance()
{
    if (instance == nullptr) instance = new DBManager();

    return instance;
}

void DBManager::release()
{    
    if (instance != nullptr)
    {
        delete instance;
        qDebug("Suppression du Singleton DBManager effectuéé.");
    }
}

DBManager::~DBManager() {}
