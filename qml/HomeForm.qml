import QtQuick 2.12
import QtQuick.Controls 2.15
import MyControllers 1.0

Page {
    width: 600
    height: 400

    title: qsTr("Список API")

    signal apiSelected(int api_id)

    ApisController {
        id: controller
    }

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

        property var columnWidths: [0, 250, 100, 200]
        columnWidthProvider: function (column) { return columnWidths[column] }

        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            color: "#efefef"
            clip: true
            Text {
                clip: true
                padding: 12
                text: display
                anchors.margins: 2
                wrapMode: Text.WrapAnywhere
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var api_id = controller.model.data(controller.model.index(model.row, 0))
                    apiSelected(api_id)
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
