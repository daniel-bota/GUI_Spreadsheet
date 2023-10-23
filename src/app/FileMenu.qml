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

Menu
{
    id: fileMenu
    title: "File"

    background: Rectangle
    {
        implicitWidth: 200
        color: menuBar.background.color
    }

    delegate: MenuItem
    {
        id: menuDelegate

        implicitWidth: parent.width
        implicitHeight: 30

        background: Rectangle
        {
            anchors.fill: parent
            color: parent.highlighted ? "lightgrey" : "transparent"
        }

        contentItem: Text
        {
            text: parent.text
            verticalAlignment: Text.AlignVCenter
            color: "black"
        }
    }

    Action
    {
        text: "New Sheet..."
        onTriggered:
        {
            table.model.clear()
            fileIO.activeFilePath = ""
        }
    }

    Action
    {
        text: "Open..."
        onTriggered: openDialog.open()
    }

    Action
    {
        text: "Save"
        onTriggered:
        {
            if (fileIO.activeFilePath.toString() === "")
            {
                saveAsDialog.open()
                return
            }

            if (!fileIO.saveFile())
            {
                saveAsDialog.open()
            }
        }
    }

    Action
    {
        text: "Save As..."
        onTriggered: saveAsDialog.open();
    }

    FileDialog
    {
        id: openDialog

        fileMode: FileDialog.OpenFile
        currentFolder: fileIO.activeFilePath.toString() === "" ? StandardPaths.writableLocation(StandardPaths.DesktopLocation) : fileIO.activeFilePath
        nameFilters: ["JSON files (*.json)", "All files (*)"]

        onAccepted:
        {
            fileIO.activeFilePath = selectedFile
            fileIO.openFile()
        }
    }

    FileDialog
    {
        id: saveAsDialog
        fileMode: FileDialog.SaveFile
        currentFolder: fileIO.activeFilePath.toString() === "" ? StandardPaths.writableLocation(StandardPaths.DesktopLocation) : fileIO.activeFilePath
        nameFilters: ["JSON files (*.json)"]

        onAccepted:
        {
            fileIO.activeFilePath = selectedFile
            fileIO.saveFile()
        }
    }

    FileIO
    {
        id: fileIO

        function openFile()
        {
            if (!fileIO.read() || !table.model.deserialize(fileIO.activeFile))
            {
                console.log("Failed to open file.")
                return false
            }

            console.log("File was opened successfully.")
            return true
        }

        function saveFile()
        {
            if(!fileIO.write(table.model.serialize()))
            {
                console.log("Failed to save file.")
                return false
            }

            console.log("File saved successfully.")
            return true
        }
    }
}
