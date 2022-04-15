

var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

// ----------------------------------------------------------------------------
// Initialization
// ----------------------------------------------------------------------------

window.addEventListener('load', onLoad);

function onLoad(event) {
    initWebSocket();
    initTextbox();
    initDropdown();
    initColor();
}

// ----------------------------------------------------------------------------
// WebSocket handling
// ----------------------------------------------------------------------------

function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onmessage;
}
function initTextbox() {
    console.log("init Textbox");
    document.getElementById('scrollingTextSubmit').addEventListener('click', update);
}
function initDropdown() {
    console.log("init Dropdown");
    document.getElementById('mode').addEventListener('click', update);
}
function initColor() {
    console.log("init Color");
    document.getElementById('color').addEventListener('change', update);
}
function onmessage(event) {
    console.log(`Received a notification from ${event.origin}`);
    console.log(event);
    let data = JSON.parse(event.data);
    if (data.modeWC) {
        document.getElementById('mode').value = 0;
    } else if (data.modeDC) {
        document.getElementById('mode').value = 1;
    } else if (data.modeST) {
        document.getElementById('mode').value = 2;
    }
    document.getElementById('InputScrollingText').value = data.scrollingText
    let colorstring =  '#'+(Number(data.R)).toString(16).padStart(2, '0')+(Number(data.G)).toString(16).padStart(2, '0')+(Number(data.B)).toString(16).padStart(2, '0');
    console.log(colorstring);
    document.getElementById('color').value = colorstring;
}


function onOpen(event) {
    console.log('Connection opened');
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

function update(event) {
    let modeWordclock = 0;
    let modeDigitalclock = 0;
    let modeScrollingtext = 0;
    let selected = document.getElementById('mode').value;
    //console.log(selected);
    switch (selected) {
        case '0': //Word Clock
            modeWordclock = 1;
            break;
        case '1': //Digital Clock
            modeDigitalclock = 1;
            break;
        case '2': //Scrolling Text
            modeScrollingtext = 1;
            break;
    }

    let scrollingtext = document.getElementById("InputScrollingText").value;
    let color = document.getElementById("color").value;
    console.log(document.getElementById('color'));
    let r = parseInt(color[1] + color[2], 16);
    let g = parseInt(color[3] + color[4], 16);
    let b = parseInt(color[5] + color[6], 16);
    console.log(r, g, b);
    let string = JSON.stringify({

        'scrollingText': scrollingtext,
        'modeWC': modeWordclock,
        'modeDC': modeDigitalclock,
        'modeST': modeScrollingtext,
        'R': r,
        'G': g,
        'B': b
    });
    console.log(string);
    websocket.send(string);
}