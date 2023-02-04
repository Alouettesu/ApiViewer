# Отображение публичных API

Программа загружает файлы описания публичных API, показывает их точки входа
и позволяет писать комментарии к точкам входа.

# Среда сборки

Программа собрана в среде

* Ubuntu 18.04.6
* Qt 5.15
* gcc version 7.5.0 (Ubuntu 7.5.0-3ubuntu1~18.04)

# Сборка

Для сборки проекта необходим Qt версии 5.15. На linux выполнить следующие команды:

```
cd ../
mkdir build
cd build
export PATH=/path/to/Qt5.15:$PATH
qmake ../ApiViewer/ApiViewer.pro
make
```

# Структура проекта

В репозитории имеется несколько проектов Qt, объединённых с помощью subdirs.
Главный проект `ApiViewer` содержит пути к вложенным проектам, а также файлы,
не относящиеся к какому-либо конкретному подпроекту.

Подпроект `qml` собирается в исполняемый файл `ApiViewer`, который работает на
декларативной системе пользовательского интерфейса QML.
Подпроект `widgets` тоже собирается в исполняемый файл `ApiViewer`, который
работает на классическом `Qt Widgets`.
Подпроект `common` собирается в статическую библиотеку и содержит
общий для двух подпроектов Backend.

# Работа программы

Сохранение локального кеша в БД получилось долгой операцией, она
выполняется даже дольше, чем загрузка JSON-файла по сети. И прервать её нельзя.
Поэтому при закрытии окна выполняется ожидание завершения сохранения
данных в БД.

Если в момент нажатия кнопки закрытия окна уже выполнялась процедура
сохранения, то программа будет ждать завершения.
Если эта процедура не выполнялась, то программа сразу завершится.
По этой же причине первичная загрузка элементов API занимает много времени.
Полная загрузка JSON-файла GitHub API, его обработка и сохранение в БД занимает
порядка 15 секунд.
