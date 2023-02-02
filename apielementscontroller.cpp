#include "apielementscontroller.h"

ApiElementsController::ApiElementsController(QSqlDatabase db, QObject *parent) :
    QObject(parent),
    m_db(db)
{
    m_elementsModel = new ElementsModel(this, m_db);
//    m_elementsModel->setApi(1);
}

ElementsModel *ApiElementsController::elementsModel()
{
    return m_elementsModel;
}

qulonglong ApiElementsController::apiId()
{
    return m_apiId;
}

void ApiElementsController::setApiId(qulonglong id)
{
    m_apiId = id;
    m_elementsModel->setApi(m_apiId);
    emit apiIdChanged();
}
