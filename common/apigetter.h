#ifndef APIGETTER_H
#define APIGETTER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class ApiGetter : public QObject
{
    Q_OBJECT
public:
    explicit ApiGetter(QString apiUrl, QObject *parent = nullptr);

signals:

    void ApiRecieved(QByteArray &apiFile);

public slots:
    void perform();
    void cancel();

private slots:
    void onRequestFinished(QNetworkReply *reply);
private:
    QNetworkAccessManager *m_network;
    QNetworkRequest m_request;
    QNetworkReply *m_reply;
    QByteArray m_result;
};

#endif // APIGETTER_H
