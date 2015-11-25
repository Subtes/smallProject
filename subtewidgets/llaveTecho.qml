import QtQuick 2.0

Rectangle {
    id: llaveTecho
    width: 100
    height: 180
    color: "#00000000"
    border.color: "#00000000"

    signal pressedKeyButton()
    signal releasedKeyButton()

    Item {
        id: item_LlaveTecho
        anchors.fill: parent

        MouseArea {
            id: mouseArea_LlaveTecho
            anchors.fill: parent
            onClicked: {
                if ( llaveTecho.state == "State1_keyON"){
                    llaveTecho.state = "State1_keyOFF";
                    releasedKeyButton();
                    console.log("pressedKeyButton");
                }
                else{
                    llaveTecho.state = "State1_keyON";
                    pressedKeyButton();
                    console.log("releasedKeyButton");
                }
            }
        }

        Image {
            id: imageBase_keyOFF
            visible: true
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            fillMode: Image.PreserveAspectFit
            anchors.fill: parent
            source: "resources/techo_llave45.png"
        }
    }

    states: [
        State {
            name: "State1_keyON"

            PropertyChanges {
                target: imageBase_keyOFF
                source: "resources/techo_llave45B.png"
            }
        },
        State {
            name: "State1_keyOFF"

            PropertyChanges {
                target: imageBase_keyOFF
                source: "resources/techo_llave45.png"
            }
        }
    ]

    function isPressed(){
        if ( llaveTecho.state == "State1_keyON"){
            return true;
        }
        else{
            return false;
        }
    }
}

