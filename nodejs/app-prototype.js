var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/tty.usbmodem411", {
	baudrate: 38400
});

serialPort.on("open", function () {
	console.log('open');

	var buff = "";	
	serialPort.on('data', function(data) {
		buff += data

		if(String(data).indexOf('}') > -1){
			console.log('data received: ' + buff);
			// WAAR???? NOU HIEEEEEEEER!
			buff = "";
		}
	});  

	// serialPort.write("ls\n", function(err, results) {
	// 	console.log('err ' + err);
	// 	console.log('results ' + results);
	// });  

});