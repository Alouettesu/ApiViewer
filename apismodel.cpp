#include "apismodel.h"

ApisModel::ApisModel(QObject *parent, QSqlDatabase db) :
    QSqlTableModel(parent, db)
{
    setTable("apis");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
    setHeaderData(0, Qt::Horizontal, tr("Id"));
    setHeaderData(1, Qt::Horizontal, tr("Url"));
    setHeaderData(2, Qt::Horizontal, tr("Name"));
    setHeaderData(3, Qt::Horizontal, tr("Description"));
}
