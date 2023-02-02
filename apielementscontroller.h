#ifndef APIELEMENTSCONTROLLER_H
#define APIELEMENTSCONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <qqml.h>
#include <QAbstractItemModel>
#include "elementsmodel.h"

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
    void setApiId(qulonglong id);
signals:

    void apiIdChanged();
public slots:

private:
    QSqlDatabase m_db;
    qulonglong m_apiId;
    ElementsModel *m_elementsModel;
};

#endif // APIELEMENTSCONTROLLER_H
