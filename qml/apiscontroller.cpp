#include "apiscontroller.h"

ApisController::ApisController(QSqlDatabase db, QObject *parent) :
    QObject(parent),
    m_db(db)
{
    m_apisModel = new ApisModel(this, m_db);

}

QAbstractItemModel *ApisController::model()
{
    return m_apisModel;
}
