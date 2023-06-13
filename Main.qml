import QtQuick
import QtCore
import QtQuick.Controls
import QtQuick.Controls.Fusion
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt.labs.folderlistmodel
import "./Resources/CustomMenuBar"
import "./Resources/Table"
import SheetModel 1.0
import SheetModel 1.1
import UI 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 1280
    height: 720
    title: qsTr("Spreadsheet")
    color: "whitesmoke"

    MenuBar
    {
        id: menuBar

        background: Rectangle
        {
            color: applicationWindow.color
        }

        delegate: MenuBarItem
        {
            id: menuBarDelegate
            implicitWidth: 100
            implicitHeight: 30

            contentItem: Text
            {
                text: parent.text
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "black"
            }

            onHighlightedChanged:
            {
                background.color = highlighted ? "lightgrey" : "transparent"
            }
        }

        FileMenu {
            id: fileMenu
        }
    }

    ScrollView
    {
        id: scrollView
        anchors
        {
            right: parent.right
            left: parent.left
            top: menuBar.bottom
            bottom: parent.bottom
        }
        enabled: true
        focus: true
        spacing: 0
        background: Rectangle
        {
            anchors.fill: parent
            color: "transparent"
        }

        Rectangle
        {
            id: bottomTableMargin
            color: "transparent"
            anchors
            {
                right: parent.right
                left: parent.left
                bottom: parent.bottom
            }

            height: 50
        }

        ScrollBar
        {
            id: tableVerticalScrollBar
            policy: ScrollBar.AlwaysOn
            anchors.right: parent.right
            anchors.top: columnHeaders.bottom
            anchors.bottom: tableHorizontalScrollBar.top
            width: 20
            orientation: Qt.Vertical
            size: table.visibleArea.heightRatio;
            position: table.contentY / table.contentHeight

            onPositionChanged:
            {
                if (!active)
                {
                    return;
                }

                table.contentY = position * table.contentHeight;
            }
        }

        ScrollBar
        {
            id: tableHorizontalScrollBar
            policy: ScrollBar.AlwaysOn
            anchors.left: rowHeaders.right
            anchors.bottom: bottomTableMargin.top
            anchors.right: tableVerticalScrollBar.left
            height: 20
            orientation: Qt.Horizontal
            size: table.visibleArea.widthRatio
            position: table.contentX / table.contentWidth

            onPositionChanged:
            {
                if (!active)
                {
                    return;
                }

                table.contentX = position * table.contentWidth;
            }
        }

        ColumnHeaders {
            id: columnHeaders
        }

        RowHeaders {
            id: rowHeaders
        }

        SheetTable {
            id: table
        }

    }
}
























//    Rectangle
//    {
//        id: menuBar
//        anchors
//        {
//            right: parent.right
//            left: parent.left
//            top: parent.top
//        }
//        color: "whitesmoke"
//        height: 30

//        Row
//        {
//            id: menuButtons
//            anchors.fill: parent

//            property bool isMenuOpen: false;
//            property Menu openMenu: nullMenu;

//            Menu
//            {
//                id: nullMenu
//            }

//            FileButton {
//                id: fileButton
//            }

//            MenuBarButton
//            {
//                id: editButton

//                Text
//                {
//                    id: editButtonText
//                    anchors.centerIn: parent
//                    text: "Edit"
//                }

//                onClicked:
//                {
//                    if (!editMenu.opened())
//                    {
//                        editMenu.open()
//                        return;
//                    }

//                    editMenu.close()
//                }

//                onEntered:
//                {
//                    if (menuButtons.openMenu == nullMenu)
//                    {
//                        return
//                    }

//                    editMenu.open()
//                }

//                MenuBarDropdown
//                {
//                    id: editMenu

//                    MenuBarButton
//                    {
//                        id: cutButton
//                        width: parent.width
//                        height: editButton.height

//                        Text
//                        {
//                            text: "Cut"
//                            leftPadding: editButtonText.x
//                            anchors.verticalCenter: parent.verticalCenter
//                        }
//                    }

//                }
//            }

//            MenuBarButton
//            {
//                id: optionsButton

//                MenuItem
//                {
//                    background: Rectangle
//                    {

//                    }
//                }

//                Text
//                {
//                    id: optionsButtonText
//                    anchors.centerIn: parent
//                    text: "Options"
//                }

//                onClicked: optionsMenu.open()

//                MenuBarDropdown
//                {
//                    id: optionsMenu
//                    height: 500
//                    width: 200

//                    Column
//                    {
//                        anchors.fill: parent
//                        MenuBarButton
//                        {
//                            id: goToMenuButton
//                            width: parent.width
//                            height: optionsButton.height

//                            Text
//                            {
//                                text: "Go To Menu"
//                                leftPadding: optionsButtonText.x
//                                anchors.verticalCenter: parent.verticalCenter
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }



















//    ScrollView
//    {
//        id: scrollView
//        anchors
//        {
//            right: parent.right
//            left: parent.left
//            top: menuBar.bottom
//            bottom: parent.bottom
//        }
//        enabled: true

//        ScrollBar.horizontal: ScrollBar
//        {
//            policy: ScrollBar.AlwaysOff
//        }
//        ScrollBar.vertical: ScrollBar
//        {
//            policy: ScrollBar.AlwaysOff
//        }

//        ScrollBar.vertical: ScrollBar
//        {
//            policy: ScrollBar.AlwaysOn
//            snapMode: ScrollBar.NoSnap
//            anchors.right: parent.right
//            anchors.top: parent.top
//            anchors.bottom: parent.bottom
//            anchors.topMargin: 30
//        }
//    }
//}
