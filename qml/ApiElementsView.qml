import QtQuick 2.12
import QtQuick.Controls 2.12
import MyControllers 1.0

Page {
    width: 600
    height: 400

    title: qsTr("Элементы API")


    ApiElementsController {
        id: controller
    }

    property alias apiId: controller.apiId

    TableView {
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        model: controller.model

        property var columnWidths: [0, 0, 100, 150, 0, 200, 0, 200]
        columnWidthProvider: function (column) { return columnWidths[column] }

        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            border.color: "black"
            border.width: 1
            clip: true
            Text {
                clip: true
                text: display
                anchors.margins: 2
                wrapMode: Text.WrapAnywhere
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
//                    var api_id = controller.model.data(controller.model.index(model.row, 0))
//                    apiSelected(api_id)
                }
            }

        }
    }
}
