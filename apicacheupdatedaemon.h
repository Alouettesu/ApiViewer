#ifndef APICACHEUPDATEDAEMON_H
#define APICACHEUPDATEDAEMON_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QThread>
#include <QTimer>
#include <QMutex>
#include <QList>
#include <QFuture>
#include <QFutureWatcher>
#include <atomic>

#include "apismodel.h"
#include "apimodel.h"
#include "apigetter.h"

class ApiCacheUpdateDaemon : public QObject
{
    Q_OBJECT
public:
    explicit ApiCacheUpdateDaemon(QSqlDatabase db);

    ~ApiCacheUpdateDaemon();

    void finish();
    void start();

signals:
    void finished();

    void updated();

public slots:

private slots:
    void onStartRequested();
    void onUpdateRequested();
    void onAllRequestsFinished();

    void processDocument(const QSqlRecord &record);
    void cancelRequests();

private:
    QThread m_thread;
    QSqlDatabase m_db;
    QTimer *m_timer;
    ApisModel *m_apisModel;
    ApiModel *m_apiElementsModel;
    QMutex m_elementsTableMutex;
    QList<QSqlRecord> m_apisList;
    QFuture<void> m_allRequestsFuture;
    QFutureWatcher<void> m_allRequestsFutureWatcher;
    std::atomic_bool m_isRunning;

    QList<ApiGetter*> m_runningProcesses;
    QMutex m_runningProcessesMutex;
    QMutex m_futureRunningMutex;
};

#endif // APICACHEUPDATEDAEMON_H
