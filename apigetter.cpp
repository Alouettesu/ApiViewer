#include "apigetter.h"
#include <QUrl>
#include <QDebug>

ApiGetter::ApiGetter(QString apiUrl, QObject *parent) :
    QObject(parent),
    m_reply(nullptr)
{
    m_network = new QNetworkAccessManager(this);
    QUrl url(apiUrl);
    m_request = QNetworkRequest(url);
    connect(m_network, qOverload<QNetworkReply*>(&QNetworkAccessManager::finished), this, &ApiGetter::onRequestFinished);
//    m_network->get(m_request);
}

void ApiGetter::perform()
{
    m_reply = m_network->get(m_request);
}

void ApiGetter::cancel()
{
    if (m_reply != nullptr)
    {
        m_reply->abort();
    }
}

void ApiGetter::onRequestFinished(QNetworkReply *reply)
{
    reply->deleteLater();

    if(reply->error() == QNetworkReply::NoError) {
        // Get the http status code
        int v = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (v >= 200 && v < 300) // Success
        {
             // Here we got the final reply
            m_result = std::move(reply->readAll());
            emit ApiRecieved(m_result);
        }
    }
    else if (reply->error() == QNetworkReply::OperationCanceledError)
    {
        QByteArray r;
        emit ApiRecieved(r);
    }
}
