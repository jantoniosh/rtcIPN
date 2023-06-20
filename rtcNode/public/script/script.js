let socket = io();

socket.on('time', (msg) => {
    console.log(msg);
    document.getElementById("texto").textContent = `Dato Recibido: ${msg}`;
});