#ifndef ELEMENTSMODEL_H
#define ELEMENTSMODEL_H

#include <QObject>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>

/**
 * @brief Модель данных элементов API
 * @details Класс представляет модель данных, хранящую элементы API.
 * Данные загружаются из базы с помощью SQL-запроса. Все поля, кроме комментария,
 * нередактируемые. При редактировании поля комментария нужный тип запроса выбирается автоматически.
 */
class ElementsModel : public QSqlQueryModel
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
        comment_id,
        comment,
    };

    ElementsModel(QObject *parent = nullptr,  QSqlDatabase db = QSqlDatabase());
    ~ElementsModel();

    /**
     * @brief Перегруженная функция редактирования данных модели
     * @param index Индекс редактируемой ячейки
     * @param value Новое значение редактируемой ячейки
     * @param role Роль редактируемого значения. Фактически используется только DisplayRole, проверок на роль не производится
     * @return Истину, если редактирование успешно, ложь в противном случае
     * @details Функция реализует редактирование данных модели.
     * Редактирование разрешено только для столбца комментария, то есть при попытке
     * редактирования любого другого столбца возвращается ложь.
     * При редактировании изменения сразу же вносятся в базу данных. Нужный тип
     * запроса (добавление, изменение или удаление) выбирается автоматически
     * исходя из наличия данных в новом и предыдущем состоянии ячейки.
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    /**
     * @brief Перегруженная функция возвращает флаги состояния для любого индекса
     * @param index Индекс целевой ячейки
     * Функция возвращает флаги, обеспечивающие редактируемость столбца комментария.
     */
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    QSqlDatabase m_db;
    QSqlQuery m_selectQuery;
    QSqlQuery m_insertQuery;
    QSqlQuery m_updateQuery;
    QSqlQuery m_deleteQuery;
};

#endif // ELEMENTSMODEL_H
