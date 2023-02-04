#include "apicacheupdatedaemon.h"
#include <QMetaMethod>
#include <QSqlRecord>
#include <QSqlField>
#include <QtConcurrent>
#include <QMutex>
#include <QEventLoop>
#include <functional>
#include <QCoreApplication>

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
    m_allRequestsFutureWatcher.moveToThread(&m_thread);
    m_thread.start();
    m_timer->setSingleShot(true);
    m_timer->setInterval(5000);
    connect(m_timer, &QTimer::timeout, this, &ApiCacheUpdateDaemon::onUpdateRequested, Qt::QueuedConnection);
    connect(&m_thread, &QThread::finished, this, &ApiCacheUpdateDaemon::finished, Qt::QueuedConnection);
}

ApiCacheUpdateDaemon::~ApiCacheUpdateDaemon()
{

}

void ApiCacheUpdateDaemon::finish()
{
    m_isRunning = false;
    QMetaObject::invokeMethod(m_timer, &QTimer::stop, Qt::QueuedConnection);
    cancelRequests();
    QCoreApplication::processEvents();
//12600
    m_futureRunningMutex.lock();
    //Просто ждём, пока запущенные процессы завершатся
    m_futureRunningMutex.unlock();
    m_timer->deleteLater();
    m_apiElementsModel->submitAll();

    m_thread.quit();
    m_thread.wait();
}

void ApiCacheUpdateDaemon::start()
{
    QMetaObject::invokeMethod(this, &ApiCacheUpdateDaemon::onStartRequested, Qt::QueuedConnection);
}

void ApiCacheUpdateDaemon::onStartRequested()
{
    m_timer->start();
    m_isRunning = true;
}

void ApiCacheUpdateDaemon::onUpdateRequested()
{
    if (!m_isRunning)
        return;
    while (m_apiElementsModel->canFetchMore())
        m_apiElementsModel->fetchMore();
    m_apiElementsModel->clear();
    for (int row = 0; row < m_apisModel->rowCount(); ++row)
    {
        m_apisList.append(m_apisModel->record(row));
    }
    m_futureRunningMutex.lock();

    m_allRequestsFuture = QtConcurrent::map(m_apisList.begin(),
                                            m_apisList.end(),
                                            std::bind(&ApiCacheUpdateDaemon::processDocument, this, std::placeholders::_1));
    m_allRequestsFutureWatcher.setFuture(m_allRequestsFuture);
    connect(&m_allRequestsFutureWatcher, &QFutureWatcher<void>::finished, this, &ApiCacheUpdateDaemon::onAllRequestsFinished, Qt::DirectConnection);
}

void ApiCacheUpdateDaemon::onAllRequestsFinished()
{
    disconnect(&m_allRequestsFutureWatcher, &QFutureWatcher<void>::finished, this, &ApiCacheUpdateDaemon::onAllRequestsFinished);
    m_apiElementsModel->submitAll();
    if (m_isRunning)
    {
        emit updated();
        m_timer->setInterval(500000);
        m_timer->start();
    }
    m_apisList.clear();
    m_futureRunningMutex.unlock();
}


void ApiCacheUpdateDaemon::processDocument(const QSqlRecord &record)
{
    if (!m_isRunning)
        return;
    QString url = record.field("url").value().toString();
    size_t id = record.field("id").value().toULongLong();
    ApiGetter getter(url);
    QEventLoop waitForFinished;
    connect(&getter, &ApiGetter::ApiRecieved, [this, id, &waitForFinished, &getter](QByteArray &text){
        m_runningProcessesMutex.lock();
        m_runningProcesses.removeAll(&getter);
        m_runningProcessesMutex.unlock();
        if (!text.isEmpty())
        {
            ApiParser parser(std::move(text), id);
            auto list = parser.parse();

            m_elementsTableMutex.lock();
            m_apiElementsModel->insertApiElement(list);
            m_elementsTableMutex.unlock();
        }
        waitForFinished.quit();

    });
    m_runningProcessesMutex.lock();
    m_runningProcesses.append(&getter);
    m_runningProcessesMutex.unlock();
    getter.perform();
    waitForFinished.exec();
}

void ApiCacheUpdateDaemon::cancelRequests()
{
    m_runningProcessesMutex.lock();
    for (ApiGetter *getter : m_runningProcesses)
    {
        QMetaObject::invokeMethod(getter, &ApiGetter::cancel, Qt::QueuedConnection);
    }
    m_runningProcessesMutex.unlock();
}
