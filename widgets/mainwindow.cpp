#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "database.h"
#include "apismodel.h"
#include "apimodel.h"
#include "apigetter.h"
#include "apiparser.h"
#include "apicacheupdatedaemon.h"
#include "elementsmodel.h"

#include <QFile>
#include <QMetaObject>
#include <QMessageBox>
#include <QTimer>
#include <QItemSelection>

Database db;
ApiCacheUpdateDaemon *daemon;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_apisListModel = new ApisModel(this, db.db());
    m_apiElementsModel = new ElementsModel(this, db.db());
    daemon = new ApiCacheUpdateDaemon(db.db());
    ui->setupUi(this);

    ui->apisView->setModel(m_apisListModel);
    ui->apisView->hideColumn(ApisModel::Column_Id);

    ui->apiElementsView->setModel(m_apiElementsModel);
    ui->apiElementsView->hideColumn(ElementsModel::Api_id);
    ui->apiElementsView->hideColumn(ElementsModel::Id);
    ui->apiElementsView->hideColumn(ElementsModel::comment_id);
    ui->apiElementsView->setColumnWidth(ElementsModel::operationId, 200);
    ui->apiElementsView->setColumnWidth(ElementsModel::comment, 150);
    ui->apiElementsView->setColumnWidth(ElementsModel::summary, 200);
    connect(daemon, &ApiCacheUpdateDaemon::updated, this, &MainWindow::onApiUpdated, Qt::QueuedConnection);
    connect(ui->apisView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onApisSelectionChanged);
    if (m_apisListModel->rowCount() > 0)
        ui->apisView->selectionModel()->select(m_apisListModel->index(0, 0), QItemSelectionModel::Select);
    daemon->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete daemon;
}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::Close)
    {
        QMessageBox box(QMessageBox::Information, "Information", "Please wait for threads finished. Window will be closed automatically.");
        box.setModal(true);
        box.show();
        daemon->finish();
        box.close();
        return QMainWindow::event(event);
    }
    return QMainWindow::event(event);
}

void MainWindow::onApiUpdated()
{
    m_apiElementsModel->refresh();
}

void MainWindow::onApisSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    if (selected.indexes().count() == 1)
    {
        QModelIndex selectedIndex = selected.indexes().at(0);
        int row = selectedIndex.row();
        qulonglong apiId = m_apisListModel->index(row, ApisModel::Column_Id).data().toULongLong();
        m_apiElementsModel->setApi(apiId);
    }
}
