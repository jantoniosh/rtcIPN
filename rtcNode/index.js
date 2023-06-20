const express = require('express');
const http = require('http');
const path = require('path');
const { Server } = require("socket.io");
const { SerialPort, ReadlineParser } = require('serialport');

const app = express();
const server = http.createServer(app);
const io = new Server(server);

const baud = 115200; // 9600 - Arduino UNO | 115200 Raspberry Pi Pico

const port = new SerialPort({ path: 'COM8', baudRate: baud }, function (err) {
    if (err) {
        return console.log('Error: ', err.message)
    }
});

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

app.use(express.static('public'));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname + '/public/index.html'));
});


io.on('connection', (socket) => {
    console.log('a user connected');
    parser.on('data', (data) => {
        console.log(data);
        socket.emit('time', data);
    })
});

server.listen(3000, () => {
    console.log('listening on *:3000');
});
