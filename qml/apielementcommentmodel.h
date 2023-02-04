#ifndef APIELEMENTCOMMENTMODEL_H
#define APIELEMENTCOMMENTMODEL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <qqml.h>


/**
 * @brief Модель данных для отдельного элемента API и его комментария
 * @details Класс содержит свойства и методы, доступные для вызова из QML.
 * Один объект этого класса представляет один элемент API и его комментарий.
 * Класс автоматически создаёт SQL-запросы, необходимые для обслуживания
 * чтения и записи комментариев.
 *
 * Для загрузки из БД нужной записи вызовите метод \ref ApiElementCommentModel::select
 * с нужными параметрами. Для сохранения комментария к элементу API
 * вызовите метод \ref ApiElementCommentModel::setComment.
 */
class ApiElementCommentModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(qulonglong elementId READ elementId NOTIFY dataChanged)
    Q_PROPERTY(qulonglong apiId READ apiId NOTIFY dataChanged)
    Q_PROPERTY(QString method READ method NOTIFY dataChanged)
    Q_PROPERTY(QString url READ url NOTIFY dataChanged)
    Q_PROPERTY(QString operationId READ operationId NOTIFY dataChanged)
    Q_PROPERTY(QString summary READ summary NOTIFY dataChanged)
    Q_PROPERTY(qulonglong commentId READ commentId NOTIFY dataChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY dataChanged)
public:
    ApiElementCommentModel(QSqlDatabase db = QSqlDatabase(), QObject *parent = nullptr);

    Q_INVOKABLE void select(qulonglong apiId, QString operationId);

    qulonglong elementId();
    qulonglong apiId();
    QString method();
    QString url();
    QString operationId();
    QString summary();
    qulonglong commentId();
    QString comment();

    /**
     * @brief Сохраняет новый комментарий в модели и в базе данных
     * @param comment Новый комментарий
     * @details При вызове этого метода новое значение комментария обновится
     * как в модели, так и в базе данных. Метод автоматически выберет
     * нужный способ обновления БД: вставка нового комментария,
     * изменение существующего или удаление существующего.
     */
    void setComment(QString comment);
signals:

    /**
     * @brief Сигнал посылается, когда в модели обновились любые данные.
     * Фактически это происходит при вызове метода \ref ApiElementCommentModel::select,
     * если SQL-запрос вернул данные, а также при вызове метода \ref ApiElementCommentModel::setComment.
     */
    void dataChanged();

public slots:

private:
    qulonglong m_elementId;
    qulonglong m_apiId;
    QString m_method;
    QString m_url;
    QString m_operationId;
    QString m_summary;
    qulonglong m_commentId;
    QString m_comment;

    QSqlDatabase m_db;
    QSqlQuery m_selectQuery;
    QSqlQuery m_insertQuery;
    QSqlQuery m_updateQuery;
    QSqlQuery m_deleteQuery;
};

#endif // APIELEMENTCOMMENTMODEL_H
