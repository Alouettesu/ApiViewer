#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class Database
{
public:
    Database();
    virtual ~Database();

    const QSqlDatabase &db();

private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
