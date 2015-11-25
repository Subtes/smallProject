import QtQuick 2.0


Rectangle {
    width: 260
    height: 260
    color: "#00000000"
    border.color: "#00000000"

    Image {
        id: background
        anchors.fill: parent
        source: "resources/velocimetroLed_Bkg.PNG"
    }

    Rectangle {
        id: needle
        objectName: "needle"
        x: 126
        y: 130
        width: 5
        height: 60
        color: "#a03131"
        rotation: 7
        transformOrigin: Item.Top
        border.color: "#00000000"
        radius: 2
        border.width: 0
        smooth:true
        property double speed: 22;
    }

    Rectangle {
        x: 121
        y: 123
        width: 14
        height: 14
        color: "#650303"
        radius: 7
        smooth:true

    }

    PropertyAnimation {
        id: animateNeedle;
        target: needle;
        properties: "rotation";
        to: needle.speed;
        duration: 500
        easing {
            type: "Linear"
        }
    }

    function updateNeedle(speedIN) {
            if(speedIN<0){
                speedIN=0
            }else if(speedIN>120){
                speedIN=120
            }

            if(speedIN<=50){
                needle.speed = (speedIN*2.65)+17
            }else if(speedIN>50 && speedIN<=70){
                needle.speed = ((speedIN+2)*2.65)+17
            }else if(speedIN>70 && speedIN<=90){
                needle.speed = ((speedIN+3)*2.65)+17
            }else if(speedIN>90){
                needle.speed = ((speedIN+4)*2.65)+17
            }
            animateNeedle.start();
            return "ok";
        }
}
