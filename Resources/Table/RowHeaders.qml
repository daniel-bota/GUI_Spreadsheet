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

VerticalHeaderView
{
    id: rowHeaders
    anchors.left: parent.left
    anchors.top: columnHeaders.bottom

    interactive: false

    delegate: Rectangle
    {
        implicitWidth: 50
        implicitHeight: 30
        color: table.currentRow === index ? "darkgrey" : "lightgrey"
        Text
        {
            text: model.display
            anchors.centerIn: parent
        }
    }
    resizableRows: true
    syncView: table
    clip: true

    boundsMovement: Flickable.StopAtBounds
}
