#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "apismodel.h"
#include "apimodel.h"
#include "apigetter.h"
#include "apiparser.h"
#include "apicacheupdatedaemon.h"
#include "elementsmodel.h"
#include <QItemSelection>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool event(QEvent *event) override;

private slots:
    void onApiUpdated();
    void onApisSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    Ui::MainWindow *ui;
    ApisModel *m_apisListModel;
    ElementsModel *m_apiElementsModel;
};

#endif // MAINWINDOW_H
