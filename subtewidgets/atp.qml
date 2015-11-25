import QtQuick 2.0

Rectangle {
    id: atp
    width: 1024
    height: 768
    color: "#00000000"
    radius: 0
    border.color: "#00000000"

    property int velTramo0: 0
    property int velTramo1: 10
    property int velTramo15: 15
    property int velTramo2: 20
    property int velTramo25: 25
    property int velTramo3: 30
    property int velTramo4: 40
    property int velTramo5: 50
    property int velTramo6: 60
    property int velTramoCL: 10

    property  int  indexLed: 0
    property variant ledsSpeed: []

    property int indexLedAllow: 0
    property variant ledsSpeedAllowed: []

    property variant digitsL0: []
    property variant digitsL1: []
    property variant digitsL2: []

    property int dL0old: 0
    property int dL1old: 0
    property int dL2old: 0
    property int auxD3: 0

    function reset(){

    }

    Image {
        id: imageBckAtp
        x: 0
        y: 0
        width: 1024
        height: 768
        visible: true
        fillMode: Image.PreserveAspectFit
        sourceSize.height: 480
        sourceSize.width: 640
        clip: false
        source: "resources/ATP_FONDO1024_Resize.PNG"

        Item {
            id: itCMC
            x: 176
            y: 185
            width: 95
            height: 46
            Image {
                id: imCMC
                x: 0
                y: 0
                width: 95
                height: 46
                fillMode: Image.Stretch
                opacity: 0
                source: "resources/ATPoCMC.PNG"
            }
        }

        Item {
            id: itFserv
            x: 176
            y: 224
            width: 95
            height: 46

            Image {
                id: imFServ
                x: 0
                y: 0
                width: 95
                height: 46
                opacity: 0
                fillMode: Image.Stretch
                source: "resources/ATPoFoSERV.PNG"
            }
        }

        Item {
            id: itCL
            x: 97
            y: 184
            width: 95
            height: 46
            Image {
                id: imCL
                x: 0
                y: 0
                width: 95
                height: 46
                fillMode: Image.Stretch
                opacity: 0
                source: "resources/ATPoCL.PNG"
            }
        }

        Item {
            id: itFrenoUrg
            x: 256
            y: 224
            width: 95
            height: 46
            Image {
                id: imFurg
                x: 0
                y: 0
                width: 95
                height: 46
                fillMode: Image.Stretch
                opacity: 0
                source: "resources/ATPoFreEmrg.PNG"
            }
        }

        Item {
            id: itFalla
            x: 256
            y: 185
            width: 95
            height: 46
            Image {
                id: imFalla
                x: 0
                y: 0
                width: 95
                height: 46
                fillMode: Image.Stretch
                opacity: 0
                source: "resources/ATPofalla.PNG"
            }
        }

        Item {
            id: itCorte
            x: 97
            y: 224
            width: 95
            height: 46
            Image {
                id: imCorte
                x: 0
                y: 0
                width: 95
                height: 46
                fillMode: Image.Stretch
                opacity: 0
                source: "resources/ATOoCORTE.PNG"
            }
        }

        Item {
            id: l0
            x: 102
            y: 273
            width: 100
            height: 100
            //opacity: 1

            Image {
                id: iml0
                x: 0
                y: 0
                width: 100
                height: 100
                source: "resources/ATP_0L.png"
                opacity:0
            }
        }

        Item {
            id: l1
            x: 170
            y: 273
            width: 100
            height: 100
            //opacity: 1
            Image {
                id: iml1
                x: 0
                y: 0
                width: 100
                height: 100
                source: "resources/ATP_0L.png"
                opacity:0
            }
        }

        Item {
            id: l2
            x: 240
            y: 273
            width: 100
            height: 100
            //opacity: 1
            Image {
                id: iml2
                x: 0
                y: 0
                width: 100
                height: 100
                source: "resources/ATP_0L.png"
                opacity:0
            }
        }

        Item {
            id: s0
            x: 739
            y: 197
            width: 60
            height: 70
            Image {
                id: ims0
                x: 0
                y: 0
                width: 60
                height: 70
                opacity: 0
                source: "resources/ATP_0S.png"
            }
        }

        Item {
            id: s1
            x: 784
            y: 197
            width: 60
            height: 70
            Image {
                id: ims1
                x: 0
                y: 0
                width: 60
                height: 70
                opacity: 0
                source: "resources/ATP_0S.png"
            }
        }

        Item {
            id: s2
            x: 829
            y: 197
            width: 60
            height: 70
            Image {
                id: ims2
                x: 0
                y: 0
                width: 60
                height: 70
                opacity: 0
                source: "resources/ATP_0S.png"
            }
        }

        Item {
            id: item1
            x: 173
            y: 269
            width: 104
            height: 104

            Image {
                id: image1
                x: 0
                y: 0
                width: 104
                height: 104
                source: "resources/ATP_PuntoL.png"
                opacity: 1
            }
        }

        Item {
            id: item2
            x: 779
            y: 196
            width: 70
            height: 70

            Image {
                id: image2
                x: 0
                y: 0
                width: 70
                height: 70
                source: "resources/ATP_PuntoS.png"
                opacity: 1
            }
        }
    }

    Row {
        id: velocidad
        x: 373
        y: 346
        width: 516
        height: 24
        Repeater{
            //49
            id: repeaterLed
            model:49
            Image {
                id: ledVelocidad
                x: 0
                y: 0
                width: 10
                height: 23
                source: "resources/ATPoLed2.png"
                opacity: 0
            }
            onItemAdded: ledsSpeed[index] = item
        }//Repeater
    }//Row LED

    function posLed(x){

        for (indexLed=0; indexLed<=(x-1); indexLed++){
            ledsSpeed[indexLed].opacity=1;
        };
        for (indexLed=x; indexLed < ledsSpeed.length; indexLed++){
            ledsSpeed[indexLed].opacity=0;
        };

    }

    Row {
        id: velocidadAllowed
        x: 373
        y: 273
        width: 516
        height: 24
        Repeater{
            //49
            id: repeaterLedAllowed
            model:49
            Image {
                id: ledVelocidadAllowed
                x: 0
                y: 0
                width: 10
                height: 23
                source: "resources/ATPoLed2.png"
                opacity: 0
            }
            onItemAdded: ledsSpeedAllowed[index] = item
        }//Repeater
    }//Row LED

    function allowedSpeed(x){
        //console.log("Dentro del QML", x);
        for (indexLedAllow=0; indexLedAllow<=(x-1); indexLedAllow++){
            ledsSpeedAllowed[indexLedAllow].opacity=1;
        };
        for (indexLedAllow=x; indexLedAllow < ledsSpeedAllowed.length; indexLedAllow++){
            ledsSpeedAllowed[indexLedAllow].opacity=0;
        };
    }

    function targetSpeed(v){

        v = parseInt(v);

        ims0.opacity=1;
        ims1.opacity=1;
        ims2.opacity=1;

        if (v === velTramo0){
            //0
            ims0.opacity=1;
        }else{
            ims0.opacity=0;
        };

        if (v === velTramo1){
            //10
            image10.opacity=1;
        } else{
            image10.opacity=0;
        };

        if (v === velTramo2){
            //20
            image20.opacity=1;
        }else{
            image20.opacity=0;
        };

        if (v === velTramo25){
            //25
            ims0.opacity=0;
            image20.opacity=1;
            ims1.opacity=0;
            image05.opacity=1;
        }else if (v === 20){
            image05.opacity=0;
        }else{
            image20.opacity=0;
            image05.opacity=0;
        };

        if (v === velTramo3){
            //30
            image30.opacity=1;
        }else{
            image30.opacity=0;
        };

        if (v === velTramo4){
            //40
            image40.opacity=1;
        }else{
            image40.opacity=0;
        };

        if (v === velTramo5){
            //50
            image50.opacity=1;
        }else{
            image50.opacity=0;
        };

        if (v === velTramo6){
            //60
            image60.opacity=1;
        }else{
            image60.opacity=0;
        };

        if (v === velTramo15){
            //15
            ims0.opacity=0;
            image10.opacity=1;
            ims1.opacity=0;
            image05.opacity=1;
        }else if (v === 10){
            image05.opacity=0;
        }else if (v === 25){
            image10.opacity=0;
        }else{
            image10.opacity=0;
            image05.opacity=0;
        }
    }

    function speedLCD(v,d){

//        console.log("velocidad v ---->", v);
//        console.log("velocidad d ---->", d*10);
//        console.log("Indiceee ---> ",dL0old);
        if ((0<d)&&(d<1)){
            auxD3=parseInt(d*10)
        }else if ((1<=d)&&(d<=9)){
            auxD3=d
        }else{
            auxD3=0;
            //console.log("QML atp: decimal velocidad 0 --",d);
        }

        digitsL0[dL0old].opacity = 0;
        digitsL1[dL1old].opacity = 0;
        digitsL2[dL2old].opacity = 0;
        dL0old = getD1(v);
        //console.log("D1...........",dL0old);
        dL1old = getD2(v);
        //console.log("D2...........",dL1old);
        dL2old = auxD3;
        //console.log("D3...........",dL2old);
        digitsL0[dL0old].opacity = 1;
        digitsL1[dL1old].opacity = 1;
        digitsL2[dL2old].opacity = 1;

    }

    //Creater digits
    Repeater{
        id: digitsL0
        model: 10
        Image {
            id: d0
            x: 102
            y: 273
            width: 100
            height: 100
            source: "resources/ATP_"+index+"L.png"
            opacity: 0
        }
        onItemAdded: digitsL0[index] = item
    }

    Repeater{
        id: digitsL1
        model: 10
        Image {
            id: dl
            x: 170
            y: 273
            width: 100
            height: 100
            source: "resources/ATP_"+index+"L.png"
            opacity: 0
        }
        onItemAdded: digitsL1[index] = item
    }

    Repeater{
        id: digitsL2
        model: 10
        Image {
            id: d2
            x: 240
            y: 273
            width: 100
            height: 100
            source: "resources/ATP_"+index+"L.png"
            opacity: 0
        }
        onItemAdded: digitsL2[index] = item
    }

    //calculate digits
    function getD1(v){
        v = parseInt(v);
        //console.log("getD1 -------> ",v);
        return (parseInt(v/10));
    }

    function getD2(v){
        v = parseInt(v);
        //console.log("SEGUNDO Digito LDC: ------>",v - ((parseInt(v/10)*10)));
        return (v - ((parseInt(v/10)*10)));
    }


    //10
    Item {
        id: s10
        x: 739
        y: 197
        width: 60
        height: 70
        Image {
            id: image10
            x: 0
            y: 0
            width: 60
            height: 70
            opacity: 0
            source: "resources/ATP_1S.png"
        }
    }
    //05
    Item {
        id: s05
        x: 784
        y: 197
        width: 60
        height: 70
        Image {
            id: image05
            x: 0
            y: 0
            width: 60
            height: 70
            opacity: 0
            source: "resources/ATP_5S.png"
        }
    }
    //20
    Item {
        id: s20
        x: 739
        y: 197
        width: 60
        height: 70
        Image {
            id: image20
            x: 0
            y: 0
            width: 60
            height: 70
            opacity: 0
            source: "resources/ATP_2S.png"
        }
    }
    //30
    Item {
        id: s30
        x: 739
        y: 197
        width: 60
        height: 70
        Image {
            id: image30
            x: 0
            y: 0
            width: 60
            height: 70
            opacity: 0
            source: "resources/ATP_3S.png"
        }
    }
    //40
    Item {
        id: s40
        x: 739
        y: 197
        width: 60
        height: 70
        Image {
            id: image40
            x: 0
            y: 0
            width: 60
            height: 70
            opacity: 0
            source: "resources/ATP_4S.png"
        }
    }
    //50
    Item {
        id: s50
        x: 739
        y: 197
        width: 60
        height: 70
        Image {
            id: image50
            x: 0
            y: 0
            width: 60
            height: 70
            opacity: 0
            source: "resources/ATP_5S.png"
        }
    }
    //60
    Item {
        id: s60
        x: 739
        y: 197
        width: 60
        height: 70
        Image {
            id: image60
            x: 0
            y: 0
            width: 60
            height: 70
            opacity: 0
            source: "resources/ATP_6S.png"
        }
    }

    function setCMC(value){
        if (value === true){
            imCMC.opacity=1
        }else{
            imCMC.opacity = 0
        }
    }

    function setCL(value){
        if (value === true){
            imCL.opacity = 1
        }else{
            imCL.opacity = 0
        }

    }

    function setFserv(value){
        if (value === true){
            imFServ.opacity = 1
        }else{
            imFServ.opacity = 0
        }
    }

    function setFServBlink(value){
        if (value === true){
            blinkFServ.start()
        }else{
            blinkFServ.stop()
        }
    }

    function setFrenoUrg(value){
        //blinkFrenoUrg.stop();
        if (value === true){
            imFurg.opacity = 1
        }else{
            imFurg.opacity = 0
        }
    }

    function setFrenoUrgBlink(value){
        if(value === true){
            blinkFrenoUrg.start()
        }else{
            blinkFrenoUrg.stop()
        }
    }

    function setCorte(value){
        //blinkCorte.stop();
        if (value === true){
            imCorte.opacity = 1
        }else{
            imCorte.opacity = 0
        }
    }

    function setCorteBlink(value){
        if(value === true){
            blinkCorte.start()
        }else{
            blinkCorte.stop()
        }
    }

    function setFalla(value){
        if (value === true){
            imFalla.opacity = 1
        }else{
            imFalla.opacity = 0
        }
    }

    SequentialAnimation{
        id: blinkFServ
        loops: Animation.Infinite
        PropertyAnimation{
            properties: "opacity"
            to: 0
            from: 1
            duration: 1000
            target: imFServ
        }
    }

    SequentialAnimation{
        id: blinkCorte
        loops: Animation.Infinite
        PropertyAnimation{
            properties: "opacity"
            to: 0
            from: 1
            duration: 800
            target: imCorte
        }
    }

    SequentialAnimation{
        id: blinkFrenoUrg
        loops: Animation.Infinite
        PropertyAnimation{
            properties: "opacity"
            to: 0
            from: 1
            duration: 800
            target: imFurg
        }
    }

    SequentialAnimation{
        id: blinkSpeedTarget
        loops: Animation.Infinite
        PropertyAnimation{
            properties: "opacity"
            to: 0
            from: 1
            duration: 1000
            targets: [ims0, ims1, ims2]
        }
    }

    function setBlinkSpeedTarget(value){
        targetSpeed(0);
        if(value === true){
            blinkSpeedTarget.start();
        }else{
            blinkSpeedTarget.stop();
            ims0.opacity=0;
            ims1.opacity=0;
            ims2.opacity=0;
        }
    }

    function setReset(value){

        iml0.opacity=0;
        iml1.opacity=0;
        iml2.opacity=0;
        ims0.opacity=0;
        ims1.opacity=0;
        ims2.opacity=0;
        image10.opacity=0;
        image05.opacity=0;
        image10.opacity=0;
        image20.opacity=0;
        image30.opacity=0;
        image40.opacity=0;
        image50.opacity=0;
        image60.opacity=0;

        for (indexLed=0; indexLed<=(x-1); indexLed++){
            ledsSpeed[indexLed].opacity=0;
        };
        for (indexLed=x; indexLed < ledsSpeed.length; indexLed++){
            ledsSpeed[indexLed].opacity=0;
        };
        for (indexLedAllow=0; indexLedAllow<=(x-1); indexLedAllow++){
            ledsSpeedAllowed[indexLedAllow].opacity=0;
        };
        for (indexLedAllow=x; indexLedAllow < ledsSpeedAllowed.length; indexLedAllow++){
            ledsSpeedAllowed[indexLedAllow].opacity=0;
        };

        for (indexLed=0; indexLed<=9; indexLed++){
            digitsL0[indexLed].opacity = 0;
            digitsL1[indexLed].opacity = 0;
            digitsL2[indexLed].opacity = 0;
        }

        setBlinkSpeedTarget(false);
        setCMC(false);
        setCL(false);
        setCorte(false);
        setFserv(false);
        setFrenoUrg(false);
    }

}
