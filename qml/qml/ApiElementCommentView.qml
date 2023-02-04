import QtQuick 2.12
import QtQuick.Controls 2.12
import Qt.labs.qmlmodels 1.0
import MyControllers 1.0

Page {
    width: 600
    height: 400

    title: qsTr("Элемент API")

    function refreshModel(apiId, operationId) {
        apiElementCommentModel.select(apiId, operationId)
    }

    ApiElementCommentModel {
        id: apiElementCommentModel
    }

    TableView {
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        boundsBehavior: Flickable.StopAtBounds

        model: tableModel
        delegate: chooser

        DelegateChooser {
            id: chooser
            DelegateChoice {
                row: 4
                column: 1
                TextInput {
                    text: model.display
                    padding: 12
                    Rectangle {
                        anchors.fill: parent
                        color: "#efefef"
                        z: -1
                    }
                    onEditingFinished: {
                        apiElementCommentModel.comment = text
                    }
                }
            }
            DelegateChoice {
                Text {
                    text: model.display
                    padding: 12
                    Rectangle {
                        anchors.fill: parent
                        color: "#efefef"
                        z: -1
                    }
                }
            }
        }
    }


    TableModel {
        id: tableModel
        TableModelColumn { display: "name" }
        TableModelColumn { display: "value" }

        rows: [
            {
                name: "Method",
                value: apiElementCommentModel.method,
            },
            {
                name: "URL",
                value: apiElementCommentModel.url,
            },
            {
                name: "OperationId",
                value: apiElementCommentModel.operationId,
            },
            {
                name: "Summary",
                value: apiElementCommentModel.summary,
            },
            {
                name: "Comment",
                value: apiElementCommentModel.comment,
            }

        ]
    }

}
