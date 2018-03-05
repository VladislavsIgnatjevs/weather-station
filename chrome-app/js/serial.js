var connection = '';

var onGetDevices = function (ports) {
    for (var i = 0; i < ports.length; i++) {

        //arduino vendorId is 9025
        if (ports[i].vendorId == 9025) {
            const DEVICE_PATH = ports[i].path;

            const DEVICE_NAME = ports[i].displayName;

            connection = new SerialConnection();

            connection.onConnect.addListener(function () {
                console.log('connected to: ' + DEVICE_NAME + ' ON ' + DEVICE_PATH);
                connection.send("hello arduino");
            });

            connection.onReadLine.addListener(function (line) {

            });

            connection.connect(DEVICE_PATH);

            setTimeout(function () {
                var current_weather = $('#current_weather').val();
                connection.send(current_weather);

                console.log('weather "' + current_weather + '" sent to controller');
            }, 8000);


        }
    }
};
chrome.serial.getDevices(onGetDevices);


const serial = chrome.serial;

/* Interprets an ArrayBuffer as UTF-8 encoded string data. */
var ab2str = function (buf) {
    var bufView = new Uint8Array(buf);
    var encodedString = String.fromCharCode.apply(null, bufView);
    return decodeURIComponent(escape(encodedString));
};

/* Converts a string to UTF-8 encoding in a Uint8Array; returns the array buffer. */
var str2ab = function (str) {
    var encodedString = unescape(encodeURIComponent(str));
    var bytes = new Uint8Array(encodedString.length);
    for (var i = 0; i < encodedString.length; ++i) {
        bytes[i] = encodedString.charCodeAt(i);
    }
    return bytes.buffer;
};


var SerialConnection = function () {
    this.connectionId = -1;
    this.lineBuffer = "";
    this.boundOnReceive = this.onReceive.bind(this);
    this.boundOnReceiveError = this.onReceiveError.bind(this);
    this.onConnect = new chrome.Event();
    this.onReadLine = new chrome.Event();
    this.onError = new chrome.Event();
};

SerialConnection.prototype.onConnectComplete = function (connectionInfo) {
    if (!connectionInfo) {
        console.log("Connection failed.");
        return;
    }
    this.connectionId = connectionInfo.connectionId;
    chrome.serial.onReceive.addListener(this.boundOnReceive);
    chrome.serial.onReceiveError.addListener(this.boundOnReceiveError);
    this.onConnect.dispatch();
};

SerialConnection.prototype.onReceive = function (receiveInfo) {
    if (receiveInfo.connectionId !== this.connectionId) {
        return;
    }

    this.lineBuffer += ab2str(receiveInfo.data);

    var index;
    while ((index = this.lineBuffer.indexOf('\n')) >= 0) {
        var line = this.lineBuffer.substr(0, index + 1);
        this.onReadLine.dispatch(line);
        this.lineBuffer = this.lineBuffer.substr(index + 1);
    }
};

SerialConnection.prototype.onReceiveError = function (errorInfo) {
    if (errorInfo.connectionId === this.connectionId) {
        this.onError.dispatch(errorInfo.error);
    }
};

SerialConnection.prototype.connect = function (path) {
    serial.connect(path, this.onConnectComplete.bind(this))
};

SerialConnection.prototype.send = function (msg) {
    if (this.connectionId < 0) {
        throw 'Invalid connection';
    }
    serial.send(this.connectionId, str2ab(msg), function () {
    });
};

SerialConnection.prototype.disconnect = function () {
    if (this.connectionId < 0) {
        throw 'Invalid connection';
    }
    serial.disconnect(this.connectionId, function () {
    });
};

