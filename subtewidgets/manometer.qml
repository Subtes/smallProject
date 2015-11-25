import QtQuick 2.0

Rectangle {
    id: manometer    
    width: 188
    height: 182
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
        id: image1
        sourceSize.height: 182
        sourceSize.width: 188
        objectName:"background"    
        anchors.fill: parent
        source: "resources/manometro_bkg.png"
    }
    Image {
        id: image2

        objectName: "needleWhite"
        anchors.fill: parent
        smooth: true
        source: "resources/manometro_aguja_blanca.png"
        transform: Rotation{
            id: rotW
            origin.x: manometer.originX
            origin.y: manometer.originY
            angle: 0
            Behavior on angle {
                PropertyAnimation{
                  duration : 400
                  easing {type: Easing.OutQuad}
                }
            }
        }
    }
    Image {
        id: image3
        objectName: "needleRed"
        rotation: 0
        anchors.fill: parent
        smooth: true
        source: "resources/manometro_aguja_roja.png"
        transform: Rotation{
            id: rotR
            origin.x: manometer.originX
            origin.y: manometer.originY
            angle: 0
            Behavior on angle {
                PropertyAnimation{
                    duration : 400
                    easing {type: Easing.OutQuad}
                }
            }
        }
    }

    Image {
        id: image4
        objectName: "glass"    
        anchors.fill: parent
        source: "resources/manometro_glass.png"
    }
// Needle white
    function updateNeedleWhite(valueIN) {
        if(valueIN<minValue){
            valueIN=minValue
        }else if(valueIN>maxValue){
            valueIN=maxValue
        }
        currentValue = (valueIN/maxValue)*maxAngle + offsetAngle
        rotW.angle = currentValue
        return "ok"
    }
/// Needle red
    function updateNeedleRed(valueIN) {
        if(valueIN<minValue){
            valueIN=minValue
        }else if(valueIN>maxValue){
            valueIN=maxValue
        }
        currentValue = (valueIN/maxValue)*maxAngle + offsetAngle
        rotR.angle = currentValue
        return "ok"
    }
}

