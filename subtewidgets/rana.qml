import QtQuick 2.0

Rectangle {
    id: rectangle1
    objectName: "rana"
    width: 100
    height: 100
    color: "#00000000"

    //Interface basica SIGNAL & SLOT
    signal position_AD()
    signal position_0()
    signal position_AT()

    function move(){
        if (item1.state == "AD"){
            item1.state = "CERO";
            position_0();
            console.log("posicion CERO")
        }
        if(item.state == "AT"){
            item1.state = "CERO"
            position_0();
            console.log("posicion CERO")
        }

    }

    Item {
        id: item1
        width: 100
        height: 100

        Image {
            id: image1
            x: 0
            y: 0
            width: 100
            height: 100
            fillMode: Image.Stretch
            opacity: 1
            source: "resources/blue.PNG"
        }

        MouseArea {
            id: mouseAreaItem1
            anchors.fill: parent
            onClicked: {
                console.log(" ---> rana on: ", item1.state);
                rana.move();
                console.log(" ---> moving Rana to",item1.state);
            }
        }
    }
    states: [
        State {
            name: "AD"

            PropertyChanges {
                target: image1
                source: "resources/redON.png"
            }
        },
        State {
            name: "CERO"

            PropertyChanges {
                target: image1
                source: "resources/blueON.png"
            }
        },
        State {
            name: "AT"

            PropertyChanges {
                target: image1
                opacity: 1
                source: "resources/greenON.png"
            }
        }
    ]
}

