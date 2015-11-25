import QtQuick 2.0


Rectangle {
    id: selector
    width: 100
    height: 100
    color: "#00000000"
    border.color: "#00000000"

    signal washer();
    signal wiper();
    signal off();

    property int newRot: 0;
    property int nextRot: 0;

    property int rotLimitDown: -90;
    property int rotLimitDownBounce: -60;
    property int rotOn: -45;
    property int rotLimitUp: 0;

    Image {
        id: bkg
        anchors.fill: parent
        source: "resources/selector_bkg.png"
        antialiasing: true
        smooth: true
    }

    Image {
        id: sel
        anchors.fill: parent
        rotation: -90
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
        anchors.fill: parent

        onReleased: {
            if(sel.rotation <= rotLimitDownBounce){
                selector.off();
                selector.nextRot = rotLimitDown;
            }else{
                selector.wiper();
                selector.nextRot = rotOn;
            }
            selectorBack.start();

        }

        onPositionChanged: {
            newRot = (-Math.atan2(mouse.x - selector.width/2 , mouse.y - selector.height/2) * 180/Math.PI) - 45;
            if(newRot < rotLimitDown){
                newRot = rotLimitDown;
            }else if(newRot > rotLimitUp){
                newRot = rotLimitUp;
                selector.washer();
            }
            sel.rotation = newRot;
        }
    }
}

