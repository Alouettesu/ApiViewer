#include "apismodel.h"

ApisModel::ApisModel(QObject *parent, QSqlDatabase db) :
    QSqlTableModel(parent, db)
{
    setTable("apis");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
    setHeaderData(ApisModel::Column_Id, Qt::Horizontal, tr("Id"));
    setHeaderData(ApisModel::Column_Url, Qt::Horizontal, tr("Url"));
    setHeaderData(ApisModel::Column_Name, Qt::Horizontal, tr("Name"));
    setHeaderData(ApisModel::Column_Description, Qt::Horizontal, tr("Description"));
}
