#ifndef APISCONTROLLER_H
#define APISCONTROLLER_H

#include <QObject>
#include <qqml.h>

#include <QSqlDatabase>
#include <QAbstractItemModel>
#include "apismodel.h"

class ApisController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel *model READ model)
    QML_ELEMENT
public:
    explicit ApisController(QSqlDatabase db = QSqlDatabase(), QObject *parent = nullptr);

    QAbstractItemModel *model();
signals:

public slots:

private:
    QSqlDatabase m_db;
    ApisModel *m_apisModel;
};

#endif // APISCONTROLLER_H
