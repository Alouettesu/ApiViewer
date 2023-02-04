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

/**
 * @brief Класс предназначен для разбора перечня элементов API по JSON-файлу
 */
class ApiParser
{
public:
    /**
     * @brief Конструирует класс ApiParser
     * @param text JSON-файл, содержащий описание функций сервера
     * @param api_id Номер API из базы данных
     * Конструктор создаёт класс ApiParser на основе переданных ему входных данных.
     * JSON-файл потенциально может быть объёмным, поэтому файл text перемещается
     * во внутреннюю память объекта.
     *
     * Параметр api_id нужен для правильного заполнения поля \ref ApiElementRecord::api_id
     * и последующего сохранения всех записей в базу данных.
     */
    ApiParser(const QByteArray &&text, qlonglong api_id);

    /**
     * @brief Функция выполняет разбор JSON-файла, переданного в конструкторе,
     * извлекает из него все функции и возвращает их в виде списка структур
     * \ref ApiElementRecord.
     */
    QList<ApiElementRecord> parse();

private:
    QByteArray m_text;
    size_t m_api_id;
};

#endif // APIPARSER_H
