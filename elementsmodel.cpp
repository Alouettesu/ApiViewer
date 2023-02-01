#include "elementsmodel.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

ElementsModel::ElementsModel(QObject *parent, QSqlDatabase db) :
    QSqlQueryModel(parent),
    m_db(db),
    m_selectQuery(m_db),
    m_insertQuery(m_db),
    m_updateQuery(m_db),
    m_deleteQuery(m_db)
{
    //В запросе не учтено, что в разных API могут быть операции с одинаковым названием

    m_selectQuery.prepare("SELECT elements.id as element_id, \
             elements.api_id as api_id, \
             elements.method as method, \
             elements.url as url, \
             elements.operationId as operationId, \
             elements.summary as summary,\
             comments.id as comment_id,\
             comments.comment as comment\
         FROM elements LEFT JOIN comments ON comments.operationId==elements.operationId");
    m_selectQuery.exec();
    m_insertQuery.prepare("INSERT INTO comments (operationId, api_id, comment) VALUES (:operationId, :api_id, :comment)");
    m_updateQuery.prepare("UPDATE comments SET comment=:comment WHERE id=:comment_id");
    m_deleteQuery.prepare("DELETE FROM comments WHERE id=:comment_id");
    setQuery(m_selectQuery);
    setHeaderData(ElementsModel::Id, Qt::Horizontal, tr("element_id"));
    setHeaderData(ElementsModel::Api_id, Qt::Horizontal, tr("api_id"));
    setHeaderData(ElementsModel::method, Qt::Horizontal, tr("method"));
    setHeaderData(ElementsModel::url, Qt::Horizontal, tr("url"));
    setHeaderData(ElementsModel::operationId, Qt::Horizontal, tr("operationId"));
    setHeaderData(ElementsModel::summary, Qt::Horizontal, tr("summary"));
    setHeaderData(ElementsModel::comment_id, Qt::Horizontal, tr("comment_id"));
    setHeaderData(ElementsModel::comment, Qt::Horizontal, tr("comment"));
}

ElementsModel::~ElementsModel()
{

}

bool ElementsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.column() == ElementsModel::comment)
    {
        if (!value.toString().isEmpty())
        {
            QVariant prevData = index.data(role);
            if (!prevData.toString().isEmpty())
            {
                QVariant idVariant = this->index(index.row(), ElementsModel::comment_id).data(role);
                bool ok;
                qulonglong id = idVariant.toULongLong(&ok);
                if (!ok)
                    return false;
                m_updateQuery.bindValue(QString(":comment_id"), QVariant(id));
                m_updateQuery.bindValue(QString(":comment"), value);
                m_updateQuery.exec();
                emit dataChanged(index, index, QVector<int>({role}));
            }
            else
            {
                QVariant operationVariant = this->index(index.row(), ElementsModel::operationId).data(role);
                QVariant apiVariant = this->index(index.row(), ElementsModel::Api_id).data(role);
                bool ok;
                QString operation_id = operationVariant.toString();
                qulonglong api_id = apiVariant.toULongLong(&ok);
                if (!ok)
                    return false;
                m_insertQuery.bindValue(QString(":operationId"), QVariant(operation_id));
                m_insertQuery.bindValue(QString(":api_id"), QVariant(api_id));
                m_insertQuery.bindValue(QString(":comment"), value);
                m_insertQuery.exec();
                emit dataChanged(this->index(index.row(), ElementsModel::comment_id), this->index(index.row(), ElementsModel::comment), QVector<int>({role}));
            }
        }
        else
        {
            QVariant idVariant = this->index(index.row(), ElementsModel::comment_id).data(role);
            bool ok;
            qulonglong id = idVariant.toULongLong(&ok);
            if (!ok)
                return false;
            m_deleteQuery.bindValue(QString(":comment_id"), id);
            m_deleteQuery.exec();
            emit dataChanged(this->index(index.row(), ElementsModel::comment_id), this->index(index.row(), ElementsModel::comment), QVector<int>({role}));
        }
        m_selectQuery.exec();
        return true;
    }
    else
        return false;
}

Qt::ItemFlags ElementsModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
    if (index.column() == ElementsModel::comment)
    {
        result |= Qt::ItemIsEditable;
    }
    return result;
}
