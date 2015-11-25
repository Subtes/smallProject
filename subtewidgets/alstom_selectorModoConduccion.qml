import QtQuick 2.0

Rectangle {
    id: selector
    width: 137
    height: 137
    color: "#00000000"
    border.color: "#00000000"

    signal pos1()
    signal pos2()
    signal pos3()
    signal pos4()

    property int newRot: 0
    property int nextRot: 0

    property int pos1stPosition: 0
    property int pos2ndPosition: 30
    property int pos3rdPosition: 60
    property int pos4thPosition: 90

    property int pos1LimitBounce: 15
    property int pos2LimitBounce: 45
    property int pos3LimitBounce: 75

    property int rotLimitDown: 0
    property int rotLimitUp: 90

    Image {
        id: sel
        anchors.fill: parent
        source: "resources/alstom_perilla4.png"
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
            if(newRot < pos1LimitBounce){
                nextRot = pos1stPosition;
                selector.pos1();
            }else if(newRot < pos2LimitBounce){
                nextRot = pos2ndPosition;
                selector.pos2();
            }else if(newRot < pos3LimitBounce){
                nextRot = pos3rdPosition;
                selector.pos3();
            }else {
                nextRot = pos4thPosition;
                selector.pos4();
            }
            selectorBack.start();
        }

        onPositionChanged: {
            newRot = -(Math.atan2(mouse.x - selector.width/2, mouse.y - selector.height/2) * 180/Math.PI )-90;

            if(newRot < 0 && newRot >-150){
                newRot = rotLimitDown;
            }else if(newRot < 0 && newRot >-270){
                newRot = rotLimitUp;
            }
            sel.rotation = newRot;
        }
    }

    /*
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
    */
}
