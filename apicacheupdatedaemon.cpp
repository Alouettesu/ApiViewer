#include "apicacheupdatedaemon.h"
#include <QMetaMethod>
#include <QSqlRecord>
#include <QSqlField>
#include <QtConcurrent>
#include <QMutex>
#include <QEventLoop>
#include <functional>

#include "apigetter.h"
#include "apiparser.h"

ApiCacheUpdateDaemon::ApiCacheUpdateDaemon(QSqlDatabase db) :
    QObject(nullptr),
    m_db(db)
{
    m_timer = new QTimer;
    m_apisModel = new ApisModel(this, m_db);
    m_apiElementsModel = new ApiModel(this, m_db);
    moveToThread(&m_thread);
    m_timer->moveToThread(&m_thread);
    m_thread.start();
    m_timer->setSingleShot(true);
    m_timer->setInterval(5000);
    connect(m_timer, &QTimer::timeout, this, &ApiCacheUpdateDaemon::onUpdateRequested, Qt::QueuedConnection);
    connect(&m_thread, &QThread::finished, this, &ApiCacheUpdateDaemon::finished, Qt::QueuedConnection);
    QMetaObject::invokeMethod(m_timer, qOverload<>(&QTimer::start), Qt::QueuedConnection);
    m_isRunning = true;
}

ApiCacheUpdateDaemon::~ApiCacheUpdateDaemon()
{

}

void ApiCacheUpdateDaemon::finish()
{
    m_isRunning = false;
    QMetaObject::invokeMethod(m_timer, &QTimer::stop, Qt::QueuedConnection);
    m_allRequestsFuture.cancel();
    m_timer->deleteLater();

    m_thread.quit();
    m_thread.wait();
}

void ApiCacheUpdateDaemon::onUpdateRequested()
{
    if (!m_isRunning)
        return;
    while (m_apiElementsModel->canFetchMore())
        m_apiElementsModel->fetchMore();
    m_apiElementsModel->clear();
    m_apiElementsModel->submitAll();
    for (int row = 0; row < m_apisModel->rowCount(); ++row)
    {
        m_apisList.append(m_apisModel->record(row));
    }
    m_allRequestsFuture = QtConcurrent::map(m_apisList.begin(),
                                            m_apisList.end(),
                                            std::bind(&ApiCacheUpdateDaemon::processDocument, this, std::placeholders::_1));
    m_allRequestsFutureWatcher.setFuture(m_allRequestsFuture);
    connect(&m_allRequestsFutureWatcher, &QFutureWatcher<void>::finished, this, &ApiCacheUpdateDaemon::onAllRequestsFinished, Qt::QueuedConnection);
}

void ApiCacheUpdateDaemon::onAllRequestsFinished()
{
    m_apiElementsModel->submitAll();
    if (m_isRunning)
    {
        m_timer->setInterval(500000);
        m_timer->start();
    }
}


void ApiCacheUpdateDaemon::processDocument(const QSqlRecord &record)
{
    if (!m_isRunning)
        return;
    QString url = record.field("url").value().toString();
    size_t id = record.field("id").value().toULongLong();
    ApiGetter getter(url);
    QEventLoop waitForFinished;
    connect(&getter, &ApiGetter::ApiRecieved, [this, id, &waitForFinished](QByteArray &text){
        ApiParser parser(std::move(text), id);
        auto list = parser.parse();

        m_elementsTableMutex.lock();
        m_apiElementsModel->insertApiElement(list);
        m_elementsTableMutex.unlock();
        waitForFinished.quit();

    });
    getter.perform();
    waitForFinished.exec();
}
