#ifndef APIMODEL_H
#define APIMODEL_H

#include <QObject>
#include <QSqlTableModel>

#include "apiparser.h"


/**
 * @brief Модель для доступа и редактирования списка элементов API
 * Модель извлекает из базы данных перечень элементов API,
 * предоставляет функции для добавления новых элементов и удаления элементов.
 */
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

    /**
     * @brief Функция добавляет элемент API в модель
     * @param record Элемент API, который необходимо добавить
     * Функция только добавляет элемент в свою память, но не
     * в базу данных. Для добавления элементов в базу данных
     * необходима функция QSqlTableModel::submitAll.
     */
    void insertApiElement(const ApiElementRecord &record);

    /**
     * @brief Функция добавляет элементы API в модель
     * @param elements Список элементов API, который необходимо добавить
     * Функция только добавляет элементы в свою память, но не
     * в базу данных. Для добавления элементов в базу данных
     * необходима функция QSqlTableModel::submitAll.
     */
    void insertApiElement(const QList<ApiElementRecord> &elements);

    /**
     * @brief Функция удаляет все элементы API из модели.
     * Для удаления их из базы данных необходима функция QSqlTableModel::submitAll.
     */
    void clear() override;

private:
    void insertApiElementInternal(const ApiElementRecord &record);

};

#endif // APIPARSER_H
