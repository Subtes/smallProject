import QtQuick 2.0

Rectangle {
    id: speedGauge
    width: 520
    height: 520
    color: "#00000000"
    border.color: "#00000000"

    property int maxGaugeSpeed: 120
    property int currentSpeed: 0
    property int maxSpeed: 0
    property int greenIndex: 0
    property int yellowIndex: 0
    property bool onStatus: false

    Image {
        id: background
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        source: "resources/velocimetroLed_Bkg.png"
        antialiasing: true
        smooth: true
    }

    Image {
        id: am
        x: speedGauge.width * 0.6961
        y: speedGauge.width * 0.9038
        width: speedGauge.width * 0.0788
        height: speedGauge.width * 0.0423
        source: "resources/velocimetroLedAM_OFF.png"
        antialiasing: true
        smooth: true
    }

    Image {
        id: fm
        x: speedGauge.width * 0.8019
        y: speedGauge.width * 0.9038
        width: speedGauge.width * 0.0788
        height: speedGauge.width * 0.0423
        source: "resources/velocimetroLedFM_OFF.png"
        antialiasing: true
        smooth: true
    }

    Image {
        id: codigos
        x: speedGauge.width * 0.1269
        y: speedGauge.width * 0.9038
        width: speedGauge.width * 0.1730
        height: speedGauge.width * 0.0423
        source: "resources/velocimetroLedcodigosOFF.png"
        antialiasing: true
        smooth: true
    }

    /*** LEDS SET ***/
    property variant greenLeds: [];
    property variant yellowLeds: [];

    Repeater {
        model: 95
        Image {
            id: yellow
            width: speedGauge.width * 0.0268
            height: speedGauge.width * 0.0652
            opacity: 0
            rotation: getRotation(index,197,360/103)
            x: getX((yellow.rotation-90)*Math.PI/180,speedGauge.width * 0.3634,speedGauge.width * 0.4884)
            y: getY((yellow.rotation-90)*Math.PI/180,speedGauge.width * 0.3615,speedGauge.width * 0.4748)
            source: "resources/velocimetroLedON_AMARILLO.png"
            antialiasing: true
            smooth: true
            states: [
                State {
                    name: "on"
                    PropertyChanges { target: yellow; opacity: 1;}
                },
                State {
                    name: "off"
                    PropertyChanges { target: yellow; opacity: 0;}
                }
            ]

            transitions: Transition {
                PropertyAnimation { properties: "opacity"; duration: 200 }
            }
        }
        onItemAdded: yellowLeds[index] = item
    }

    Repeater {
        model: 96
        Image {
            id: green
            width: speedGauge.width * 0.0230
            height: speedGauge.width * 0.0518
            opacity: 0
            rotation: getRotation(index,194,360/103)
            x: getX((green.rotation-90)*Math.PI/180,speedGauge.width * 0.3095,speedGauge.width * 0.4903)
            y: getY((green.rotation-90)*Math.PI/180,speedGauge.width * 0.3115,speedGauge.width * 0.4788)
            source: "resources/velocimetroLedON_VERDE.png"
            antialiasing: true
            smooth: true
            states: [
                State {
                    name: "on"
                    PropertyChanges { target: green; opacity: 1;}
                },
                State {
                    name: "off"
                    PropertyChanges { target: green; opacity: 0;}
                }
            ]

            transitions: Transition {
                PropertyAnimation { properties: "opacity"; duration: 200 }
            }

        }
        onItemAdded: greenLeds[index] = item
    }

    Image {
        id: red
        x: speedGauge.width * 0.4
        y: speedGauge.width * 0.8269
        width: speedGauge.width * 0.0269
        height: speedGauge.width * 0.0653
        rotation: 13
        opacity: 0
        source: "resources/velocimetroLedON_ROJO.png"
        antialiasing: true
        smooth: true
    }

    Image {
        id: aroBlanco
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        source: "resources/velocimetroLedAroBlanco.png"
        antialiasing: true
        smooth: true
    }

    Image {
        id: glass
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        source: "resources/velocimetroLedGlass.png"
        antialiasing: true
        smooth: true
    }

    function getX(rot,r,offset){
        return (r*Math.cos(rot)+offset)
    }

    function getY(rot,r,offset){
        return (r*Math.sin(rot)+offset)
    }

    function getRotation(index,start,rot){
        return start + (rot * index)
    }

    function updateSpeed(speed){
        if(speed>=120)
        {
            currentSpeed = 95
        }else if(speed>0){
            currentSpeed = speed*96/120
        }else{
            currentSpeed=0
        }

        if(onStatus){
            if (greenIndex>currentSpeed){
                for(greenIndex; greenIndex>=currentSpeed; greenIndex--){
                    greenLeds[greenIndex].state = "off"
                }
                greenIndex++
            }else if (greenIndex<currentSpeed){
                for(greenIndex; greenIndex<=currentSpeed; greenIndex++){
                    greenLeds[greenIndex].state = "on"
                }
                greenIndex--
            }
        }
    }

    function updateMaxSpeed(speed){
        red.opacity = 1
        if(speed>=120)
        {
            maxSpeed = 94
        }else if(speed>0){
            maxSpeed = speed*95/120
        }else{
            maxSpeed=0
        }
        if(onStatus){
            if (yellowIndex>maxSpeed){
                for(yellowIndex; yellowIndex>=maxSpeed; yellowIndex--){
                    yellowLeds[yellowIndex].state = "off"
                }
                yellowIndex++
            }else if (yellowIndex<maxSpeed){
                for(yellowIndex; yellowIndex<=maxSpeed; yellowIndex++){
                    yellowLeds[yellowIndex].state = "on"
                }
                yellowIndex--
            }
        }
    }

    function turnOff(){
        updateSpeed(0);
        updateMaxSpeed(0);
        red.opacity = 0;
        onStatus = false;
    }

    function turnOn(){
        red.opacity = 1;
        updateMaxSpeed(60);
        updateSpeed(0);
        onStatus = true;
    }

/******************** Modos ATP ATO EEE --- As ***********************/
    Image {
        id: m_sourceModoOFF
        x: speedGauge.width * 0.4307
        y: speedGauge.width * 0.5576
        width: speedGauge.width * 0.1384
        height: speedGauge.width * 0.07115
        source: "resources/velocimetroMODO---.png"
        antialiasing: true
        smooth: true
    }

    Image {
        id: m_sourceModo
        x: speedGauge.width * 0.4307
        y: speedGauge.width * 0.5576
        width: speedGauge.width * 0.1384
        height: speedGauge.width * 0.07115
        source: "resources/velocimetroMODO.png"
        antialiasing: true
        smooth: true
    }

    Image {
        id: m_sourceModo20
        x: speedGauge.width * 0.4307
        y: speedGauge.width * 0.5576
        width: speedGauge.width * 0.1384
        height: speedGauge.width * 0.07115
        source: "resources/velocimetroMODO20.png"
        antialiasing: true
        smooth: true
    }

    Image {
        id: m_sourceModoAs
        x: speedGauge.width * 0.4307
        y: speedGauge.width * 0.5576
        width: speedGauge.width * 0.1384
        height: speedGauge.width * 0.07115
        source: "resources/velocimetroMODOAs.png"
        antialiasing: true
        smooth: true
    }

    Image {
        id: m_sourceModoATO
        x: speedGauge.width * 0.4307
        y: speedGauge.width * 0.5576
        width: speedGauge.width * 0.1384
        height: speedGauge.width * 0.07115
        source: "resources/velocimetroMODOAto.png"
        antialiasing: true
        smooth: true
    }

    Image {
        id: m_sourceModoATP
        x: speedGauge.width * 0.4307
        y: speedGauge.width * 0.5576
        width: speedGauge.width * 0.1384
        height: speedGauge.width * 0.07115
        source: "resources/velocimetroMODOAtP.png"
        antialiasing: true
        smooth: true
    }

    Image {
        id: m_sourceModoEEE
        x: speedGauge.width * 0.4307
        y: speedGauge.width * 0.5576
        width: speedGauge.width * 0.1384
        height: speedGauge.width * 0.07115
        source: "resources/velocimetroMODOEEE.png"
        antialiasing: true
        smooth: true
    }

    states: [
        State {
            name: "m_sourceModoOFF";
            PropertyChanges { target: m_sourceModoOFF;      opacity: 1}
            PropertyChanges { target: m_sourceModo;       opacity: 0}
            PropertyChanges { target: m_sourceModo20; opacity: 0}
            PropertyChanges { target: m_sourceModoAs;  opacity: 0}
            PropertyChanges { target: m_sourceModoATO;  opacity: 0}
            PropertyChanges { target: m_sourceModoATP;  opacity: 0}
            PropertyChanges { target: m_sourceModoEEE;  opacity: 0}
        },
        State {
            name: "m_sourceModo";
            PropertyChanges { target: m_sourceModoOFF;      opacity: 0}
            PropertyChanges { target: m_sourceModo;       opacity: 1}
            PropertyChanges { target: m_sourceModo20; opacity: 0}
            PropertyChanges { target: m_sourceModoAs;  opacity: 0}
            PropertyChanges { target: m_sourceModoATO;  opacity: 0}
            PropertyChanges { target: m_sourceModoATP;  opacity: 0}
            PropertyChanges { target: m_sourceModoEEE;  opacity: 0}
        },
        State {
            name: "m_sourceModo20";
            PropertyChanges { target: m_sourceModoOFF;      opacity: 0}
            PropertyChanges { target: m_sourceModo;       opacity: 0}
            PropertyChanges { target: m_sourceModo20; opacity: 1}
            PropertyChanges { target: m_sourceModoAs;  opacity: 0}
            PropertyChanges { target: m_sourceModoATO;  opacity: 0}
            PropertyChanges { target: m_sourceModoATP;  opacity: 0}
            PropertyChanges { target: m_sourceModoEEE;  opacity: 0}
        },
        State {
            name: "m_sourceModoAs";
            PropertyChanges { target: m_sourceModoOFF;      opacity: 0}
            PropertyChanges { target: m_sourceModo;       opacity: 0}
            PropertyChanges { target: m_sourceModo20; opacity: 0}
            PropertyChanges { target: m_sourceModoAs;  opacity: 1}
            PropertyChanges { target: m_sourceModoATO;  opacity: 0}
            PropertyChanges { target: m_sourceModoATP;  opacity: 0}
            PropertyChanges { target: m_sourceModoEEE;  opacity: 0}
        },
        State {
            name: "m_sourceModoATO";
            PropertyChanges { target: m_sourceModoOFF;      opacity: 0}
            PropertyChanges { target: m_sourceModo;       opacity: 0}
            PropertyChanges { target: m_sourceModo20; opacity: 0}
            PropertyChanges { target: m_sourceModoAs;  opacity: 0}
            PropertyChanges { target: m_sourceModoATO;  opacity: 1}
            PropertyChanges { target: m_sourceModoATP;  opacity: 0}
            PropertyChanges { target: m_sourceModoEEE;  opacity: 0}
        },
        State {
            name: "m_sourceModoATP";
            PropertyChanges { target: m_sourceModoOFF;      opacity: 0}
            PropertyChanges { target: m_sourceModo;       opacity: 0}
            PropertyChanges { target: m_sourceModo20; opacity: 0}
            PropertyChanges { target: m_sourceModoAs;  opacity: 0}
            PropertyChanges { target: m_sourceModoATO;  opacity: 0}
            PropertyChanges { target: m_sourceModoATP;  opacity: 1}
            PropertyChanges { target: m_sourceModoEEE;  opacity: 0}
        },
        State {
            name: "m_sourceModoEEE";
            PropertyChanges { target: m_sourceModoOFF;      opacity: 0}
            PropertyChanges { target: m_sourceModo;       opacity: 0}
            PropertyChanges { target: m_sourceModo20; opacity: 0}
            PropertyChanges { target: m_sourceModoAs;  opacity: 0}
            PropertyChanges { target: m_sourceModoATO;  opacity: 0}
            PropertyChanges { target: m_sourceModoATP;  opacity: 0}
            PropertyChanges { target: m_sourceModoEEE;  opacity: 1}
        }
    ]

    state: "m_sourceModo"

    function setOperationMode(m){
        if (m === 0){
            speedGauge.state = "m_sourceModoOFF";
        }else if (m === 1){
            speedGauge.state = "m_sourceModo";
        }else if (m === 2){
            speedGauge.state = "m_sourceModo20";
        }else if (m === 3){
            speedGauge.state = "m_sourceModoAs";
        }else if (m === 4){
            speedGauge.state = "m_sourceModoATO";
        }else if (m === 5){
            speedGauge.state = "m_sourceModoATP";
        }else if (m === 6){
            speedGauge.state = "m_sourceModoEEE";
        }
        else{
            speedGauge.state = "m_sourceModoOFF";
        }
    }

}
