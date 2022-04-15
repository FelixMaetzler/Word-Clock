

var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

// ----------------------------------------------------------------------------
// Initialization
// ----------------------------------------------------------------------------

window.addEventListener('load', onLoad);

function onLoad(event) {
    initWebSocket();
    initButton();
    initTextbox();
    initDropdown();
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
function initButton() {
    console.log("init Button");
    document.getElementById('toggle').addEventListener('click', update);
}
function initTextbox() {
    console.log("init Textbox");
    document.getElementById('scrollingTextSubmit').addEventListener('click', update);
}
function initDropdown() {
    console.log("init Dropdown");
    document.getElementById('mode').addEventListener('click', update);
}
function onmessage(event) {
    console.log(`Received a notification from ${event.origin}`);
    console.log(event);
    let data = JSON.parse(event.data);
    document.getElementById('led').className = data.status;
    if (data.modeWC) {
        document.getElementById('mode').value = 0;
    } else if (data.modeDC) {
        document.getElementById('mode').value = 1;
    } else if (data.modeST) {
        document.getElementById('mode').value = 2;
    }
    document.getElementById('InputScrollingText').value = data.scrollingText
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
    let string = JSON.stringify({

        'scrollingText': scrollingtext,
        'action': 'toggle',
        'modeWC': modeWordclock,
        'modeDC': modeDigitalclock,
        'modeST': modeScrollingtext
    });
    console.log(string);
    websocket.send(string);
}