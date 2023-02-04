#ifndef APISMODEL_H
#define APISMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QSqlDatabase>

class ApisModel : public QSqlTableModel
{
    Q_OBJECT
public:
    enum Columns {
        Column_Id = 0,
        Column_Url,
        Column_Name,
        Column_Description
    };

    ApisModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
};

#endif // APISMODEL_H
