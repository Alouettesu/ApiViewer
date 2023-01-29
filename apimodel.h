#ifndef APIMODEL_H
#define APIMODEL_H

#include <QObject>
#include <QSqlTableModel>

#include "apiparser.h"

class ApiModel : public QSqlTableModel
{
    Q_OBJECT
public:
    enum Columns {
        Id = 0,
        Api_id,
        method,
        url,
        operationId,
        summary,
    };
    ApiModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    virtual ~ApiModel();

    void insertApiElement(const ApiElementRecord &record);

    void insertApiElement(const QList<ApiElementRecord> &elements);

    void clear() override;

private:
    void insertApiElementInternal(const ApiElementRecord &record);

};

#endif // APIPARSER_H
