#include "database.h"
#include <QFile>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

//#include "apis.db.inc"

Database::Database()
{
    QString path = "apis.db";
//    bool dbExists = QFile::exists(path);
    m_db = QSqlDatabase::addDatabase("QSQLITE");//not dbConnection
    m_db.setDatabaseName(path);
    m_db.open();

//    if (!dbExists)
//    {
//        QSqlQuery query(m_db);
//        query.exec(QString(apis_db_sql));
//        qDebug() << query.lastError();
//    }
}

Database::~Database()
{

}

const QSqlDatabase &Database::db()
{
    return m_db;
}
