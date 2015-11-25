import QtQuick 2.0

Rectangle {
    id: gauge
    width: 212
    height: 212
    color: "#00000000"
    border.color: "#00000000"

    property double currentValue: 0
    property double maxValue: 100
    property double minValue: -100
    property double maxAngle: 0
    property double offsetAngle: 0
    property double originX: width/2
    property double originY: height/2

    Image {
        id: background
        objectName: "background"
        anchors.fill: parent
        source: "resources/Relojtecho01.png"
    }

    Image {
        id: needle
        objectName: "needle"
        anchors.fill: parent
        antialiasing: true
        smooth: true
        source: "resources/RelojtechoAGUJA01.png"
        transform: Rotation {
            id: rot
            origin.x: gauge.originX
            origin.y: gauge.originY
            angle: 0
            Behavior on angle {
                PropertyAnimation{
                    duration: 1500
                    easing {type: Easing.OutBack}
                }
            }
        }
    }

    function updateNeedle(valueIN) {
        if(valueIN<minValue){
            valueIN=minValue
        }else if(valueIN>maxValue){
            valueIN=maxValue
        }
        currentValue = (valueIN/maxValue)*maxAngle + offsetAngle
        rot.angle = currentValue
        return "ok"
    }
}



