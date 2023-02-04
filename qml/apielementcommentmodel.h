#ifndef APIELEMENTCOMMENTMODEL_H
#define APIELEMENTCOMMENTMODEL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <qqml.h>

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

    void setComment(QString comment);
signals:

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
