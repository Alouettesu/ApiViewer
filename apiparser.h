#ifndef APIPARSER_H
#define APIPARSER_H

#include <QByteArray>
#include <QList>

struct ApiElementRecord {
    qulonglong api_id;
    QString method;
    QString url;
    QString operationId;
    QString summary;
};

class ApiParser
{
public:
    ApiParser(const QByteArray &&text, size_t api_id);

    QList<ApiElementRecord> parse();

private:
    QByteArray m_text;
    size_t m_api_id;
};

#endif // APIPARSER_H
