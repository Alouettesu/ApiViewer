#include "database.h"
#include <QFile>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDir>
#include <QDirIterator>

Database::Database()
{
    QString path = "apis.db";
    bool dbExists = QFile::exists(path);
    if (!dbExists)
    {
        Q_INIT_RESOURCE(dbresource);
        QFile file(":/dbFiles/apis.db");
        file.copy(path);
        QFile targetDbFile(path);
        qDebug() << targetDbFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
    }

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    m_db.open();

}

Database::~Database()
{

}

const QSqlDatabase &Database::db()
{
    return m_db;
}
