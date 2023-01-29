#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "database.h"
#include "apismodel.h"
#include "apimodel.h"
#include "apigetter.h"
#include "apiparser.h"
#include "apicacheupdatedaemon.h"

#include <QFile>
#include <QMetaObject>
#include <QMessageBox>

Database db;
ApiCacheUpdateDaemon *daemon;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ApisModel *model = new ApisModel(this, db.db());
    ApiModel *apiModel = new ApiModel(this, db.db());
    daemon = new ApiCacheUpdateDaemon(db.db());
    ui->setupUi(this);

    ui->apisView->setModel(model);
    ui->apisView->hideColumn(0);

    ui->apiElementsView->setModel(apiModel);
    ui->apiElementsView->hideColumn(0);


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
