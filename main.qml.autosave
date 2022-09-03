import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
//import "icons" as Icons


ApplicationWindow {
    id: root
    minimumHeight: 800
    minimumWidth: 1200
    width: Screen.width * 0.6
    height: Screen.height * 0.8
    visible: true
    title: qsTr("Icom PCR1000")
    
    property bool powerOn: false
    property int hzOnes: 0
    property int hzTens: 0
    property int hzHunds: 0
    property int kHzOnes: 0
    property int kHzTens: 0
    property int kHzHunds: 0
    property int tuningStepSize: 1
    
    header: ToolBar {
        id: toolbar
        width: parent.width
        contentItem.children: iconrow
        RowLayout {
            id: iconrow
            ToolButton {
                id: pwr
                visible: true
                
                icon.source: {
                    if (powerOn) { return "qrc:icons/toolbar/pwrOnLg.png" }
                    else { return "qrc:icons/toolbar/pwrOffLg.png" }
                }
                onClicked: {if (powerOn == false) {powerOn = true}
                    else {powerOn = false}
                }
            }
            
        }
    }
    Item {
        id: tuningColumn
        visible: true
        width: parent.width / 2.5
        height: parent.height
        //background: powerOn ? "red" : "black"
        anchors.horizontalCenter: parent.horizontalCenter

        Label {
            id: tuningLabel
            visible: true
            text: "TUNING"
            font.pixelSize: root.height * 0.05
            font.bold: true
            color: powerOn ? "green" : "black"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
        }




        // Hz Ones Digit
        Text {
            id: onesDigit
            anchors.top: tuningLabel.bottom
            anchors.right: tuningColumn.right
            text: hzOnes.toString()
            font.pixelSize: root.height * 0.05
            leftPadding: 5
            MouseArea {
                width: parent.width
                height: parent.height
                enabled: powerOn ? true : false
                cursorShape: powerOn ? Qt.PointingHandCursor : Qt.ArrowCursor
                onWheel: {
                    if (wheel.angleDelta.y > 0) {hzOnes++}
                    else {hzOnes--}
                    if (hzOnes > 9) {
                        hzOnes = 0;
                        hzTens++;
                        if (hzTens > 9) {
                            hzTens = 0;
                        }
                    } else if (hzOnes < 0) {
                        hzOnes = 9;
                        hzTens--;
                        if (hzTens < 0) {
                            hzTens = 9;
                            }
                        }
                    }
                }
            }



/*
//        // Hz Tens Digit
//        Text {
//            id: tensDigit
//            anchors.top: tuningLabel.bottom
//            anchors.right: onesDigit.left
//            text: hzTens.toString()
//            font.pixelSize: root.height * 0.05
//            leftPadding: 5
//            MouseArea {
//                width: parent.width
//                height: parent.height
//                enabled: powerOn ? true : false
//                cursorShape: powerOn ? Qt.PointingHandCursor : Qt.ArrowCursor
//                onWheel: {
//                    if (wheel.angleDelta.y > 0) {hzTens++}
//                    else {hzTens--}
//                    if (hzTens > 9) {
//                        hzTens = 0;
//                        hzHunds++;
//                        if (hzHunds > 9) {
//                            hzHunds = 0;
//                        }
//                    } else if (hzTens < 0) {
//                        hzTens = 9;
//                        hzTens--;
//                        if (hzHunds < 0) {
//                            hzHunds = 9;
//                            }
//                        }
//                }
//            }
//        }

//        // Hz Hundreds Digit
//        Text {
//            id: hundredsDigit
//            anchors.top: tuningLabel.bottom
//            anchors.right: tensDigit.left
//            text: hzHunds.toString()
//            font.pixelSize: root.height * 0.05
//            leftPadding: 10
//            MouseArea {
//                width: parent.width
//                height: parent.height
//                enabled: powerOn ? true : false
//                onWheel: {
//                    if (wheel.angleDelta.y > 0) {hzHunds++}
//                    else {hzHunds--}
//                    if (hzHunds > 9) { hzHunds = 0;}
//                    else if (hzHunds < 0) {hzHunds = 9;
//                        if (hzHunds > 9) {
//                            hzHunds = 0;
//                            kHzOnes++;
//                            if (kHzOnes > 9) {
//                                kHzOnes = 0;
//                            }
//                        } else if (hzHunds < 0) {
//                            hzHunds = 9;
//                            kHzOnes--;
//                            if (kHzOnes < 0) {
//                                kHzOnes = 9;
//                                }
//                            }
//                    }
//                }
//            }
//        } // hundreds

//        // kHz Ones Digit
//        Text {
//            id: kHzOnesDigit
//            anchors.top: tuningLabel.bottom
//            anchors.right: hundredsDigit.left
//            text: kHzOnes.toString()
//            font.pixelSize: root.height * 0.05
//            leftPadding: 10
//            MouseArea {
//                width: parent.width
//                height: parent.height
//                enabled: powerOn ? true : false
//                onWheel: {
//                    if (wheel.angleDelta.y > 0) {kHzOnes++}
//                    else {kHzOnes--}
//                    if (kHzOnes > 9) { kHzOnes = 0;}
//                    else if (kHzOnes < 0) {kHzOnes = 9;
//                        if (hzHunds > 9) {
//                            hzHunds = 0;
////                            kHzOnes++;
////                            if (kHzOnes > 9) {
////                                kHzOnes = 0;
////                            }
////                        } else if (hzHunds < 0) {
////                            hzHunds = 9;
////                            kHzOnes--;
////                            if (kHzOnes < 0) {
////                                kHzOnes = 9;
////                                }
////                            }
//                        }
//                    }
//                }
//            }
//        } // hundreds
*/
    } // Item
} // root


