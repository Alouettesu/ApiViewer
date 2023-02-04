import QtQuick 2.12
import QtQuick.Controls 2.15
import MyControllers 1.0

Page {
    width: 600
    height: 400

    title: qsTr("Элементы API")


    signal apiElementSelected(int api_id, string operationId)
    ApiElementsController {
        id: controller
    }

    property alias apiId: controller.apiId

    TableView {
        id: tableView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: horizontalHeader.bottom
        columnSpacing: 1
        rowSpacing: 1
        clip: true
        boundsBehavior: Flickable.StopAtBounds

        model: controller.model

        property var columnWidths: [0, 0, 100, 150, 0, 200, 0, 200]
        columnWidthProvider: function (column) { return columnWidths[column] }

        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            color: "#efefef"
            clip: true
            Text {
                clip: true
                text: display
                padding: 12
                anchors.margins: 2
                wrapMode: Text.WrapAnywhere
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var api_id = controller.model.data(controller.model.index(model.row, 1))
                    var operationId = controller.model.data(controller.model.index(model.row, 4))
                    apiElementSelected(api_id, operationId)
                }
            }
        }
    }

    HorizontalHeaderView {
        id: horizontalHeader
        syncView: tableView
        anchors.left: tableView.left
    }
}
