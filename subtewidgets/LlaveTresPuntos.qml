import QtQuick 2.0

Rectangle {
    id: selector
    width: 110
    height: 100
    color: "#00000000"
    border.color: "#00000000"

    signal pos1()
    signal pos2()
    signal pos3()

    property int newRot: 0
    property int nextRot: 0

    property int pos1stPosition: 0
    property int pos2ndPosition: -45
    property int pos3rdPosition: -90

    property int pos1LimitBounce: -23
    property int pos2LimitBounce: -67

    property int rotLimitDown: 0
    property int rotLimitUp: -90

    Image {
        id: bkg
        x: 0
        y: 0
        width: 78
        height: 78
        anchors.horizontalCenter: parent.horizontalCenter
        source: "resources/selector_bkg.png"
        antialiasing: true
        smooth: true
    }

    Image {
        id: sel
        x: 0
        y: 0
        width: 78
        height: 78
        transformOrigin: Item.Center
        anchors.horizontalCenter: parent.horizontalCenter
        rotation: pos1stPosition
        source: "resources/selector_handler.png"
        antialiasing: true
        smooth: true
    }

    PropertyAnimation {
        id: selectorBack;
        target: sel;
        properties: "rotation";
        to: selector.nextRot;
        duration: 60
        easing {
            type: "Linear"
        }
    }

    MouseArea {
        x: 0
        y: 6
        width: 56
        height: 62
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        transformOrigin: Item.Center

        onReleased: {
            if(newRot > pos1LimitBounce){
                nextRot = pos1stPosition;
                selector.pos1();
            }else if(newRot > pos2LimitBounce){
                nextRot = pos2ndPosition;
                selector.pos2();
            }else{
                nextRot = pos3rdPosition;
                selector.pos3();
            }
            selectorBack.start();
        }

        onPositionChanged: {
            newRot = (-Math.atan2(mouse.x - sel.width/2 , mouse.y - sel.height/2) * 180/Math.PI ) - 45;
            //-45 porque la imagen esta a 45 grados, para normalizarla en 0

            if(newRot > rotLimitDown){
                newRot = rotLimitDown;
            }else if(newRot < rotLimitUp){
                newRot = rotLimitUp;
            }
            sel.rotation = newRot;
        }
    }

    function setPos1(){
        selector.newRot = selector.pos1stPosition
        selector.nextRot = selector.pos1stPosition
        selectorBack.start()
    }

    function setPos2(){
        selector.newRot = selector.pos2ndPosition
        selector.nextRot = selector.pos2ndPosition
        selectorBack.start()
    }

    function setPos3(){
        selector.newRot = selector.pos3rdPosition
        selector.nextRot = selector.pos3rdPosition
        selectorBack.start()
    }

    MouseArea {
        id: pos1
        x: 0
        y: 49
        width: 26
        height: 37

        onClicked: {
            selector.setPos1();
            selector.pos1();
        }
    }

    MouseArea {
        id: pos2
        x: 0
        y: 0
        width: 46
        height: 28
        anchors.bottom: parent.top
        anchors.bottomMargin: -100
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter

        onClicked: {
            selector.setPos2();
            selector.pos2();
        }
    }

    MouseArea {
        id: pos3
        x: 83
        y: 49
        width: 26
        height: 37

        onClicked: {
            selector.setPos3();
            selector.pos3();
        }
    }

    Rectangle {
        id: rectangle1
        x: 19
        y: 63
        width: 4
        height: 4
        color: "#666666"
        radius: 2
        border.width: 0
    }

    Rectangle {
        id: rectangle2
        x: 86
        y: 63
        width: 4
        height: 4
        color: "#666666"
        radius: 5
        border.width: 0
    }

    Rectangle {
        id: rectangle3
        x: 52
        y: 79
        width: 4
        height: 4
        color: "#666666"
        radius: 2
        anchors.horizontalCenter: parent.horizontalCenter
        border.width: 0
    }
}



