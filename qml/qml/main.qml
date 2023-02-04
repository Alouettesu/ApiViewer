import QtQuick 2.12
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Stack")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : ""
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.currentItem == apiElementCommentView)
                {
                    //Force model refresh
                    apiElementsView.apiId = apiElementsView.apiId
                }

                if (stackView.depth > 1) {
                    stackView.pop()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    HomeForm {
        id: homeForm
        onApiSelected: {
            stackView.push(apiElementsView, {"apiId": api_id})
        }
    }

    ApiElementsView {
        id: apiElementsView
        onApiElementSelected: {
            apiElementCommentView.refreshModel(api_id, operationId)
            stackView.push(apiElementCommentView)
        }
    }

    ApiElementCommentView {
        id: apiElementCommentView

    }

    StackView {
        id: stackView
        initialItem: homeForm
        anchors.fill: parent

    }
}
