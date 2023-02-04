#include "apielementcommentmodel.h"
#include <QDebug>

ApiElementCommentModel::ApiElementCommentModel(QSqlDatabase db, QObject *parent) :
    QObject(parent),
    m_db(db),
    m_selectQuery(m_db),
    m_insertQuery(m_db),
    m_updateQuery(m_db),
    m_deleteQuery(m_db)
{
    m_selectQuery.prepare("SELECT elements.id as element_id, \
             elements.api_id as api_id, \
             elements.method as method, \
             elements.url as url, \
             elements.operationId as operationId, \
             elements.summary as summary,\
             comments.id as comment_id,\
             comments.comment as comment\
         FROM elements LEFT JOIN comments ON comments.operationId==elements.operationId\
                          WHERE elements.api_id==:api_id AND elements.operationId==:operationId");

    m_insertQuery.prepare("INSERT INTO comments (operationId, api_id, comment) VALUES (:operationId, :api_id, :comment)");
    m_updateQuery.prepare("UPDATE comments SET comment=:comment WHERE id=:comment_id");
    m_deleteQuery.prepare("DELETE FROM comments WHERE id=:comment_id");
}

void ApiElementCommentModel::select(qulonglong apiId, QString operationId)
{
    m_apiId = apiId;
    m_operationId = operationId;
    m_selectQuery.bindValue(QString(":api_id"), QVariant(m_apiId));
    m_selectQuery.bindValue(QString(":operationId"), QVariant(m_operationId));
    if (m_selectQuery.exec() && m_selectQuery.next())
    {
        m_elementId = m_selectQuery.value("element_id").toULongLong();
        m_method = m_selectQuery.value("method").toString();
        m_url = m_selectQuery.value("url").toString();
        m_summary = m_selectQuery.value("summary").toString();
        m_commentId = m_selectQuery.value("comment_id").toULongLong();
        m_comment = m_selectQuery.value("comment").toString();
        emit dataChanged();
    }
}

qulonglong ApiElementCommentModel::elementId()
{
    return m_elementId;
}

qulonglong ApiElementCommentModel::apiId()
{
    return m_apiId;
}

QString ApiElementCommentModel::method()
{
    return m_method;
}

QString ApiElementCommentModel::url()
{
    return m_url;
}

QString ApiElementCommentModel::operationId()
{
    return m_operationId;
}

QString ApiElementCommentModel::summary()
{
    return m_summary;
}

qulonglong ApiElementCommentModel::commentId()
{
    return m_commentId;
}

QString ApiElementCommentModel::comment()
{
    return m_comment;
}

void ApiElementCommentModel::setComment(QString comment)
{
    if (comment.isEmpty())
    {
        if (!m_comment.isEmpty())
        {
            //Если новый комментарий пуст, но был старый, то удаляем его
            m_deleteQuery.bindValue(QString(":comment_id"), m_commentId);
            m_deleteQuery.exec();
        }
    }
    else
    {
        if (m_comment.isEmpty())
        {
            //Если имеется новый комментарий, но старого не было, то добавляем новый
            m_insertQuery.bindValue(QString(":operationId"), m_operationId);
            m_insertQuery.bindValue(QString(":api_id"), m_apiId);
            m_insertQuery.bindValue(QString(":comment"), comment);
            m_insertQuery.exec();
        }
        else
        {
            //Если имеется новый комментарий, и был старый, то обновляем его
            m_updateQuery.bindValue(QString(":comment_id"), m_commentId);
            m_updateQuery.bindValue(QString(":comment"), comment);
            m_updateQuery.exec();
        }
    }
    m_comment = comment;
    emit dataChanged();
}
