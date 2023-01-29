#include "apiparser.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

ApiParser::ApiParser(const QByteArray &&text, size_t api_id) :
    m_text(std::move(text)),
    m_api_id(api_id)
{

}

QList<ApiElementRecord> ApiParser::parse()
{
    QList<ApiElementRecord> result;
    QJsonDocument doc = QJsonDocument::fromJson(m_text);
    QJsonObject root = doc.object();
    QJsonValue paths = root.value("paths");
    if (paths == QJsonValue::Undefined)
        return QList<ApiElementRecord>();

    QJsonObject pathsObject = paths.toObject();
    QStringList pathsList = pathsObject.keys();
    for (const auto& path : pathsList)
    {
        QJsonValue curPathValue = pathsObject.value(path);
        if (curPathValue == QJsonValue::Undefined)
            continue;

        QJsonObject curPathObject = curPathValue.toObject();
        QStringList methodsList = curPathObject.keys();
        for (const auto& method : methodsList)
        {
            ApiElementRecord curRecord;
            curRecord.api_id = m_api_id;
            curRecord.url = path;
            curRecord.method = method;
            QJsonValue curMethodValue = curPathObject.value(method);
            if (curMethodValue == QJsonValue::Undefined)
                continue;
            QJsonObject curMethodObject = curMethodValue.toObject();
            QJsonValue operationIdValue = curMethodObject.value("operationId");
            if (operationIdValue == QJsonValue::Undefined)
                continue;
            curRecord.operationId = operationIdValue.toString();
            QJsonValue summaryValue = curMethodObject.value("summary");
            if (summaryValue != QJsonValue::Undefined)
            {
                curRecord.summary = summaryValue.toString();
            }
            result.append(curRecord);

        }
    }
    return result;
}
