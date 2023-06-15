import QtQuick
import QtCore
import QtQuick.Controls
import QtQuick.Controls.Fusion
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt.labs.folderlistmodel
import "../CustomMenuBar"
import "../Table"
import SheetModel 1.0
import SheetModel 1.1
import UI 1.0

TableView
{
    id: table

    anchors.top: columnHeaders.bottom
    anchors.bottom: tableHorizontalScrollBar.top
    anchors.left: rowHeaders.right
    anchors.right: tableVerticalScrollBar.left

    property int previousContentX: -1
    property int previousContentY: -1

    property string editInput: ""

    function ensureRows()
    {
        if (contentY > previousContentY && model.lastRetrievedAddress.y >= rows - 1)
        {
            model.insertRows();
            return;
        }

        if (contentY < previousContentY && model.lastRetrievedAddress.y <= rows - 75)
        {
            model.removeRows();
        }
    }
    function ensureColumns()
    {
        if (contentX > previousContentX && model.lastRetrievedAddress.x >= columns - 1)
        {
            model.insertColumns();
            return;
        }

        if (contentX < previousContentX && model.lastRetrievedAddress.x <= columns - 51)
        {
            model.removeColumns();
        }
    }

    clip: true
    interactive: true
    keyNavigationEnabled: true
    focus: true
    enabled: true
    boundsMovement: Flickable.StopAtBounds
    editTriggers: TableView.NoEditTriggers

    selectionModel: ItemSelectionModel
    {
        id: tableSelectionModel
        model: tableModel
    }
    model: CustomTableModel
    {
        id: tableModel
    }

    delegate: Rectangle
    {
        id: delegate
        property TableView thisTable: TableView.view
        required property bool selected
        required property bool current
        property var value: model.value

        implicitWidth: 170
        implicitHeight: 30
        color: "white"
        border
        {
            width: current ? 2 : 1
            color: current ? "green" : "whitesmoke"
        }
        Text
        {
            id: textField
            anchors.fill: parent
            color: "black"
            font.pixelSize: 15
            text: model.display
            horizontalAlignment: typeof(value) === "number" ? Text.AlignRight : Text.AlignLeft
            verticalAlignment: Text.AlignBottom
            leftPadding: 4
            rightPadding: 4
            wrapMode: Text.Wrap
            clip: true
        }

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                var row = index % thisTable.rows;
                var column = Math.floor(index / thisTable.rows);
                tableSelectionModel.setCurrentIndex(
                            tableModel.index(row,column),
                            tableSelectionModel.Select | tableSelectionModel.ToggleCurrent)
            }
        }

        TableView.editDelegate: TextField
        {
            id: inputField
            anchors.fill: parent
            color: "black"
            font.pixelSize: 15

            background: Rectangle
            {
                border.color: "orange"
                border.width: 2
            }

            verticalAlignment: Text.AlignBottom
            text: table.editInput == "" ? edit : table.editInput

            TableView.onCommit:
            {
                display = text
                table.editInput = ""
            }
        }
    }

    Component.onCompleted:
    {
        console.log("table generation complete")

        ensureRows();
        ensureColumns();

        tableSelectionModel.setCurrentIndex(
                    tableModel.index(0,0),
                    tableSelectionModel.Select | tableSelectionModel.ToggleCurrent);
    }

    Keys.onPressed:
        (event) =>
        {
            if (event.text.length > 0 && event.key !== Qt.Key_Tab)
            {
                editInput = event.text
                edit(table.index(currentRow, currentColumn))
            }

            if (event.key === Qt.Key_F2)
            {
                editInput = event.text
                edit(table.index(currentRow, currentColumn))
            }
        }

    onContentXChanged:
    {
        ensureColumns();

        previousContentX = contentX;
    }

    onContentYChanged:
    {
        ensureRows();

        previousContentY = contentY;
    }

}
