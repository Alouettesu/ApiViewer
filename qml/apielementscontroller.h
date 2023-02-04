#ifndef APIELEMENTSCONTROLLER_H
#define APIELEMENTSCONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <qqml.h>
#include <QAbstractItemModel>
#include "elementsmodel.h"

/**
 * @brief Класс содержит модель данных для отображения элементов API и методы управления ею
 */
class ApiElementsController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel *model READ elementsModel)
    Q_PROPERTY(qulonglong apiId READ apiId WRITE setApiId NOTIFY apiIdChanged)
    QML_ELEMENT
public:
    explicit ApiElementsController(QSqlDatabase db = QSqlDatabase(), QObject *parent = nullptr);

    ElementsModel *elementsModel();
    qulonglong apiId();

    /**
     * @brief Метод назначает новый идентификатор API для вывода его в модели
     * @param id Новый идентификатор API
     * @details Метод устанавливает новый идентификатор API и обновляет
     * модель данных. При вызове этого метода выполнится SQL-запрос,
     * извлекающий из БД список элементов выбранного API.
     */
    void setApiId(qulonglong id);

    /**
     * @brief Метод выполняет SQL-запрос, извлекающий из БД
     * список элементов ранее выбранного API. Метод следует вызывать,
     * когда получены сведения об изменениях в таблице элементов API в базе данных.
     */
    void refreshModel();
signals:

    void apiIdChanged();
public slots:

private:
    QSqlDatabase m_db;
    qulonglong m_apiId;
    ElementsModel *m_elementsModel;
};

#endif // APIELEMENTSCONTROLLER_H
