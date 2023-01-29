#ifndef APISMODEL_H
#define APISMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QSqlDatabase>

class ApisModel : public QSqlTableModel
{
    Q_OBJECT
public:
    ApisModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
};

#endif // APISMODEL_H
