import QtQuick
import QtCore
import QtQuick.Controls
import QtQuick.Controls.Fusion
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt.labs.folderlistmodel

VerticalHeaderView
{
    id: rowHeaders
    anchors.left: parent.left
    anchors.top: columnHeaders.bottom

    interactive: false
    focus: false
    enabled: true
    keyNavigationEnabled: false

    resizableRows: true
    syncView: table
    clip: true

    boundsMovement: Flickable.StopAtBounds

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
}
