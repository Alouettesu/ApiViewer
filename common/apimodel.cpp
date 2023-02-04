#include "apimodel.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>

ApiModel::ApiModel(QObject *parent, QSqlDatabase db) :
    QSqlTableModel(parent, db)
{
    setTable("elements");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
    setHeaderData(ApiModel::Id, Qt::Horizontal, tr("id"));
    setHeaderData(ApiModel::Api_id, Qt::Horizontal, tr("api_id"));
    setHeaderData(ApiModel::method, Qt::Horizontal, tr("method"));
    setHeaderData(ApiModel::url, Qt::Horizontal, tr("url"));
    setHeaderData(ApiModel::operationId, Qt::Horizontal, tr("operationId"));
    setHeaderData(ApiModel::summary, Qt::Horizontal, tr("summary"));
}

ApiModel::~ApiModel()
{

}

void ApiModel::insertApiElement(const ApiElementRecord &record)
{
    insertApiElementInternal(record);
}

void ApiModel::insertApiElement(const QList<ApiElementRecord> &elements)
{
    for (const auto& element : elements)
    {
        insertApiElementInternal(element);
    }
}

void ApiModel::clear()
{
    removeRows(0, rowCount());
}

void ApiModel::insertApiElementInternal(const ApiElementRecord &record)
{
    QSqlRecord sqlRecord;
    QSqlField api_id("api_id", QVariant::ULongLong);
    api_id.setValue(record.api_id);
    sqlRecord.append(api_id);

    QSqlField method("method", QVariant::String);
    method.setValue(record.method);
    sqlRecord.append(method);

    QSqlField url("url", QVariant::String);
    url.setValue(record.url);
    sqlRecord.append(url);

    QSqlField operationId("operationId", QVariant::String);
    operationId.setValue(record.operationId);
    sqlRecord.append(operationId);

    QSqlField summary("summary", QVariant::String);
    summary.setValue(record.summary);
    sqlRecord.append(summary);
    insertRecord(-1, sqlRecord);
}
