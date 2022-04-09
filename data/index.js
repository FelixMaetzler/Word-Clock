

var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

// ----------------------------------------------------------------------------
// Initialization
// ----------------------------------------------------------------------------

window.addEventListener('load', onLoad);

function onLoad(event) {
    initWebSocket();
    initButton();
}

// ----------------------------------------------------------------------------
// WebSocket handling
// ----------------------------------------------------------------------------

function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen  = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onmessage;
}
function initButton(){
    document.getElementById('toggle').addEventListener('click', onToggle);
}
function onmessage(event){
    console.log(`Received a notification from ${event.origin}`);
    console.log(event);
    let data = JSON.parse(event.data);
    document.getElementById('led').className = data.status;
}
function onToggle(event) {
    websocket.send(JSON.stringify({'action':'toggle'}));
}

function onOpen(event) {
    console.log('Connection opened');
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}
