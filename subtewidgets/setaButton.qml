import QtQuick 2.0

Rectangle {
    id: setaButton
    width: 150
    height: 150
    color: "#00000000"

    signal pressedButton()
    signal releasedButton()

    Item {
        id: item_SetaButton
        anchors.fill: parent

        MouseArea {
            id: mouseArea_SetaButton
            anchors.fill: parent
            onClicked: {
                if ( setaButton.state == "State1_SetaON"){
                    setaButton.state = "State1_SetaOFF";
                    releasedButton();
                }
                else{
                    setaButton.state = "State1_SetaON";
                    pressedButton();
                }
            }
        }

        Image {
            id: imageBase_SetaOff
            anchors.fill: parent
            source: "resources/setaOff.png"
        }
    }

    states: [
        State {
            name: "State1_SetaON"

            PropertyChanges {
                target: imageBase_SetaOff
                source: "resources/setaOn.png"
            }
        },
        State {
            name: "State2_SetaOFF"

            PropertyChanges {
                target: imageBase_SetaOff
                source: "resources/setaOff.png"
            }
        }
    ]

    function isPressed(){
        if ( setaButton.state == "State1_SetaON"){
            return true;
        }
        else{
            return false;
        }
    }
}

